/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 17:37:00 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

void	child_process(t_data data, char ***commands, char **path, int end[2])
{
	int	d1;
	int	d2;

	d1 = dup2(data.in, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		error(3, commands, path);
	close(end[0]);
	execute(commands[0], path, data.env);
}

void	parent_process(t_data data, char ***commands, char **path, int end[2])
{
	int	d1;
	int	d2;

	d1 = dup2(end[0], STDIN_FILENO);
	d2 = dup2(data.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		error(3, commands, path);
	close(end[1]);
	execute(commands[1], path, data.env);
}

void	pipex(t_data data, char ***commands, char **path)
{
	int		end[2];

	if (pipe(end) == -1)
		error(2, commands, path);
	data.pid1 = fork();
	if (data.pid1 < 0)
		error(2, commands, path);
	if (data.pid1 == 0)
		child_process(data, commands, path, end);
	if (data.pid1 > 0)
	{
		data.pid2 = fork();
		if (data.pid2 == 0)
			parent_process(data, commands, path, end);
	}
	if (data.pid1 > 0 || data.pid2 > 0)
		wait_and_close(data, end);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	***commands;
	t_data	data;

	if (check_arg(argc, argv, &data) == 1)
		return (1);
	data.env = env;
	data.argv = argv;
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	access_main(commands, path);
	pipex(data, commands, path);
	free_all(commands, path);
	return (0);
}
