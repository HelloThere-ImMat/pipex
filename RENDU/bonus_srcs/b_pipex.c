/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/15 12:05:11 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	init_fork(t_fd fd, pid_t **pid)
{
	int		i;

	i = 0;
	*pid = malloc(sizeof(pid_t) * (fd.cmdnbr));
	while (i < fd.cmdnbr)
	{
		*pid[i] = fork();
		if (*pid[i] < 0)
		{
			write(2, "Fork Error\n", 11);
			return (1);
		}
		if (pid[i] == 0)
			return (0);
		i++;
	}
	return (0);
}

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
			printf("Salut\n");
	}
	return (1);
}

int	pipex(t_fd fd, char ***commands, char **path)
{
	pid_t	*pid;
	int		i;

	if (init_fork(fd, &pid) == 1)
		return (1);
	if (pid[0] == 0)
	{
		if (first_process(commands[0], path, fd) == 1)
			return (1);
	}
	i = 1;
	while (i < fd.cmdnbr - 1)
	{
		if (pid[i] == 0)
		{
			if (middle_process(commands[i], path, fd) == 1)
				return (1);
		}
	}
	if (pid[fd.cmdnbr] == 0)
	{
		if (last_process(commands[fd.cmdnbr - 1], path, fd) == 1)
			return (1);
	}
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
	t_fd	fd;

	if (check_arg(argc, argv, &fd) == 1)
		return (1);
	fd.env = env;
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	fd.cmdnbr = get_cmd_nbr(commands);
	if (access_main(commands, path) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	if (pipex(fd, commands, path) == 1)
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

ERRORS LOGS :
	command not found should write the command name
		Command not found : cato
			solution : test the commands with the access function before calling pipex


LEAKS



*/