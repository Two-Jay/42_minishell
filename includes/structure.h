/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:02:25 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/10 18:47:39 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

/*
	* Structures
*/
typedef struct s_input_process
{
	char	*scenv_ret;
	int		*qtrim_checker;
	char	*isbs_ret;
	char	**split_ret;
}	t_input_process;

typedef struct s_parser_env_bucket
{
	char	*srcp;
	int		now_ix;
	int		src_l;
	char	*envkey;
	int		key_l;
	char	*envval;
	int		value_l;
	char	*nbr_str;
	int		nbr_l;
}	t_eb;

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

typedef struct s_envlst
{
	char			*key;
	char			*value;
	t_env_state		env_state;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_data
{
	t_envlst		*envlst;
	t_token			*input;
	t_input_process	*ip;
	void			**malloc_queue;
	char			*homedir;
}	t_data;

typedef struct s_pipe
{
	int		index;
	int		max_index;
	int		fd_tmp;
	int		last_pid;
}	t_pipe;

#endif
