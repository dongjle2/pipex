/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:47:06 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/10 00:20:27 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"
#include "libft/libft.h"

void	ft_str_toupper(char *s)
{
	while (*s)
	{
		if ('a' <= *s && *s <= 'z')
			*s -= 32;
		s++;
	}
}

int	ft_max(long long a, long long b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_min(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

int	print_padding(t_display *d, int *ret_val)
{
	char	*buf_zero;

	buf_zero = ft_calloc(d->num_zero + 1, 1);
	if (buf_zero == NULL)
		return (-1);
	ft_memset(buf_zero, '0', d->num_zero);
	if (ft_putstr_fd(buf_zero, 1, ret_val) == -1)
	{
		free(buf_zero);
		return (-1);
	}
	free(buf_zero);
	return (0);
}

int	print_space(t_display *d, int *ret_val)
{
	char	*buf_space;

	if (d->num_space == 0)
		return (0);
	buf_space = ft_calloc(1, d->num_space + 1);
	if (buf_space == NULL)
		return (-1);
	ft_memset(buf_space, ' ', d->num_space);
	if (ft_putstr_fd(buf_space, 1, ret_val) == -1)
	{
		free(buf_space);
		return (-1);
	}
	free(buf_space);
	d->num_space = 0;
	return (0);
}
