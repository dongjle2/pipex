/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_s_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:56:17 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/10 00:37:52 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ck_input_bigger(t_display *d, t_packet *k);
static void	set_t_display(t_display *d, t_packet *k);
static int	print_display(t_display *d, t_packet *k, int *ret_val);

int	prt_s(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->pstr = va_arg(ap, char *);
	if (k->pstr == 0)
		k->pstr = "(null)";
	init_t_display(d);
	ck_input_bigger(d, k);
	set_t_display(d, k);
	if (print_display(d, k, ret_val) == -1)
		return (-1);
	return (0);
}

static void	ck_input_bigger(t_display *d, t_packet *k)
{
	d->strlen = ft_strlen(k->pstr);
	if (k->precision == -1)
	{
		if (ft_strncmp(k->pstr, "(null)", 6) == 0)
			k->precision = 6;
		else
			k->precision = d->strlen;
	}
	k->precision = ft_min(k->precision, d->strlen);
	k->width = ft_max(k->width, k->precision);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	d->num_space = ft_max(k->width - k->precision - d->prefix, 0);
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display(t_display *d, t_packet *k, int *ret_val)
{
	char	*buf_display;
	char	sys_fun_fail;

	sys_fun_fail = 0;
	buf_display = ft_calloc(k->precision + 1, 1);
	if (buf_display == NULL)
		sys_fun_fail = 1;
	if (sys_fun_fail == 0)
		ft_memmove(buf_display, k->pstr, k->precision);
	if (sys_fun_fail == 0 && d->num_space && d->space_location == 0)
	{
		if (print_space(d, ret_val) == -1)
			sys_fun_fail = 1;
	}
	if (sys_fun_fail == 0 && ft_putstr_fd(buf_display, 1, ret_val) == -1)
		sys_fun_fail = 1;
	if (sys_fun_fail == 0 && print_space(d, ret_val) == -1)
		sys_fun_fail = 1;
	free(buf_display);
	if (sys_fun_fail == 1)
		return (-1);
	return (0);
}
