/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 20:13:27 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structure.h"
# include "headers.h"

# define PSR_ERRHEAD "shell "
# define PSR_ERRSYNTAX "syntax error near unexpected token "

/*
** root setting functions
*/
int			init_env(char **envp, t_data *data);

/*
** readline;
*/
char		*readinput(char *prompt);

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
int			check_isclosed(const char *input);
int			parse_input_string(const char *str, t_data *data);
int			setup_and_check_env(const char *str, t_data *data);
char		*quote_trim(char *str, t_data *data);
int			delete_nullish_token(t_token *token);
int			replace_env_in_input(char *dst, const char *str, t_data *data);
int			insert_space_beside_spclcmd(const char *str, t_data *data);
int			split_by_chunk(const char *str, t_data *data);
int			build_input_token_lst(char **split_ret, t_data *data);
int			assign_type_input_token_lst(t_token *token);
int			guard_syntax_error(t_token *token);

/*
**		syntax error sub-functions
*/
int			check_isclosed(const char *input);
int			print_syntax_error(char *cmd, char *error_str);

/*
**		replace_env sub-functions
*/
char		*append_nbr(char *src, int *now_ix, int target);
char		*append_env(char *src, int *now_ix, t_data *data);
int			save_target(t_eb *eb, int target);
t_eb		*set_envbucket(char *src, int now_ix);
char		*return_append_env(t_eb	*eb, char *ret);

/*
**		trim-quote sub-functions
*/
int			check_opener_quote(char *ret, int ix, int *qf);
int			check_closer_quote(char *ret, int ix, int *qf);
char		*free_int_checker(t_data *data);
void		check_into_checker_arr(int *arr, int startp, int endp);
int			set_int_checker(t_data *data, int length);

/*
**		condition checker
*/
int			is_redirection(const char *str, int ix);
int			is_pipe(const char *str, int ix);
int			is_pipe_redirection_middle_str(const char *str, int ix);
int			is_pipe_middle_str(const char *str, int ix);
int			is_redirection_middle_str(const char *str, int ix);
int			is_pipe_redirection(const char *str, int ix);
int			is_quotation(const char *str, int ix);
int			is_double_quote(const char *str, int ix);
int			is_single_quote(const char *str, int ix);
void		is_inquoted(const char *str, int ix, int *flag);
int			is_start_charset_envkey(char c);
int			is_end_envkey(const char *src, int ix);
int			is_CMD(int cmd_flag);
int			is_contain_space_or_dash(t_token *token);
int			is_flag(t_token *token);
int			is_filepath(t_token *token);
int			is_quoted_input(char *str);
int			is_end_quotation(const char *str, int ix, int flag);
int			is_word_condition(const char *str, int ix, int flag);
int			check_split_condition(const char *str, int ix, int flag);
int			is_envflag(const char *str, int ix, int flag);
int			is_dq(const char *str, int ix, int flag);
int			is_env_print_process(const char *str, int ix, int flag);
int			is_start_charset_envkey(char c);
int			is_end_envkey(const char *src, int ix);

#endif
