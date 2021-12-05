/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:05:22 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 17:05:44 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_data	*data;
	t_token	*input[3];

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
	input[0]->content = ft_strdup("exit");
	input[0]->type = CMD;
	input[1]->content = ft_strdup("1243124210");
	input[1]->type = STR;
	input[1]->next = NULL;
	input[2]->content = ft_strdup("150");
	input[2]->type = STR;
	data->input = input[0];
	minishell_exit(data, data->input);
	printf("$? : %d\n", data->dq);
}
