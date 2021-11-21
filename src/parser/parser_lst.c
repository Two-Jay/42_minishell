/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:12:08 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 19:58:15 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int assign_input_token_type(t_token *token)
{
    t_state ret;
 
    if (token->ix == 1 || (token->ix > 1 && token->prev->type == PIPE))
        ret = CMD;
    else if (token->prev->type == CMD && token->content[0] == '-')
        ret = FLAG;
    else if (ft_strequel(token->content, '|'))
        ret = PIPE;
    else if (check_redirection(token->content))
        ret = REDIRECT;
    else
        ret = STR;
    token->type = ret;
    return (0);
}

t_token *create_input_token(const char *str, int *ix)
{
    t_token *ret;

    ret = (t_token *)malloc(sizeof(t_token));
    if (!ret)
        return (NULL);
    ret->content = NULL;
    if (str && *str)
        ret->content = str;
    ret->ix = *ix;
    return (ret);
}