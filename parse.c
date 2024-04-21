/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:31:30 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/19 17:26:10 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include "include/typedef.h"
#include <fcntl.h>
#include <stdio.h>
#include "include/pipex.h"

int	parse_strlen(const char *s)
{
	int		cnt;
	int		tmp;

	cnt = 0;
	while (*s)
	{
		while (*s && isspace(*s) == 0)
		{
			s++;
			cnt++;
		}
		tmp = 0;
		while (*s && isspace(*s) == 1)
		{
			s++;
			tmp++;
		}
		if (0 < tmp)
			cnt++;
	}
	return (cnt);
}

char	*parse_argv(const char *s)
{
	int		new_strlen;
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 1;
	new_strlen = parse_strlen(s);
	ret = ft_calloc(1, new_strlen + 2);
	if (ret == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ret[0] = '/';
	while (s[i])
	{
		while (s[i] && isspace(s[i]) == 0)
			ret[j++] = s[i++];
		while (s[i] && isspace(s[i]) == 1)
			i++;
		if (j < new_strlen)
			ret[j++] = ' ';
	}
	return (ret);
}

int	save_t_input(t_input *input, int argc, char *argv[])
{
	int	i;

	i = -1;
	input->infile = argv[1];
	input->outfile = argv[argc - 1];
	input->cmds = (char **)ft_calloc(input->num_cmds, sizeof(char *));
	if (input->cmds == NULL)
		return (1);
	input->cmds_split = (char ***)ft_calloc(input->num_cmds, sizeof(char **));
	if (input->cmds_split == NULL)
		return (2);
	while (++i < input->num_cmds)
	{
		input->cmds[i] = argv[i + 2];
		input->cmds_split[i] = ft_split(input->cmds[i], ' ');
		if (input->cmds_split[i] == NULL)
			return (3);
		// input->cnt_cmds++;
	}
	return (0);
}
