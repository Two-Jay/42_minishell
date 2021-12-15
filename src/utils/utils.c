/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:27:37 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	indexOf_char(const char *str, char target)
{
	int	ix;

	ix = 0;
	while (str[ix])
	{
		if (str[ix] == target)
			return (ix);
		ix++;
	}
	return (-1);
}

int	print_intro(int argc, char **argv)
{
	printf("%s\n", INTRO);
	(void)argc;
	(void)argv;
	return (0);
}
