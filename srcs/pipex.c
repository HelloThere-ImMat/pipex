/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/27 11:42:19 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	if (path == NULL || command[0][0] == 47)
	{
		execve(command[0], command, NULL);
		return (0);
	}
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0], 1);
		if (execve(path[i], command, env) == -1)
			i++;
	}
	return (1);
}

void	free_pipes(t_data data)
{
	int	i;

	i = 0;
	while (i < data.cmdnbr - 1)
		free(data.end_tab[i++]);
	free(data.end_tab);
	close(data.in);
	close(data.out);
}

void	pipex(t_data data, char ***commands, char **path)
{
	int	i;

	create_pipes(&data, commands, path);
	i = 0;
	while (i < data.cmdnbr)
	{
		child_process(data, commands, path, i);
		i++;
	}
	close_pipes(&data);
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
	free_pipes(data);
	free_all(commands, path);
}

int	main(int argc, char **argv, char **env)
{
	int		arg;
	char	**path;
	char	***commands;
	t_data	data;

	data.env = env;
	arg = check_arg(argc, argv, &data);
	if (arg == 1)
		return (1);
	commands = ft_split_arg(argc, argv);
	if (!commands)
		return (1);
	path = get_path(env);
	if (!path && env[0])
		error(4, commands, path);
	data.cmdnbr = get_cmd_nbr(commands);
	access_main(commands, path);
	pipex(data, commands, path);
	return (0);
}
