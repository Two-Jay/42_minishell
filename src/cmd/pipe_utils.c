/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 11:39:45 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 00:58:47 by jiychoi          ###   ########.fr       */
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

static int	pipe_count_param(t_token *input)
{
	int	count;

	count = 0;
	while (input->type != PIPE && input->type != REDIRECT && input)
	{
		input = input->next;
		count++;
	}
	return (count);
}

char	**pipe_insert_arr(t_token *input)
{
	char	**arr_return;
	int		index;

	index = 0;
	*exec_argv[index++] = input->content;
	if (input->next->type == FLAG)
		*exec_argv[index++] = input->next->content;
	if (input->next->next->)
	else
	{
		if (input->next->type == STR)
			*exec_argv[1] == input->next->next->content;

	}
}
