/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:13:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:27:18 by jiychoi          ###   ########.fr       */
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

static int	unset_check_all_node(t_data *data, t_token *tree)
{
	char		*str;
	t_envlst	*node_todel;
	t_envlst	*node_temp;

	while (tree)
	{
		if (!export_name_check(tree->content, 0))
			return (unset_printerr(str));
		node_todel = find_env(tree->content, data);
		if (node_todel)
		{
			node_temp = unset_find_node_before(data, node_todel);
			node_temp->next = node_todel->next;
			free(node_temp->key);
			free(node_todel->value);
			free(node_todel);
		}
		tree = tree->next;
	}
	return (0);
}

int	minishell_unset(t_data *data)
{
	return (unset_check_all_node(data, data->input));
}
