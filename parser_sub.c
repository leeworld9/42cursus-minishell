/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:43:34 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_dollar(char *s, int idx, int i, char *value)
{
	char	*ret;
	int		j;
	int		k;

	ret = (char *)malloc(ft_strlen(s) + ft_strlen(value) + 1);
	j = 0;
	while (j < idx)
	{
		ret[j] = s[j];
		j++;
	}
	k = 0;
	while (value[k])
		ret[j++] = value[k++];
	ret[j] = '\0';
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	free(value);
	free(g_state.input);
	return (ret);
}

char	*treat_dollar(int len, int idx, int i)
{
	int		j;
	char	*buf;
	char	*value;
	char	*tmp;

	j = 0;
	value = NULL;
	buf = (char *)malloc(len + 1);
	while (g_state.input[i] != '?' && !((has_type(g_state.input, i)) >= 1 \
		 || !g_state.input[i]))
		buf[j++] = g_state.input[i++];
	if (g_state.input[i] == '?')
	{
		tmp = ft_itoa(g_state.ret);
		value = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	else if ((has_type(g_state.input, i)) >= 1 || !g_state.input[i])
	{
		buf[j] = '\0';
		value = ft_strdup(return_envval(buf));
	}
	free(buf);
	return (convert_dollar(g_state.input, idx, i, value));
}

void	treat_quote(int type)
{
	if (type == SINGLE && g_state.flag == 0)
		g_state.flag = 1;
	else if (type == SINGLE && g_state.flag == 1)
		g_state.flag = 0;
	if (type == DOUBLE && g_state.flag == 0)
		g_state.flag = 2;
	else if (type == DOUBLE && g_state.flag == 2)
		g_state.flag = 0;
}

void	generate_token(char *buf, int type, int len)
{
	t_token		*token;
	char		*temp;

	if (len == 0)
		return ;
	if (type == PIPE)
		g_state.len++;
	temp = ft_substr(buf, 0, len);
	if (!g_state.head)
		g_state.head = create_token(temp, type);
	else
	{
		if (type == SPACING)
			type = ARG;
		token = g_state.head;
		while (token->next)
			token = token->next;
		token->next = create_token(temp, type);
	}
	free(temp);
}
