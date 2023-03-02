/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:48:52 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/02 17:25:42 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

char	*ft_strjoin(char *s1, const char *s2, int must_free)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char)
			* (ft_strlen_p(s1) + ft_strlen_p(s2) + 1));
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
	if (must_free == 1)
		free(s1);
	return (dst);
}

void	writestr(int fd, const char *str)
{
	write(fd, str, ft_strlen_p(str));
}
