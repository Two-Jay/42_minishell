/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:41:01 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 18:07:46 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data		*data;
	t_envlst	*env1;
	t_envlst	*env2;
	t_token		*input[10];

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	env1 = malloc(sizeof(t_envlst));
	env2 = malloc(sizeof(t_envlst));
	if (!data || !env1 || !env2)
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
	env1->key = ft_strdup("PWD");
	env1->value = ft_strdup("/Users/chichoon/Documents/minishell/");
	env1->next = env2;
	env2->key = ft_strdup("HOME");
	env2->value = ft_strdup("/Users/chichoon/");
	env2->next = NULL;
	input[9]->next = NULL;
	input[0]->prev = NULL;
	//test
	input[0]->content = ft_strdup("ls");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("-al");
	input[1]->type = FLAG;
	input[2]->content = ft_strdup("|");
	input[2]->type = PIPE;
	input[3]->content = ft_strdup("cat");
	input[3]->type = CMD;
	input[4]->content = ft_strdup("-e");
	input[4]->type = FLAG;
	input[5]->content = ft_strdup("|");
	input[5]->type = PIPE;
	input[6]->content = ft_strdup("echo");
	input[6]->type = CMD;
	input[7]->content = ft_strdup("hello");
	input[7]->type = STR;
	input[8]->content = ft_strdup(">");
	input[8]->type = REDIRECT;
	input[8]->content = ft_strdup("test.txt");
	input[8]->type = FILEPATH;
	data->input = input[0];
	data->envlst = env1;
	minishell_executor(data, envp);
	for (int i = 0; i < 10; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
	free(env1->key);
	free(env1->value);
	free(env2->key);
	free(env2->value);
	free(data);
	system("leaks a.out");
}
