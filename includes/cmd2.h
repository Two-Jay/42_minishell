/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/14 20:50:04 by jiychoi          ###   ########.fr       */
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
}	t_pipe_arr;

# define PIPE_READ 0
# define PIPE_WRITE 1
# define LLMAX 9223372036854775807

/*
	* Pipelines
*/
char		*pipe_getcmd(char *cmd, char *envp[]);
void		ft_free_char2d(char **arr);

/*
	* Environment Variables
*/
char		*get_env(char *envname, t_data *data);
t_envlst	*find_env(char *envname, t_data *data);

/*
	* Exit
*/
int			minishell_perror(char *cmd, int err, int exit_status);

#endif
