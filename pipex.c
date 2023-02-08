/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/08 16:10:46 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   int execv(const char *path, char *const argv[]);
//   execv("/bin/echo", commands);

int	test_first_process(char **command, char **path, t_fd fd)
{
	int	d1;

	d1 = dup2(STDIN_FILENO, fd.in);
	if (d1 < 0)
		return (1);
	//close(fd);
	if (execute(command, path, fd.env) == 1)
		return (1);
	close(fd.in);
	return (0);
}


int	first_process(char **command, char **path, t_fd fd, int *end)
{
	int	d1;
	int	d2;

	//printf("HELLO FROM CHILD\n");
	d1 = dup2(fd.in, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		return (1);
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

	//printf("HELLO FROM PARENT\n");
	buf = malloc(sizeof(char));
	d1 = dup2(end[0], STDIN_FILENO);
	d2 = dup2(fd.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		return (1);
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
		printf("Fork Error\n");
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
	int		i;

	if (check_arg(argc, argv, &fd) == 1)
		return (1);
	fd.env = env;
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	//print_tab(path);
	//execute(commands[0], path, env);
	//pipex(fd, commands, path);
	test_first_process(commands[0], path, fd);
	return (0);
}

//		./pipex infile "ls -l" "wc -l" outfile
