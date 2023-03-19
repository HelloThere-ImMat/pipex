/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:17:55 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/19 14:46:04 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	check_arg(int argc, char **argv, t_data *data)
{
	if (argc != 5)
	{
		ft_printf_fd(2, "Arg error\n");
		return (1);
	}
	if (check_files(argv[1], argv[argc - 1], data, 0) == 1)
		return (1);
	return (0);
}

void	error_big_free(char ***commands, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i > index)
	{
		j = 0;
		while (commands[i][j])
			free(commands[i][j++]);
		free(commands[i]);
	}
	free(commands);
}

char	***ft_split_arg(int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * argc - 2);
	if (!commands)
		return (NULL);
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], " ");
		if (!commands[i - 2])
		{
			error_big_free(commands, i - 2);
			return (NULL);
		}
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}
