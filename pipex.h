/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:00 by dongjle2          #+#    #+#             */
/*   Updated: 2024/04/07 01:52:36 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include "./ft_printf_bonus.h"
#include "./get_next_line_bonus.h"
#include <unistd.h>

# define READ_END	0
# define WRITE_END	1

char	**path_value(void);
// char	*ck_access(t_input *input);
char	*ck_access(char ***cmds_split, int cmds_order);
char	**get_execve_argv(char ***cmds_split, int cmds_order);
// char	**get_execve_argv(t_input *input, int num);
void	save_input(t_input *input, int argc, char *argv[]);
int		isspace(const int c);
int		parse_strlen(const char *s);
char	*parse_argv(const char *s);
void	init_t_input(t_input *input);
void	redirect_file(const char *file, int bit);
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
void	first_op(t_input *input, int pipe_fd[2]);
void	set_t_pipe(t_pipes *pipes, int num_pipes);
void	close_pipes(t_pipes *pipes);
void	create_pipe(t_pipes *pipes, int num_pipes);