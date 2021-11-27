/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:39:45 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 11:57:09 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static int	pipe_count_cmd(t_token *input)
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

t_pipe	*pipe_struct(t_token *input, char *envp[])
{
	t_pipe	*struct_pipe;

	struct_pipe = malloc(sizeof(t_pipe));
	if (!struct_pipe)
		return (NULL);
	struct_pipe->index = 0;
	struct_pipe->max_index = pipe_count_cmd(input);
	struct_pipe->fd_tmp = STDIN_FILENO;
	struct_pipe->envp = envp;
	return (struct_pipe);
}

char	**pipe_insert_arr(t_token *input, t_pipe *struct_pipe, char *cmd_path)
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
