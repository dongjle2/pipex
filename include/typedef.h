/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:34:43 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/19 22:25:01 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

#include <sys/types.h>

typedef union u_nums
{
	unsigned long long	ull;
	unsigned int		ui;
	int					i;
}	t_nums;

typedef struct s_packet
{
	t_nums	val;
	char	fmt;
	char	plus_flag;
	char	minus_flag;
	char	space_flag;
	char	hash_flag;
	char	pad_flag;
	int		width;
	int		precision;
	char	chr;
	char	*pstr;
}	t_packet;

typedef struct s_display
{
	int		digit_len;
	int		strlen;
	int		num_space;
	int		num_zero;
	short	prefix;
	char	space_location;
	char	sign;
	char	*itoa;
}	t_display;

typedef struct s_input
{
	const char	*infile;
	const char	*outfile;
	char		**cmds;
	char		***cmds_split;
	int			num_cmds;
	int			cnt_cmds;
}	t_input;

typedef struct s_pipes
{
	int	(*fd)[2];
	int	total_num_pipes;
	int	cur;
}	t_pipes;

typedef struct s_pids
{
	pid_t	*arr;
	int		idx;
}	t_pids;

typedef struct s_heredoc
{
	char	*limiter;
	char	*cmd;
	char	*cmd1;
	char	*file;
}	t_heredoc;

typedef struct s_structs
{
	t_input	input;
	t_pipes	pipes;
	t_pids	pids;
}	t_structs;
#endif

