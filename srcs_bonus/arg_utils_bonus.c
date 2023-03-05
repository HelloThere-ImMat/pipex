/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_arg_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:17:55 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/02 15:41:57 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	check_arg(int argc, char **argv, t_data *data)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data->heredoc = 1;
		if (heredoc_main(argc, argv, data) == 1)
			return (1);
		return (2);
	}
	if (argc < 5)
	{
		ft_printf("Arg error\n");
		return (1);
	}
	if (check_files(argv[1], argv[argc - 1], data, 0) == 1)
		return (1);
	return (0);
}

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

char	***ft_split_arg(int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * argc - 2);
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], " ");
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}
