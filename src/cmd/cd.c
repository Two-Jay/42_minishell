/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:41 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 17:29:26 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	cd_move_directory(t_data *data)
{
	char	*str;

	str = data->input->next->content;
	if (ft_strequel(str, "~"))
	{
		if (chdir(find_env("HOME", data)->value) < 0)
			return (CD_HOMENOTSET);
	}
	else if (ft_strequel(str, "-"))
	{
		if (chdir(find_env("OLDPWD", data)->value) < 0)
			return (CD_PWDNOTSET);
	}
	else
	{
		if (chdir(str) < 0)
			return (CD_FAILED);
	}
	return (CD_SUCCESS);
}

static int	cd_add_pwd(t_data *data)
{
	char		*env_old_value;
	char		*env_value;

	env_old_value = get_env("PWD", data);
	env_value = getcwd(0, 10);
	if (!env_value)
	{
		free(env_old_value);
		return (-1);
	}
	if (!env_old_value)
		save_env(data, ft_strdup("PWD"), env_value, ENV);
	free(env_old_value);
	env_old_value = get_env("PWD", data);
	save_env(data, ft_strdup("OLDPWD"), env_old_value, ENV);
	return (save_env(data, ft_strdup("PWD"), env_value, ENV));
}

int	minishell_cd(t_data *data)
{
	t_token	*input;
	int		result_movedir;

	input = data->input;
	if (!input->next)
		return (0);
	if (check_flag(input))
		return (builtin_error(data, "cd",
				ft_strjoin(input->next->content, CD_ERROPT), 1));
	if (input->next->type == PIPE || input->next->type == REDIRECT)
		return (0);
	result_movedir = cd_move_directory(data);
	if (result_movedir == CD_PWDNOTSET)
		return (builtin_error(data, "cd", ft_strdup(CD_ERROLD), 1));
	if (result_movedir == CD_HOMENOTSET)
		return (builtin_error(data, "cd", ft_strdup(CD_ERRHOME), 1));
	if (result_movedir == CD_FAILED)
		return (builtin_error(data, "cd",
				ft_strjoin(input->next->content, CD_ERRNODIR), 1));
	if (cd_add_pwd(data) < 0)
		return (builtin_error(data, "cd",
				ft_strdup(strerror(errno)), 1));
	return (0);
}
