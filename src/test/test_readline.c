/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:54:21 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 18:58:54 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;
	int		i;

	input = readline(">> :");
	i = -1;
	while (input[++i])
	{
		printf("%d: %c (%d)\n", i, input[i], input[i]);
	}
	free(input);
	return (0);
}
