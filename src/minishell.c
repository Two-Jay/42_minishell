/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 20:06:15 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_input(const char *input, t_data *data)
{
	char *buf;
	char **tokened;

	buf = NULL;
	tokened = NULL;
	buf = preprocess_input(input);
	buf = parse_env(buf, data);
	if (ft_strlen(buf))
		tokenize_input(buf, data);
	trs(buf);
	trp(buf);
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
			parse_input_string(input, &data);
			add_history(input);
		}
		free(input);
	}
	return (0);
}
