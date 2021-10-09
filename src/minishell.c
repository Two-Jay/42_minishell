/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/09 18:44:37 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	printf("%s\n", INTRO);
	(void)argc;
	(void)argv;
	(void)envp;
	init_env(envp, &data);
	while (1)
	{
		input = readline(NULL);
		if (input)
		{
			if (ft_strncmp(input, "exit", 4) == 0)
				exit(EXIT_SUCCESS);
			parse_input(input);

		}
		add_history(input);
	}
	return (0);
}
