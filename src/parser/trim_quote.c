/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 12:56:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(char *str, char *dst)
{
	dst = ft_strdup(str);
	return (0);
}

int	check_unprint_char(char *ret, t_data *data)
{
	int		startp;
	int		endp;
	int		ix;
	int		quote_flag;

	ix = -1;
	quote_flag = 0;
	while (ret[++ix])
	{
		startp = -1;
		endp = -1;
		startp = check_opener_quote(ret, ix, &quote_flag);
		endp = check_closer_quote(ret, startp + 1, &quote_flag);
		if (startp > -1 || endp > -1)
			check_into_checker_arr(data->ip->qtrim_checker, startp, endp);
		if (endp > -1)
			ix = endp;
	}
	return (0);
}

int	get_ret_buf_length(t_data *data, int length)
{
	int	ret;
	int	ix;

	ret = 0;
	ix = -1;
	while (++ix < length)
	{
		if (data->ip->qtrim_checker[ix] == 1)
			ret++;
	}
	return (ret);
}

char	*strdup_as_checked(char *str, t_data *data, int length)
{
	char	*ret;
	int		len;
	int		ix;
	int		jx;

	ix = 0;
	jx = 0;
	len = get_ret_buf_length(data, length);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (str[ix])
	{
		if (data->ip->qtrim_checker[ix] == 1)
			ret[jx++] = str[ix];
		if (jx == len)
			break ;
		ix++;
	}
	return (ret);
}

char	*quote_trim(char *str, t_data *data)
{
	char	*ret;

	if (is_quoted_input(str) == FALSE)
		return (ft_strdup(str));
	if (set_int_checker(data, ft_strlen(str)))
		return (NULL);
	check_unprint_char(str, data);
	ret = strdup_as_checked(str, data, ft_strlen(str));
	if (!ret)
	{
		free_int_checker(data);
		return (NULL);
	}
	free_int_checker(data);
	return (ret);
}
