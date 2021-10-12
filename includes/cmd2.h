/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:40:00 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 13:48:11 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD2_H
# define CMD2_H

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
void		ft_free_char2d(char **arr);

/*
	* Environment Variables
*/
char		*get_env(char *str);
t_envlst	*find_env(char *envname, t_data *data);

#endif
