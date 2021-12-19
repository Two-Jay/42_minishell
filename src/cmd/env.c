/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:26:51 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/19 15:05:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_no_param(t_data *data, int ofd)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	while (node_tmp)
	{
		if (node_tmp->env_state == ENV)
		{
			ft_putstr_fd(node_tmp->key, ofd);
			ft_putstr_fd("=", ofd);
			ft_putstr_fd(node_tmp->value, ofd);
			ft_putstr_fd("\n", ofd);
		}
		node_tmp = node_tmp->next;
	}
	return (0);
}

int	minishell_env(t_data *data, t_token *input, int ofd)
{
	int	argument_check;

	argument_check = check_argument(input);
	if (argument_check == FLAG_O)
	{
		input = input->next;
		while (input && (input->type == REDIRECT || input->type == FILEPATH))
			input = input->next;
		return (builtin_error("env",
				ft_strjoin(input->content, ENV_ERROPT), 1));
	}
	else if (argument_check == ARGUMENT_O)
	{
		input = input->next;
		while (input && (input->type == REDIRECT || input->type == FILEPATH))
			input = input->next;
		return (builtin_error("env",
				ft_strjoin(input->content, ENV_ERRNODIR), 1));
	}
	return (env_no_param(data, ofd));
}
