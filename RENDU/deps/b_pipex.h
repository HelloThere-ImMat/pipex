/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 13:57:45 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_PIPEX_H
# define B_PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../lib/ft_printf.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//^-To be removed

typedef struct s_data
{
	int		end[2];
	int		end2[2];
	int		cmdnbr;
	int		in;
	int		out;
	char	**env;
	pid_t	pid1;
	pid_t	pid2;
}	t_data;

//FT SPLIT

int		char_is_in_charset(char c, char *charset);
int		count_str(char *str, char *charset);
int		wlength(char *str, int *j, char *charset);
char	*get_word(char *str, int len, int *j, char *charset);
char	**ft_split(char *str, char *charset);

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

int		check_arg(int argc, char **argv, t_data *fd);
void	free_all(char ***commands, char **path);

//UTILS 2

char	***ft_split_arg(int argc, char **argv);
char	**get_path(char **env);
void	print_tab(char **path);


//PROCESSES

int		first_child(char **command, char **path, t_data fd);
//int		middle_process(char **command, char **path, t_data fd);
int		last_child(char **command, char **path, t_data fd);
void	wait_and_close(t_data data);

//ACCESS

int		access_main(char ***commands, char **path);
int		test_access(char **path, char **command);

//PIPEX

int		execute(char **command, char **path, char **env);
int		main(int argc, char **argv, char **env);
int		get_cmd_nbr(char ***commands);
int		pipex(t_data data, char ***commands, char **path);
pid_t	parent_process(t_data data, char ***commands, char **path);

#endif
