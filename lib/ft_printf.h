/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:40:06 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/08 17:15:33 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf_fd(int fd, const char *format, ...);
void	ft_print_unsigned(int fd, unsigned int nb, int *strlen);
void	print_master(int fd, va_list args, const char c, int *strlen);
void	ft_print_ptr(int fd, size_t loc, int *strlen);
void	ft_print_hex_maj(int fd, unsigned int hex, int *strlen);
void	ft_print_hex_min(int fd, unsigned int hex, int *strlen);
void	ft_print_nbr(int fd, int nb, int *strlen);
void	ft_print_str(int fd, char *s, int *strlen);
void	ft_print_char(int fd, char c, int *strlen);
size_t	ft_strlen(const char *str);

#endif
