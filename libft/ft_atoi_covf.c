/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_covf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:45:10 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:58:06 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return int nbr when the value of nbr is between INTMAX and INTMIN
** if an overflow occur, returns 1 and adds a value on ovf_flag pointer
*/
int	ft_atoi_covf(const char *nptr, int *ovf_flag)
{
	long long	nbr;
	int			sign;
	int			ix;

	nbr = 0;
	ix = 0;
	sign = 1;
	while (nptr[ix] && ft_isspace(nptr[ix]))
		ix++;
	if (nptr[ix] == '-')
		sign = -1;
	if (nptr[ix] == '-' || nptr[ix] == '+')
		ix++;
	while (nptr[ix] && ('0' <= nptr[ix] && nptr[ix] <= '9'))
		nbr = (nbr * 10) + (nptr[ix++] - '0');
	if (ft_isoverflow(nbr * sign) == 1 || ft_isoverflow(nbr * sign) == -1)
		return (++(*ovf_flag));
	else
		return ((int)(nbr * sign));
}
