/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 14:31:01 by mdorr            ###   ########.fr       */
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
	if (path == NULL)
		return ;
	while (path[i] && ft_strlen_p(path[i]) != 0)
		free(path[i++]);
	free(path);
}

int	check_arg(int argc, char **argv, t_data *data)
{
	if (argc != 5)
	{
		ft_printf("Arg error\n");
		return (1);
	}
	data->in = open(argv[1], O_RDONLY);
	if (data->in == -1)
	{
		if (access(argv[1], F_OK) == 0)
			ft_printf("%s is not accessible\n", argv[1]);
		else
			ft_printf("%s no such file or directory\n", argv[1]);
		return (1);
	}
	data->out = open(argv[argc - 1], O_RDWR | O_TRUNC);
	if (data->out == -1)
	{
		data->out = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
		if (data->out == -1)
		{
			ft_printf("error while creating file\n");
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
	if (!env[0])
		return (NULL);
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
		ft_printf("%s\n", path[i]);
		i++;
	}
	return ;
}
