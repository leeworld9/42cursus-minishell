/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:33:21 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:33:22 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*copy;
	size_t	i;

	i = 0;
	len_s1 = ft_strlen(s1);
	copy = (char *)malloc((len_s1 + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (i < len_s1)
	{
		*(copy + i) = *(s1 + i);
		i++;
	}
	*(copy + i) = '\0';
	return (copy);
}
