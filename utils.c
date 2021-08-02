/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:00:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 19:07:00 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *arr1, char *arr2)
{
	int	i;

	i = 0;
	if (arr1 == NULL)
		return (-1);
	while (arr1[i] != '\0' || arr2[i] != '\0')
	{
		if (arr1[i] > arr2[i])
			return (arr1[i] - arr2[i]);
		else if (arr1[i] < arr2[i])
			return (arr1[i] - arr2[i]);
		i++;
	}
	return (0);
}

void	env_free(t_env *env)
{
	free(env->key);
	free(env->value);
	if (env->next != NULL)
		free(env->next);
	free(env);
}
