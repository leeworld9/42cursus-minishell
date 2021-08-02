/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 09:55:43 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 16:04:22 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORM3 OK

void	sig_handler(int sig_num)
{
	if (g_state.heredoc_using != true && g_state.cmd_using != true)
	{
		if (sig_num == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (sig_num == SIGQUIT)
		{
			ft_putchar_fd('\r', 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (g_state.heredoc_using != true && g_state.cmd_using == true)
	{
		if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3", 1);
	}
}

void	heredoc_sig_handler(int sig_num)
{
	if (g_state.heredoc_using == true)
	{
		if (sig_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			close(g_state.heredoc_fd);
			exit(3);
		}
		else if (sig_num == SIGQUIT)
		{
			ft_putchar_fd('\r', 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
