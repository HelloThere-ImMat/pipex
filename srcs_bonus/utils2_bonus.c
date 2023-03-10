/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:44 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/14 03:45:20 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

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

void	error(int type, char ***commands, char **path)
{
	if (type == 1)
		write(2, "Fork Error\n", 11);
	if (type == 2)
		write(2, "Pipe error\n", 11);
	if (type == 3)
		write(2, "Dup error\n", 10);
	if (type == 4)
		write(2, "Malloc error\n", 13);
	free_all(commands, path);
	exit(EXIT_FAILURE);
}

void	create_pipes(t_data *data, char ***commands, char **path)
{
	int	i;

	i = 0;
	data->end_tab = init_end_tab(*data);
	while (i < data->cmdnbr - 1)
	{
		if (pipe(data->end_tab[i]) == -1)
		{
			free(data->end_tab);
			error(2, commands, path);
		}
		i++;
	}
}
