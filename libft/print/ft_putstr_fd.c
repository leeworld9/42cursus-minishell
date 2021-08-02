/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:32:57 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:32:58 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len_s;

	if (s == NULL)
		return ;
	len_s = ft_strlen(s);
	write(fd, s, len_s);
}
