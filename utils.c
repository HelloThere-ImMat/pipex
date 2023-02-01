/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:30:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/01 13:40:37 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_arg(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("arg error\n");
		return (1);
	}
	return (0);
}

char	**ft_split_arg(int argc, char **argv)
{
	char	**tab;
	char	*word;
	int		i;

	tab = malloc(sizeof(char *) * (argc));
	if (tab == NULL)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		tab[i] = ft_strdup(argv[i + 1]);
		if (tab[i] == NULL)
			return (0);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char **get_path(char **env)
{
	int	i;
	char	*trimed;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	trimed = trim_path(env[i]);
	path = ft_split(trimed, ":");
	return (path);
}

void	print_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i] && ft_strlen(path[i]) != 0)
	{
		printf("%s\n", path[i]);
		i++;
	}
	return ;
}
