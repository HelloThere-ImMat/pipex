/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:09:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/29 16:21:42 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <stdlib.h>

//FT SPLIT

int		char_is_in_charset(char c, char *charset);
int		count_str(char *str, char *charset);
int		wlength(char *str, int *j, char *charset);
char	*get_word(char *str, int len, int *j, char *charset);
char	**ft_split(char *str, char *charset);


//PIPEX

int		main(int argc, char **argv, char **env);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

#endif