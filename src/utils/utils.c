/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/10/11 15:28:50 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int indexOf_char(const char *str, char target)
{
	int ix;

	ix = 0;
	while (str[ix])
	{
		if (str[ix] == target)
			return (ix);
		ix++;
	}
	return (-1);
}

int print_intro(int argc, char **argv)
{
	printf("%s\n", INTRO);
	(void)argc;
	(void)argv;
	return (0);
}

int is_pipe(const char *target)
{
	if (ft_strncmp(target, "|", 1) == 0)
		return (1);
	if (ft_strncmp(target, ">", 1) == 0)
		return (2);
	if (ft_strncmp(target, "<", 1) == 0)
		return (3);
	return (0);
}

int is_redirection(const char *target)
{
	if (ft_strncmp(target, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(target, "<<", 2) == 0)
		return (2);
	return (0);
}