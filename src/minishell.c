/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/12/12 04:35:57 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	if (print_intro(argc, argv)
		|| init_env(envp, &data))
		exit(EXIT_FAILURE);
	add_shlvl(&data);
	while (1)
	{
		set_signal_handler();
		input = readline(PROMPT);
		if (input)
		{
			parse_input_string(input, &data);
			add_history(input);
			if (data.input && data.input->next)
			{
				minishell_executor(&data);
				free_token(data.input);
			}
		}
		free(input);
	}
	return (0);
}
