/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:32:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

int	main(void)
{
	t_data		*data;
	t_envlst	*env1;
	t_envlst	*env2;
	t_token		*input[3];
	char		buf[100];

	data = malloc(sizeof(t_data));
	env1 = malloc(sizeof(t_envlst));
	env2 = malloc(sizeof(t_envlst));
	if (!data || !env1 || !env2)
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
	chdir("/Users/chichoon/Documents/minishell/");
	env1->key = ft_strdup("PWD");
	env1->value = ft_strdup("/Users/chichoon/Documents/minishell/");
	env1->next = env2;
	env2->key = ft_strdup("OLDPWD");
	env2->value = ft_strdup("/Users/chichoon/Documents/minishell/src/test");
	env2->next = NULL;
	input[2]->next = NULL;
	input[0]->prev = NULL;
	//test
	input[0]->content = ft_strdup("cd");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("src/test");
	input[1]->type = STR;
	input[2]->content = ft_strdup("src");
	input[2]->type = STR;
	data->input = input[0];
	data->envlst = env1;
	getcwd(buf, 100);
	printf("before cd : %s\n", buf);
	minishell_cd(data, data->input);
	getcwd(buf, 100);
	printf("after cd : %s\n", buf);
	printf("env 1 -> %s : %s\n", env1->key, env1->value);
	printf("env 2 -> %s : %s\n", env1->next->key, env1->next->value);

	//free
	free(input[0]->content);
	free(input[0]);
	free(input[1]->content);
	free(input[1]);
	free(input[2]->content);
	free(input[2]);
	free(env1->key);
	free(env1->value);
	free(env2->key);
	free(env2->value);
	free(data);
	system("leaks a.out");
}
