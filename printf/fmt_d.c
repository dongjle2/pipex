/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:26:46 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/09 23:41:25 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ck_input_bigger(t_display *d, t_packet *k);
static void	set_t_display(t_display *d, t_packet *k);
static int	print_display(t_display *d, t_packet *k, int *ret_val);
static int	print_sign(t_display *d, t_packet *k, int *ret_val);

int	prt_d(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->val.i = va_arg(ap, int);
	init_t_display(d);
	if (ck_input_bigger(d, k) == -1)
	{
		free(d->itoa);
		return (-1);
	}
	set_t_display(d, k);
	if (print_display(d, k, ret_val) == -1)
	{
		free(d->itoa);
		return (-1);
	}
	free(d->itoa);
	return (0);
}

static int	ck_input_bigger(t_display *d, t_packet *k)
{
	d->itoa = ft_numtoa(k->val, &k->fmt);
	if (d->itoa == NULL)
		return (-1);
	d->strlen = ft_strlen(d->itoa);
	if (k->val.i == 0 && k->precision == 0)
		d->strlen = 0;
	k->width = ft_max(k->width, d->strlen);
	return (0);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	if (k->val.i < 0)
	{
		d->sign = '-';
		ft_memmove(d->itoa, d->itoa + 1, d->strlen);
		d->strlen--;
	}
	if (k->precision == -1 && k->pad_flag && k->minus_flag == 0)
	{
		d->num_zero = k->width - d->strlen;
		if (k->plus_flag || k->space_flag || k->val.i < 0)
			d->num_zero = ft_max(d->num_zero - 1, 0);
	}
	else if (k->precision != -1)
		d->num_zero = ft_max(k->precision - d->strlen, 0);
	d->num_space = ft_max(k->width - d->num_zero - d->strlen, 0);
	if (d->sign == '-' || (0 <= k->val.i && (k->plus_flag || k->space_flag)))
		d->num_space = ft_max(d->num_space - 1, 0);
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display(t_display *d, t_packet *k, int *ret_val)
{
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, ret_val) == -1)
			return (-1);
	}
	if (print_sign(d, k, ret_val) == -1)
		return (-1);
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	if (!(k->val.i == 0 && k->precision == 0))
	{
		if (ft_putstr_fd(d->itoa, 1, ret_val) == -1)
			return (-1);
	}
	if (print_space(d, ret_val) == -1)
		return (-1);
	return (0);
}

static int	print_sign(t_display *d, t_packet *k, int *ret_val)
{
	if (k->plus_flag || k->val.i < 0)
	{
		if (ft_putchar_fd(d->sign, 1, ret_val) == -1)
			return (-1);
	}
	else if (k->space_flag && 0 <= k->val.i)
	{
		if (ft_putchar_fd(' ', 1, ret_val) == -1)
			return (-1);
	}
	return (0);
}
