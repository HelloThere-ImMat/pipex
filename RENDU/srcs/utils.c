/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/10 18:16:56 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

void	free_all(char ***commands, char **path)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
	i = 0;
	while (path[i] && ft_strlen_p(path[i]) != 0)
		free(path[i++]);
	free(path);
}

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
	fd->out = open(argv[argc - 1], O_RDWR | O_TRUNC);
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
	int		i;

	commands = malloc(sizeof(char **) * argc - 2);
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], " ");
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
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
	free(trimed);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/", 1);
		i++;
	}
	return (path);
}

void	print_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i] && ft_strlen_p(path[i]) != 0)
	{
		printf("%s\n", path[i]);
		i++;
	}
	return ;
}
