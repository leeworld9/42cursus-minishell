/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:03:37 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/21 12:36:19 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *homedir_convert(char *home)
{
	char *path;
	char *tmp;

	if ((path = (char *)malloc(sizeof(char) * (PATHLEN_MAX))) == NULL)
		return (NULL); // strerror로 에러 처리 필요
	getcwd(path, PATHLEN_MAX);
	if (!ft_strncmp(home, path, ft_strlen(home)))
	{
		tmp = ft_substr(path, ft_strlen(home) - 1, ft_strlen(path));
		tmp[0] = '~';
		free(path);
		path = tmp;
	}
	return (path);
}

char *join_prompt(char *user, char *name, char *path, char *shell_prompt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (user[j] != '\0')
		shell_prompt[i++] = user[j++];
	shell_prompt[i++] = '@';
	j = 0;
	while (name[j] != '\0')
		shell_prompt[i++] = name[j++];
	shell_prompt[i++] = ':';
	j = 0;
	while (path[j] != '\0')
		shell_prompt[i++] = path[j++];
	free(path);
	shell_prompt[i++] = '$';
	shell_prompt[i++] = ' ';
	shell_prompt[i] = '\0';
	return (shell_prompt);
}

char *prompt()
{
	char *user;
	char *name;
	char *home;
	char *shell_prompt;
	char *path;

    user = getenv("USER"); // 나중에 전역변수에 넣어준 값을 가져와야할듯, 환경변수가 변경된걸 가져 올수가 없음.
	name = getenv("NAME");
	home = getenv("HOME");
	path = homedir_convert(home);
	int len = ft_strlen(user) + 1 + ft_strlen(name) + 1 + ft_strlen(path) + 1;
	if ((shell_prompt = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);  // strerror로 에러 처리 필요
	return (join_prompt(user, name, path, shell_prompt));
}
