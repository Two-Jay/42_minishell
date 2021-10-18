/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/18 22:21:27 by jekim            ###   ########seoul.kr  */
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
			parse_input(input, &data);
			add_history(input);
		}
		free(input);
	}
	return (0);
}
