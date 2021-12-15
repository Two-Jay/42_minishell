/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:30:17 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:26:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_envfile(char **envp)
{
	int	ix;
	int	len;
	int	fd;
	int	write_checker;

	ix = -1;
	len = 0;
	fd = open("./envrc", O_RDWR, S_IWUSR | S_IRUSR);
	if (!fd)
		return ;
	while (envp[++ix])
	{
		len = ft_strlen(envp[ix]);
		write_checker = write(fd, envp[ix], len);
		write(fd, "\n", 1);
	}
	close(fd);
}

static t_envlst	*create_node_envlst(char *env_line)
{
	int			len;
	int			equel_idx;
	t_envlst	*tmp;

	tmp = (t_envlst *)ft_calloc(sizeof(t_envlst), 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	len = ft_strlen(env_line);
	equel_idx = indexOf_char(env_line, '=');
	tmp->key = ft_substr(env_line, 0, equel_idx);
	tmp->value = ft_substr(env_line, equel_idx + 1, len - equel_idx);
	return (tmp);
}

static int	get_envlen(char **envp)
{
	int	ix;

	ix = -1;
	while (envp[++ix])
		;
	return (ix);
}

static int	set_envlst(char **envp, int fd, t_data *data)
{
	int			ix;
	int			envlen;
	char		*buf;
	t_envlst	*nptr;

	ix = 0;
	nptr = NULL;
	envlen = get_envlen(envp);
	if (fd == -1)
		fd = open("./envrc", O_RDWR, S_IWUSR | S_IRUSR);
	ft_strgnl(fd, &buf);
	data->envlst = create_node_envlst(buf);
	nptr = data->envlst;
	free(buf);
	while (ix < envlen - 1)
	{
		ft_strgnl(fd, &buf);
		nptr->next = create_node_envlst(buf);
		free(buf);
		nptr = nptr->next;
		ix++;
	}
	nptr->next = NULL;
	return (0);
}

int	init_env(char **envp, t_data *data)
{
	int	envfd;

	envfd = open("./envrc", O_RDONLY | O_CREAT, S_IWUSR | S_IRUSR);
	if (envfd != -1)
		set_envfile(envp);
	set_envlst(envp, envfd, data);
	return (0);
}
