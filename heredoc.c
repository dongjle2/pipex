/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:45:12 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/15 14:55:11 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

void	set_heredoc_input(t_heredoc *input, char *argv[])
{
	input->limiter = argv[2];
	input->cmd = argv[3];
	input->cmd1 = argv[4];
	input->file = argv[5];
}

// void	save_heredoc_input(t_heredoc *input)
// {
// 	int		pipe_fd[2];
// 	char	*single_line;

// 	pipe(pipe_fd);
// 	// dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		single_line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(input->limiter, single_line, ft_strlen(input->limiter)) != 0)
// 			write(STDOUT_FILENO, single_line, ft_strlen(single_line));
// 		else
// 			break ;
// 	}
// }
void	save_heredoc_input(t_heredoc *input, int pipe_fd[2])
{
	char	*single_line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		single_line = get_next_line(STDIN_FILENO);
		if (!single_line || ft_strncmp(input->limiter, single_line, ft_strlen(input->limiter)) == 0)
		{
			free(single_line);
			single_line = NULL;
			break ;
		}
		write(pipe_fd[WRITE_END], single_line, ft_strlen(single_line));
		free(single_line);
		single_line = NULL;
	}
	get_next_line(-1);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		exit(1);
}

void	run_cmd(int pipe_fd[2], t_heredoc *input)
{
	char	*full_path;
	char	**args;
	char	**cmd_split;

	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		exit(1);
	if (close(pipe_fd[0]) || close(pipe_fd[1]))
		exit(1);
	cmd_split = ft_split(input->cmd, ' ');
	full_path = ck_access(cmd_split[0]);
	args = mk_execve_argv(cmd_split);
	args[0] = full_path;
	execve(full_path, args, NULL);
	free_2d_arr(cmd_split);
	perror("execve");
	exit(1);
}

void	run_cmd1(int pipe_fd[2], t_heredoc *input)
{
	char	*full_path;
	char	**args;
	char	**cmd1_split;
	int		file_fd;

	file_fd = open(input->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	// dup2(pipe_fd[WRITE_END], file_fd);
	dup2(file_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(file_fd);
	cmd1_split = ft_split(input->cmd1, ' ');
	full_path = ck_access(cmd1_split[0]);
	args = mk_execve_argv(cmd1_split);
	args[0] = full_path;
	execve(full_path, args, NULL);
	free(cmd1_split);
	perror("execve");
	exit(1);
}


void	exec_heredoc(char *argv[])
{
	t_heredoc	input;
	pid_t		pid[2];
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	set_heredoc_input(&input, argv);
	save_heredoc_input(&input, pipe_fd);
	pid[0] = fork();
	if (pid[0] == 0)
		run_cmd(pipe_fd, &input);
	pid[1] = fork();
	if (pid[1] == 0)
		run_cmd1(pipe_fd, &input);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}
