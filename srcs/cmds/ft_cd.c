/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:58:45 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 18:05:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		cd_error(t_data *shell)
{
	ft_printf_fd(2, "cd: ");
	if (shell->arg[2])
		ft_printf_fd(2, "string not in pwd");
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_printf_fd(2, "%s\n", shell->arg[1]);
}

static int		add_oldpwd(t_data *shell)
{
	char *oldpwd;
	char cwd[4096];

	if (!(getcwd(cwd, 4096)))
		return (0);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (0);
	del_env(shell, "OLDPWD");
	add_env(shell, oldpwd);
	free(oldpwd);
	return (1);
}

static char		*ft_path_env(t_data *shell, char *env, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = (int)len;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], env, len) == 0)
		{
			lst_malloc((void **)&oldpwd, ft_strlen(shell->env[i]) - len, shell);
			k++;
			while (shell->env[i][k])
				oldpwd[j++] = shell->env[i][k++];
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		i++;
	}
	return (NULL);
}

static int		ft_cd2(t_data *shell, int homeback)
{
	char	*path;
	int		ret;

	if (!homeback)
	{
		add_oldpwd(shell);
		path = ft_path_env(shell, "HOME", 4);
		if (!path)
			return (0);
	}
	else if (homeback)
	{
		path = ft_path_env(shell, "OLDPWD", 6);
		if (!path)
			return (0);
		add_oldpwd(shell);
	}
	ret = chdir(path);
	return (ret);
}

int				ft_cd(t_data *shell)
{
	int		ret;
	char	*curr_pwd;
	char	cwd[4096];

	if (!shell->arg[1] || !ft_strncmp(shell->arg[1], "~", 2))
		ret = ft_cd2(shell, 0);
	else if (!ft_strncmp(shell->arg[1], "-", 2) && !shell->arg[2])
		ret = ft_cd2(shell, 1);
	else
	{
		add_oldpwd(shell);
		ret = chdir(shell->arg[1]);
		if (ret < 0)
			ret = -1 * ret;
		if (ret)
			cd_error(shell);
	}
	if (!(getcwd(cwd, 4096)))
		return (0);
	if (!(curr_pwd = ft_strjoin("PWD=", cwd)))
		return (0);
	del_env(shell, "PWD");
	add_env(shell, curr_pwd);
	free(curr_pwd);
	return (ret);
}
