/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:31:30 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/05 15:18:46 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include "typedef.h"
#include <fcntl.h>
#include <stdio.h>

int	isspace(const int c)
{
	const char	*space;

	space = "\t\n\v\f\r ";
	while (*space)
	{
		if (c == *space++)
			return (1);
	}
	return (0);
}

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

void	init_t_input(t_input *input)
{
	input->infile = NULL;
	input->outfile = NULL;
	input->cmds = NULL;
	input->cmds_split = NULL;
	input->cnt_cmds = 0;
	input->pcnt_cmds = &input->cnt_cmds;

}

void	save_input(t_input *input, int argc, char *argv[])
{
	int	i;

	i = 0;
	input->infile = argv[1];
	input->outfile = argv[argc - 1];
	input->cmds = ft_calloc(argc -3, sizeof(char *));
	input->cmds_split = ft_calloc(argc - 3, sizeof(char **));
	if (input->cmds == NULL || input->cmds_split == NULL)
	{
		perror("Malloc");
		exit(1);
	}
	while (i < argc - 3)
	{
		input->cmds[i] = argv[i + 2];
		i++;
	}
	i = 0;
	while (i < argc - 3)
	{
		input->cmds_split[i] = ft_split(input->cmds[i], ' ');
		i++;
	}
}
