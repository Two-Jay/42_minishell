/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/09 21:49:17 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	data = NULL;
	if (print_intro(argc, argv) || init_data(data) || init_env(envp, data))
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline(NULL);
		if (input)
		{
			if (ft_strncmp(input, "exit", 4) == 0)
				exit_minishell_SUCC();
			parse_input(input);
			free(input);
		}
		add_history(input);
	}
	return (0);
}
