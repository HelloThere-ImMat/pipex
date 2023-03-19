/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:36 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/15 17:19:08 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

char	*double_and_fill(int buffer_size, char *buffer, int position)
{
	char	*new_buffer;
	int		i;

	new_buffer = malloc(sizeof(char) * buffer_size);
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (i <= position)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

char	*read_input(void)
{
	t_read	r;

	r.buffer_size = 32;
	r.position = 0;
	r.buffer = malloc(sizeof(char) * r.buffer_size);
	if (r.buffer == NULL)
		return (NULL);
	while ((read(STDIN_FILENO, &r.buffer[r.position], 1)) > 0)
	{
		if (r.buffer[r.position] == '\n')
		{
			r.buffer[r.position] = '\0';
			return (r.buffer);
		}
		r.position++;
		if (r.position == r.buffer_size - 1)
		{
			r.buffer_size *= 2;
			r.new_buffer = double_and_fill(r.buffer_size, r.buffer, r.position);
			r.buffer = r.new_buffer;
		}
	}
	r.buffer[r.position] = '\0';
	return (r.buffer);
}
