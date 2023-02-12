/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_processes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:28:39 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/12 13:53:36 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	first_process(char **command, char **path, t_fd fd)
{
	int	d1;
	int	d2;

	d1 = dup2(fd.in, STDIN_FILENO);
	d2 = dup2(fd.end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(fd.end[0]);
	close(fd.in);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(fd.end[1]);
	return (0);
}

int	middle_process(char **command, char **path, t_fd fd)
{
	char	*buf;
	int		d1;
	int		d2;

	buf = malloc(sizeof(char));
	d1 = dup2(fd.end[0], STDIN_FILENO);
	d2 = dup2(fd.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(fd.end[1]);
	close(fd.out);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(fd.end[0]);
	while (read(fd.end[0], buf, 1) > 0)
		write(fd.out, &buf, 1);
	free(buf);
	return (0);
}


int	last_process(char **command, char **path, t_fd fd)
{
	char	*buf;
	int		d1;
	int		d2;

	buf = malloc(sizeof(char));
	d1 = dup2(fd.end[0], STDIN_FILENO);
	d2 = dup2(fd.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(fd.end[1]);
	close(fd.out);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(fd.end[0]);
	while (read(fd.end[0], buf, 1) > 0)
		write(fd.out, &buf, 1);
	free(buf);
	return (0);
}