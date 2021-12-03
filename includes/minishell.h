/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/12/03 23:48:11 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "cmd.h"

# define INTRO "Nyamnyam_shell.dev '-'//"
# define TRUE 0
# define FALSE 1
# define ERROR_OCCURED 1

# define trs(x...) { printf("[%s:%d] %s = ", __func__, __LINE__, #x); printf("%s\n", x); }
# define trc(x...) { printf("[%s:%d] %s = ", __func__, __LINE__, #x); printf("%c\n", x); }
# define tri(x...) { printf("[%s:%d] %s = ", __func__, __LINE__, #x); printf("%d\n", x); }
# define trp(x...) { printf("[%s:%d] %s = ", __func__, __LINE__, #x); printf("%p\n", x); }

typedef enum s_state
{
	CMD = 0,
	FLAG,
	PIPE,
	REDIRECT,
	FILEPATH,
	STR
}	t_state;


typedef struct s_token
{
	char			*content;
	int				ix;
	t_state			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum s_env_state
{
	ENV = 0,
	EXPORT_ONLY,
	TEMP_ENV,
}	t_env_state;

typedef struct	s_envlst
{
	char			*key;
	char			*value;
	t_env_state		env_state;
	struct s_envlst	*next;
}	t_envlst;

typedef struct	input_process
{
	char 	*scenv_ret;
	int		*qtrim_checker;
	char 	*qtrim_ret;
	char 	*isbs_ret;
	char 	**split_ret;
}	t_input_process;

typedef struct	s_data
{
	t_envlst	*envlst;
	t_token		*input;
	t_input_process *ip;
	int			dq;
	void		**malloc_queue;
	char		*homedir;
}	t_data;

typedef struct	s_parser_env_bucket
{
	char	*srcp;
	int		now_ix;
	int		src_l;
	char	*envkey;
	int		key_l;
	char	*envval;
	int		value_l;
	char	*errno_str;
	int		errno_l;
}	t_eb;

extern int errno;

/*
** root setting functions
*/
int		init_env(char **envp, t_data *data);

/*
** util functions
*/
int		print_intro(int argc, char **argv);
int		indexOf_char(const char *str, char target);
int		is_pipe_redirection(const char *str, int ix);
char	*get_env(char *envname, t_data *data);
t_envlst	*find_env(char *envname, t_data *data);
char	*ft_strndup(char *str, int length);
char	*ft_strncpy(char *s1, const char *s2, size_t n);

/*
**		parsing functions
*/
int		check_isclosed(const char *input);
int		parse_input_string(const char *str, t_data *data);
int		setup_and_check_env(const char *str, t_data *data);
int 	quote_trim(char *str, t_data *data);
int		replace_env_in_input(char *dst, const char *str, t_data *data);
int		insert_space_beside_spclcmd(const char *str, t_data *data);
int		split_by_chunk(const char *str, t_data *data);
int		build_input_token_lst(char **split_ret, t_data *data);
int		assign_type_input_token_lst(t_token *token);


/*
**		parsing util functions
*/
void	is_inquoted(const char *str, int ix, int *flag);
int		is_double_quote(const char *str, int ix);
int		is_single_quote(const char *str, int ix);
int		is_quotation(const char *str, int ix);
int		ft_putstr_fd_error(char *str, int fd, int error_code);

#endif
