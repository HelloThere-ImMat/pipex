/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:01:30 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/12 12:02:09 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	test_access(char **path, char **command)
{
	int		i;
	char	*path_str;

	i = 0;
	while (path[i])
	{
		path_str = ft_strjoin(path[i], command[0], 0);
		if (access(path_str, X_OK) == 0)
		{
			free(path_str);
			return (0);
		}
		free(path_str);
		i++;
	}
	ft_printf("command not found: %s\n", command[0]);
	return (1);
}

int	access_main(char ***commands, char **path)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (test_access(path, commands[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
