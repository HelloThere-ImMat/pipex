/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:08:18 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/27 09:59:13 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../deps/pipex.h"

int	char_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_str(char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (char_is_in_charset(str[i], charset) && str[i] != '\0')
			i++;
		if (!char_is_in_charset(str[i], charset) && str[i] != '\0')
			count++;
		while (!char_is_in_charset(str[i], charset) && str[i] != '\0')
			i++;
	}
	return (count);
}

int	wlength(char *str, int *j, char *charset)
{
	int	len;

	len = 0;
	while (char_is_in_charset(str[*j], charset) && str[*j] != '\0')
		(*j)++;
	while (!char_is_in_charset(str[*j], charset) && str[*j] != '\0')
	{
		(*j)++;
		len++;
	}
	return (len);
}

char	*get_word(char *str, int len, int *j, char *charset)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (char_is_in_charset(str[*j], charset) && str[*j] != '\0')
		(*j)++;
	while (!char_is_in_charset(str[*j], charset) && str[*j] != '\0')
	{
		word[i] = str[*j];
		(*j)++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		j;
	int		word_len;
	int		str_count;

	str_count = count_str(str, charset);
	tab = malloc(sizeof(char *) * (str_count + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < str_count)
	{
		word_len = wlength(str, &j, charset);
		j = j - word_len;
		tab[i++] = get_word(str, word_len, &j, charset);
		if (!tab[i - 1])
		{
			error_free(tab, i - 1);
			return (NULL);
		}
	}
	tab[i] = 0;
	return (tab);
}
