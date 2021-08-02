/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 15:01:25 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_pipe(char ***arg, char **env, int cnt, t_redir **re)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while (i < cnt)
	{
		pipe(fd);
		g_state.cmd_using = true;
		if (check_cmd(arg[i], &i))
			continue ;
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
		{
			child_process(cnt, fd, re[i], i);
			check_cmd2(arg[i], env);
		}
		else
			parent_process(pid, fd, re[i], &i);
	}
}

void	parse_cmd(t_token *head)
{
	int	len;
	int	i;

	i = -1;
	g_state.cmd = (char ***)malloc(sizeof(char **) * (g_state.len + 1));
	g_state.re = (t_redir **)malloc(sizeof(t_redir *) * (g_state.len + 1));
	while (++i < g_state.len)
	{
		len = 0;
		while (head && head->type != PIPE)
		{
			len++;
			head = head->next;
		}
		g_state.cmd[i] = (char **)malloc(sizeof(char *) * (len + 1));
		g_state.re[i] = (t_redir *)malloc(sizeof(t_redir));
		g_state.re[i]->out = 0;
		g_state.re[i]->in = 0;
		g_state.re[i]->out_t = 0;
		g_state.re[i]->in_t = 0;
		if (head && head->type == PIPE)
			head = head->next;
	}
	g_state.cmd[i] = 0;
	g_state.re[i] = 0;
}

t_token	*control_redir(t_token *head, int j)
{
	if (!head->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (head);
	}
	if (head->type == R || head->type == RR)
	{
		g_state.re[j]->out = 1;
		g_state.re[j]->out_t = head;
	}
	else
	{
		g_state.re[j]->in = 1;
		g_state.re[j]->in_t = head;
	}
	return (head->next);
}

void	ft_cmd(t_token *head, char **path)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!head)
		return ;
	parse_cmd(head);
	while (head)
	{
		if (head->type == R || head->type == RR || \
			head->type == L || head->type == LL)
			head = control_redir(head, j);
		else if (head->type == CMD || head->type == ARG || \
			head->type == DOUBLE || head->type == SINGLE)
			g_state.cmd[j][i++] = head->str;
		if (head->type == PIPE || head->next == 0)
		{
			g_state.cmd[j][i] = 0;
			i = 0;
			j++;
		}
		head = head->next;
	}
	loop_pipe(g_state.cmd, path, g_state.len, g_state.re);
}
