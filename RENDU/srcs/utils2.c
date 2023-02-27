/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:51:33 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/26 14:03:17 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	execute(char **command, char **path, char **env)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], command[0], 1);
		if (execve(path[i], command, env) == -1)
			i++;
		else
			return (0);
	}
	return (1);
}

void	wait_and_close(t_data data, int end[2])
{
	waitpid(data.pid1, NULL, 0);
	close(end[1]);
	close(data.in);
	waitpid(data.pid2, NULL, 0);
	close(end[0]);
	close(data.out);
}
