/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:32:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 18:34:20 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	main(void)
{
	t_data		*data;
	t_envlst	*env;
	t_token		*input[3];
	char		buf[100];

	data = malloc(sizeof(t_data));
	env = malloc(sizeof(t_envlst));
	if (!data || !env)
		return (0);
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
	env->key = ft_strdup("PWD");
	env->value = ft_strdup("/");
	input[2]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("cd");
	data->input = input[0];
	data->envlst = env;
	//test
	input[1]->content = ft_strdup("a");
	input[1]->next = 0;
	getcwd(buf, 100);
	printf("before cd : %s\n", buf);
	minishell_cd(data);
	getcwd(buf, 100);
	printf("after cd : %s\n", buf);
	printf("env 1 -> %s : %s\n", env->key, env->value);
	printf("env 2 -> %s : %s\n", env->next->key, env->next->value);
/*
	for (int i = 0; i < 10; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
*/
	free(data);
	system("leaks a.out");
}
