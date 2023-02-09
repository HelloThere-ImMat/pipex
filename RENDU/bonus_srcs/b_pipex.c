/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/09 16:35:18 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	first_process(char **command, char **path, t_fd fd, int *end)
{
	int	d1;
	int	d2;

	d1 = dup2(fd.in, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(end[0]);
	close(fd.in);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(end[1]);
	return (0);
}

int	last_process(char **command, char **path, t_fd fd, int *end)
{
	char	*buf;
	int		d1;
	int		d2;

	buf = malloc(sizeof(char));
	d1 = dup2(end[0], STDIN_FILENO);
	d2 = dup2(fd.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(end[1]);
	close(fd.out);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(end[0]);
	while (read(end[0], buf, 1) > 0)
		write(fd.out, &buf, 1);
	free(buf);
	return (0);
}

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0]);
		if (execve(path[i], command, env) == -1)
			i++;
		else
			return (0);
	}
	write(2, "Command not found\n", 18);
	return (1);
}

int	pipex(t_fd fd, char ***commands, char **path)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
	{
		write(2, "Fork Error\n", 11);
		return (1);
	}
	if (!parent)
	{
		if (first_process(commands[0], path, fd, end) == 1)
			return (1);
	}
	else
	{
		if (last_process(commands[1], path, fd, end) == 1)
			return (1);
	}
	return (0);
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
	print_tab(commands[0]);
	print_tab(commands[1]);
	print_tab(commands[2]);
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