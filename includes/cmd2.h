/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/10 19:11:01 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

# define REDIR_NONE		0;
# define REDIR_SINGLE	1;
# define REDIR_DOUBLE	2;

typedef struct s_parsed_arr
{
	char	**cmd;
	char	**flags;
	char	**str;
	char	**envp;
}	t_parsed_arr;

typedef struct s_pipe_arr
{
	char	**cmd;
	char	**flags;
	char	**str;
	char	**envp;
	int		index;
	int		if_redir;
}	t_pipe_arr;

/*
	* Pipelines
*/
void	ft_free_char2d(char **arr);
<<<<<<< HEAD
void    exit_minishell_SUCC(void);
=======
char	**pipe_getcmd(char *cmd, char *flag, char *envp[]);
>>>>>>> 4cb456e ([minishell] UPDATE: 파이프 너무헷갈려요 살료~~)

#endif
