/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:34:23 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:55:16 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	export_printerr(char *str)
{
	write(2, "export: `", 9);
	write(2, str, ft_strlen(str));
	write(2, EXPORT_ERRID, ft_strlen(EXPORT_ERRID));
	return (-1);
}

int	export_no_param(t_data *data)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	if (!node_tmp)
		return (-1);
	while (node_tmp->next != NULL)
	{
		if (node_tmp->env_state == ENV || node_tmp->env_state == EXPORT_ONLY)
		{
			write(1, node_tmp->key, ft_strlen(node_tmp->key));
			if (node_tmp->env_state == ENV)
			{
				write(1, "=\"", 2);
				ft_putstr_fd(node_tmp->value, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 2);
		}
		node_tmp = node_tmp->next;
	}
	return (0);
}

int	export_save_env(
	t_data *data, char *env_key, char *env_value, t_env_state flag)
{
	t_envlst	*node_found;
	t_envlst	*node_new;

	node_found = find_env(env_key, data);
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

int	export_with_param(t_data *data, t_token *tree)
{
	char		*str;
	char		*ptr_equal;
	char		*env_key;
	char		*env_value;
	t_env_state	flag;

	str = tree->content;
	ptr_equal = export_equal_check(str);
	env_value = 0;
	if (export_name_check(str, ptr_equal))
	{
		if (!ptr_equal)
		{
			env_key = ft_strdup(str);
			flag = EXPORT_ONLY;
		}
		else
		{
			env_key = ft_strndup(str, ptr_equal - str);
			env_value = trim_quote(ptr_equal + 1);
			flag = ENV;
		}
		return (export_save_env(data, env_key, env_value, flag));
	}
	return (export_printerr(str));
}

int	minishell_export(t_data *data)
{
	t_token	*tree;
	int		return_value;

	if (!data->input->next)
		return (export_no_param(data));
	else
	{
		tree = data->input->next;
		while (tree)
		{
			return_value = export_with_param(data, tree);
			if (return_value < 0)
				return (return_value);
			tree = tree->next;
		}
	}
}
