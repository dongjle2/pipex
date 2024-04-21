/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:24:58 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/20 00:22:35 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <stdio.h>
#include "include/libft.h"

extern char	**environ;

char	**path_value(void)
{
	static const char	**env;

	env = (const char **)environ;
	while (env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (ft_split(*env + 5, ':'));
		else
			env++;
	}
	return (NULL);
}

char	*ck_access(char *cmd_only)
{
	char	**paths;
	char	*full_path;
	char	**p_paths;

	paths = path_value();
	p_paths = paths;
	while (*p_paths)
	{
		full_path = ft_strjoin_3(*p_paths, "/", cmd_only);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			free_2d_arr(paths);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		p_paths++;
	}
	return (full_path);
}

char	**mk_execve_argv(char **cmd_split)
{
	char	**args;
	int		cnt_words;
	int		i;

	i = 0;
	cnt_words = 0;
	while (cmd_split[cnt_words] != NULL)
		cnt_words++;
	args = ft_calloc(cnt_words + 1, sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < cnt_words)
	{
		args[i] = cmd_split[i];
		i++;
	}
	return (args);
}

int	fill_exec_argv(t_input *input, char **full_path, char ***args)
{
	*full_path = ck_access(input->cmds_split[input->cnt_cmds][0]);
	if (*full_path == NULL)
		return (1);
	*args = mk_execve_argv(input->cmds_split[input->cnt_cmds]);
	if (*args == NULL)
		return (1);
	(*args)[0] = *full_path;
	return (0);
}

int	set_t_input(t_input *input, int argc, char *argv[])
{
	int	ret_status;

	ret_status = save_t_input(input, argc, argv);
	if(ret_status == 0)
		return (0);
	else if(ret_status == 1)
		return (1);
	else if(ret_status == 2)
	{
		free(input->cmds);
		input->cmds = NULL;
	}
	else if (ret_status == 3)
	{
		free(input->cmds);
		input->cmds = NULL;
		free_t_input(input);
	}
	return (0);
}
