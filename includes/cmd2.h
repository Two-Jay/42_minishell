/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/20 23:10:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD2_H
# define CMD2_H

# include "minishell.h"

typedef struct s_pipe_arr
{
	char	**cmd;
	char	**flags;
	char	**str;
	char	**envp;
	int		idx_max;
	int		fd_tmp;
	int		redir_flag;
	int		fildes_opened;
}	t_pipe_arr;

# define PIPE_READ 0
# define PIPE_WRITE 1
# define LLMAX 9223372036854775807
# define REDIR_NONE 0
# define REDIR_RIGHT_ONE 1
# define REDIR_RIGHT_TWO 2

/*
	* Pipelines
*/
void		minishell_pipe(char *cmd[], char *flag[], char *str[], char *envp[], int redir_flag);
char		*pipe_getcmd(char *cmd, char *envp[]);
void		ft_free_char2d(char **arr);

/*
	* cd & pwd
*/
# define	CD_ERRNODIR "No such file or directory"
# define	CD_ERROPT "invalid option\ncd : usage: cd [dir]"
int			minishell_cd(t_data *data);
int			minishell_pwd(t_data *data);

/*
	* Export
*/
# define	EXPORT_ERRID "\': not a valid ident\ifier"
# define	EXPORT_ERROPT "invalid option\
\nexport: usage: export [name[=value] ...]"
int			minishell_export(t_data *data);
int			export_save_env(
				t_data *data,
				char *env_key,
				char *env_value,
				t_env_state flag);
int			export_with_param(t_data *data);
int			export_no_param(t_data *data);
char		*export_equal_check(char *str);
int			export_name_check(char *str, char *ptr_equal);

/*
	* Env
*/
# define	ENV_ERROPT 0
# define	ENV_ERRDIR 1
int			minishell_env(t_data *data);

/*
	* Unset
*/
# define	UNSET_ERRID "\': not a valid identifier"
int			minishell_unset(t_data *data);

/*
	* Exit
*/
# define	EXIT_ERRNUM ": numeric argument required"
# define	EXIT_ERRMANY "too many arguments"
void		minishell_exit(t_data *data);

/*
	* Utilities
*/
char		*trim_quote(char *str);
char		**trim_quote_and_parse(char *str);
char		*ft_strndup(char *str, int length);
char		*get_envname(char *str);
t_envlst	*find_env(char *envname, t_data *data);
int			builtin_error(
				t_data *data,
				char *value_str,
				char *error_str,
				int dollar_q);
int			check_flag(t_data *data);

#endif
