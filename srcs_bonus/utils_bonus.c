/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/05 15:37:04 by mdorr            ###   ########.fr       */
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

int	check_files(char *in, char *out, t_data *data, int heredoc)
{
	if (heredoc == 0)
	{
		data->in = open(in, O_RDONLY);
		if (data->in == -1)
		{
			if (access(in, F_OK) == 0)
				ft_printf("%s is not accessible\n", in);
			else
				ft_printf("%s no such file or directory\n", in);
			return (1);
		}
		data->out = open(out, O_RDWR | O_TRUNC);
	}
	else
		data->out = open(out, O_RDWR | O_APPEND);
	if (data->out == -1)
	{
		data->out = open(out, O_CREAT | O_RDWR, 0644);
		if (data->out == -1)
		{
			ft_printf("error while creating file\n");
			return (1);
		}
	}
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

void	print_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i] && ft_strlen_p(path[i]) != 0)
	{
		ft_printf("%s\n", path[i]);
		i++;
	}
	return ;
}
