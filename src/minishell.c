/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 19:08:23 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_input(const char *input, t_data *data)
{
	char *buf;

	buf = NULL;
	if (preprocess_input(input, buf)
		|| tokenize_input(buf, data))
		return (ERROR_OCCURED);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	if (print_intro(argc, argv) || init_env(envp, &data))
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline(">> :");
		if (input)
		{
			trs(input);
			parse_input(input, &data);
			add_history(input);
		}
		free(input);
	}
	return (0);
}
