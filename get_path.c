/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:24:58 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/07 02:05:22 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "./libft.h"

extern char	**environ;

char	**path_value(void)
{
	const static char	**env;

	env = (const char **)environ;
	while (env != NULL)
	{
		// printf("%s\n", *env);
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(*env + 5, ':'));
		else
			env++;
	}
	return (NULL);
}

char	*ck_access(char ***cmds_split, int order)
{
	char	**paths;
	char	*full_path;
	char	**p_paths;

	paths = path_value();
	p_paths = paths;
	while (*p_paths)
	{
		full_path = ft_strjoin_3(*p_paths, "/", cmds_split[order][0]);
		if (access(full_path, X_OK) == 0)
		{
			printf("%s\n", full_path);
			free(paths);	//freeing 2d array wrong
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		p_paths++;
	}
	return (full_path);
}

char	**get_execve_argv(char ***cmds_split, int cmds_order)
{
	char	**args;
	int		cnt_words;
	int		i;

	i = 0;
		cnt_words = sizeof(cmds_split[cmds_order]);	//strlen?
	args = ft_calloc(cnt_words, sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(1);
	}
	while (i++ < cnt_words)
	{
		args[i] = cmds_split[cmds_order][i];
	}
	return (args);
}
