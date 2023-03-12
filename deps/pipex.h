/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/12 16:32:26 by mdorr            ###   ########.fr       */
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
	int		in;
	int		out;
	char	**env;
	char	**argv;
	pid_t	pid1;
	pid_t	pid2;
}	t_data;

//FT SPLIT

int		char_is_in_charset(char c, char *charset);
int		count_str(char *str, char *charset);
int		wlength(char *str, int *j, char *charset);
char	*get_word(char *str, int len, int *j, char *charset);
char	**ft_split(char *str, char *charset);

//FT_SPLIT 2

void	error_free(char **tab, int index);

//STR UTILS

int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen_p(const char *str);
char	*ft_strdup(const char *s);
char	*trim_path(char *path);
int		ft_isalpha(int c);

//STR UTILS 2

char	*ft_strjoin(char *s1, const char *s2, int must_free);
void	writestr(int data, const char *str);

//UTILS

char	***ft_split_arg(int argc, char **argv);
char	**get_path(char **env);
int		check_arg(int argc, char **argv, t_data *data);
void	print_tab(char **path);

//UTILS 2

int		execute(char **command, char **path, char **env);
void	error(int type, char ***commands, char **path);
void	wait_and_close(t_data data, int end[2]);
void	error_cmd(t_data data, char ***commands, char **path, int *end);
void	free_all(char ***commands, char **path);

//ACCESS

void	access_main(char ***commands, char **path);
void	test_access(char **path, char **command);
void	test_access_absolute(char **command);

//PIPEX

void	pipex(t_data data, char ***commands, char **path);
void	parent_process(t_data data, char ***commands, char **path, int end[2]);
void	child_process(t_data data, char ***commands, char **path, int end[2]);
int		main(int argc, char **argv, char **env);

#endif
