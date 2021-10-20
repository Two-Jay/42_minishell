/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:26:51 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/21 01:43:39 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	env_print_error(t_data *data, int env_errflag)
{
	if (env_errflag == ENV_ERRDIR)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(data->input->next->content, 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else if (env_errflag == ENV_ERROPT)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putstr_fd(*data->input->next->content, 2);
		ft_putstr_fd("\nusage: env\n", 2);
	}
	// $? 세팅: 1
	return (-1);
}

static int	env_no_param(t_data *data)
{
	t_envlst	*node_tmp;

	node_tmp = data->envlst;
	if (!node_tmp)
		return (-1);
	while (node_tmp)
	{
		if (node_tmp->env_state == ENV)
		{
			write(1, node_tmp->key, ft_strlen(node_tmp->key));
			write(1, "=", 1);
			write(1, node_tmp->value, ft_strlen(node_tmp->value));
			write(1, "\n", 1);
		}
		node_tmp = node_tmp->next;
	}
	return (0);
}

int	minishell_env(t_data *data)
{
	if (check_flag(data))
		return (env_print_error(data, ENV_ERROPT));
	if (env_no_param(data) < 0)
		return (env_print_error(data, ENV_ERROPT));
	return (0);
}
