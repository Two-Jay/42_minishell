/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:41:54 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/04 13:09:54 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	main(void)
{
	t_data		*data;
	t_envlst	*env1;
	t_token		*input[4];

	data = malloc(sizeof(t_data));
	env1 = malloc(sizeof(t_envlst));
	if (!data || !env1)
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
	env1->next = NULL;
	input[3]->next = NULL;
	input[0]->prev = NULL;
	//test
	input[0]->content = ft_strdup("export");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("-a");
	input[1]->type = FLAG;
	input[2]->content = ft_strdup("c=50");
	input[2]->type = STR;
	input[3]->content = ft_strdup("123d=999");
	input[3]->type = STR;
	data->input = input[0];
	data->envlst = env1;
	minishell_export(data, data->input); //export (with arguments)
	free(input[1]->content);
	free(input[2]->content);
	input[1]->content = ft_strdup(">");
	input[1]->type = REDIRECT;
	input[2]->content = ft_strdup("test.txt");
	input[2]->type = FILEPATH;
	input[2]->next = NULL;
	minishell_export(data, data->input); //export (no arguments)
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
