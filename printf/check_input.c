/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:55:28 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/10 00:03:40 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	check_flags(t_packet *k, char **pmem)
{
	while (ft_strchr(FLAGS, **pmem))
	{
		if (**pmem == '+' && k->plus_flag == 0)
			k->plus_flag = 1;
		else if (**pmem == ' ' && k->space_flag == 0)
			k->space_flag = 1;
		else if (**pmem == '-' && k->minus_flag == 0)
			k->minus_flag = 1;
		else if (**pmem == '#' && k->hash_flag == 0)
			k->hash_flag = 1;
		else if (**pmem == '0' && k->pad_flag == 0)
			k->pad_flag = 1;
		(*pmem)++;
	}
}

void	check_precision(t_packet *k, char **pmem)
{
	int		i;
	char	j;

	i = 0;
	j = 0;
	while (**pmem == '.')
	{
		j = 1;
		(*pmem)++;
		if (!ft_isdigit(**pmem))
		{
			k->precision = 0;
			return ;
		}
		while (ft_isdigit(**pmem))
		{
			i = i * 10 + (**pmem - '0');
			(*pmem)++;
		}
	}
	if (j == 1)
		k->precision = i;
	else
		k->precision = -1;
}

void	check_width(t_packet *k, char **pmem)
{
	int		i;
	char	j;

	i = 0;
	j = 0;
	if (!ft_isdigit(**pmem))
		return ;
	while (ft_isdigit(**pmem))
	{
		j = 1;
		i = i * 10 + (**pmem - '0');
		(*pmem)++;
	}
	if (j == 1)
		k->width = i;
}

void	check_format(t_packet *k, char *pmem)
{
	if (ft_strchr("pxX", *pmem))
	{
		if (*pmem == 'p')
			k->fmt = 'p';
		else if (*pmem == 'x')
			k->fmt = 'x';
		else
			k->fmt = 'X';
	}
	else if (ft_strchr("di", *pmem))
	{
		if (*pmem == 'd')
			k->fmt = 'd';
		else
			k->fmt = 'i';
	}
	else if (*pmem == 'u')
		k->fmt = 'u';
	else if (*pmem == 'c')
		k->fmt = 'c';
	else if (*pmem == '%')
		k->fmt = '%';
	else
		k->fmt = 's';
}
