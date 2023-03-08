/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:44 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 14:45:05 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

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

int	**init_end_tab(t_data data)
{
	int	**end_tab;
	int	i;

	i = 0;
	end_tab = malloc(sizeof(int *) * data.cmdnbr);
	while (i < data.cmdnbr - 1)
	{
		end_tab[i] = malloc(sizeof(int) * 2);
		i++;
	}
	end_tab[i] = NULL;
	return (end_tab);
}
