/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:30:51 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:30:52 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	i = 0;
	ptr_dest = dest;
	ptr_src = src;
	while (i < n)
	{
		*(ptr_dest + i) = *(ptr_src + i);
		if (*(ptr_src + i) == (unsigned char)c)
		{
			return ((void *)ptr_dest + i + 1);
		}
		i++;
	}
	return (NULL);
}
