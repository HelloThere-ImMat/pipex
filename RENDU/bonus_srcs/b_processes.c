/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_processes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:28:39 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 11:56:33 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	first_child(char **command, char **path, t_data data)
{
	int	d1;
	int	d2;

	d1 = dup2(data.in, STDIN_FILENO);
	d2 = dup2(data.end[1], STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(data.end[0]);
	if (execute(command, path, data.env) == 1)
		return (1);
	return (0);
}

//int	middle_process(char **command, char **path, t_data data)
//{
//	int	d1;
//	int	d2;

//	d1 = dup2(data.end[0], STDIN_FILENO);
//	d2 = dup2(data.end2[1], STDOUT_FILENO);
//	if (d1 < 0 || d2 < 0)
//	{
//		write(2, "Dup error\n", 10);
//		return (1);
//	}
//	close(data.end[1]);
//	close(data.end2[0]);
//	if (execute(command, path, data.env) == 1)
//		return (1);
//	close(data.end[0]);
//	close(data.end2[1]);
//	return (0);
//}

int	last_child(char **command, char **path, t_data data)
{
	int		d1;
	int		d2;

	d1 = dup2(data.end[0], STDIN_FILENO);
	d2 = dup2(data.out, STDOUT_FILENO);
	if (d1 < 0 || d2 < 0)
	{
		write(2, "Dup error\n", 10);
		return (1);
	}
	close(data.end[1]);
	if (execute(command, path, data.env) == 1)
		return (1);
	return (0);
}

void	wait_and_close(t_data data)
{
	waitpid(data.pid1, NULL, 0);
	close(data.end[1]);
	close(data.in);
	waitpid(data.pid2, NULL, 0);
	close(data.end[0]);
	close(data.out);
}
