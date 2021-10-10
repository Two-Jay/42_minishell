/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:33:13 by jekim             #+#    #+#             */
/*   Updated: 2021/10/10 12:29:43 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef enum s_state
{
	NOT_PARSERED = 0,
	SCOLON,
	BUILTIN,
	REDIRECT,
	STRING,
}	t_state;

typedef struct s_token
{
	char			*contents;
	t_state			type;
	struct t_token	*left;
	struct t_token	*right;
}	t_token;

typedef struct s_tree
{
	struct t_token	*node;
	int				depth;
}	t_tree;

int parse_input(const char *input);

#endif