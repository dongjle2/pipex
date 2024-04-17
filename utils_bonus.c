/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:22 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/15 14:41:50 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	safe_write(char *s, int fd)
{
	ssize_t	strlen;
	ssize_t	written;

	strlen = ft_strlen(s);
	written = write(fd, s, strlen);
	if (strlen != written)
		return (-1);
	return (strlen);
}