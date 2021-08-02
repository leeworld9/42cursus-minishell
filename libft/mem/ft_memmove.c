/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:31:10 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:31:11 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	non_overlap_loop(unsigned char *ptr_dst,
						const unsigned char *ptr_src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(ptr_dst + i) = *(ptr_src + i);
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	ptr_src = src;
	ptr_dst = dst;
	if (dst < src)
	{
		non_overlap_loop(ptr_dst, ptr_src, len);
	}
	else
	{
		while (i < len)
		{
			*(ptr_dst + len - i - 1) = *(ptr_src + len - i - 1);
			i++;
		}
	}
	return ((void *)dst);
}
