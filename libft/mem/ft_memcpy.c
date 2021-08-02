/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:31:06 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:31:07 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	ptr_src = src;
	ptr_dest = dest;
	while (i < n)
	{
		*(ptr_dest + i) = *(ptr_src + i);
		i++;
	}
	return (dest);
}
