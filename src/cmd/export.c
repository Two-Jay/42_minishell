/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:34:23 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 20:23:56 by jiychoi          ###   ########.fr       */
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

static int	export_no_param(t_data *data)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	if (!node_tmp)
		return (-1);
	while (node_tmp->next != NULL)
	{
		write(1, node_tmp->key, ft_strlen(node_tmp->key));
		write(1, "=\"", 2);
		write(1, node_tmp->value, ft_strlen(node_tmp->value));
		write(1, "\"\n", 2);
		node_tmp = node_tmp->next;
	}
	return (0);
}

static int	export_save_env(t_data *data, char *env_key, char *env_value)
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

static int	export_with_param(t_data *data)
{
	char		*str;
	char		*ptr_equal;
	char		*env_key;
	char		*env_value;
	t_envlst	*node_found;

	str = data->input->next->contents;
	ptr_equal = export_equal_check(str);
	env_value = 0;
	if (export_name_check(str, ptr_equal))
	{
		if (!ptr_equal)
			env_key = ft_strdup(str);
		else
		{
			env_key = ft_strndup(str, ptr_equal - str);
			env_value = trim_quote(ptr_equal + 1);
		}
		return (export_save_env(data, env_key, env_value));
	}
	return (export_printerr(str));
}

int	minishell_export(t_data *data)
{
	if (!data->input->next)
		return (export_no_param(data));
	else
		return (export_with_param(data));
}
