/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:34:43 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/07 01:45:38 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

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
	int			*pcnt_cmds;
	int			cnt_cmds;
}	t_input;

typedef struct s_pipes
{
	int	(*pipes_fd)[2];
	int	total_num_pipes;
	int	cur_pipe;
}	t_pipes;
#endif