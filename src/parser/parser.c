/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/11/24 21:22:01 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		|| insert_space_beside_spclcmd(str, data)
		|| split_by_chunk(data->ip->isbs_ret, data)
		|| build_input_token_lst(data->ip->split_ret, data))
		return (ERROR_OCCURED);
	return (0);
}