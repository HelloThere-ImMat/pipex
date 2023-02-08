/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:57:49 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/08 14:59:23 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(const char *s);

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

int main(void)
{
	char *bla = "bla";
	char *ta = "ta";
	char *total;

	total = ft_strjoin(bla, "/");
	printf("%s\n", total);

}

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

//int	main(void)
//{
//	char	**command;
//	char	*buf;
//	int		end[2];
//	int		fd;

//	buf = malloc(sizeof(char));
//	fd = open("outfile.txt", O_RDWR);
//	pipe(end);
//	command = malloc(sizeof(char *) * 3);
//	command[0] = ft_strdup("wc");
//	command[1] = ft_strdup("-lw");
//	command[2] = NULL;
//	close(end[0]);
//	dup2(end[1], STDOUT_FILENO);
//	execv("/bin/wc", command);
//	while (read(end[0], buf, 1) > 0)
//	{
//		write(1, buf, 1);
//	}
//	return (0);
//}
