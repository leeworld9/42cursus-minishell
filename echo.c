/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhee <rhee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:11:37 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/30 19:00:51 by rhee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NORM3 OK

int	cnt_arg(char **arg)
{
	int	cnt;

	cnt = 0;
	while (arg[cnt])
		cnt++;
	return (cnt);
}

int	ft_echo(char **arg)
{
	int	i;
	int	cnt;
	int	n_flag;

	i = 1;
	n_flag = 0;
	cnt = cnt_arg(arg);
	if (cnt > 1)
	{
		if (arg[i] && !ft_strcmp(arg[i], "-n"))
		{
			n_flag = 1;
			i++;
		}
		while (arg[i])
		{
			printf("%s", arg[i]);
			if (arg[i + 1] && arg[i][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (n_flag == 0)
		printf("\n");
	exit(0);
}
