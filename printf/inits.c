/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:02:13 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/10 00:22:38 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	init_t_display(t_display *d)
{
	ft_bzero(d, sizeof(*d));
	d->sign = '+';
	d->itoa = (void *)0;
}

void	init_packet(t_packet *k)
{
	ft_bzero(k, sizeof(*k));
	k->width = -1;
	k->precision = -1;
	k->pstr = (void *)0;
}

int	prt_pkt(t_packet *k, va_list ap, int *ret_val)
{
	t_display	d;
	int			malloc_fail;

	malloc_fail = 0;
	if (k->fmt == 'c' || k->fmt == '%')
		malloc_fail = prt_c(k, &d, ap, ret_val);
	else if (k->fmt == 's')
		malloc_fail = prt_s(k, &d, ap, ret_val);
	else if (k->fmt == 'p')
		malloc_fail = prt_p(k, &d, ap, ret_val);
	else if (k->fmt == 'x' || k->fmt == 'X')
		malloc_fail = prt_x(k, &d, ap, ret_val);
	else if (k->fmt == 'd' || k->fmt == 'i')
		malloc_fail = prt_d(k, &d, ap, ret_val);
	else if (k->fmt == 'u')
		malloc_fail = prt_u(k, &d, ap, ret_val);
	if (malloc_fail == -1)
		return (-1);
	return (0);
}
