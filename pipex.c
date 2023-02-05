/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:00:48 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/04 13:03:42 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   int execv(const char *path, char *const argv[]);

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	**new_arg;
	t_fd	fd;

	if (check_arg(argc, argv, &fd) == 1)
		return (1);
	new_arg = ft_split_arg(argc, argv);
	path = get_path(env);
	print_tab(new_arg);
	print_tab(path);
	printf("fd in is %d and fd out is %d\n", fd.in, fd.out);
	//execv("/bin/echo", new_arg);
	return (0);
}

//		./pipex infile "ls -l" "wc -l" outfile
