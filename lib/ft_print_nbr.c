/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:38:17 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 17:12:14 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_unsigned(int fd, unsigned int nb, int *strlen)
{
	if (nb <= 9)
	{
		ft_print_char(fd, nb + 48, strlen);
	}
	if (nb >= 10)
	{
		ft_print_unsigned(fd, nb / 10, strlen);
		ft_print_unsigned(fd, nb % 10, strlen);
	}
}

void	ft_print_nbr(int fd, int nb, int *strlen)
{
	long int	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_print_char(fd, '-', strlen);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_print_char(fd, nbr + 48, strlen);
	}
	if (nbr >= 10)
	{
		ft_print_nbr(fd, nbr / 10, strlen);
		ft_print_nbr(fd, nbr % 10, strlen);
	}
}

void	ft_print_hex_min(int fd, unsigned int hex, int *strlen)
{
	char	*base;

	if (hex > 15)
	{
		ft_print_hex_min(fd, hex / 16, strlen);
		ft_print_hex_min(fd, hex % 16, strlen);
	}
	else
	{
		base = "0123456789abcdef";
		ft_print_char(fd, base[hex], strlen);
	}
}

void	ft_print_hex_maj(int fd, unsigned int hex, int *strlen)
{
	char	*base;

	if (hex > 15)
	{
		ft_print_hex_maj(fd, hex / 16, strlen);
		ft_print_hex_maj(fd, hex % 16, strlen);
	}
	else
	{
		base = "0123456789ABCDEF";
		ft_print_char(fd, base[hex], strlen);
	}
}

void	ft_print_ptr(int fd, size_t loc, int *strlen)
{
	if (loc > 15)
	{
		ft_print_ptr(fd, loc / 16, strlen);
		ft_print_ptr(fd, loc % 16, strlen);
	}
	else
		ft_print_hex_min(fd, (unsigned int)loc, strlen);
}
