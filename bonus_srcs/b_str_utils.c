/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_str_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:03:25 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/27 16:21:47 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	if (s == NULL)
		return (NULL);
	while (s[len])
		len++;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	r;

	r = 0;
	if (!s1 || !s2)
		return (-1);
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

int	ft_strlen_p(const char *str)
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
	len = ft_strlen_p(path);
	trim = malloc(sizeof(char) * len - 4);
	if (trim == NULL)
		return (NULL);
	while (path[i])
		trim[j++] = path[i++];
	trim[j] = '\0';
	return (trim);
}

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
