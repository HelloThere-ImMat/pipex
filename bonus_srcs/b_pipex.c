/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pipex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/03 15:28:37 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0], 1);
		if (execve(path[i], command, env) == -1)
			i++;
	}
	return (1);
}

void	pipex_mult(t_data data, char ***commands, char **path)
{
	int	i;

	create_pipes(&data, commands, path);
	i = 0;
	printf("fd of end tab [7] is %d\n", data.end_tab[2][0]);
	while (i < data.cmdnbr)
	{
		child_process(data, commands, path, i);
		i++;
	}
	waitpid(-1, NULL, 0);
	close_pipes(&data);
	if (data.heredoc == 1)
		unlink(".heredoc_tmp");
	free(data.end_tab);
	free_all(commands, path);
}

int	main(int argc, char **argv, char **env)
{
	int		arg;
	char	**path;
	char	***commands;
	t_data	data;

	data.heredoc = 0;
	data.env = env;
	arg = check_arg(argc, argv, &data);
	if (arg == 1)
		return (1);
	if (arg == 2)
		return (0);
	commands = ft_split_arg(argc, argv);
	path = get_path(env);
	data.cmdnbr = get_cmd_nbr(commands);
	access_main(commands, path);
	pipex_mult(data, commands, path);
	return (0);
}


//ERROR LOG

/*

WE have DUP ERRORS WHEN ONE OF THE COMMANDS IS WRONG, IT IS PROBABLY LINKED TO THE COMMANDS TAB AND THE PIPE TAB WHICH SEG FAULTS CF LINE 35

*/