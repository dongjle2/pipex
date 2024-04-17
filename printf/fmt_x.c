/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_x_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:13:45 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/10 00:11:26 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ck_input_bigger(t_display *d, t_packet *k);
static void	set_t_display(t_display *d, t_packet *k);
static int	print_display_x(t_display *d, t_packet *k, int *ret_val);
static int	print_display_xx(t_display *d, t_packet *k, int *ret_val);

int	prt_x(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->val.ui = va_arg(ap, unsigned int);
	init_t_display(d);
	if (ck_input_bigger(d, k) == -1)
		return (-1);
	set_t_display(d, k);
	if (k->fmt == 'x')
	{
		if (print_display_x(d, k, ret_val) == -1)
		{
			free(d->itoa);
			return (-1);
		}
	}
	else
	{
		if (print_display_xx(d, k, ret_val) == -1)
		{
			free(d->itoa);
			return (-1);
		}
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
	if (k->hash_flag && k->val.ui != 0)
		d->prefix = 2;
	if (k->val.ui == 0 && k->precision == 0)
		d->strlen = 0;
	k->width = ft_max(k->width, d->strlen + d->prefix);
	return (0);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	if (k->precision == -1 && k->pad_flag)
		d->num_zero = k->width - d->strlen - d->prefix;
	else if (k->precision != -1)
	{
		d->num_zero = ft_max(k->precision - d->strlen, 0);
	}
	d->num_space = ft_max(k->width - d->num_zero - d->strlen - d->prefix, 0);
	if (k->plus_flag)
		d->num_space = ft_max(d->num_space - 1, 0);
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display_x(t_display *d, t_packet *k, int *ret_val)
{
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, ret_val) == -1)
			return (-1);
	}
	if (d->prefix)
	{
		if (ft_putstr_fd("0x", 1, ret_val) == -1)
			return (-1);
	}
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	if (!(k->val.ui == 0 && k->precision == 0))
	{
		if (ft_putstr_fd(d->itoa, 1, ret_val) == -1)
			return (-1);
	}
	if (print_space(d, ret_val) == -1)
		return (-1);
	return (0);
}

static int	print_display_xx(t_display *d, t_packet *k, int *ret_val)
{
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, ret_val) == -1)
			return (-1);
	}
	if (d->prefix)
	{
		if (ft_putstr_fd("0X", 1, ret_val) == -1)
			return (-1);
	}
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	if (!(k->val.ui == 0 && k->precision == 0))
	{
		ft_str_toupper(d->itoa);
		if (ft_putstr_fd(d->itoa, 1, ret_val) == -1)
			return (-1);
	}
	if (print_space(d, ret_val) == -1)
		return (-1);
	return (0);
}
