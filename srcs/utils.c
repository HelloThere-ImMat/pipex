/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/18 11:41:19 by mdorr            ###   ########.fr       */
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

static int	check_out_file(char *out, t_data *data, int heredoc)
{
	if (heredoc == 0)
		data->out = open(out, O_RDWR | O_TRUNC);
	else
		data->out = open(out, O_RDWR | O_APPEND);
	if (access(out, F_OK) == 0 && data->out == -1)
		ft_printf_fd(2, "%s is not accessible\n", out);
	else if (data->out == -1)
	{
		data->out = open(out, O_CREAT | O_RDWR, 0644);
		if (data->out == -1)
			ft_printf_fd(2, "error while creating file");
	}
	return (0);
}

int	check_files(char *in, char *out, t_data *data, int heredoc)
{
	if (heredoc == 0)
	{
		data->in = open(in, O_RDONLY);
		if (data->in == -1)
		{
			if (access(in, F_OK) == 0)
				ft_printf_fd(2, "%s is not accessible\n", in);
			else
				ft_printf_fd(2, "%s no such file or directory\n", in);
		}
		check_out_file(out, data, heredoc);
	}
	else
		check_out_file(out, data, heredoc);
	return (0);
}

int	get_cmd_nbr(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

int	**init_end_tab(t_data data)
{
	int	**end_tab;
	int	i;

	i = 0;
	end_tab = malloc(sizeof(int *) * (data.cmdnbr - 1));
	while (i < data.cmdnbr - 1)
	{
		end_tab[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (end_tab);
}
