/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:34:23 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/19 14:48:11 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_no_param(t_data *data, int ofd)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	while (node_tmp)
	{
		if (node_tmp->env_state == ENV || node_tmp->env_state == EXPORT_ONLY)
		{
			ft_putstr_fd("declare -x ", ofd);
			ft_putstr_fd(node_tmp->key, ofd);
			if (node_tmp->env_state == ENV)
			{
				ft_putstr_fd("=\"", ofd);
				ft_putstr_fd(node_tmp->value, ofd);
				ft_putstr_fd("\"", ofd);
			}
			ft_putstr_fd("\n", ofd);
		}
		node_tmp = node_tmp->next;
	}
	return (0);
}

static int	export_traverse(t_data *data, t_token *input)
{
	char		*ptr_equal;
	char		*env_key;
	char		*env_value;
	t_env_state	flag;

	ptr_equal = env_equal_check(input->content);
	env_value = NULL;
	if (!env_name_check(input->content, ptr_equal))
		return (builtin_error(
				"shell: export", ft_strjoin(input->content, EXPORT_ERRID), 1));
	if (!ptr_equal)
	{
		env_key = ft_strdup(input->content);
		flag = EXPORT_ONLY;
	}
	else
	{
		env_key = ft_strndup(input->content, ptr_equal - input->content);
		env_value = ft_strdup(ptr_equal + 1);
		flag = ENV;
	}
	return (save_env(data, env_key, env_value, flag));
}

int	minishell_export(t_data *data, t_token *input, int ofd)
{
	int		return_value;
	int		argument_check;

	argument_check = check_argument(input);
	if (argument_check == FLAG_O)
		return (builtin_error("shell: export",
				ft_strjoin(input->next->content, EXPORT_ERROPT), 2));
	else if (argument_check == ARGUMENT_X)
		return (export_no_param(data, ofd));
	else
	{
		while (input && input->type != PIPE)
		{
			if (input->type == STR)
				return_value = export_traverse(data, input);
			input = input->next;
		}
	}
	return (return_value);
}
