/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:29:36 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/12 09:29:36 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat_error_str(char *err_msg, char *input)
{
	char	*concat;
	int		len_concat_all;

	if (!err_msg)
		return (NULL);
	len_concat_all = ft_strlen(err_msg) + ft_strlen("minishell: ") + 1;
	if (input)
		len_concat_all = len_concat_all + ft_strlen(input) + 2;
	concat = malloc(sizeof(char) * (len_concat_all + 1));
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	ft_strlcat(concat, "minishell: ", (ft_strlen("minishell: ") + 1));
	if (input)
	{
		ft_strlcat(concat, input, len_concat_all + 1);
		ft_strlcat(concat, ": ", len_concat_all + 3);
	}
	ft_strlcat(concat, err_msg, len_concat_all + 1);
	ft_strlcat(concat, "\n", len_concat_all + 2);
	return (concat);
}

char	*ft_concat_error_str_spe(char *err_msg, char *input, char *input1)
{
	char	*concat;
	int		len_concat_all;

	if (!err_msg || !input1 || !input)
		return (NULL);
	len_concat_all = ft_strlen(err_msg)
		+ ft_strlen("minishell: ")
		+ 1
		+ ft_strlen(input)
		+ 2
		+ ft_strlen(input1)
		+ 2;
	concat = malloc(sizeof(char) * (len_concat_all + 1));
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	ft_strlcat(concat, "minishell: ", len_concat_all + 1);
	ft_strlcat(concat, input, len_concat_all + 1);
	ft_strlcat(concat, ": ", len_concat_all + 1);
	ft_strlcat(concat, input1, len_concat_all + 1);
	ft_strlcat(concat, ": ", len_concat_all + 1);
	ft_strlcat(concat, err_msg, len_concat_all + 1);
	ft_strlcat(concat, "\n", len_concat_all + 1);
	return (concat);
}

char	*ft_concat_error_str_export(char *err_msg, char *input, char *input1)
{
	char	*concat;
	int		len_concat_all;

	if (!err_msg || !input1 || !input)
		return (NULL);
	len_concat_all = ft_strlen(err_msg)
		+ ft_strlen("minishell: ")
		+ 7
		+ ft_strlen(input)
		+ ft_strlen(input1);
	concat = malloc(sizeof(char) * (len_concat_all + 1));
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	ft_strlcat(concat, "minishell: ", len_concat_all + 1);
	ft_strlcat(concat, input, len_concat_all + 1);
	ft_strlcat(concat, ": ", len_concat_all + 1);
	ft_strlcat(concat, "`", len_concat_all + 1);
	ft_strlcat(concat, input1, len_concat_all + 1);
	ft_strlcat(concat, "\'", len_concat_all + 1);
	ft_strlcat(concat, ": ", len_concat_all + 1);
	ft_strlcat(concat, err_msg, len_concat_all + 1);
	ft_strlcat(concat, "\n", len_concat_all + 1);
	return (concat);
}

char	*ft_concat_error_str_he(char *eof_msg)
{
	char	*concat;
	int		len_concat_all;

	if (!eof_msg)
		return (NULL);
	len_concat_all = ft_strlen(eof_msg)
		+ ft_strlen("minishell: ")
		+ ft_strlen("warning")
		+ ft_strlen("unexpected end of file (wanted ")
		+ 6;
	concat = malloc(sizeof(char) * (len_concat_all + 1));
	if (!concat)
		return (NULL);
	concat[0] = '\0';
	ft_strlcat(concat, "minishell: ", len_concat_all + 1);
	ft_strlcat(concat, "warning", len_concat_all + 1);
	ft_strlcat(concat, ": ", len_concat_all + 1);
	ft_strlcat(concat, "unexpected end of file (wanted ", len_concat_all + 1);
	ft_strlcat(concat, "`", len_concat_all + 1);
	ft_strlcat(concat, eof_msg, len_concat_all + 1);
	ft_strlcat(concat, "')\n", len_concat_all + 1);
	return (concat);
}
