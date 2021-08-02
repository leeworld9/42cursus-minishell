/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:10:35 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 19:05:13 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_env(t_env *head, char *key, char *value)
{
	t_env	*env;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = 0;
	env = head;
	while (env->next)
		env = env->next;
	env->next = new;
}

void	update_env(char *key, char *value)
{
	t_env	*env;

	env = get_env(g_state.env, key);
	if (env == NULL)
		add_new_env(g_state.env, key, value);
	else
	{
		if (env->value)
		{
			free(env->value);
			env->value = ft_strdup(value);
		}
		else
			env->value = ft_strdup(value);
	}
}

void	change_path(char *arg)
{
	int		ret;
	char	*path;

	if (!ft_strncmp(arg, "~", 1))
		path = ft_strdup(get_env(g_state.env, "HOME")->value);
	else if (!ft_strncmp(arg, "-", 1))
		path = ft_strdup(get_env(g_state.env, "OLDPWD")->value);
	else
		path = ft_strdup(arg);
	ret = chdir(path);
	free(path);
	if (ret == -1)
		printf("bash: cd: %s: No such file or directory\n", arg);
}

void	ft_cd(char **arg)
{
	char	path[PATH_MAX];

	if (!arg[1])
	{
		change_path("~");
		return ;
	}
	change_path(arg[1]);
	getcwd(path, PATH_MAX);
	update_env("OLDPWD", get_env(g_state.env, "PWD")->value);
	update_env("PWD", path);
}
