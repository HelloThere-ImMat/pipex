/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:40:06 by mdorr             #+#    #+#             */
/*   Updated: 2022/11/24 15:50:49 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
void	ft_print_unsigned(unsigned int nb, int *strlen);
void	print_master(va_list args, const char c, int *strlen);
void	ft_print_ptr(size_t loc, int *strlen);
void	ft_print_hex_maj(unsigned int hex, int *strlen);
void	ft_print_hex_min(unsigned int hex, int *strlen);
void	ft_print_nbr(int nb, int *strlen);
void	ft_print_str(char *s, int *strlen);
void	ft_print_char(char c, int *strlen);
size_t	ft_strlen(const char *str);

#endif
