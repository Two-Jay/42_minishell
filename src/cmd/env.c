/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:26:51 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	env_no_param(t_data *data, t_token *input)
{
	t_envlst	*node_tmp;
	int			fd;

	node_tmp = data->envlst;
	fd = get_redir_fd(input);
	while (node_tmp)
	{
		if (node_tmp->env_state == ENV)
		{
			ft_putstr_fd(node_tmp->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(node_tmp->value, fd);
			ft_putstr_fd("\n", fd);
		}
		node_tmp = node_tmp->next;
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

int	minishell_env(t_data *data, t_token *input)
{
	if (input->next
		&& (input->next->type != REDIRECT && input->next->type != PIPE))
		return (builtin_error("env",
				ft_strjoin(input->next->content, ENV_ERROPT), 1));
	return (env_no_param(data, input->next));
}
