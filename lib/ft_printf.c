/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:38:17 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 17:09:33 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ptr_test(int fd, size_t loc, int *strlen)
{
	if (loc == 0)
		ft_print_str(fd, "(nil)", strlen);
	else
	{
		*strlen += write(1, "0x", 2);
		ft_print_ptr(fd, loc, strlen);
	}
}

void	print_master(int fd, va_list args, const char c, int *strlen)
{
	if (c == 'c')
		ft_print_char(fd, va_arg(args, int), strlen);
	else if (c == 's')
		ft_print_str(fd, va_arg(args, char *), strlen);
	else if (c == 'p')
		ft_ptr_test(fd, va_arg(args, size_t), strlen);
	else if (c == 'd' || c == 'i')
		ft_print_nbr(fd, va_arg(args, int), strlen);
	else if (c == 'u')
		ft_print_unsigned(fd, va_arg(args, unsigned int), strlen);
	else if (c == 'x')
		ft_print_hex_min(fd, va_arg(args, unsigned int), strlen);
	else if (c == 'X')
		ft_print_hex_maj(fd, va_arg(args, unsigned int), strlen);
	else if (c == '%')
		ft_print_char(fd, 37, strlen);
}

int	ft_printf_fd(int fd, const char *format, ...)
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
			print_master(fd, args, format[i + 1], &strlen);
			i++;
		}
		else
			ft_print_char(fd, format[i], &strlen);
		i++;
	}
	va_end(args);
	return (strlen);
}
