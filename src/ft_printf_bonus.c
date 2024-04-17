/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:02:57 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/11 20:43:03 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		ret_val;

	va_start(ap, s);
	ret_val = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (parsing(&s, ap, &ret_val) == -1)
				break ;
		}
		else
		{
			if (ft_putchar_fd(*s, 1, &ret_val) == -1)
			{
				ret_val = -1;
				break ;
			}
			s++;
		}
	}
	va_end(ap);
	return (ret_val);
}

int	parsing(const char **s, va_list ap, int *ret_val)
{
	int	num_read;

	num_read = begin_rd(++(*s), ap, ret_val);
	if (num_read == -1)
	{
		*ret_val = -1;
		return (-1);
	}
	else
	{
		*s += num_read;
		return (0);
	}
}

int	begin_rd(const char *s, va_list ap, int *ret_val)
{
	t_packet	k;
	char		*mem;
	size_t		mem_len;

	mem = cp_s_to_calloc(s);
	if (!mem)
		return (-1);
	rd_mem_to_pkt(&k, mem);
	if (prt_pkt(&k, ap, ret_val) == -1)
	{
		free(mem);
		return (-1);
	}
	mem_len = ft_strlen(mem);
	free(mem);
	return (mem_len);
}

int	rd_mem_to_pkt(t_packet *k, char *mem)
{
	char	*pmem;

	pmem = mem;
	init_packet(k);
	while (!ft_strchr(FORMATS, *pmem))
	{
		check_flags(k, &pmem);
		check_width(k, &pmem);
		check_precision(k, &pmem);
	}
	check_format(k, pmem);
	return (0);
}

char	*cp_s_to_calloc(const char *s)
{
	size_t	i;
	char	*mem;

	i = 0;
	while (!ft_strchr(FORMATS, s[i++]))
		;
	mem = ft_calloc(i + 1, sizeof(char));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s, i + 1);
	return (mem);
}
