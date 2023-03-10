/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:51:33 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/10 14:47:29 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	if (path == NULL || command[0][0] == 47)
	{
		execve(command[0], command, NULL);
		return (0);
	}
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0], 1);
		if (execve(path[i], command, env) == -1)
			i++;
	}
	return (1);
}

void	error_cmd(t_data data, char ***commands, char **path, int *end)
{
	close(data.in);
	close(data.out);
	close(end[1]);
	close(end[0]);
	error(0, commands, path);
}

void	error(int type, char ***commands, char **path)
{
	if (type == 1)
		write(2, "Fork Error\n", 11);
	if (type == 2)
		write(2, "Pipe error\n", 11);
	if (type == 3)
		write(2, "Dup error\n", 10);
	free_all(commands, path);
	exit(EXIT_FAILURE);
}

void	wait_and_close(t_data data, int end[2])
{
	waitpid(-1, NULL, 0);
	close(end[1]);
	close(data.in);
	close(end[0]);
	close(data.out);
}
