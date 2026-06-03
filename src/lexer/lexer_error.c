/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:08:51 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/31 18:08:51 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool to see if the quote are incomplete
// return :
// OK -> if complete
// INVALID_INPUT -> if incomplete
int	ft_incomplete_quote(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == SQ)
		{
			i++;
			while (line[i] && line[i] != SQ)
				i++;
			if (line[i] == '\0')
				return (INVALID_INPUT);
		}
		if (line[i] == DQ)
		{
			i++;
			while (line[i] && line[i] != DQ)
				i++;
			if (line[i] == '\0')
				return (INVALID_INPUT);
		}
		i++;
	}
	return (OK);
}

// bool to see if the char is '<' or '>' or '|'
// return :
// 0 -> faux
// 1 -> vrai
int	ft_is_spe_char(char c)
{
	if (c == '|' || c == '<' || c == '>' )
		return (1);
	return (0);
}
