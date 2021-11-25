/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/11/25 15:06:01 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int free_ip(t_input_process *ip, int errflag)
{
	int ix;

	ix = -1;
	if (ip->scenv_ret)
		free(ip->scenv_ret);
	if (ip->isbs_ret)
		free(ip->isbs_ret);
	if (ip->split_ret)
	{
		while (ip->split_ret[++ix])
			free(ip->split_ret[ix]);
		free(ip->split_ret);
	}
	if (errflag == ERROR_OCCURED)
		return (ERROR_OCCURED);
	return (0);
}

int set_input_process_struct(t_data *data)
{
	data->ip = (t_input_process *)malloc(sizeof(t_input_process));
	if (!data->ip)
		return (ERROR_OCCURED);
	return (0);
}

int parse_input_string(const char *str, t_data *data)
{
	if (set_input_process_struct(data)
		|| setup_and_check_env(data->ip->scenv_ret, str, data)
		|| insert_space_beside_spclcmd(data->ip->scenv_ret, data)
		|| split_by_chunk(data->ip->isbs_ret, data)
		|| build_input_token_lst(data->ip->split_ret, data))
		return (free_ip(data->ip, ERROR_OCCURED));
	return (free_ip(data->ip, 0));
}