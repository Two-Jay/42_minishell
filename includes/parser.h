/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:33:13 by jekim             #+#    #+#             */
/*   Updated: 2021/10/12 21:49:12 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef enum s_state
{
	NOT_PARSERED = 0,
	BUILTIN,
	REDIRECT,
	STRING,
}	t_state;

typedef struct s_token
{
	char			*contents;
	int				idx;
	t_state			type;
	struct t_token	*prev;
	struct t_token	*next;
}	t_token;

int		parse_input(const char *input);
int		preprocess_input(const char *input, char *buf);
int		is_closed(const char *input);
void	is_quoted(const char cha, int *flag);
void	is_inquote(const char cha, int *flag);

#endif
