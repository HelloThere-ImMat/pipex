/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/01 13:04:43 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//^-To be removed

//FT SPLIT

int		char_is_in_charset(char c, char *charset);
int		count_str(char *str, char *charset);
int		wlength(char *str, int *j, char *charset);
char	*get_word(char *str, int len, int *j, char *charset);
char	**ft_split(char *str, char *charset);

//STR UTILS

int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
char	*ft_strdup(const char *s);
char	*trim_path(char *path);

//UTILS

char	**ft_split_arg(int argc, char **argv);
char 	**get_path(char **env);
int 	check_arg(int argc, char **argv);
void	print_tab(char **path);

//PIPEX

int		main(int argc, char **argv, char **env);

#endif
