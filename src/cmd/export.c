/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 13:34:23 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	export_no_param(t_data *data, t_token *input)
{
	t_envlst	*node_tmp;
	int			fd;

	node_tmp = data->envlst;
	fd = get_redir_fd(input);
	while (node_tmp)
	{
		if (node_tmp->env_state == ENV || node_tmp->env_state == EXPORT_ONLY)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(node_tmp->key, fd);
			if (node_tmp->env_state == ENV)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(node_tmp->value, fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		node_tmp = node_tmp->next;
	}
	if (fd != STDOUT_FILENO)
		close(fd);
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

int	minishell_export(t_data *data, t_token *input)
{
	int		return_value;

	if (check_flag(input))
		return (builtin_error("shell: export",
				ft_strjoin(input->next->content, EXPORT_ERROPT), 2));
	return_value = 0;
	input = input->next;
	if (!input || input->type != STR)
		return (export_no_param(data, input));
	while (input && input->type == STR)
	{
		return_value = export_traverse(data, input);
		input = input->next;
	}
	return (return_value);
}
