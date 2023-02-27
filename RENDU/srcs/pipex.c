/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 11:26:51 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	first_child(char **command, char **path, t_data data, int end[2])
{
	int	d1;
	int	d2;

	d1 = dup2(data.in, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(end[0]);
	if (execute(command, path, data.env) == 1)
		return (1);
	return (0);
}

int	last_child(char **command, char **path, t_data data, int end[2])
{
	int		d1;
	int		d2;

	d1 = dup2(end[0], STDIN_FILENO);
	d2 = dup2(data.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(end[1]);
	if (execute(command, path, data.env) == 1)
		return (1);
	return (0);
}

pid_t	parent_process(t_data data, char ***commands, char **path, int end[2])
{
	pid_t	t_pid2;


	t_pid2 = fork();
	if (t_pid2 < 0)
	{
		write(2, "Fork Error\n", 11);
		return (-1);
	}
	if (!t_pid2)
	{
		waitpid(data.pid1, NULL, 0);
		if (last_child(commands[1], path, data, end) == 1)
			return (-1);
	}
	return (t_pid2);

}

int	pipex(t_data data, char ***commands, char **path)
{
	int		end[2];

	pipe(end);
	data.pid1 = fork();
	if (data.pid1 < 0)
	{
		write(2, "Fork Error\n", 11);
		return (1);
	}
	if (!data.pid1)
	{
		if (first_child(commands[0], path, data, end) == 1)
			return (1);
	}
	if (data.pid1 > 0)
	{
		data.pid2 = parent_process(data, commands, path, end);
		if (data.pid2 == -1)
			return (1);
	}
	if (data.pid1 > 0 && data.pid2 > 0)
		wait_and_close(data, end);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	***commands;
	t_data	data;

	if (check_arg(argc, argv, &data) == 1)
		return (1);
	data.env = env;
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	if (access_main(commands, path) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	if (pipex(data, commands, path) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	free_all(commands, path);
	return (0);
}

/*

FORMAT :	./pipex infile "ls -l" "wc -l" outfile

ERROR LOGS :

	si la command 2 est incorecte n'excecuter que la commande 1

	si la command 1 et incorecte, n'excecuter que la commande 2

	et ducoup utiliser /dev/null comme input pour prevenir les bugs



*/