/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:41 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 19:57:21 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	cd_move_directory(char *str)
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

void	minishell_cd(t_data *data)
{
	t_envlst	*node_pwd;
	char		*env_key;
	char		*env_value;
	int			return_value;

	return_value = cd_move_directory(data->input->next->content);
	if (return_value != 0)
		return (return_value);
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
	return (return_value);
}
