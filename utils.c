/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/08 15:02:46 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_arg(int argc, char **argv, t_fd *fd)
{
	if (argc != 5)
	{
		printf("arg error\n");
		return (1);
	}
	fd->in = open(argv[1], O_RDONLY);
	if (fd->in == -1)
	{
		printf("%s no such file or directory\n", argv[1]);
		return (1);
	}
	fd->out = open(argv[argc - 1], O_RDWR);
	if (fd->out == -1)
	{
		fd->out = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
		if (fd->out == -1)
		{
			printf("error while creating file\n");
			return (1);
		}
	}
	return (0);
}

char	***ft_split_arg(int argc, char **argv)
{
	char	***commands;
	char	**tab;
	char	*word;
	int		i;

	commands = malloc(sizeof(char **) * argc - 3);
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], " ");
		i++;
	}
	return (commands);
}

void	writestr(int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
}

char	**get_path(char **env)
{
	int		i;
	char	*trimed;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	trimed = trim_path(env[i]);
	path = ft_split(trimed, ":");
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

void	print_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i] && ft_strlen(path[i]) != 0)
	{
		printf("%s\n", path[i]);
		i++;
	}
	return ;
}
