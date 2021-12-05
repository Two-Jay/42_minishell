/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:06:28 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 17:05:44 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_data		*data;
	t_envlst	*env[4];
	t_token		*input[3];

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	for (int i = 0; i < 4; i++)
	{
		env[i] = malloc(sizeof(t_envlst));
		if (!env[i])
			return (0);
		env[i]->env_state = ENV;
		if (i != 0)
			env[i - 1]->next = env[i];
	}
	for (int i = 0; i < 3; i++)
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
	env[0]->key = ft_strdup("a");
	env[0]->value = ft_strdup("10");
	env[1]->key = ft_strdup("b");
	env[1]->value = ft_strdup("10");
	env[2]->key = ft_strdup("c");
	env[2]->value = ft_strdup("10");
	env[3]->key = ft_strdup("d");
	env[3]->value = ft_strdup("10");
	env[3]->next = NULL;
	input[0]->prev = NULL;
	input[2]->next = NULL;
	input[0]->content = ft_strdup("env");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("asd");
	input[1]->type = STR;
	input[2]->content = ft_strdup("test.txt");
	input[2]->type = STR;
	data->envlst = env[0];
	data->input = input[0];
	minishell_env(data, data->input);
	for (int i = 0; i < 4; i++)
	{
		free(env[i]->key);
		free(env[i]->value);
		free(env[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
	free(data);
	system("leaks a.out");
}
