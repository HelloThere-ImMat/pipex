/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:01:30 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/01 13:04:30 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	test_access_absolute(char **command, char **path)
{
	if (access(command[0], X_OK) == 0)
		return (EXIT_SUCCESS);
	else if (path == NULL && command[0][0] != '/')
	{
		ft_printf_fd(2, "command not found: %s\n", command[0]);
		return (EXIT_FAILURE);
	}
	else
		ft_printf_fd(2, "command not found: %s\n", command[0]);
	return (EXIT_FAILURE);
}

int	test_access_absolute_np(char **command, char **path)
{
	if (access(command[0], X_OK) == 0)
		return (EXIT_SUCCESS);
	else if (path == NULL && command[0][0] != '/')
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	test_access(char **path, char **command)
{
	int		i;
	char	*path_str;

	i = 0;
	if (!command[0])
	{
		ft_printf_fd(2, "command not found : %s\n", command[0]);
		return (EXIT_FAILURE);
	}
	if (path == NULL || command[0][0] == 47)
	{
		return (test_access_absolute(command, path));
	}
	while (path[i])
	{
		path_str = ft_strjoin(path[i++], command[0], 0);
		if (access(path_str, X_OK) == 0)
		{
			free(path_str);
			return (EXIT_SUCCESS);
		}
		free(path_str);
	}
	ft_printf_fd(2, "command not found: %s\n", command[0]);
	return (EXIT_FAILURE);
}

int	test_access_np(char **path, char **command)
{
	int		i;
	char	*path_str;

	i = 0;
	if (!command[0])
	{
		return (EXIT_FAILURE);
	}
	if (path == NULL || command[0][0] == 47)
	{
		return (test_access_absolute_np(command, path));
	}
	while (path[i])
	{
		path_str = ft_strjoin(path[i++], command[0], 0);
		if (access(path_str, X_OK) == 0)
		{
			free(path_str);
			return (EXIT_SUCCESS);
		}
		free(path_str);
	}
	return (EXIT_FAILURE);
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
