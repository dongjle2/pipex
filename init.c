/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:29:45 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/19 17:44:23 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/typedef.h"

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
	input->cnt_cmds = 0;
}

void	init_t_pipes(t_pipes *pipes)
{
	pipes->cur = 0;
	pipes->total_num_pipes = 0;
	pipes->fd = (void *)0;
}

void	init_structs(t_structs *structs, int argc)
{
	init_t_input(&structs->input, argc);
	init_t_pids(&structs->pids);
	init_t_pipes(&structs->pipes);
}