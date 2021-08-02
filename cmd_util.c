/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/08/02 17:37:54 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd2(char **arg, char **env)
{
	char	*curr;

	if (!arg[0])
		exit(2);
	if (!ft_strcmp(arg[0], "pwd"))
		printf("%s\n", get_env(g_state.env, "PWD")->value);
	else if (!ft_strcmp(arg[0], "env"))
		show_env(g_state.env);
	else if (!ft_strcmp(arg[0], "echo"))
		ft_echo(arg);
	else
	{
		curr = parse_path(arg[0], -1);
		if (curr)
		{
			if (execve(curr, arg, env) == -1)
			{
				printf("command can not apply\n");
				g_state.ret = 1;
			}
		}
		else
			exit(127);
	}
	exit(1);
}

int	check_cmd(char **arg, int *i)
{
	if (!ft_strcmp(arg[0], "cd"))
	{
		ft_cd(arg);
		*i += 1;
		return (1);
	}
	else if (!ft_strcmp(arg[0], "export"))
	{
		add_env(g_state.env, arg[1]);
		*i += 1;
		return (1);
	}
	else if (!ft_strcmp(arg[0], "unset"))
	{
		delete_env(g_state.env, arg[1]);
		*i += 1;
		return (1);
	}
	else if (!ft_strcmp(arg[0], "exit"))
	{
		printf("exit\n");
		exit(check_exitarg(arg));
	}
	else
		return (0);
}

int	ft_re(t_redir *re, int flag)
{
	if (flag == 1 && re->in)
	{
		if (re->in_t->type == LL)
			unlink("$&^@.tmp");
	}
	else if (flag == 0)
	{
		if (!re->in)
			return (1);
		g_state.fd_in = check_redirect(re);
		if (g_state.fd_in > 1 || g_state.fd_in == -1)
		{
			if (g_state.fd_in == -1)
				exit(1);
			else if (g_state.fd_in == 3)
				exit(1);
		}
	}
	return (0);
}

void	child_process(int cnt, int *fd, t_redir *re, int i)
{
	if (ft_re(re, 0))
		dup2(g_state.fd_in, 0);
	if (re->out)
		g_state.fd_out = check_redirect(re);
	else if (i != cnt - 1)
		dup2(fd[1], 1);
	close(fd[0]);
}

void	parent_process(int pid, int *fd, t_redir *re, int *i)
{
	waitpid(pid, &g_state.cmd_status, 0);
	g_state.ret = WEXITSTATUS(g_state.cmd_status);
	g_state.cmd_using = false;
	close(fd[1]);
	ft_re(re, 1);
	g_state.fd_in = fd[0];
	*i += 1;
}
