/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/12 16:50:07 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	check_arg(int argc, char **argv, t_data *data)
{
	if (argc != 5)
	{
		ft_printf_fd(2, "Arg error\n");
		return (1);
	}
	data->in = open(argv[1], O_RDONLY);
	if (data->in == -1)
	{
		if (access(argv[1], F_OK) == 0)
			ft_printf_fd(2, "%s is not accessible\n", argv[1]);
		else
			ft_printf_fd(2, "%s no such file or directory\n", argv[1]);
		data->in = open("/dev/null", O_RDONLY);
	}
	data->out = open(argv[argc - 1], O_RDWR | O_TRUNC);
	if (data->out == -1)
	{
		data->out = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
		if (data->out == -1)
		{
			ft_printf_fd(2, "error while creating file\n");
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
	if (!commands)
		return (NULL);
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], " ");
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}

char	*get_trimed_path(char **env)
{
	int		i;
	char	*trimed;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	trimed = trim_path(env[i]);
	if (!trimed)
		return (NULL);
	return (trimed);
}

char	**path_error_free(char **path, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (NULL);
}

char	**get_path(char **env)
{
	int		i;
	char	*trimed;
	char	**path;

	if (!env[0])
		return (NULL);
	trimed = get_trimed_path(env);
	path = ft_split(trimed, ":");
	if (!path)
		return (NULL);
	free(trimed);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/", 1);
		if (!path[i])
		{
			path = path_error_free(path, i);
			return (NULL);
		}
		i++;
	}
	return (path);
}

//void	print_tab(char **path)
//{
//	int	i;

//	i = 0;
//	while (path[i] && ft_strlen_p(path[i]) != 0)
//	{
//		ft_printf_fd(1, "%s\n", path[i]);
//		i++;
//	}
//	return ;
//}
