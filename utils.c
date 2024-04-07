/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:38:16 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/07 02:12:55 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

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
		return (mem);
	ft_memmove(mem, s1, len_s1);
	ft_memmove(mem + len_s1, s2, len_s2);
	ft_memmove(mem + len_s1 + len_s2, s3, len_s3 + 1);
	return (mem);
}

void	create_pipe(t_pipes *pipes, int num_pipes)
{
	int	i;

	i = 0;
	pipes->cur_pipe = 0;
	pipes->total_num_pipes = num_pipes;
	printf("num pipes: %d\n", num_pipes);
	pipes->pipes_fd = NULL;
	pipes->pipes_fd = ft_calloc(num_pipes, sizeof(int) * 2);
	if (pipes->pipes_fd == NULL)
	{
		perror("Malloc");
		exit(1);
	}
	while (i < num_pipes)
	{
		if (pipe(pipes->pipes_fd[i]) == -1)
		{
			perror("Pipe");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_pipes *pipes)
{
	int	i;

	i = -1;
	while (++i < pipes->total_num_pipes)
	{
		if (i == pipes->cur_pipe)
			continue ;
		close(pipes->pipes_fd[i][0]);
		close(pipes->pipes_fd[i][1]);
		i++;
	}
	pipes->cur_pipe++;
}
