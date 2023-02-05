/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:57:49 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/05 17:50:39 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(const char *s);

//int	main()
//{
//	int	fd;

//	fd = open("out.txt", O_RDWR);
//	if (fd == -1)
//	{
//		printf("No such file\n");
//		fd = open("out.txt", O_CREAT | O_RDWR);
//		if (fd == -1)
//		{
//			printf("error creating file\n");
//			return (1);
//		}
//		printf("file created and the fd is %d\n", fd);
//		return (0);
//	}
//	printf("is all good\n");
//	return (0);

//}

int	main(void)
{
	char	**command;

	command = malloc(sizeof(char *) * 3);
	command[0] = ft_strdup("wc");
	command[1] = ft_strdup("-lw");
	command[2] = NULL;

	execv("/bin/wc", command);
}
