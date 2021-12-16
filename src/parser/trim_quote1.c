/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:25:12 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 12:56:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opener_quote(char *ret, int ix, int *qf)
{
	while (ret[ix])
	{
		if (is_single_quote(ret, ix)
			&& *qf == 0)
		{
			*qf = 1;
			break ;
		}
		if (is_double_quote(ret, ix)
			&& *qf == 0)
		{
			*qf = 2;
			break ;
		}
		ix++;
	}
	return (ix);
}

int	check_closer_quote(char *ret, int ix, int *qf)
{
	while (ret[ix])
	{
		if (is_single_quote(ret, ix)
			&& *qf == 1)
		{
			*qf = 0;
			break ;
		}
		if (is_double_quote(ret, ix)
			&& *qf == 2)
		{
			*qf = 0;
			break ;
		}
		ix++;
	}
	return (ix);
}

char	*free_int_checker(t_data *data)
{
	if (data->ip->qtrim_checker)
		free(data->ip->qtrim_checker);
	return (NULL);
}

void	check_into_checker_arr(int *arr, int startp, int endp)
{
	arr[startp] = 2;
	arr[endp] = 2;
}

int	set_int_checker(t_data *data, int length)
{
	int	ix;

	ix = -1;
	if (!length)
		data->ip->qtrim_checker = NULL;
	data->ip->qtrim_checker = (int *)malloc((length + 1) * sizeof(int));
	if (!data->ip->qtrim_checker)
		return (ERROR_OCCURED);
	while (++ix < length)
		data->ip->qtrim_checker[ix] = 1;
	data->ip->qtrim_checker[length] = '\0';
	return (0);
}
