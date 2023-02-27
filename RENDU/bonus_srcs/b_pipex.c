/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 14:39:13 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0], 1);
		if (execve(path[i], command, env) == -1)
			i++;
		else
			return (0);
	}
	return (1);
}

pid_t	parent_process(t_data data, char ***commands, char **path)
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
		if (last_child(commands[1], path, data) == 1)
			return (-1);
	}
	return (t_pid2);

}

int	pipex(t_data data, char ***commands, char **path)
{
	pipe(data.end);
	data.pid1 = fork();
	if (data.pid1 < 0)
	{
		write(2, "Fork Error\n", 11);
		return (1);
	}
	if (!data.pid1)
	{
		if (first_child(commands[0], path, data) == 1)
			return (1);
	}
	if (data.pid1 > 0)
	{
		data.pid2 = parent_process(data, commands, path);
		if (data.pid2 == -1)
			return (1);
	}
	if (data.pid1 > 0 && data.pid2 > 0)
		wait_and_close(data);
	return (0);
}

int	get_cmd_nbr(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	***commands;
	t_data	data;

	data.env = env;
	if (check_arg(argc, argv, &data) == 1 || check_arg(argc, argv, &data) == 2)
		return (1);
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	data.cmdnbr = get_cmd_nbr(commands);
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


TBD : Heredoc and >>
	for heredoc
		we have to change the split arg as it is different for the heredoc

ERRORS LOGS :


LEAKS



*/