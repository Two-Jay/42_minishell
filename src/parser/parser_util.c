/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:37:34 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 16:53:34 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strndup(const char *str, size_t n)
{
	char	*ret;
	int		ix;

	if (!str)
		return (NULL);
	ix = -1;
	ret = (char *)ft_calloc(sizeof(char), (n + 1));
	if (!ret)
		return (NULL);
	ret[n] = '\0';
	while (++ix < n)
		ret[ix] = str[ix];
	return (ret);
}