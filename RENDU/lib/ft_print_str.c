/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:39:36 by mdorr             #+#    #+#             */
/*   Updated: 2022/11/24 15:48:13 by mdorr            ###   ########.fr       */
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

void	ft_print_char(char c, int *strlen)
{
	(*strlen)++;
	write(1, &c, 1);
}

void	ft_print_str(char *s, int *strlen)
{
	int	i;
	int	len;

	i = 0;
	if (s == NULL)
	{
		ft_print_str("(null)", strlen);
		return ;
	}
	len = ft_strlen(s);
	while (i < len)
	{
		write(1, &s[i], 1);
		i++;
	}
	*strlen += len;
}
