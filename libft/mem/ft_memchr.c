/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:30:58 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:30:59 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr_s;

	i = 0;
	ptr_s = s;
	while (i < n)
	{
		if (*(ptr_s + i) == (unsigned char)c)
		{
			return ((void *)ptr_s + i);
		}
		i++;
	}
	return (NULL);
}
