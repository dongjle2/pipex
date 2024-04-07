/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:31:35 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/07 02:10:22 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

void	first_op(t_input *input, int pipe_fd[2])
{
	char	*full_path;
	char	**args;

	printf("first_op\n");
	close(pipe_fd[READ_END]);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[WRITE_END]);
	redirect_file(input->infile, 0);
	full_path = ck_access(input->cmds_split, *(input->pcnt_cmds));
	printf("%s\n", full_path);
	args = get_execve_argv(input->cmds_split, *(input->pcnt_cmds));
	(*input->pcnt_cmds)++;
	args[0] = full_path;
	printf("%s\n", full_path);
	// execve(full_path, args, NULL);
	// perror("Execve1");
	// free(full_path);
	// free(args);
	exit(1);
}

void	redirect_file(const char *file, int bit)
{
	int	fd;

	if (bit == 0)
		fd = open(file, O_RDONLY | O_CREAT);	//infile
	else
		fd = open(file, O_WRONLY | O_CREAT);	//outfile
	if (fd == -1)
	{
		perror("Open, redirect_file");
		exit(0);
	}
	if (bit == 0)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	middle_op(t_input *input, int pipe_fd[2])
{
	char	*full_path;
	char	**args;

	printf("middle_op\n");
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[WRITE_END]);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
	full_path = ck_access(input->cmds_split, *(input->pcnt_cmds));
	printf("%s\n", full_path);
	args = get_execve_argv(input->cmds_split, *(input->pcnt_cmds));
	(*input->pcnt_cmds)++;
	args[0] = full_path;
	sleep(10);
	execve(full_path, args, NULL);
	perror("execve");
	// free(full_path);
	exit(1);
}

void	second_op(t_input *input, int pipe_fd[2])
{
	char	*full_path;
	char	**args;

	close(pipe_fd[WRITE_END]);
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
	redirect_file(input->outfile, 1);
	full_path = ck_access(input->cmds_split, *(input->pcnt_cmds));
	args = get_execve_argv(input->cmds_split, *(input->pcnt_cmds));
	(*input->pcnt_cmds)++;
	args[0] = full_path;
	sleep(5);
	execve(full_path, args, NULL);
	perror("execve");
	free(full_path);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_input	input;
	// int		pipe_fd[2];
	t_pipes	pipes;
	pid_t	pid[3];

	if (argc < 5)
	{
		write(1, "\n", 1);
		return (0);
	}
	init_t_input(&input);
	save_input(&input, argc, argv);
	create_pipe(&pipes, argc - 3);
	ck_access(input.cmds_split, *(input.pcnt_cmds));
	pid[0] = fork();
	if (pid[0] == 0)	//child
		first_op(&input, pipes.pipes_fd[pipes.cur_pipe]);
	close_pipes(&pipes);
	// close(pipes.pipes_fd[0][0]);
	// close(pipes.pipes_fd[0][1]);
	while ((*(input.pcnt_cmds)) < argc - 3)
	{
		pid[1] = fork();
		if (pid[1] == 0)
		{
			// printf("%d\n", *(input.pcnt_cmds));
			(*(input.pcnt_cmds))++;
			middle_op(&input, pipes.pipes_fd[pipes.cur_pipe++]);
		}
		else
			close_pipes(&pipes);
	}
	pid[2] = fork();
	if (pid[2] == 0)
		second_op(&input, pipes.pipes_fd[pipes.cur_pipe]);
	close_pipes(&pipes);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// free(input.cmd1);
	// free(input.cmd2);
	return (0);
}
