/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:17 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/15 17:57:01 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/b_pipex.h"

int	get_cmd_nbr(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

int	**init_end_tab(t_data data)
{
	int	**end_tab;
	int	i;

	i = 0;
	end_tab = malloc(sizeof(int *) * data.cmdnbr - 1);
	while (i < data.cmdnbr - 1)
	{
		end_tab[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (end_tab);
}
