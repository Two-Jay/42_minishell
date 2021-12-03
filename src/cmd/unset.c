/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:13:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/03 17:01:16 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static t_envlst	*unset_find_prev(t_data *data, t_envlst *node_todel)
{
	t_envlst	*node_return;

	node_return = data->envlst;
	while (node_return->next != node_todel)
		node_return = node_return->next;
	return (node_return);
}

static int	unset_traverse(t_data *data, t_token *input)
{
	char		*str;
	t_envlst	*node_todel;
	t_envlst	*node_prev;

	str = input->content;
	if (!env_name_check(str, 0))
		return (builtin_error(
				"shell: unset: `", ft_strjoin(str, UNSET_ERRID), 1));
	node_todel = find_env(str, data);
	if (node_todel)
	{
		node_prev = unset_find_prev(data, node_todel);
		node_prev->next = node_todel->next;
		free(node_todel->key);
		free(node_todel->value);
		free(node_todel);
	}
	return (0);
}

int	minishell_unset(t_data *data, t_token *input)
{
	t_token	*tree;
	int		return_value;

	return_value = 0;
	if (check_flag(input))
		return (builtin_error("shell: unset: ",
				ft_strjoin(tree->next->content, UNSET_ERRFLAG), 2));
	tree = input->next;
	while (input->type == STR)
	{
		return_value = unset_traverse(data, input);
		tree = tree->next;
	}
	return (return_value);
}
