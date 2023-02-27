/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:26:53 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/10 12:53:01 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int		read_and_stash(int fd, t_list **stash);
int		found_newline(t_list *stash);
void	add_to_lst(t_list **stash, char *buf, int counter);
void	generate_line(t_list *stash, char **line);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
t_list	*ft_lstlast(t_list *lst);
void	free_stash(t_list *stash);
size_t	ft_strlen(const char *str);

#endif
