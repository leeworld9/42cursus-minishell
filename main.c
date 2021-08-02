/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 20:44:17 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **envpp)
{
	int	i;

	i = 0;
	while (envpp[i] != NULL)
	{
		if (g_state.env == NULL)
			g_state.env = init_env(g_state.env, envpp[i++]);
		else
			init_env(g_state.env, envpp[i++]);
	}
	g_state.head = 0;
	g_state.redirection = NULL;
	g_state.ret = 0;
}

void	ft_free(void)
{
	int		i;
	t_token	*tmp;

	if (g_state.input)
		free(g_state.input);
	if (!g_state.head)
		return ;
	i = 0;
	while (i < g_state.len + 1)
	{
		free(g_state.cmd[i]);
		free(g_state.re[i]);
		i++;
	}
	free(g_state.cmd);
	free(g_state.re);
	while (g_state.head)
	{
		tmp = g_state.head;
		free(tmp->str);
		g_state.head = g_state.head->next;
		free(tmp);
	}
}

void	var_init(void)
{
	g_state.len = 1;
	g_state.fd_in = 0;
	g_state.fd_out = 1;
}

int	loop_msg(char *shell_prompt)
{
	var_init();
	if (WIFSIGNALED(g_state.cmd_status) == 1)
	{
		g_state.cmd_status = 0;
		printf("\n");
	}
	shell_prompt = ft_strdup("bash-42$ ");
	g_state.input = readline(shell_prompt);
	if (g_state.input == NULL)
	{	
		ft_putstr_fd("exit\n", 1);
		free(shell_prompt);
		return (0);
	}
	if (ft_strcmp(g_state.input, "") != 0)
	{
		add_history(g_state.input);
		if (!check_quote(g_state.input, 0, 0))
			printf("invalid quote\n");
		else
			parser(0, 0);
	}
	ft_free();
	free(shell_prompt);
	return (1);
}

int	main(int argc, char **argv, char **envpp)
{
	char	*shell_prompt;

	(void)argc;
	(void)argv;
	shell_prompt = NULL;
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	init(envpp);
	while (loop_msg(shell_prompt))
		continue ;
	free_env(g_state.env);
	return (0);
}
