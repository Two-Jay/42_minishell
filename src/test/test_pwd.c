/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:56:22 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/06 02:42:05 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_data	*data;
	t_token	*input[5];

	data = malloc(sizeof(t_data));
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
	input[2]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("pwd");
	input[0]->type = CMD;
	input[1]->content = ft_strdup(">");
	input[1]->type = REDIRECT;
	input[2]->content = ft_strdup("a");
	input[2]->type = FILEPATH;
	data->input = input[0];
	minishell_pwd(data->input, STDOUT_FILENO);
	for (int i = 0; i < 3; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
	free(data);
	system("leaks a.out");
}
