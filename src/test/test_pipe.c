/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:16:36 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

// Test Code for Pipe
int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	t_token	*input[10];

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	for (int i = 0; i < 8; i++)
	{
		input[i] = malloc(sizeof(t_token));
		if (!input[i])
			return (0);
		input[i]->ix = i;
		if (i != 0)
		{
			input[i - 1]->next = input[i];
			input[i]->prev = input[i - 1];
		}
	}
	input[7]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("cat");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("/dev/urandom");
	input[1]->type = STR;
	input[2]->content = ft_strdup("|");
	input[2]->type = PIPE;
	input[3]->content = ft_strdup("head");
	input[3]->type = CMD;
	input[4]->content = ft_strdup("-n");
	input[4]->type = FLAG;
	input[5]->content = ft_strdup("1000");
	input[5]->type = STR;
	input[6]->content = ft_strdup("|");
	input[6]->type = PIPE;
	input[7]->content = ft_strdup("wc");
	input[7]->type = CMD;
	input[7]->next = NULL;
	data->input = input[0];
	// Test
	//printf("%d\n", pipe_count_cmd(input[0])); //check if pipe_count_cmd works
	//printf("%d\n", pipe_count_param(input[2])); //check if pipe_count_paramworks
	minishell_pipe(data, envp);
	free(data);
	system("leaks a.out");
}
