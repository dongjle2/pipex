/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:58:38 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/05 14:35:35 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd, int *ret_val)
{
	ssize_t	strlen;
	ssize_t	written;

	strlen = ft_strlen(s);
	written = write(fd, s, strlen);
	if (strlen != written)
		return (-1);
	*ret_val += written;
	return (strlen);
}
