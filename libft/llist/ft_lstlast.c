/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:30:21 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:30:23 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	size;
	int	i;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	i = 0;
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
