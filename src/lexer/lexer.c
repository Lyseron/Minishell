/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 05:32:40 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/18 05:32:40 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer_c(t_token **tokens, char *line, int *i, t_qstate *state);
void	ft_lexer(char *line, t_token **tokens, t_qstate state);

static void	ft_print_err_quote(void)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for ", 2);
	ft_putstr_fd("matching quote\n", 2);
}

// check if the quotes are complete before calling the lexer
int	ft_lexer_check(char *line, t_token **tokens)
{
	t_qstate	state;

	state = NO_Q;
	if (ft_incomplete_quote(line) == INVALID_INPUT)
		return (ft_print_err_quote(), INVALID_INPUT);
	ft_lexer(line, tokens, state);
	return (OK);
}

// sort the word if there are in quotes or not
void	ft_lexer(char *line, t_token **tokens, t_qstate state)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (state == NO_Q)
		{
			while (line[i] && ft_iswhitespace(line[i]) == 1)
				i++;
			if (line[i] == '\0')
				break ;
			ft_lexer_c(tokens, line, &i, &state);
		}
		else if (state == SQUOTE)
		{
			ft_lexer_word(tokens, &i, line);
			state = NO_Q;
		}
		else if (state == DQUOTE)
		{
			ft_lexer_word(tokens, &i, line);
			state = NO_Q;
		}
	}
}

// conditions to sort the different input depending on the char
void	ft_lexer_c(t_token **tokens, char *line, int *i, t_qstate *state)
{
	if (line[*i] == SQ)
		*state = SQUOTE;
	else if (line[*i] == DQ)
		*state = DQUOTE;
	else if (line[*i] == '|')
		ft_lexer_spe_char(tokens, i, "|", PIPE);
	else if (line[*i + 1] && (line[*i] == '&' && line[*i + 1] == '&'))
		ft_lexer_a_and_h(tokens, i, "&&", NONO_CHAR);
	else if (line[*i] == ';')
		ft_lexer_spe_char(tokens, i, ";", NONO_CHAR);
	else if (line[*i + 1] && (line[*i] == '>' && line[*i + 1] == '>'))
		ft_lexer_a_and_h(tokens, i, ">>", APPEND);
	else if (line[*i + 1] && (line[*i] == '<' && line[*i + 1] == '<'))
		ft_lexer_a_and_h(tokens, i, "<<", HEREDOC);
	else if (line[*i] == '<')
		ft_lexer_spe_char(tokens, i, "<", REDIR_IN);
	else if (line[*i] == '>')
		ft_lexer_spe_char(tokens, i, ">", REDIR_OUT);
	else
		ft_lexer_word(tokens, i, line);
}
