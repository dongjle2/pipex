/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:34:54 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/15 00:37:06 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_memmmove(void *dst, const void *src, size_t len);

int	resize_str(t_stored_str *i)
{
	char	*tmp;
	size_t	idx;

	while (i->size < i->len + BUFFER_SIZE + 1)
		i->size *= 2;
	tmp = malloc(i->size);
	if (tmp == NULL)
	{
		free(i->stored_str);
		i->stored_str = NULL;
		return (-1);
	}
	ft_memmmove(tmp, i->stored_str, i->len);
	idx = i->len;
	while (idx < i->size)
		tmp[idx++] = 0;
	free(i->stored_str);
	i->stored_str = NULL;
	i->stored_str = tmp;
	return (1);
}

int	read_file(t_stored_str *i, int fd, ssize_t *num_read)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		nl_buffer;

	while (1)
	{
		*num_read = read(fd, buffer, BUFFER_SIZE);
		if (*num_read <= 0)
			return (*num_read);
		buffer[*num_read] = 0;
		if (i->size < i->len + BUFFER_SIZE + 1)
		{
			if (resize_str(i) == -1)
				return (-2);
		}
		ft_memmmove(i->stored_str + i->len, buffer, *num_read + 1);
		nl_buffer = find_nl_idx(buffer);
		i->len += *num_read;
		if (0 <= nl_buffer)
			break ;
	}
	return (*num_read);
}

char	*print_single_line(t_stored_str *i, ssize_t *nl_idx, ssize_t *num_read)
{
	*nl_idx = find_nl_idx(i->stored_str + i->start_idx);
	i->tmp_chr = (i->stored_str + i->start_idx)[*nl_idx + 1];
	if (*nl_idx == -1)
	{
		if (*num_read <= 0)
		{
			i->eof = 1;
			if (*(i->stored_str + i->start_idx) == 0 || *num_read == -1)
				return (NULL);
			else
				return (ft_strdup(i->stored_str + i->start_idx));
		}
	}
	(i->stored_str + i->start_idx)[*nl_idx + 1] = 0;
	return (ft_strdup(i->stored_str + i->start_idx));
}

void	mv_line(t_stored_str *i, ssize_t *nl_idx, char *single_line)
{
	if (i->eof == 1 || single_line == NULL)
	{
		free(i->stored_str);
		i->stored_str = NULL;
		i->start_idx = 0;
		i->tmp_chr = 0;
		i->size = 2;
		i->len = 0;
		i->rd_flag = 1;
		i->eof = 0;
		return ;
	}
	(i->stored_str + i->start_idx)[*nl_idx + 1] = i->tmp_chr;
	i->start_idx += *nl_idx + 1;
	if (0 <= find_nl_idx(i->stored_str + i->start_idx))
		i->rd_flag = 0;
	else
		i->rd_flag = 1;
	return ;
}

char	*get_next_line(int fd)
{
	static t_stored_str	i[OPEN_MAX];
	char				*single_line;
	ssize_t				nl_idx;
	ssize_t				num_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (i->stored_str != NULL)
			free(i->stored_str);
		return (NULL);
	}
	if (i[fd].stored_str == NULL)
	{
		if (init_static(&i[fd]) == 0)
			return (NULL);
	}
	num_read = 0;
	if (i[fd].rd_flag)
		num_read = read_file(&(i[fd]), fd, &num_read);
	if (num_read == -2)
		return (NULL);
	single_line = print_single_line(&i[fd], &nl_idx, &num_read);
	mv_line(&i[fd], &nl_idx, single_line);
	return (single_line);
}
