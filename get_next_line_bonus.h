/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:34:26 by dongjle2          #+#    #+#             */
/*   Updated: 2023/12/19 15:56:31 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stored_str
{
	char	*stored_str;
	size_t	start_idx;
	char	tmp_chr;
	size_t	size;
	size_t	len;
	char	rd_flag;
	char	eof;
}	t_stored_str;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *s1);
int		init_static(t_stored_str *i);
ssize_t	find_nl_idx(char *str);
int		resize_str(t_stored_str *i);
int		read_file(t_stored_str *i, int fd, ssize_t *num_read);
char	*print_single_line(t_stored_str *i, ssize_t *nl_idx, ssize_t *num_read);
void	mv_line(t_stored_str *i, ssize_t *nl_idx, char *single_line);
#endif
