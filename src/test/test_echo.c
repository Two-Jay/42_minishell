/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:11:45 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 18:46:50 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	main(void)
{
	t_data	*data;
	t_token	*input[5];

	data = malloc(sizeof(t_data));
	for (int i = 0; i < 5; i++)
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
	input[4]->next = NULL;
	input[0]->prev = NULL;
	input[0]->content = ft_strdup("echo");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("-nn-nnnnn");
	input[1]->type = FLAG;
	input[2]->content = ft_strdup("jiychoi zzang");
	input[2]->type = STR;
	input[3]->content = ft_strdup("asdasd");
	input[3]->type = STR;
	input[4]->content = ft_strdup("haha\nhaha");
	input[4]->type = STR;
	data->input = input[0];
	minishell_echo(data);
	for (int i = 0; i < 4; i++)
	{
		free(input[i]->content);
		free(input[i]);
	}
	free(data);
	system("leaks a.out");
}
