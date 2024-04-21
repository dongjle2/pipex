/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:31:35 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/20 19:29:49 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

extern char	**environ;

int	redirect_file(const char *file, int bit)
{
	int	fd;
	int	dup_ret;

	if (bit == 0)
		fd = open(file, O_RDONLY, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Open, redirect_file");
		return (1);
	}
	if (bit == 0)
		dup_ret = dup2(fd, STDIN_FILENO);
	else
		dup_ret = dup2(fd, STDOUT_FILENO);
	if (dup_ret == -1)
		return (1);
	if (close(fd) == -1)
	{
		perror("close");
		return (1);
	}
	return (0);
}

void	first_op(t_pids *pids, t_input *input, t_pipes *pipes)
{
	char	*full_path;
	char	**args;

	full_path = NULL;
	if (dup2(pipes->fd[pipes->cur][WRITE_END], STDOUT_FILENO) == -1 || \
		redirect_file(input->infile, 0) == 1 || close_pipes(pipes) || \
		fill_exec_argv(input, &full_path, &args) == 1)
	{
		perror("dup2 failed\n");
		free_mallocs(input, pipes, pids);
		free(full_path);
		close_pipes(pipes);
		exit(1);
	}
	execve(full_path, args, environ);
	free_mallocs(input, pipes, pids);
	free(full_path);
	close_pipes(pipes);
	perror("command not found\n");
	exit(1);
}

void	middle_op(t_pids *pids, t_input *input, t_pipes *pipes)
{
	char	*full_path;
	char	**args;

	full_path = NULL;
	if (dup2(pipes->fd[pipes->cur - 1][READ_END], STDIN_FILENO) == -1 || \
		dup2(pipes->fd[pipes->cur][WRITE_END], STDOUT_FILENO) == -1 || \
		close_pipes(pipes) || \
		fill_exec_argv(input, &full_path, &args) == 1)
	{
		free_mallocs(input, pipes, pids);
		free(full_path);
		close_pipes(pipes);
		exit(1);
	}
	execve(full_path, args, environ);
	free_mallocs(input, pipes, pids);
	free(full_path);
	close_pipes(pipes);
	perror("command not found\n");
	exit(1);
}

void	last_op(t_pids *pids, t_input *input, t_pipes *pipes)
{
	char	*full_path;
	char	**args;

	full_path = NULL;
	if (redirect_file(input->outfile, 1) == 1 || \
		dup2(pipes->fd[pipes->cur - 1][READ_END], STDIN_FILENO) == -1 || \
		close_pipes(pipes) || \
		fill_exec_argv(input, &full_path, &args) == 1)
	{
		free_mallocs(input, pipes, pids);
		free(full_path);
		close_pipes(pipes);
		exit(1);
	}
	execve(full_path, args, environ);
	free_mallocs(input, pipes, pids);
	free(full_path);
	close_pipes(pipes);
	perror("command not found\n");
	exit(127);
}

void	exec_cmd(t_pids *pids, t_input *input, t_pipes *pipes)
{
	if (pids->idx == 0)
		first_op(pids, input, pipes);
	else if (pids->idx == input->num_cmds - 1)
		last_op(pids, input, pipes);
	else
		middle_op(pids, input, pipes);
}

int	setup_process(t_structs *structs, int argc, char *argv[])
{
	int	fail;

	fail = 0;
	init_structs(structs, argc);
	fail += set_t_input(&structs->input, argc, argv);
	fail += set_pid_arr(argc, &structs->pids);
	if (0 < fail)
	{
		free_mallocs(&structs->input, &structs->pipes, &structs->pids);
		exit(1);
	}
	if (create_pipe(&structs->pipes, argc - 3) == 1)
	{
		free_mallocs(&structs->input, &structs->pipes, &structs->pids);
		close_pipes(&structs->pipes);
		exit(1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_structs	structs;

	if (argc < 5)
		exit(1);
	if (argc == 6 && ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		exec_heredoc(argv);
		return (0);
	}
	setup_process(&structs, argc, argv);
	pipeline(&structs.pids, &structs.input, &structs.pipes);
	close_pipes(&structs.pipes);
	wait_and_free(&structs.pids, &structs.input, &structs.pipes);
	exit (0);
}
