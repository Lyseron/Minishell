/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:47:28 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/15 15:47:28 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_err_msg_spe(char *input, char *msg, char *input1)
{
	char	*err_str;

	err_str = ft_concat_error_str_spe(msg, input, input1);
	if (!err_str)
		return ;
	ft_putstr_fd(err_str, 2);
	free(err_str);
}

int	ft_print_error(t_token *token)
{
	char	*concat;
	char	*type;
	int		size_all;

	type = ft_type_to_str(token);
	if (!type)
		return (ERROR);
	size_all = ft_strlen(type)
		+ ft_strlen(STR_ERR)
		+ ft_strlen("'\n");
	concat = malloc(sizeof(char) * (size_all + 1));
	if (!concat)
		return (ERROR);
	concat[0] = '\0';
	ft_strlcat(concat, STR_ERR, size_all + 1);
	ft_strlcat(concat, type, size_all + 1);
	ft_strlcat(concat, "'\n", size_all + 1);
	ft_putstr_fd(concat, 2);
	free(concat);
	return (INVALID_INPUT);
}

void	ft_print_err_msg(char *input, char *msg)
{
	char	*err_str;

	err_str = ft_concat_error_str(msg, input);
	if (!err_str)
		return ;
	ft_putstr_fd(err_str, 2);
	free(err_str);
}

void	ft_print_err_msg_export(char *input, char *msg, char *input1)
{
	char	*err_str;

	err_str = ft_concat_error_str_export(msg, input, input1);
	if (!err_str)
		return ;
	ft_putstr_fd(err_str, 2);
	free(err_str);
}

void	ft_print_err_msg_heredoc(char *eof)
{
	char	*err_str;

	err_str = ft_concat_error_str_he(eof);
	if (!err_str)
		return ;
	ft_putstr_fd(err_str, 2);
	free(err_str);
}
