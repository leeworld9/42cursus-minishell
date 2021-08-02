/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:24:50 by dohelee           #+#    #+#             */
/*   Updated: 2021/08/02 16:06:29 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORM3 OK

int	redirect_right_single(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("open faild\n");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	redirect_right_double(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("open faild\n");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	redirect_left_single(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	redirect_left_double(char *str)
{
	int	fd;
	int	heredoc_status;

	read_heredoc(str);
	heredoc_status = WEXITSTATUS(g_state.heredoc_status);
	if (heredoc_status != 0)
	{
		if (heredoc_status == 3)
			return (heredoc_status);
		else if (heredoc_status == 1)
			return (heredoc_status);
	}
	fd = open("$&^@.tmp", O_RDONLY);
	if (fd < 0)
	{
		printf("open faild\n");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}
