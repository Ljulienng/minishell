/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:55:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 14:43:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sig		g_sig;

static void	signal_handlers(t_data *shell)
{
	shell->params.parent = 0;
	shell->params.child = 0;
	signal_reset(shell);
	signal(SIGINT, &signal_int);
	signal(SIGQUIT, &signal_quit);
	ft_printf_fd(1, "minishell >> ");
}

static int	main_loop(char **env, t_data *shell)
{
	int ret;
	int status;
	int gnl;

	ret = 0;
	init_env(shell, env);
	ft_bzero(&g_sig, sizeof(t_sig));
	shell->sig = &g_sig;
	while (!shell->exit)
	{
		signal_handlers(shell);
		gnl = get_next_line(0, &shell->cmd_line);
		if (gnl == -2 && shell->cmd_line[0] == '\0' && (shell->exit = 1))
			ft_printf_fd(STDERR, "\nexit\n");
		detect_cmd(shell);
		reset_shell(shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		shell->ret = (shell->params.parent == 1) ? status : shell->ret;
		if (shell->params.child == 1)
			break ;
		shell->noexec = 0;
	}
	full_clean(shell, &ret);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	t_data		*shell;

	if (ac > 1)
	{
		ft_printf_fd(2, "%s :Unrecognized argument..\n", av[1]);
		return (1);
	}
	if (!(shell = ft_calloc(1, sizeof(t_data))))
		return (1);
	shell->in = dup(STDIN_FILENO);
	shell->out = dup(STDOUT_FILENO);
	reset_stds(shell);
	return (main_loop(env, shell));
}
