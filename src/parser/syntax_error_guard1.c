/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_guard1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:56:16 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 20:12:55 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_syntax_error(char *cmd, char *error_str)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_str, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	g_dq = DQ_ERRSYNTAX;
	if (error_str)
		free(error_str);
	return (ERROR_OCCURED);
}

int	check_isclosed(const char *input)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1 && is_quotation(input, ix))
		return (print_syntax_error(
				PSR_ERRHEAD,
				ft_strjoin(PSR_ERRSYNTAX, "'unclosed quote'")));
	while (input[++ix])
		is_inquoted(input, ix, &flag);
	if (flag == 0)
		return (TRUE);
	return (print_syntax_error(
			PSR_ERRHEAD,
			ft_strjoin(PSR_ERRSYNTAX, "'unclosed quote'")));
}
