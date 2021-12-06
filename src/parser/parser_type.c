/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 03:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 20:57:38 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_CMD(int cmd_flag)
{
	return (cmd_flag == 0);
}

int is_contain_space_or_dash(t_token *token)
{
	int ix;

	ix = 0;
	while (token->content[ix])
	{
		if (ft_isspace(token->content[ix]))
			return (TRUE);
		if (ix > 0 && token->content[ix] == '-')
			return (TRUE);
		ix++;
	}
	return (FALSE);
}

int is_flag(t_token *token)
{
	return (token->prev->type == CMD
		&& token->content[0] == '-'
		&& ft_strlen(token->content) > 1
		&& is_contain_space_or_dash(token) == FALSE);
}

int is_filepath(t_token *token)
{
	return (is_redirection(token->prev->content, 0));
}

t_state define_type_input_token(t_token *token, int cmd_flag)
{
	t_state ret;
 
	if (is_redirection(token->content, 0))
		ret = REDIRECT;
	else if (is_filepath(token))
		ret = FILEPATH;
	else if (is_pipe(token->content, 0))
		ret = PIPE;
	else if (is_CMD(cmd_flag))
		ret = CMD;
	else if (is_flag(token))
		ret = FLAG;
	else
		ret = STR;
	return (ret);
}

int check_cmd_inline(t_token *token)
{	
	return (token->type == CMD);
}

int check_pipe_to_init_condition(t_token *token)
{
	return (token->type == PIPE);
}

int assign_type_input_token_lst(t_token *token)
{
	t_token *lst;
	int		cmd_flag;

	lst = token;
	cmd_flag = 0;
	while (lst)
	{
		lst->type = define_type_input_token(lst, cmd_flag);
		if (check_cmd_inline(lst))
			cmd_flag = 1;
		if (check_pipe_to_init_condition(lst))
			cmd_flag = 0;
		lst = lst->next;
	}
	return (0);
}
