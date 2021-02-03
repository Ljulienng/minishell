/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:37:32 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 14:30:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_arg(t_data *shell)
{
	int i;

	i = 0;
	while (shell->arg[i])
	{
		free(shell->arg[i]);
		i++;
	}
}

void	reset_options(t_data *shell)
{
	shell->params.has_option = 0;
	shell->params.semicolon = 0;
	shell->params.r_angle = 0;
	shell->params.l_angle = 0;
	shell->params.d_angle = 0;
	shell->params.pipe = 0;
}

int		is_option(t_data *shell, char *arg)
{
	int ret;

	if (ft_strncmp(arg, ";", 2) == 0)
		ret = 1;
	else if (ft_strncmp(arg, "|", 2) == 0)
		ret = 1;
	else if (ft_strncmp(arg, ">", 2) == 0)
		ret = 1;
	else if (ft_strncmp(arg, "<", 2) == 0)
		ret = 1;
	else if (ft_strncmp(arg, ">>", 3) == 0)
		ret = 1;
	else
		ret = 0;
	if (ret)
		shell->params.has_option = 1;
	return (ret);
}

int		is_builtin(t_data *shell, char **arg)
{
	if (!reco_cmd(arg[0], "echo"))
		shell->ret = ft_echo(shell);
	else if (!reco_cmd(arg[0], "pwd"))
		shell->ret = ft_pwd(shell);
	else if (!reco_cmd(arg[0], "exit"))
		ft_exit(shell);
	else if (!reco_cmd(arg[0], "cd"))
		shell->ret = ft_cd(shell);
	else if (!reco_cmd(arg[0], "env"))
		ft_env(shell);
	else if (!reco_cmd(arg[0], "export"))
		shell->ret = ft_export(shell);
	else if (!reco_cmd(arg[0], "unset"))
		ft_unset(shell);
	else
		return (0);
	return (1);
}

char	*join_path(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	tmp = NULL;
	return (path);
}
