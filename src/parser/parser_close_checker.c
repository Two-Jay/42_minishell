/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_close_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:53:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 11:36:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_isclosed(const char *input, t_data *data)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1 && is_quotation(input, ix))
		return (print_syntax_error(
			"Shell ",
			PSR_ERRSYNTAX, "'unclosed quote'",
			data));
	while (input[++ix])
        is_inquoted(input, ix, &flag);
	if (flag == 0)
		return (TRUE);
	return (print_syntax_error(
			"Shell ",
			PSR_ERRSYNTAX, "'unclosed quote'",
			data));
}