/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:20:50 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/21 21:35:00 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <stdio.h>

void	sys_err(int err_type)
{
	if (err_type == 0)
	{
		perror("Pipe");
		exit(1);
	}
	else if (err_type == 1)
	{
		perror("dup2");
		exit(1);
	}
	else if (err_type == 2)
	{
		perror("close");
		exit(1);
	}
}