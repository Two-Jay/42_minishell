/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:38:19 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

char	*pwd_set_value(t_data *data)
{
	t_envlst	*node_pwd;
	char		*env_key;
	char		*env_value;

	node_pwd = find_env("PWD", data);
	if (!node_pwd)
	{
		env_key = ft_strdup("PWD");
		env_value = getcwd(0, 100);
		if (!env_value || export_save_env(data, env_key, env_value, ENV) < 0)
		{
			free(env_key);
			return (NULL);
		}
		node_pwd = find_env("PWD", data);
	}
	else
	{
		free(node_pwd->value);
		node_pwd->value = getcwd(0, 100);
		if (!node_pwd->value)
			return (NULL);
	}
	return (node_pwd->value);
}

int	minishell_pwd(t_data *data)
{
	char	*pwd;

	pwd = pwd_set_value(data);
	if (!pwd)
		return (-1);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	return (0);
}
