/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:38:17 by mdorr             #+#    #+#             */
/*   Updated: 2022/11/24 15:46:31 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_unsigned(unsigned int nb, int *strlen)
{
	if (nb <= 9)
	{
		ft_print_char(nb + 48, strlen);
	}
	if (nb >= 10)
	{
		ft_print_unsigned(nb / 10, strlen);
		ft_print_unsigned(nb % 10, strlen);
	}
}

void	ft_print_nbr(int nb, int *strlen)
{
	long int	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_print_char('-', strlen);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_print_char(nbr + 48, strlen);
	}
	if (nbr >= 10)
	{
		ft_print_nbr(nbr / 10, strlen);
		ft_print_nbr(nbr % 10, strlen);
	}
}

void	ft_print_hex_min(unsigned int hex, int *strlen)
{
	char	*base;

	if (hex > 15)
	{
		ft_print_hex_min(hex / 16, strlen);
		ft_print_hex_min(hex % 16, strlen);
	}
	else
	{
		base = "0123456789abcdef";
		ft_print_char(base[hex], strlen);
	}
}

void	ft_print_hex_maj(unsigned int hex, int *strlen)
{
	char	*base;

	if (hex > 15)
	{
		ft_print_hex_maj(hex / 16, strlen);
		ft_print_hex_maj(hex % 16, strlen);
	}
	else
	{
		base = "0123456789ABCDEF";
		ft_print_char(base[hex], strlen);
	}
}

void	ft_print_ptr(size_t loc, int *strlen)
{
	if (loc > 15)
	{
		ft_print_ptr(loc / 16, strlen);
		ft_print_ptr(loc % 16, strlen);
	}
	else
		ft_print_hex_min((unsigned int)loc, strlen);
}
