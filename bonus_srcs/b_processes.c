/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_processes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:08:02 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/03 15:19:32 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

void	sub_dup(int in, int out, char ***commands, char **path)
{
	int	d1;
	int	d2;

	write(1, "in dup\n", 7);
	d1 = dup2(in, STDIN_FILENO);
	d2 = dup2(out, STDOUT_FILENO);
	printf("D1 is %d and D2 is %d\n", d1, d2);
	printf("in est %d et out est %d\n", in, out);
	if (d1 < 0 || d2 < 0)
		error(3, commands, path);
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

void	child_process(t_data data, char ***commands, char **path, int cmd_i)
{
	data.pid = fork();
	if (data.pid == 0)
	{
		if (cmd_i == 0)
			sub_dup(data.in, data.end_tab[cmd_i][1], commands, path);
		else if (cmd_i == data.cmdnbr - 1)
			sub_dup(data.end_tab[cmd_i - 1][0], data.out, commands, path);
		else
			sub_dup(data.end_tab[cmd_i - 1][0],
				data.end_tab[cmd_i][1], commands, path);
		close_pipes(&data);
		execute(commands[cmd_i], path, data.env);
	}
}
