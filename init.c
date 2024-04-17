/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:29:45 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/17 00:55:16 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"

void	init_t_pids(t_pids *pids)
{
	pids->arr = (void *)0;
	pids->idx = -1;
}

void	init_t_input(t_input *input, int argc)
{
	input->infile = (void *)0;
	input->outfile = (void *)0;
	input->cmds = (void *)0;
	input->cmds_split = (void *)0;
	input->num_cmds = argc - 3;
}

void	init_t_pipes(t_pipes *pipes)
{
	pipes->cur = 0;
	pipes->total_num_pipes = 0;
	pipes->fd = (void *)0;
}

void	init_structs(t_pids *pids, t_input *input, t_pipes *pipes, int argc)
{
	init_t_input(input, argc);
	init_t_pids(pids);
	init_t_pipes(pipes);
}