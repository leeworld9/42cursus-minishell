/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:33:51 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:33:52 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_unsig;
	unsigned char	*s2_unsig;

	i = 0;
	s1_unsig = (unsigned char *)s1;
	s2_unsig = (unsigned char *)s2;
	while (i < n && (*(s1_unsig + i) != '\0' || *(s2_unsig + i) != '\0'))
	{
		if (*(s1_unsig + i) != *(s2_unsig + i))
			return (*(s1_unsig + i) - *(s2_unsig + i));
		i++;
	}
	return (0);
}
