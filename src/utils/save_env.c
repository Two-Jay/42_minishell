/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:00:59 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 15:10:43 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static t_envlst	*get_last_node(t_data *data)
{
	t_envlst	*node_found;

	node_found = data->envlst;
	if (!node_found)
		return (NULL);
	while (node_found->next)
		node_found = node_found->next;
	return (node_found);
}

static int	save_new_env(
	t_data *data, char *env_key, char *env_value, t_env_state flag)
{
	t_envlst	*node_last;
	t_envlst	*node_new;

	node_new = malloc(sizeof(t_envlst));
	if (!node_new)
		return (-1);
	node_new->key = env_key;
	node_new->value = env_value;
	node_new->env_state = flag;
	node_new->next = NULL;
	node_last = get_last_node(data);
	if (!node_last)
	{
		free(env_key);
		free(env_value);
		free(node_new);
		return (-1);
	}
	node_last->next = node_new;
	return (0);
}

static void	override_env(
	t_envlst *node_found, char *env_key, char *env_value)
{
	if (node_found->key)
	{
		free(node_found->key);
		node_found->key = env_key;
	}
	if (node_found->value)
	{
		free(node_found->value);
		node_found->value = env_value;
	}
}

int	save_env(
	t_data *data, char *env_key, char *env_value, t_env_state flag)
{
	t_envlst	*node_found;
	t_envlst	*node_new;

	node_found = find_env(env_key, data);
	if (!node_found)
		return (save_new_env(data, env_key, env_value, flag));
	override_env(node_found, env_key, env_value);
	return (0);
}
