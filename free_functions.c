/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:39:24 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/19 22:33:18 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <sys/wait.h>

void	wait_and_free(t_pids *pids, t_input *input, t_pipes *pipes)
{
	int		i;
	int		wpidstatus;
	pid_t	last_one;

	i = 0;
	while (i < pids->idx)
	{
		waitpid(pids->arr[i], NULL, 0);
		i++;
	}
	last_one = pids->arr[i];
	free_mallocs(input, pipes, pids);
	waitpid(last_one, &wpidstatus, 0);
	if (WIFEXITED(wpidstatus))
		exit (WEXITSTATUS(wpidstatus));
	exit (1);
}

void	free_t_input(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	while (i < input->num_cmds)
	{
		j = 0;
		while (input->cmds_split[i][j])
		{
			free(input->cmds_split[i][j]);
			input->cmds_split[i][j] = NULL;
			j++;
		}
		free(input->cmds_split[i][j]);
		input->cmds_split[i][j] = NULL;
		free(input->cmds_split[i]);
		input->cmds_split[i] = NULL;
		i++;
	}
	free(input->cmds_split);
	input->cmds_split = NULL;
}

void	free_mallocs(t_input *input, t_pipes *pipes, t_pids *pids)
{
	if (input->cmds)
	{
		free(input->cmds);
		input->cmds = NULL;
	}
	if (input)
	{
		free_t_input(input);
		input = NULL;
	}
	if (pipes->fd)
	{
		free(pipes->fd);
		pipes->fd = NULL;
	}
	if (pids->arr)
	{
		free(pids->arr);
		pids->arr = NULL;
	}
}

void	free_2d_arr(char **arr)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (arr[row] != NULL)
		row++;
	while (i < row)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
