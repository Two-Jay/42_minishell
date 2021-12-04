/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:13:29 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/04 12:49:32 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

void	print_env(t_data *data)
{
	t_envlst	*env;

	env = data->envlst;
	while (env)
	{
		printf("%s: %s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(void)
{
	t_data		*data;
	t_envlst	*env1;
	t_envlst	*env2;
	t_token		*input[4];

	data = malloc(sizeof(t_data));
	env1 = malloc(sizeof(t_envlst));
	env2 = malloc(sizeof(t_envlst));
	if (!data || !env1 || !env2)
		return (0);
	for (int i = 0; i < 4; i++)
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
	env1->key = ft_strdup("a");
	env1->value = ft_strdup("10");
	env1->next = env2;
	env2->key = ft_strdup("b");
	env2->value = ft_strdup("15");
	env2->next = NULL;
	input[3]->next = NULL;
	input[0]->prev = NULL;
	//test
	input[0]->content = ft_strdup("unset");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("a");
	input[1]->type = STR;
	input[2]->content = ft_strdup("1231241");
	input[2]->type = STR;
	input[3]->content = ft_strdup("-12312");
	input[3]->type = STR;
	data->input = input[0];
	data->envlst = env1;
	printf("====before unset====\n");
	print_env(data);
	minishell_unset(data, data->input);
	printf("====after unset====\n");
	print_env(data);
	//free
	free(input[0]->content);
	free(input[0]);
	free(input[1]->content);
	free(input[1]);
	free(input[2]->content);
	free(input[2]);
	free(input[3]->content);
	free(input[3]);
	free(data);
	system("leaks a.out");
}
