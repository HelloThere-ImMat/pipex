/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:38:17 by mdorr             #+#    #+#             */
/*   Updated: 2022/11/24 15:39:42 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ptr_test(size_t loc, int *strlen)
{
	if (loc == 0)
		ft_print_str("(nil)", strlen);
	else
	{
		*strlen += write(1, "0x", 2);
		ft_print_ptr(loc, strlen);
	}
}

void	print_master(va_list args, const char c, int *strlen)
{
	if (c == 'c')
		ft_print_char(va_arg(args, int), strlen);
	else if (c == 's')
		ft_print_str(va_arg(args, char *), strlen);
	else if (c == 'p')
		ft_ptr_test(va_arg(args, size_t), strlen);
	else if (c == 'd' || c == 'i')
		ft_print_nbr(va_arg(args, int), strlen);
	else if (c == 'u')
		ft_print_unsigned(va_arg(args, unsigned int), strlen);
	else if (c == 'x')
		ft_print_hex_min(va_arg(args, unsigned int), strlen);
	else if (c == 'X')
		ft_print_hex_maj(va_arg(args, unsigned int), strlen);
	else if (c == '%')
		ft_print_char(37, strlen);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		strlen;
	va_list	args;

	va_start(args, format);
	i = 0;
	strlen = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			print_master(args, format[i + 1], &strlen);
			i++;
		}
		else
			ft_print_char(format[i], &strlen);
		i++;
	}
	va_end(args);
	return (strlen);
}
