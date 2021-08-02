/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 17:45:18 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, int type)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}

int	has_type(char *input, int i)
{
	if (input[i] == '\'')
		    return (SINGLE);
	else if (input[i] == '\"')
		return (DOUBLE);
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (RR);
		return (R);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (LL);
		return (L);
	}
	else if (input[i] == '|')
		return (PIPE);
	else if (input[i] == ' ')
		return (SPACING);
	else if (input[i] == '$')
		return (DOLLAR);
	return (ARG);
}

int	check_quote(char *s, int flag_d, int flag_s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && !flag_d)
		{
			if (flag_s == 1)
				flag_s = 0;
			else
				flag_s = 1;
		}
		else if (s[i] == '\"' && !flag_s)
		{
			if (flag_d == 1)
				flag_d = 0;
			else
				flag_d = 1;
		}
	}
	if (flag_s || flag_d)
		return (0);
	return (1);
}

char	*return_envval(char *buf)
{
	t_env		*env;

	env = g_state.env;
	while (env)
	{
		if (!ft_strncmp(env->key, buf, ft_strlen(buf)))
			return (env->value);
		env = env->next;
	}
	return ("");
}
