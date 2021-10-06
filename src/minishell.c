/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/07 04:44:38 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;

	printf("%s\n", INTRO);
	(void)argc;
	(void)argv;
	(void)envp;
	// set_envlst(envp, data);
	while (1)
	{
		input = readline(NULL);
		if (input)
		{
			parse_input(input);
		}
		add_history(input);
	}
	return (0);
}
