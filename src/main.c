/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:59:58 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/14 02:59:58 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_final_check(char *line, t_ast *ast, t_shell *shell);
static int	ft_init_shell(t_shell *shell, char **env, char **av, int ac);
static int	ft_for_signal(void);
static int	ft_main_loop(t_shell *shell, t_ast *ast, char *line);

int	main(int ac, char *av[], char *env[])
{
	t_ast	*ast;
	t_shell	shell;
	char	*line;

	line = NULL;
	if (ft_init_shell(&shell, env, av, ac) == 1)
		return (ERROR);
	ast = NULL;
	if (ft_main_loop(&shell, ast, line) == ERROR)
		return (ERROR);
	return (ft_clean_at_exit(ast, &shell), shell.last_exit_code);
}

static int	ft_main_loop(t_shell *shell, t_ast *ast, char *line)
{
	while (1)
	{
		if (ft_for_signal() == ERROR)
			return (ERROR);
		line = readline("minishell> ");
		ft_sig_readline_parent(shell);
		if (!line)
		{
			write(1, "exit\n", 5);
			ft_clean_all_child(shell, shell->last_exit_code);
		}
		if (ft_needs_more(line) == 1)
			line = ft_second_chance_parent(line, shell);
		if (!line)
			continue ;
		shell->line = line;
		if (line[0] != '\0')
			add_history(line);
		shell->last_exit_code = ft_final_check(line, ast, shell);
		free(line);
		line = NULL;
		shell->line = NULL;
	}
	return (OK);
}

static int	ft_final_check(char *line, t_ast *ast, t_shell *shell)
{
	int				error_pars;
	t_token			*tokens;
	t_token			*head;
	int				status;

	tokens = NULL;
	head = NULL;
	status = OK;
	if (ft_isonly_space(line) == ERROR)
		return (OK);
	if (ft_lexer_check(line, &tokens) == INVALID_INPUT)
		return (ft_lstfree(tokens), INVALID_INPUT);
	head = tokens;
	shell->token = head;
	error_pars = ft_parsing_check(&tokens, &ast, shell);
	if (error_pars == INVALID_INPUT)
		return (ft_clean(head, ast, shell, INVALID_INPUT));
	else if (error_pars == ERROR)
		return (ft_clean(head, ast, shell, ERROR));
	if (ft_handle_all(ast, shell) == ERROR)
		return (ft_clean(head, ast, shell, ERROR));
	shell->ast = ast;
	status = ft_exec_check(ast, shell);
	ft_clean(head, ast, shell, OK);
	return (status);
}

static int	ft_init_shell(t_shell *shell, char **env, char **av, int ac)
{
	(void)ac;
	(void)av;
	shell->build_env = ft_copy_env(env);
	if (!shell->build_env)
		return (ft_free_dba(shell->build_env), shell->build_env = NULL, ERROR);
	shell->last_exit_code = 0;
	shell->exit = false;
	shell->in_pipe = false;
	shell->ast = NULL;
	shell->token = NULL;
	shell->in_quote = false;
	shell->line = NULL;
	return (OK);
}

static int	ft_for_signal(void)
{
	if (ft_sig_init(SIGINT, ft_handler, 0) == ERROR)
		return (ERROR);
	if (ft_sig_init(SIGQUIT, SIG_IGN, 0) == ERROR)
		return (ERROR);
	return (OK);
}
