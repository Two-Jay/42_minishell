/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:09:01 by jekim             #+#    #+#             */
/*   Updated: 2021/10/17 15:02:12 by jekim            ###   ########seoul.kr  */
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
	NOT_PARSERED = 0,
	BUILTIN,
	REDIRECT,
	SQUOTE_STRING,
	NQUOTE_STRING,
	NON_QUOTE_STRING,
}	t_state;

typedef enum s_env_state
{
	ENV = 0,
	EXPORT_ONLY,
	TEMP_ENV,
}	t_env_state;

typedef struct s_token
{
	char			*content;
	int				idx;
	t_state			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_envlst
{
	char			*key;
	char			*value;
	t_env_state		env_state;
	struct s_envlst	*next;
}	t_envlst;

typedef struct	s_data
{
	t_envlst	*envlst;
	t_token		*input;
	void		*malloc_queue;
	char		*homedir;
}	t_data;

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
int		is_pipe_redirection(const char *target, int idx);
char	*get_env(char *envname, t_data *data);
t_envlst	*find_env(char *envname, t_data *data);

/*
**		parsing functions
*/
int		parse_input(const char *input, t_data *data);
char	*preprocess_input(const char *input);
char	*parse_env(char *buf, t_data *data);
char	**tokenize_input(char *buf, t_data *data);

/*
**		parser_utils functions
*/
int		is_closed(const char *input);
void	is_quoted(const char cha, int *flag);
void	is_inquote(const char cha, int *flag);
int		is_envname_charset(char cha);

#endif
