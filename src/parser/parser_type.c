/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 03:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 06:13:19 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_CMD(t_token *token)
{
	return (token->ix == 1 || (token->ix > 1 && token->prev->type == PIPE));
}

int is_flag(t_token *token)
{
	return (token->prev->type == CMD
		&& ((is_quotation(token->content, 0) && token->content[1] == '-')
		|| token->content[0] == '-'));
}

/*
** i leave it because i don't know the condition....;
*/
int is_filepath(t_token *token)
{
	(void)token;
	return (0);
}

t_state define_type_input_token(t_token *token)
{
	t_state ret;
 
	trs(token->content);
	if (is_redirection(token->content, 0))
		ret = REDIRECT;
	else if (is_CMD(token))
		ret = CMD;
	else if (is_flag(token))
		ret = FLAG;
	else if (is_pipe(token->content, 0))
		ret = PIPE;
	else if (is_filepath(token))
		ret = FILEPATH;
	else
		ret = STR;
	return (ret);
}

int assign_type_input_token_lst(t_token *token)
{
	t_token *lst;

	lst = token;
	while (lst)
	{
		lst->type = define_type_input_token(lst);
		lst = lst->next;
	}
	return (0);
}
