/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:13:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static t_envlst	*unset_find_prev(t_data *data, t_envlst *node_todel)
{
	t_envlst	*node_return;

	node_return = data->envlst;
	if (node_return == node_todel)
		return (NULL);
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
				"shell: unset", ft_strjoin(str, UNSET_ERRID), 1));
	node_todel = find_env(str, data);
	if (node_todel)
	{
		node_prev = unset_find_prev(data, node_todel);
		if (!node_prev)
			data->envlst = node_todel->next;
		else
			node_prev->next = node_todel->next;
		free(node_todel->key);
		free(node_todel->value);
		free(node_todel);
	}
	return (0);
}

int	minishell_unset(t_data *data, t_token *input)
{
	int		return_value;

	return_value = 0;
	input = input->next;
	if (check_flag(input))
		return (builtin_error("shell: unset",
				ft_strjoin(input->next->content, UNSET_ERROPT), 2));
	while (input && input->type == STR)
	{
		return_value = unset_traverse(data, input);
		input = input->next;
	}
	return (return_value);
}
