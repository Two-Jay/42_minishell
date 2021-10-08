/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:41 by jekim             #+#    #+#             */
/*   Updated: 2021/10/09 02:47:30 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_env(char *envp, t_data *data)
{
	int			equel_check;
	t_envlst	*ptr;

	while (*envp)
	{
		ptr = (t_envlst *)malloc(sizeof(t_envlst));
		equel_check = indexOf(*envp, "=");
		
		envp++;
	}	
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	printf("%s\n", INTRO);
	(void)argc;
	(void)argv;
	(void)envp;
	// set_envlst(envp, &data);
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
