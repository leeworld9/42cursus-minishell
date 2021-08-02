/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:31:49 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 17:31:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_nblen function calculates the length of a number based
** on a given base.
** E.g. 3869 with base 10 has a length of 4 (4 digits).
**
** Arguments:
**		(long)	nb: the input number.
**		(int)	base: the base for which to calculate the length.
**
** Returns:
**		(int)	i: length of the number
*/

int	ft_nblen(long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}
