/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 11:35:40 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structure.h"
# include "headers.h"

# define PSR_ERRSYNTAX "syntax error near unexpected token "
# define DQ_ERRSYNTAX 258

/*
** root setting functions
*/
int			init_env(char **envp, t_data *data);

/*
** util functions
*/
int			print_intro(int argc, char **argv);
int			indexOf_char(const char *str, char target);
int			is_pipe_redirection(const char *str, int ix);
char		*get_env(char *envname, t_data *data);
t_envlst	*find_env(char *envname, t_data *data);
char		*ft_strndup(char *str, int length);
char		*ft_strncpy(char *s1, const char *s2, size_t n);

/*
**		parsing functions
*/
int			check_isclosed(const char *input, t_data *data);
int			parse_input_string(const char *str, t_data *data);
int			setup_and_check_env(const char *str, t_data *data);
char		*quote_trim(char *str, t_data *data);
int			delete_nullish_token(t_token *token);
int			replace_env_in_input(char *dst, const char *str, t_data *data);
int			insert_space_beside_spclcmd(const char *str, t_data *data);
int			split_by_chunk(const char *str, t_data *data);
int			build_input_token_lst(char **split_ret, t_data *data);
int			assign_type_input_token_lst(t_token *token);
int         guard_syntax_error(t_token *token, t_data *data);

/*
**		parsing util functions
*/
int         print_syntax_error(char *cmd,
                char *error_str, char *error_target, t_data *data);
void		is_inquoted(const char *str, int ix, int *flag);
int			is_double_quote(const char *str, int ix);
int			is_single_quote(const char *str, int ix);
int			is_quotation(const char *str, int ix);
int			is_redirection(const char *str, int ix);
int			is_pipe(const char *str, int ix);

#endif
