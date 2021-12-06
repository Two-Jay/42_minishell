/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:39:45 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/06 01:25:58 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_count_cmd(t_token *input)
{
	int	cmd_len;

	cmd_len = 0;
	while (input)
	{
		if (input->type == CMD)
			cmd_len++;
		input = input->next;
	}
	return (cmd_len);
}

static int	pipe_count_param(t_token *input)
{
	int	count;

	count = 0;
	while (input && input->type != PIPE && input->type != REDIRECT)
	{
		input = input->next;
		count++;
	}
	return (count);
}

char	**pipe_insert_arr(t_token *input, char *cmd_path)
{
	char	**arr_return;
	int		index;
	int		param_cnt;

	param_cnt = pipe_count_param(input);
	arr_return = malloc(sizeof(char *) * (param_cnt + 1));
	if (!arr_return)
		return (NULL);
	index = 0;
	while (index < param_cnt)
	{
		arr_return[index++] = input->content;
		input = input->next;
	}
	arr_return[0] = cmd_path;
	arr_return[index] = 0;
	return (arr_return);
}

void	pipe_dup_ifd(t_token *input, t_pipe *struct_pipe)
{
	int	ifd;

	ifd = get_redir_ifd(input->next);
	if (dup2(struct_pipe->fd_tmp, STDIN_FILENO) < 0)
		exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
	if (ifd != STDIN_FILENO)
	{
		if (dup2(ifd, STDIN_FILENO) < 0)
			exit(builtin_error("shell", ft_strdup(PIPE_ERR), 1));
		close(ifd);
	}
}

void	pipe_dup_ofd(t_token *input, t_pipe *struct_pipe, int fd[2])
{
	int	ofd;

	ofd = get_redir_ofd(input->next);
	if (struct_pipe->index + 1 < struct_pipe->max_index)
		if (dup2(fd[PIPE_WRITE], STDOUT_FILENO) < 0)
			exit(builtin_error("pipe", ft_strdup(PIPE_ERR), 1));
	if (ofd != STDOUT_FILENO)
	{
		if (dup2(ofd, STDOUT_FILENO) < 0)
			exit(builtin_error("shell", ft_strdup(PIPE_ERR), 1));
		close(ofd);
	}
}
