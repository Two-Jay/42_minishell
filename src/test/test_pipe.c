/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:16:36 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 13:42:11 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

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
	for (int i = 0; i < 10; i++)
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
	input[9]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("ls");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("|");
	input[1]->type = PIPE;
	input[2]->content = ft_strdup("cat");
	input[2]->type = CMD;
	input[3]->content = ft_strdup("-e");
	input[3]->type = FLAG;
	input[4]->content = ft_strdup("|");
	input[4]->type = PIPE;
	input[5]->content = ft_strdup("cat");
	input[5]->type = CMD;
	input[6]->content = ft_strdup("-e");
	input[6]->type = FLAG;
	input[7]->content = ft_strdup("|");
	input[7]->type = PIPE;
	input[8]->content = ft_strdup("cat");
	input[8]->type = CMD;
	input[9]->content = ft_strdup("-e");
	input[9]->type = FLAG;
	data->input = input[0];
	// Test
	//printf("%d\n", pipe_count_cmd(input[0])); //check if pipe_count_cmd works
	//printf("%d\n", pipe_count_param(input[2])); //check if pipe_count_paramworks
	minishell_pipe(data, envp);
	for (int i = 0; i < 10; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
	free(data);
	system("leaks a.out");
}
