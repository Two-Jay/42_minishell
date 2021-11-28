/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:00:59 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 15:03:48 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	save_env(
	t_data *data, char *env_key, char *env_value, t_env_state flag)
{
	t_envlst	*node_found;
	t_envlst	*node_new;

	node_found = find_env(env_key, data);
	node_new = NULL;
	if (!node_found)
	{
		node_found = data->envlst;
		while (node_found->next != NULL)
			node_found = node_found->next;
		node_new = malloc(sizeof(t_envlst));
		if (!node_new)
			return (-1);
		node_new->key = env_key;
		node_new->value = env_value;
		node_new->env_state = flag;
		node_new->next = NULL;
		node_found->next = node_new;
		return (0);
	}
	if (node_new->value)
		free(node_new->value);
	free(env_key);
	node_new->value = env_value;
	return (0);
}
