/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:49:10 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:56:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (ft_strchr(path, '/') == NULL)
		ft_printf_fd(2, "command not found: %s\n", path);
	else if (fd == -1 && folder == NULL)
		ft_printf_fd(2, "No such file or directory: %s\n", path);
	else if (fd == -1 && folder != NULL)
		ft_printf_fd(2, ": is a directory\n");
	else if (fd != -1 && folder == NULL)
		ft_printf_fd(2, ": Permission denied\n");
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	if (fd > 0)
		close(fd);
	return (ret);
}

static int	ft_execve(t_data *shell, char *path, char **arg)
{
	int		ret;

	ret = 0;
	shell->sig->pid = fork();
	if (!shell->sig->pid)
	{
		if ((ft_strchr(path, '/')))
			execve(path, arg, shell->env);
		ret = error_message(path);
		free(path);
		exit(ret);
	}
	else
		waitpid(shell->sig->pid, &ret, 0);
	if (g_sig.sig_int == 1 || g_sig.sig_quit == 1)
		return (g_sig.sig_exit);
	ret = (ret == 256 || ret == 512 ||\
	ret == 32512 || ret == 32256) ? ret / 256 : !!ret;
	return (ret);
}

static char	*check_dir(char *bin, char **arg)
{
	char			*path;
	struct dirent	*dir;
	DIR				*folder;

	path = NULL;
	if (!(folder = opendir(bin)))
		return (NULL);
	while ((dir = readdir(folder)))
	{
		if (!(ft_strncmp(dir->d_name, arg[0], \
		(ft_strlen(arg[0]) + 1))))
			path = join_path(bin, dir->d_name);
	}
	closedir(folder);
	return (path);
}

int			exec_bin(t_data *shell, char **arg)
{
	int		i;
	int		ret;
	char	*path;
	char	**bin;

	i = 0;
	ret = 127;
	while (shell->env[i] && ft_strncmp(shell->env[i], "PATH", 4))
		i++;
	if (!shell->env[i] || shell->env[i + 1] == NULL)
		return (ft_execve(shell, arg[0], arg));
	bin = ft_split(shell->env[i], ':');
	i = 0;
	path = check_dir(bin[i++] + 5, arg);
	while (arg[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], arg);
	if (path)
		ret = ft_execve(shell, path, arg);
	else
		ret = ft_execve(shell, arg[0], arg);
	clean_str(bin);
	free(path);
	return (ret);
}
