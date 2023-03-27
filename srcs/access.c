/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:01:30 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/27 09:59:18 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

void	test_access_absolute(char **command, char **path)
{
	if (path == NULL && command[0][0] != '/')
	{
		ft_printf_fd(2, "command not found: %s\n", command[0]);
		return ;
	}
	if (access(command[0], X_OK) == 0)
		return ;
	else
		ft_printf_fd(2, "command not found: %s\n", command[0]);
}

void	test_access(char **path, char **command)
{
	int		i;
	char	*path_str;

	i = 0;
	if (!command[0])
	{
		ft_printf_fd(2, "command not found : %s\n", command[0]);
		return ;
	}
	if (path == NULL || command[0][0] == 47)
	{
		test_access_absolute(command, path);
		return ;
	}
	while (path[i])
	{
		path_str = ft_strjoin(path[i++], command[0], 0);
		if (access(path_str, X_OK) == 0)
		{
			free(path_str);
			return ;
		}
		free(path_str);
	}
	ft_printf_fd(2, "command not found: %s\n", command[0]);
}

void	access_main(char ***commands, char **path)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		test_access(path, commands[i]);
		i++;
	}
}
