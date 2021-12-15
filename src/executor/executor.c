/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:39:47 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/16 01:37:20 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_if_pipe(t_data *data)
{
	t_token	*input;

	input = data->input->next;
	while (input)
	{
		if (input->type == PIPE)
			return (1);
		input = input->next;
	}
	return (0);
}

int	exec_builtin(t_data *data, t_token *input, int ofd)
{
	int	builtin_return;

	builtin_return = 0;
	while (input && (input->type == REDIRECT || input->type == FILEPATH))
		input = input->next;
	if (!input || input->type == PIPE)
		return (0);
	if (ft_strequel(input->content, "cd"))
		builtin_return = minishell_cd(data, input);
	else if (ft_strequel(input->content, "echo"))
		builtin_return = minishell_echo(input, ofd);
	else if (ft_strequel(input->content, "pwd"))
		builtin_return = minishell_pwd(input, ofd);
	else if (ft_strequel(input->content, "env"))
		builtin_return = minishell_env(data, input, ofd);
	else if (ft_strequel(input->content, "exit"))
		builtin_return = minishell_exit(input);
	else if (ft_strequel(input->content, "export"))
		builtin_return = minishell_export(data, input, ofd);
	else if (ft_strequel(input->content, "unset"))
		builtin_return = minishell_unset(data, input);
	g_dq = builtin_return;
	if (ofd != STDOUT_FILENO)
		close(ofd);
	return (builtin_return);
}

int	exec_program(t_data *data, t_token *input)
{
	char	*cmd_path;
	char	**exec_argv;
	char	**exec_envp;

	cmd_path = exec_getcmd(data, input->content);
	if (!cmd_path)
		exit(g_dq);
	exec_argv = pipe_insert_arr(input, cmd_path);
	exec_envp = exec_getenvp(data);
	if (!exec_argv || !exec_envp)
		exit(builtin_error("shell",
				ft_strjoin(input->content, EXEC_ERRPARSE), 1));
	execve(cmd_path, exec_argv, exec_envp);
	ft_free_char2d(exec_argv);
	ft_free_char2d(exec_envp);
	free(cmd_path);
	exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
}

static int	exec_dup_builtin(t_data *data, t_token *input)
{
	int		ofd;
	int		ifd;

	if (!if_builtin(input))
		return (EXEC_NOTBUILTIN);
	ofd = get_redir_ofd(input);
	if (ofd < 0)
		return (builtin_error("shell", ft_strdup(PIPE_ERR), 1));
	ifd = get_redir_ifd(input);
	if (ifd < 0)
		return (builtin_error("shell", ft_strdup(PIPE_ERR), 1));
	if (ifd != STDIN_FILENO)
		close(ifd);
	return (exec_builtin(data, input, ofd));
}

int	minishell_executor(t_data *data)
{
	int		builtin_return;
	int		exec_pid;
	int		status;
	t_token	*input_start;

	input_start = data->input->next;
	if (exec_if_pipe(data))
		return (minishell_pipe(data));
	builtin_return = exec_dup_builtin(data, input_start);
	if (builtin_return != EXEC_NOTBUILTIN)
		return (builtin_return);
	set_signal_handler_blocked_cmd();
	exec_pid = fork();
	if (!exec_pid)
	{
		exec_dup_ifd(input_start);
		exec_dup_ofd(input_start);
		exec_program(data, input_start);
	}
	else if (exec_pid < 0)
		return (builtin_error("shell", ft_strdup(EXEC_ERRFORK), 1));
	waitpid(exec_pid, &status, 0);
	g_dq = WEXITSTATUS(status);
	return (0);
}
