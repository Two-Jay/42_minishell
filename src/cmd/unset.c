/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:13:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 20:24:14 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static t_envlst	*unset_find_node_before(t_data *data, t_envlst *node_todel)
{
	t_envlst	*node_return;

	node_return = data->envlst;
	while (node_return->next != node_todel)
		node_return = node_return->next;
	return (node_return);
}

static int	unset_printerr(char *str)
{
	write(2, "unset: `", 9);
	write(2, str, ft_strlen(str));
	write(2, UNSET_ERRID, ft_strlen(UNSET_ERRID));
	return (-1);
}

int	minishell_unset(t_data *data)
{
	char		*str;
	t_envlst	*node_todel;
	t_envlst	*node_temp;

	str = data->input->next->contents;
	if (!export_name_check(str, 0))
		return (unset_printerr(str));
	if (str)
	{
		node_todel = find_env(str, data);
		if (node_todel)
		{
			node_temp = unset_find_node_before(data, node_todel);
			node_temp->next = node_todel->next;
			free(node_temp->key);
			free(node_todel->value);
			free(node_todel);
		}
	}
	return (0);
}
