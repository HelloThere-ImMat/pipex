/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/01 13:04:47 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../lib/ft_printf.h"

# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		**end_tab;
	int		cmdnbr;
	int		in;
	int		out;
	char	**env;
	pid_t	pid;
}	t_data;

typedef struct s_read
{
	int		buffer_size;
	int		position;
	char	*buffer;
	char	*new_buffer;
}	t_read;

//FT SPLIT

int		char_is_in_charset(char c, char *charset);
int		count_str(char *str, char *charset);
int		wlength(char *str, int *j, char *charset);
char	*get_word(char *str, int len, int *j, char *charset);
char	**ft_split(char *str, char *charset);

//FT SPLIT 2

void	error_free(char **tab, int index);

//STR UTILS

int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen_p(const char *str);
char	*ft_strdup(const char *s);
char	*trim_path(char *path);
int		ft_isalpha(int c);

//STR UTILS 2

char	*ft_strjoin(char *s1, const char *s2, int must_free);
void	writestr(int fd, const char *str);

//UTILS

void	free_all(char ***commands, char **path);
void	print_tab(char **path);
int		check_files(char *in, char *out, t_data *data, int heredoc);
int		get_cmd_nbr(char ***commands);
int		**init_end_tab(t_data data);

//UTILS 2

char	**path_error_free(char **path, int index);
char	**get_path(char **env, char ***commands);
void	error(int type, char ***commands, char **path);
void	create_pipes(t_data *data, char ***commands, char **path);
char	*get_trimed_path(char **env, char ***commands);

//ARG UTILS

int		check_arg(int argc, char **argv, t_data *fd);
char	***ft_split_arg(int argc, char **argv);
int		check_hd_arg(int argc, char **argv, t_data *data);
char	***ft_split_hd_arg(char **argv);
char	***ft_split_arg(int argc, char **argv);

//HERE DOC

int		read_and_write(char *limiter, int fd_hd);
int		ft_heredoc(t_data *data, char *limiter);
int		heredoc_main(int argc, char **argv, t_data *data);

//READ INPUT

char	*read_input(void);
char	*double_and_fill(int buffer_size, char *buffer, int position);

//PROCESSES

void	child_process(t_data data, char ***commands, char **path, int cmd_i);
void	sub_dup(int in, int out, char ***commands, char **path);
void	close_pipes(t_data *data);

//ACCESS

void	access_main(char ***commands, char **path);
int		test_access(char **path, char **command);
int		test_access_np(char **path, char **command);
int		test_access_absolute(char **command, char **path);

//PIPEX

int		execute(char **command, char **path, char **env);
int		main(int argc, char **argv, char **env);
void	free_pipes(t_data data);
void	pipex(t_data data, char ***commands, char **path);

#endif
