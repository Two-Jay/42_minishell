/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:41 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 00:48:22 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	cd_move_directory(t_data *data)
{
	char	*str;

	str = data->input->next;
	if (ft_strequel(str, "~"))
		if (chdir(find_env("HOME", data)) < 0)
			return (-1);
	else if (ft_strequel(str, "-"))
		if (chdir(find_env("OLDPWD", data)) < 0)
			return (-1);
	else
		if (chdir(str) < 0)
			return (-1);
	return (0);
}

int	minishell_cd(t_data *data)
{
	t_token	*input;

	input = data->input;
	if (!input->next)
		return (0);
	if (check_flag(input))
		return (builtin_error("cd",
				ft_strjoin(input->next->content, CD_ERROPT), 1));
	if (input->next->type == PIPE || input->next->type == REDIRECT)
		return (0);
	if (cd_move_directory(data) < 0)
		return (builtin_error("cd",
				ft_strjoin(input->next->content, CD_ERRNODIR), 1));
	if (cd_add_env(data) < 0)
		return (builtin_error("cd",
				ft_strdup(strerror(errno)), 1));
	return (0);
}
