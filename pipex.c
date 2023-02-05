/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/05 18:50:45 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   int execv(const char *path, char *const argv[]);
//   execv("/bin/echo", commands);

int	execute(char **command, char **path, t_fd fd)
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
	i = 0;
	while (commands[i])
	{
		execute(commands[i], path, fd);
		i++;
	}
	return (0);
}

//		./pipex infile "ls -l" "wc -l" outfile
