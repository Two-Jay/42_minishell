/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:41 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/17 18:32:21 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	cd_move_directory(char *str)
{
	char	*path_curr;
	char	*path_temp;
	char	*path_absol;
	int		return_value;

	if (*str == '/')
		if (chdir(str) < 0)
			return (minishell_perror("cd: ", -1, 1));
	else
	{
		path_curr = getcwd(0, 100);
		path_temp = ft_strjoin(path_curr, "/");
		path_absol = ft_strjoin(path_temp, str);
		return_value = chdir(path_absol);
		free(path_curr);
		free(path_temp);
		free(path_absol);
		if (return_value < 0)
			return (minishell_perror("cd: ", -1, 1));
	}
	return (0);
}

static int	cd_add_oldpwd(t_data *data, t_envlst *node_pwd)
{
	t_envlst	*node_oldpwd;
	char		*env_key;
	char		*env_value;

	node_oldpwd = find_env("OLDPWD", data);
	if (!node_oldpwd)
	{
		env_key = ft_strdup("OLDPWD");
		if (!env_key)
			return (-1);
		env_value = node_pwd->value;
		if (export_save_env(data, env_key, env_value, ENV) < 0)
			return (-1);
		node_oldpwd = find_env("OLDPWD", data);
	}
	else
		free(node_oldpwd->value);
	node_oldpwd->value = node_pwd->value;
	node_pwd->value = getcwd(0, 10);
	return (0);
}

static int	cd_add_pwd(t_data *data)
{
	t_envlst	*node_pwd;
	char		*env_key;
	char		*env_value;

	node_pwd = find_env("PWD", data);
	if (!node_pwd)
	{
		env_key = ft_strdup("PWD");
		if (!env_key)
			return (-1);
		env_value = getcwd(0, 10);
		if (export_save_env(data, env_key, env_value, ENV) < 0)
			return (-1);
		node_pwd = find_env("PWD", data);
	}
	if (cd_add_oldpwd(data, node_pwd) < 0)
		return (-1);
	return (0);
}

int	minishell_cd(t_data *data)
{
	int			return_value;

	return_value = cd_move_directory(data->input->next->content);
	if (return_value != 0)
		return (return_value);
	if (cd_add_pwd(data) < 0)
		return_value = -1;
	return (return_value);
}
