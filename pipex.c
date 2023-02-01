/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/01 13:41:00 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   int execv(const char *path, char *const argv[]);

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	**new_arg;

	new_arg = ft_split_arg(argc, argv);
	//new_arg = NULL;
	//path = get_path(env);
	//printf("%s\n", new_arg[0]);
	//print_tab(new_arg);
	//print_tab(path);
	execv("/bin/echo", new_arg);
	return (0);
}

//		./pipex infile "ls -l" "wc -l" outfile
