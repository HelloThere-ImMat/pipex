/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 13:56:58 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

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

int	check_arg(int argc, char **argv, t_data *data)
{
	if (argc < 5)
	{
		ft_printf("Arg error\n");
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (ft_heredoc() == 1)
			return (1);
		return (0);
	}
	data->in = open(argv[1], O_RDONLY);
	if (data->in == -1)
	{
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