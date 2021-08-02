/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 16:22:10 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	white_space(int *i)
{
	while (g_state.input[*i] == ' ' || g_state.input[*i] == '\n' || \
	 g_state.input[*i] == '\t' || g_state.input[*i] == '\v' || \
	 g_state.input[*i] == '\f' || g_state.input[*i] == '\r')
		*i += 1;
}

void	ft_parser(int i, int j, char *buf, int type)
{
	while (g_state.input[++i])
	{
		type = has_type(g_state.input, i);
		if (!type || (g_state.flag && (type != g_state.flag) \
		 && !(g_state.flag == 2 && type == DOLLAR)))
			buf[j++] = g_state.input[i];
		else if (type == SINGLE || type == DOUBLE)
			treat_quote(type);
		else if (type == DOLLAR)
		{
			g_state.input = treat_dollar(ft_strlen(g_state.input), i, i + 1);
			i--;
		}
		else if (type && j)
		{
			generate_token(buf, ARG, j);
			j = 0;
			i--;
		}
		else if (type == R || type == L || type == PIPE)
			generate_token(&g_state.input[i], type, 1);
		else if (type == RR || type == LL)
			generate_token(&g_state.input[i++], type, 2);
	}
	generate_token(buf, type, j);
}

void	parser(int i, int j)
{
	char	*buf;
	int		type;

	g_state.flag = 0;
	white_space(&i);
	type = 0;
	buf = (char *)malloc(ft_strlen(g_state.input) + 1 + PATH_MAX);
	ft_parser(i - 1, j, buf, type);
	free(buf);
	ft_cmd(g_state.head, g_state.path);
}
