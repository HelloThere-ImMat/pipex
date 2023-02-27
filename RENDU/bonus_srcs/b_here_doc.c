/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:18:41 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 16:23:43 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	check_hd_arg(int argc, char **argv, t_data *data)
{
	if (argc != 6)
		return (1);
	if (check_files(NULL, argv[5], data, 1) == 1)
		return (1);
	return (0);
}

char	***ft_split_hd_arg(char **argv)
{
	char	***commands;

	commands = malloc(sizeof(char **) * 3);
	commands[0] = ft_split(argv[3], " ");
	commands[1] = ft_split(argv[4], " ");
	commands[2] = NULL;
	return (commands);
}

int	read_and_write(t_data data, char *limiter)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	line = NULL;
	while (ft_strncmp(limiter, line, len) != 0)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		write(data.out, line, ft_strlen(line));
		//write(data.end[1], line, ft_strlen(line));
	}
	free(line);
	printf("on est sorti de la boucle\n");
	return (0);
}

int	ft_heredoc(t_data data, char ***commands, char **path, char *limiter)
{
	//pipe(data.end);
	//data.pid1 = fork();
	//if (data.pid1 < 0)
	//{
	//	write(2, "Fork Error\n", 11);
	//	return (1);
	//}
	//if (!data.pid1)
	//{
	//	if (read_and_write(data, limiter) == 1)
	//		return (0);
	//}
	read_and_write(data, limiter);
	(void)commands;
	(void)path;
	return (0);
}

int	heredoc_main(int argc, char **argv, t_data *data)
{
	char	***commands;
	char	**path;

	if (check_hd_arg(argc, argv, data) == 1)
		return (1);
	commands = ft_split_hd_arg(argv);
	path = get_path(data->env);
	if (access_main(commands, path) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	if (ft_heredoc(*data, commands, path, argv[2]) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	free_all(commands, path);
	return (0);
}
