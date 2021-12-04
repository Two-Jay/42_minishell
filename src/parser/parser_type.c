/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 03:42:40 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 08:25:18 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_CMD(t_token *token)
{
	return (token->ix == 1 || (token->ix > 1 && token->prev->type == PIPE));
}

int is_contain_space_or_slash(t_token *token)
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
		&& is_contain_space_or_slash(token) == FALSE);
}

int is_filepath(t_token *token)
{
	return (is_redirection(token->prev->content, 0)
		|| (token->next && is_redirection(token->next->content, 0)));
}

t_state define_type_input_token(t_token *token)
{
	t_state ret;
 
	if (is_redirection(token->content, 0))
		ret = REDIRECT;
	else if (is_filepath(token))
		ret = FILEPATH;
	else if (is_CMD(token))
		ret = CMD;
	else if (is_flag(token))
		ret = FLAG;
	else if (is_pipe(token->content, 0))
		ret = PIPE;
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
