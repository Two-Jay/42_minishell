/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_close_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:53:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/03 19:18:15 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_isclosed(const char *input)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1 && is_quotation(input, ix))
		return (FALSE);
	while (input[++ix])
        is_inquoted(input, ix, &flag);
	if (flag == 0)
		return (TRUE);
	return (FALSE);
}