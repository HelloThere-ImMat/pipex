/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:18:41 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/02 17:24:25 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

void	read_and_write(char *limiter, int fd_hd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, line, len) == 0)
			break ;
		write(fd_hd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd_hd);
}

int	ft_heredoc(t_data *data, char *limiter)
{
	int	fd_hd;

	fd_hd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd_hd == -1)
	{
		unlink(".heredoc_tmp");
		ft_printf("Error while creating file\n");
		return (1);
	}
	read_and_write(limiter, fd_hd);
	data->in = open(".heredoc_tmp", O_RDONLY);
	if (data->in < 0)
	{
		unlink(".heredoc_tmp");
		ft_printf("Error with heredoc file\n");
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
	path = get_path(data->env);
	data->cmdnbr = get_cmd_nbr(commands);
	if (access_main(commands, path) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	if (ft_heredoc(data, argv[2]) == 1)
	{
		free_all(commands, path);
		return (1);
	}
	pipex_mult(*data, commands, path);
	return (0);
}
