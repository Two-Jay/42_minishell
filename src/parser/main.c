/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 12:56:06 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	empty_input_checker(t_data *data)
{
	if (data->input->next == NULL)
		free(data->input);
	return (0);
}

int	free_ip(t_data *data, int errflag)
{
	int	ix;

	ix = 0;
	if (data->ip->scenv_ret)
		free(data->ip->scenv_ret);
	if (data->ip->isbs_ret)
		free(data->ip->isbs_ret);
	if (data->ip->split_ret)
	{
		while (data->ip->split_ret[ix])
			free(data->ip->split_ret[ix++]);
		free(data->ip->split_ret);
	}
	if (data->ip)
		free(data->ip);
	if (errflag == ERROR_OCCURED)
		return (ERROR_OCCURED);
	return (empty_input_checker(data));
}

char	*catch_lst_type(t_state state)
{
	if (state == CMD)
		return ("CMD\n");
	if (state == FLAG)
		return ("FLAG\n");
	if (state == PIPE)
		return ("PIPE\n");
	if (state == REDIRECT)
		return ("REDIRECT\n");
	if (state == FILEPATH)
		return ("FILEPATH\n");
	if (state == STR)
		return ("STR\n");
	return ("ERROR\n");
}

int	set_input_process_struct(t_data *data)
{
	data->ip = (t_input_process *)malloc(sizeof(t_input_process));
	if (!data->ip)
		return (ERROR_OCCURED);
	return (0);
}

int	parse_input_string(const char *str, t_data *data)
{
	if (check_isclosed(str))
		return (ERROR_OCCURED);
	if (set_input_process_struct(data)
		|| setup_and_check_env(str, data)
		|| insert_space_beside_spclcmd(data->ip->scenv_ret, data)
		|| split_by_chunk(data->ip->isbs_ret, data)
		|| build_input_token_lst(data->ip->split_ret, data)
		|| delete_nullish_token(data->input->next)
		|| assign_type_input_token_lst(data->input->next)
		|| guard_syntax_error(data->input->next))
		return (free_ip(data, ERROR_OCCURED));
	return (free_ip(data, 0));
}
