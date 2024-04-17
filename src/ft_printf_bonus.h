/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:05:02 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/11 20:37:27 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include "libft/libft.h"
# include "typedef_bonus.h"
# define FORMATS "cspdiuxX%"
# define FLAGS "+ -#0"

int		begin_rd(const char *s, va_list ap, int *ret_val);
char	*cp_s_to_calloc(const char *s);
void	check_format(t_packet *k, char *pmem);
void	check_flags(t_packet *k, char **mem);
void	check_width(t_packet *k, char **mem);
void	check_precision(t_packet *k, char **pmem);
int		check_sign(t_nums *val, char *sign, char *mode);
char	*ft_numtoa(t_nums val, char *mode);
int		ft_ulllen(unsigned long long n, int l);
int		ft_uilen(unsigned int n, int l, char *fmt);
int		ft_ilen(int n, int l);
void	ft_str_toupper(char *s);
int		ft_printf(const char *s, ...);
int		ft_max(long long a, long long b);
int		ft_min(long long a, long long b);
void	init_packet(t_packet *k);
void	init_t_display(t_display *d);
int		prt_pkt(t_packet *k, va_list ap, int *ret_val);
int		prt_c(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		prt_s(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		prt_p(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		prt_x(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		prt_u(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		prt_d(t_packet *k, t_display *d, va_list ap, int *ret_val);
int		print_padding(t_display *d, int *ret_val);
int		print_space(t_display *d, int *ret_val);
int		parsing(const char **s, va_list ap, int *ret_val);
int		rd_mem_to_pkt(t_packet *k, char *mem);
#endif
