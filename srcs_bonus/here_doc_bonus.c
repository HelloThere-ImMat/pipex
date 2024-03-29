/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:18:41 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/18 13:25:36 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	read_and_write(char *limiter, int fd_hd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = read_input();
		if (ft_strlen(limiter) == ft_strlen(line)
			&& ft_strncmp(limiter, line, len) == 0)
			break ;
		if (ft_strlen(line) == 0 && line[0] != '\n')
			break ;
		write(fd_hd, line, ft_strlen(line));
		write(fd_hd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_hd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_data *data, char *limiter)
{
	int	fd_hd;

	fd_hd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd_hd == -1)
	{
		unlink(".heredoc_tmp");
		ft_printf_fd(2, "Error while creating file\n");
		return (1);
	}
	if (read_and_write(limiter, fd_hd) == 1)
		return (1);
	data->in = open(".heredoc_tmp", O_RDONLY);
	if (data->in < 0)
	{
		unlink(".heredoc_tmp");
		ft_printf_fd(2, "Error with heredoc file\n");
		return (1);
	}
	return (0);
}

int	heredoc_main(int argc, char **argv, t_data *data)
{
	char	***commands;
	char	**path;

	if (check_hd_arg(argc, argv, data) == 1)
		return (1);
	commands = ft_split_hd_arg(argv);
	if (!commands)
		return (1);
	path = get_path(data->env, commands);
	if (!path)
		return (1);
	data->cmdnbr = get_cmd_nbr(commands);
	access_main(commands, path);
	if (ft_heredoc(data, argv[2]) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	pipex_mult(*data, commands, path);
	return (0);
}
