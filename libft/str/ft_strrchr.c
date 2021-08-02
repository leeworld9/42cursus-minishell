/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:34:00 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:34:01 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	set_i;

	i = 0;
	set_i = -1;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
			set_i = i;
		i++;
	}
	if (set_i >= 0)
		return ((char *)s + set_i);
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
