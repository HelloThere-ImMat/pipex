/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:28:25 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/28 20:30:36 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

void	sub_dup(int in, int out, char ***commands, char **path)
{
	int	d1;
	int	d2;

	d1 = dup2(in, STDIN_FILENO);
	d2 = dup2(out, STDOUT_FILENO);
	if (d1 < 0)
		d1 = dup2(-1, STDIN_FILENO);
	(void)commands;
	(void)path;
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmdnbr - 1)
	{
		close(data->end_tab[i][0]);
		close(data->end_tab[i][1]);
		i++;
	}
}

void	clean_exit(t_data data, char ***commands, char **path)
{
	close(data.in);
	close(data.out);
	close_pipes(&data);
	free_pipes(data);
	error(0, commands, path);
}

void	child_process(t_data data, char ***commands, char **path, int cmd_i)
{
	data.pid = fork();
	if (data.pid == 0)
	{
		if (!commands[cmd_i][0] || test_access2(path, commands[cmd_i]) == 1)
			clean_exit(data, commands, path);
		if (cmd_i == 0)
			sub_dup(data.in, data.end_tab[cmd_i][1], commands, path);
		else if (cmd_i == data.cmdnbr - 1)
			sub_dup(data.end_tab[cmd_i - 1][0], data.out, commands, path);
		else if (cmd_i > 0 && cmd_i < data.cmdnbr - 1)
			sub_dup(data.end_tab[cmd_i - 1][0],
				data.end_tab[cmd_i][1], commands, path);
		close_pipes(&data);
		if (execute(commands[cmd_i], path, data.env) == 1)
			clean_exit(data, commands, path);
	}
}
