/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:33:35 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/15 00:26:13 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strllen(const char *s)
{
	size_t	l;

	l = 0;
	if (s == NULL)
		return (l);
	while (*s++)
		l++;
	return (l);
}

char	*ft_memmmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (pdst < psrc)
	{
		while (len--)
			*pdst++ = *psrc++;
	}
	else if (psrc < pdst)
	{
		while (len--)
			pdst[len] = psrc[len];
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	char	*mem;

	len_s1 = ft_strllen(s1);
	mem = malloc(len_s1 + 1);
	if (!mem)
		return (NULL);
	mem[len_s1] = 0;
	return (ft_memmmove(mem, s1, len_s1));
}

ssize_t	find_nl_idx(char *str)
{
	size_t	idx;

	idx = 0;
	if (str == NULL)
		return (-1);
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

int	init_static(t_stored_str *i)
{
	size_t	idx;

	idx = 0;
	i->stored_str = (char *)malloc(2);
	if (i->stored_str == NULL)
		return (0);
	i->size = 2;
	while (idx < i->size)
		i->stored_str[idx++] = 0;
	i->rd_flag = 1;
	return (1);
}
