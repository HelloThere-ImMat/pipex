/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/12 16:42:43 by mdorr            ###   ########.fr       */
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

typedef struct s_fd
{
	int		end[2];
	int		end2[2];
	int		cmdnbr;
	int		in;
	int		out;
	char	**env;

}	t_fd;

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

char	***ft_split_arg(int argc, char **argv);
char	**get_path(char **env);
int		check_arg(int argc, char **argv, t_fd *fd);
void	print_tab(char **path);
void	free_all(char ***commands, char **path);

//PROCESSES

int		first_process(char **command, char **path, t_fd fd);
int		middle_process(char **command, char **path, t_fd fd);
int		last_process(char **command, char **path, t_fd fd);

//ACCESS

int		access_main(char ***commands, char **path);
int		test_access(char **path, char **command);

//PIPEX

int		execute(char **command, char **path, char **env);
int		main(int argc, char **argv, char **env);

#endif
