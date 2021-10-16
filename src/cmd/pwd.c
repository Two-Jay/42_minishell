/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:59:33 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 20:02:39 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	minishell_pwd(t_data *data)
{
	t_envlst	*node_pwd;
	char		*env_key;
	char		*env_value;

	node_pwd = find_env("PWD", data);
	if (!node_pwd)
	{
		env_key = ft_strdup("PWD");
		env_value = getcwd(0, 100);
		export_save_env(data, env_key, env_value);
		node_pwd = find_env("PWD", data);
	}
	else
	{
		free(node_pwd->value);
		node_pwd->value = getcwd(0, 100);
	}
	write(1, node_pwd->value, ft_strlen(node_pwd->value));
	write(1, "\n", 1);
	return (0);
}
