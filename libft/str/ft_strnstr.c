/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:33:55 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:33:57 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*find_little(const char *big, const char *little,
						size_t len, size_t len_little)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && *(big + i) != '\0')
	{
		if (*(little + j) == *(big + i))
		{
			while (i + j < len && *(little + j) != '\0')
			{
				if (*(little + j) == *(big + i + j))
					j++;
				else
					break ;
			}
			if (j == len_little)
				return ((char *)(big + i));
		}
		j = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	char	*result;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	result = find_little(big, little, len, len_little);
	return (result);
}
