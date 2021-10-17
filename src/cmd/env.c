/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:26:51 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/17 18:23:38 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	env_no_param(t_data *data)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	if (!node_tmp)
		return (-1);
	while (node_tmp->next != NULL)
	{
		if (node_tmp->env_state == ENV)
		{
			write(1, node_tmp->key, ft_strlen(node_tmp->key));
			write(1, "=\"", 2);
			write(1, node_tmp->value, ft_strlen(node_tmp->value));
			write(1, "\"\n", 2);
		}
		node_tmp = node_tmp->next;
	}
	return (0);
}

int	minishell_env(t_data *data)
{
	if (export_no_param(data) < 0)
		return (-1);
	return (0);
}
