/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:39:47 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 22:16:42 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

/*
static int	exec_if_pipe(t_data *data)
{
	t_token	*input;

	input = data->input;
	while (input)
	{
		if (input->type == PIPE)
			return (1);
		input = input->next;
	}
	return (0);
}
int	exec_builtin(t_data *data)
{

}

int	exec_program(t_data *data)
{

}
*/

int	executor(t_token *input, char *envp[])
{
	char	*cmd_path;
	char	**exec_argv;

	cmd_path = getcmd(input->content, envp);
	if (!cmd_path)
		exit(builtin_error(
				"shell", ft_strjoin(input->content, EXEC_ERRNOCMD), 127));
	exec_argv = pipe_insert_arr(input, cmd_path);
	if (!exec_argv)
		exit(builtin_error(
				"shell", ft_strjoin(input->content, EXEC_ERRPARSE), 1));
	execve(cmd_path, exec_argv, envp);
	ft_free_char2d(exec_argv);
	free(cmd_path);
	exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
}

/*
void	exec_pipe(t_data *data, char *envp[])
{

}
*/
