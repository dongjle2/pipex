/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:53:08 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/01 22:12:02 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "./libft.h"

extern char	**environ;

int	find_path(const char **str);

char	**path_value(void)
{
	const static char	**env;

	env = (const char **)environ;
	while (env != NULL)
	{
		if (find_path(env) == 1)
			return (ft_split(*env, ':'));
		else
			env++;
	}
	printf("\n");
	return (NULL);
}

int	find_path(const char **str)
{
	if (4 < ft_strlen(*str))
	{
		if ((*str)[0] == 'P' && (*str)[1] == 'A' && (*str)[2] == 'T' &&\
		 	(*str)[3] == 'H')
			return (1);
	}
	return (0);
}

int	main(void)
{
	char	**path;

	path = path_value();
	while (*path != NULL)
	{
		printf("%s\n", *path);
		path++;
	}
	// free(path);
	return (0);
}