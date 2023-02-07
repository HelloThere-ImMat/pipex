/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/07 00:11:24 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   int execv(const char *path, char *const argv[]);
//   execv("/bin/echo", commands);

int	first_process(char **command, char **path, int fd, int *end)
{
	int	d1;
	int	d2;

	d1 = dup2(fd, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		return (1);
	close(end[0]);
	close(fd);
	if (execute(command, path, fd) == 1)
		return (1);
	return (0);
}

int	last_process(char **command, char **path, int fd, int *end)
{
	int	d1;
	int	d2;

	d1 = dup2(fd, STDIN_FILENO);
	d2 = dup2(end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
		return (1);
	close(end[0]);
	close(fd);
	if (execute(command, path, fd) == 1)
		return (1);
	return (0);
}

int	execute(char **command, char **path, int fd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (execv(path[i], command) == -1)
			i++;
		else
			return (0);
	}
	printf("Command not found\n");
	return (1);
}

void	pipex(t_fd fd, char ***command, char **path, int *end)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork Error"));
	if (!parent)
		first_process(command[0], path, fd.in, end);
	else
		execute(command[1], path, fd.out);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	***commands;
	t_fd	fd;
	int		i;

	if (check_arg(argc, argv, &fd) == 1)
		return (1);
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	//print_tab(env);
	i = 0;
	pipex(fd.in, fd.out);
	// while (commands[i])
	// {
	// 	//execute(commands[i], path, fd);
	// 	printf("---%d---\n", i);
	// 	print_tab(commands[i]);
	// 	i++;
	// }
	return (0);
}

//		./pipex infile "ls -l" "wc -l" outfile
