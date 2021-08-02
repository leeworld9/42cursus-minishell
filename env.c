/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:52:38 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 16:12:28 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORM3 OK

void	env_parsing(t_env *tmp, char *variable)
{
	int	i;
	int	len;

	i = 0;
	while (variable[i] != '\0')
	{
		if (variable[i] == '=')
			break ;
		i++;
	}
	len = ft_strlen(variable);
	tmp->key = ft_substr(variable, 0, i);
	tmp->value = ft_substr(variable, i + 1, len);
	tmp->next = 0;
}

t_env	*init_env(t_env *env, char *variable)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == NULL)
		return (NULL);
	env_parsing(tmp, variable);
	if (env != NULL)
	{
		while (env->next != NULL)
			env = env->next;
		env->next = tmp;
	}
	else
		env = tmp;
	return (env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		env = env->next;
		free(tmp);
	}
}

t_env	*get_env(t_env *env, char *key)
{
	int	i;
	int	j;

	while (env != NULL)
	{
		i = ft_strncmp(env->key, key, ft_strlen(env->key));
		j = ft_strncmp(key, env->key, ft_strlen(key));
		if (i == 0 && j == 0)
			return (env);
		env = env -> next;
	}
	return (NULL);
}
