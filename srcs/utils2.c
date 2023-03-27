/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:44 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/27 14:12:20 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

char	**path_error_free(char **path, int index)
{
	int	i;

	i = 0;
	while (i < index && path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (NULL);
}

char	*get_trimed_path(char **env, char ***commands)
{
	int		i;
	int		j;
	char	*trimed;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	if (i == j)
		return (NULL);
	trimed = trim_path(env[i]);
	if (!trimed)
		error(4, commands, NULL);
	return (trimed);
}

char	**get_path(char **env, char ***commands)
{
	int		i;
	char	*trimed;
	char	**path;

	if (!env[0])
		return (NULL);
	trimed = get_trimed_path(env, commands);
	if (!trimed)
		return (NULL);
	path = ft_split(trimed, ":");
	if (!path)
		error(4, commands, path);
	free(trimed);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/", 1);
		if (!path[i])
		{
			path = path_error_free(path, i);
			error(4, commands, path);
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
