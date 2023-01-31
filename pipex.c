/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/29 17:18:37 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
//^-To be removed

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	r;

	r = 0;
	while (s1[r] != '\0' && s2[r] != '\0' && r < n)
	{
		if (s1[r] != s2[r])
		{
			return (s1[r] - s2[r]);
		}
		r++;
	}
	if (r < n)
	{
		return (s1[r] - s2[r]);
	}
	else
	{
		return (0);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*trim_path(char *path)
{
	char	*trim;
	int		len;
	int		i;
	int		j;

	i = 5;
	j = 0;
	len = ft_strlen(path);
	trim = malloc(sizeof(char) * len - 5);
	if (trim == NULL)
		return (NULL);
	while (path[i])
		trim[j++] = path[i++];
	return (trim);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*trimed;
	char	**path;

	(void)argc;
	(void)argv;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	printf("");
	trimed = trim_path(env[i]);
	path = split(env[i], ":");
	return (0);
}
