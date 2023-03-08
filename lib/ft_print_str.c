/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:39:36 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 17:10:14 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_print_char(int fd, char c, int *strlen)
{
	(*strlen)++;
	write(fd, &c, 1);
}

void	ft_print_str(int fd, char *s, int *strlen)
{
	int	i;
	int	len;

	i = 0;
	if (s == NULL)
	{
		ft_print_str(fd, "(null)", strlen);
		return ;
	}
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
	*strlen += len;
}
