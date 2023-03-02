/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:42:02 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/02 17:25:08 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/get_next_line.h"

void	add_to_lst(t_list **stash, char *buf, int counter)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->content = malloc(sizeof(char) * counter + 1);
	if (new_node->content == NULL)
		return ;
	new_node->next = NULL;
	i = 0;
	while (buf[i] && i < counter)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last_node = ft_lstlast(*stash);
	last_node->next = new_node;
}

int	found_newline(t_list *stash)
{
	t_list	*current;
	int		i;

	i = 0;
	if (stash == NULL)
		return (0);
	current = ft_lstlast(stash);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
