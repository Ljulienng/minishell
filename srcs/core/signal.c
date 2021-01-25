/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:50:29 by julienngy         #+#    #+#             */
/*   Updated: 2021/01/22 19:36:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_reset(t_data *shell)
{
	shell->sig->sig_quit = 0;
	shell->sig->sig_int = 0;
	shell->sig->sig_exit = 0;
	shell->sig->pid = 0;
}

void	signal_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_printf_fd(2, "\b\b  \n");
		ft_printf_fd(2, "minishell >> ");
		g_sig.sig_exit = 1;
	}
	else
	{
		ft_printf_fd(2, "\n");
		g_sig.sig_exit = 130;
	}
	g_sig.sig_int = 1;
}

void	signal_quit(int code)
{
	if (g_sig.pid != 0)
	{
		ft_printf_fd(2, "Core dumped: %d\n", code);
		g_sig.sig_exit = 131;
		g_sig.sig_quit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}
