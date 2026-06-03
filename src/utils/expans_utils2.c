/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:59:26 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/09 08:59:26 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_str(char *word, char *line, int	*i, t_shell *shell)
{
	char	*var_content;
	char	*var;
	int		size_new_new_word;
	char	*concat_word;

	*i = *i + 1;
	var = ft_get_var(line, *i);
	if (!var)
		return (free(word), word = NULL, NULL);
	var_content = ft_return_var_content(shell, var);
	if (!var_content)
		var_content = ft_strdup("");
	else
		var_content = ft_strdup(var_content);
	if (!var_content)
		return (free(var), free(word), word = NULL, NULL);
	size_new_new_word = ft_strlen(word) + ft_strlen(var_content) + 1;
	concat_word = malloc(sizeof(char) * size_new_new_word);
	if (!concat_word)
		return (free(var), free(word), word = NULL, free(var_content), NULL);
	ft_strlcpy(concat_word, word, (ft_strlen(word) + 1));
	ft_strlcat(concat_word, var_content, size_new_new_word);
	*i = *i + ft_strlen(var);
	ft_free_vars(&var, &var_content, &word);
	return (concat_word);
}

char	*ft_string_exit_code(char *word, int *i, t_shell *shell)
{
	char	*exit_string;
	char	*concat_word;
	int		size_new_new_word;

	*i = *i + 2;
	exit_string = ft_itoa(shell->last_exit_code);
	if (!exit_string)
		return (free(word), word = NULL, NULL);
	size_new_new_word = ft_strlen(exit_string) + ft_strlen(word) + 1;
	concat_word = malloc(sizeof(char) * (size_new_new_word + 1));
	if (!concat_word)
		return (free(word), word = NULL, free(exit_string), NULL);
	ft_strlcpy(concat_word, word, (ft_strlen(word) + 1));
	ft_strlcat(concat_word, exit_string, size_new_new_word);
	free(word);
	free(exit_string);
	return (concat_word);
}

void	ft_remove_empty_arg(char **args, int i)
{
	free(args[i]);
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

bool	ft_has_quote(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	ft_write_line(char **line, int std_out)
{
	write(std_out, *line, ft_strlen(*line));
	write(std_out, "\n", 1);
	free(*line);
}
