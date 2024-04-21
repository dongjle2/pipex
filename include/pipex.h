/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:00 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/21 21:28:44 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./libft.h"
#include "./ft_printf_bonus.h"
#include "./get_next_line_bonus.h"

#define READ_END 0
#define WRITE_END 1

char	**path_value(void);
char	*ck_access(char *cmd_only);
char	**mk_execve_argv(char **cmds_split);
int		save_t_input(t_input *input, int argc, char *argv[]);
int		isspace(const int c);
int		parse_strlen(const char *s);
char	*parse_argv(const char *s);
void	init_t_input(t_input *input, int argc);
int		redirect_file(const char *file, int bit);
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
void	first_op(t_pids *pids, t_input *input, t_pipes *pipes);
void	last_op(t_pids *pids, t_input *input, t_pipes *pipes);
void	set_t_pipe(t_pipes *pipes, int num_pipes);
int		close_pipes(t_pipes *pipes);
void	middle_op(t_pids *pids, t_input *input, t_pipes *pipes);
int		create_pipe(t_pipes *pipes, int num_pipes);
void	wait_and_free(t_pids *pids, t_input *input, t_pipes *pipes);
int		set_pid_arr(int argc, t_pids *pids);
int		fill_exec_argv(t_input *input, char **full_path, char ***args);
void	exec_cmd(t_pids *pids, t_input *input, t_pipes *pipes);
void	set_heredoc_input(t_heredoc *input, char *argv[]);
void	save_heredoc_input(t_heredoc *input);
void	run_cmd1(int pipe_fd[2], t_heredoc input);
void	run_cmd(int pipe_fd[2], t_heredoc input);
void	exec_heredoc(char *argv[]);
void	free_2d_arr(char **arr);
void	free_mallocs(t_input *input, t_pipes *pipes, t_pids *pids);
ssize_t	safe_write(char *s, int fd);
void	free_t_input(t_input *input);
int		set_t_input(t_input *input, int argc, char *argv[]);
void	init_structs(t_structs *structs, int argc);
void	pipeline(t_pids *pids, t_input *input, t_pipes *pipes);
void	wait_and_free(t_pids *pids, t_input *input, t_pipes *pipes);
void	free_t_input(t_input *input);
void	free_mallocs(t_input *input, t_pipes *pipes, t_pids *pids);
void	free_2d_arr(char **arr);
void	sys_err(int err_type);
