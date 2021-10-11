/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/10/11 18:36:09 by jekim            ###   ########.fr       */
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

int is_pipe_redirection(const char *target, int idx)
{
	if (target[idx] == '|')
		return (1);
	if (target[idx] == '>')
	{
		if (target[idx + 1] == '>')
			return (4);
		return (2);
	}
	if (target[idx] == '<')
	{
		if (target[idx + 1] == '<')
			return (5);
		return (3);
	}
	return (0);
}
