/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 21:39:40 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 19:04:32 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORM3 OK

int	check_redirect(t_redir *re)
{
	int	fd;

	if (re->in)
	{
		if (re->in_t->type == L)
			fd = redirect_left_single(re->in_t->next->str);
		if (re->in_t->type == LL)
			fd = redirect_left_double(re->in_t->next->str);
	}
	if (re->out)
	{
		if (re->out_t->type == R)
			fd = redirect_right_single(re->out_t->next->str);
		else if (re->out_t->type == RR)
			fd = redirect_right_double(re->out_t->next->str);
	}
	return (fd);
}

int	readline_heredoc(char *str)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			close(g_state.heredoc_fd);
			return (2);
		}
		else
		{
			if (ft_strcmp(input, str) == 0)
				break ;
			ft_putstr_fd(input, g_state.heredoc_fd);
			ft_putchar_fd('\n', g_state.heredoc_fd);
		}
	}
	return (0);
}

int	read_heredoc(char *str)
{
	int	pid;

	g_state.heredoc_using = true;
	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR)
			printf("failed to register interrupts with kernel\n");
		g_state.heredoc_fd = open("$&^@.tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (g_state.heredoc_fd < 0)
		{
			printf("open faild\n");
			exit(1);
		}
		if (readline_heredoc(str) == 2)
			exit(2);
		close(g_state.heredoc_fd);
		exit(0);
	}
	else if (pid < 0)
		printf("fork error\n");
	waitpid(pid, &g_state.heredoc_status, 0);
	g_state.heredoc_using = false;
	return (0);
}
