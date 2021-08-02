/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:59:34 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 16:15:13 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_env *env, char *variable)
{
	t_env	*target;
	char	*tmp_value;

	target = (t_env *)malloc(sizeof(t_env));
	if (target == NULL)
		return ;
	env_parsing(target, variable);
	while (env != NULL)
	{	
		if (ft_strcmp(env->key, target->key) == 0)
		{
			tmp_value = env->value;
			env->value = ft_strdup(target->value);
			env_free(target);
			free(tmp_value);
			break ;
		}
		if (env->next == NULL)
		{
			env->next = target;
			target->next = NULL;
			break ;
		}
		env = env->next;
	}
}

void	delete_env(t_env *env, char *key)
{
	t_env	*before;

	before = env;
	while (env != NULL)
	{	
		if (ft_strcmp(env->key, key) == 0)
		{
			before->next = env->next;
			if (env->key != NULL)
				free(env->key);
			if (env->value != NULL)
				free(env->value);
			free(env);
			return ;
		}
		else
		{
			before = env;
			env = env->next;
		}
	}
	return ;
}

void	show_env(t_env *env)
{
	while (env != NULL)
	{	
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return ;
}

int	ft_flowcase(char *arg)
{
	int	result;

	result = ft_atoi(arg);
	if (result > 255)
	{
		while (result > 255)
			result -= 256;
		return (result);
	}
	else if (result < 0)
	{
		while (result < 0)
			result += 256;
		return (result);
	}
	else
		return (result);
}

int	check_exitarg(char **arg)
{
	int	j;

	if (arg[1] == NULL)
		return (EXIT_SUCCESS);
	if (arg[2])
	{
		printf("bash: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	j = 0;
	if (arg[1][j] == '-')
		j++;
	if (arg[1][j] != '\0')
	{
		if (ft_isdigit(arg[1][j]))
			j++;
		else
		{
			printf("bash: exit: %s: numeric argument required\n", arg[1]);
			return (2);
		}
	}
	return (ft_flowcase(arg[1]));
}
