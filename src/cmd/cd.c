/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:41 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/06 02:46:51 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_no_argument(t_data *data)
{
	if (!find_env("HOME", data) || chdir(find_env("HOME", data)->value) < 0)
		return (CD_HOMENOTSET);
	return (CD_SUCCESS);
}

static int	cd_move_directory(t_data *data)
{
	char	*str;

	str = data->input->next->content;
	if (ft_strequel(str, "~"))
	{
		if (!find_env("HOME", data) || chdir(find_env("HOME", data)->value) < 0)
			return (CD_HOMENOTSET);
	}
	else if (ft_strequel(str, "-"))
	{
		if (!find_env("OLDPWD", data)
			|| chdir(find_env("OLDPWD", data)->value) < 0)
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

int	minishell_cd(t_data *data, t_token *input)
{
	int		result_movedir;

	input = input->next;
	while (input->type == REDIRECT || input->type == FILEPATH)
		input = input->next;
	if (check_flag(input))
		return (builtin_error(
				"cd", ft_strjoin(input->content, CD_ERROPT), 1));
	if (!input || input->type == PIPE)
		result_movedir = cd_no_argument(data);
	else
		result_movedir = cd_move_directory(data);
	if (result_movedir == CD_PWDNOTSET)
		return (builtin_error("cd", ft_strdup(CD_ERROLD), 1));
	if (result_movedir == CD_HOMENOTSET)
		return (builtin_error("cd", ft_strdup(CD_ERRHOME), 1));
	if (result_movedir == CD_FAILED)
		return (builtin_error("cd",
				ft_strjoin(input->next->content, CD_ERRNODIR), 1));
	if (cd_add_pwd(data) < 0)
		return (builtin_error("cd", ft_strdup(strerror(errno)), 1));
	return (0);
}
