/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 14:01:30 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_ip(t_input_process *ip, int errflag)
{
	int	ix;

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

void	print_token(t_data *data)
{
	int		lst_len;
	t_token	*lst;

	lst_len = 0;
	lst = data->input->next;
	while (lst)
	{
		trs(lst->content);
		tri(lst->ix);
		trs(catch_lst_type(lst->type));
		lst = lst->next;
		lst_len++;
	}
	tri(lst_len);
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
		return (ft_putstr_fd_error(ERRM_UNCLOSED_QUOTE, 2, ERROR_OCCURED));
	if (set_input_process_struct(data)
		|| setup_and_check_env(str, data)
		|| insert_space_beside_spclcmd(data->ip->scenv_ret, data)
		|| split_by_chunk(data->ip->isbs_ret, data)
		|| build_input_token_lst(data->ip->split_ret, data)
		|| delete_nullish_token(data->input->next)
		|| assign_type_input_token_lst(data->input->next))
		return (free_ip(data->ip, ERROR_OCCURED));
	print_token(data);
	return (free_ip(data->ip, 0));
}
