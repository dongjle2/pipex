/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:38:16 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/17 01:35:59 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>

void	pipeline(t_pids *pids, t_input *input, t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < input->num_cmds)
	{
		pids->arr[++pids->idx] = fork();
		if (pids->arr[pids->idx] == 0)
			exec_cmd(&pids, &input, &pipes);
		else
			pipes->cur++;
		i++;
	}
}

int	create_pipe(t_pipes *pipes, int num_pipes)
{
	int	i;
	int	pipe_cnt;

	i = -1;
	pipe_cnt = 0;
	pipes->total_num_pipes = num_pipes;
	pipes->fd = ft_calloc(num_pipes, sizeof(*pipes->fd));
	if (pipes->fd == NULL)
	{
		perror("Malloc");
		return (1);
	}
	while (++i < pipes->total_num_pipes)
		pipe_cnt += pipe(pipes->fd[i]);
	if (pipe_cnt < 0)
	{
		perror("Pipe");
		return (1);
	}
}

int	close_pipes(t_pipes *pipes)
{
	int	i;
	int	error_cnt;

	i = -1;
	error_cnt = 0;
	if (pipes->fd == NULL)
		return (0);
	while (++i < pipes->total_num_pipes)
	{
		if (close(pipes->fd[i][0]) == -1)
			error_cnt++;
		if (close(pipes->fd[i][1]) == -1)
			error_cnt++;
	}
	if (error_cnt == 0)
		return (0);
	return (1);
}

int	set_pid_arr(int argc, t_pids *pids)
{
	pids->arr = ft_calloc(argc - 3 , sizeof(pid_t));
	if (pids->arr == NULL)
	{
		perror("Malloc");
		return (1);
	}
	return (0);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	char	*mem;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	mem = malloc(len_s1 + len_s2 + len_s3 + 1);
	if (!mem)
	{
		perror("Malloc");
		return (NULL);
	}
	ft_memmove(mem, s1, len_s1);
	ft_memmove(mem + len_s1, s2, len_s2);
	ft_memmove(mem + len_s1 + len_s2, s3, len_s3 + 1);
	return (mem);
}

int	isspace(const int c)
{
	const char	*space;

	space = "\t\n\v\f\r ";
	while (*space)
	{
		if (c == *space++)
			return (1);
	}
	return (0);
}