/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 18:05:33 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_slash(char *s, struct stat	*buf)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
	{
		if (!stat(s, buf))
			return (1);
		printf("bash: %s: No such file or directory\n", s);
		return (2);
	}
	return (3);
}

char	**return_dir(void)
{
	char	*path;

	if (!get_env(g_state.env, "PATH"))
		path = NULL;
	else
		path = get_env(g_state.env, "PATH")->value;
	return (ft_split(path, ':'));
}

void	parse_free(char **dir_list)
{
	int	i;

	i = 0;
	if (dir_list == NULL)
		return ;
	while (dir_list[i] != NULL)
	{
		free(dir_list[i]);
		i++;
	}
	if (dir_list != NULL)
		free(dir_list);
}

char	*parse_path(char *cmd, int i)
{
	char		**dir_list;
	char		*curr;
	char		*tmp;
	int			slash;

	slash = find_slash(cmd, &g_state.buf);
	if (slash == 1)
		return (cmd);
	else if (slash == 3)
	{
		dir_list = return_dir();
		while (dir_list && dir_list[++i])
		{
			tmp = ft_strjoin(dir_list[i], "/");
			curr = ft_strjoin(tmp, cmd);
			free(tmp);
			if (!stat(curr, &g_state.buf))
				return (curr);
		}
		parse_free(dir_list);
		printf("bash: %s: command not found\n", cmd);
		free(curr);
	}
	return (NULL);
}
