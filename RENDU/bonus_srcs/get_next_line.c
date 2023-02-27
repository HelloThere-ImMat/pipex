/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:34:20 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 16:01:27 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/get_next_line.h"

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	int		len;

	i = 0;
	clean = malloc(sizeof(t_list));
	if (stash == NULL || clean == NULL)
		return ;
	clean->next = NULL;
	last = ft_lstlast(*stash);
	len = ft_strlen(last->content);
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char) * (len - i + 1));
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stash(*stash);
	*stash = clean;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	j = 0;
	if (stash == NULL)
		return ;
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i++];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	generate_line(t_list *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (stash != NULL)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

int	read_and_stash(int fd, t_list **stash)
{
	char	*buf;
	int		counter;

	counter = 1;
	while (found_newline(*stash) == 0 && counter != 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buf == NULL)
			return (0);
		counter = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && counter == 0) || counter == -1)
		{
			free(buf);
			free_stash(*stash);
			return (0);
		}
		buf[counter] = '\0';
		add_to_lst(stash, buf, counter);
		free(buf);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (read_and_stash(fd, &stash) == 0)
		return (NULL);
	generate_line(stash, &line);
	extract_line(stash, &line);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	clean_stash(&stash);
	return (line);
}
