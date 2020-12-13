/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:02:43 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/13 14:06:59 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int			count_words(char const *str, char sep)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			count++;
		i++;
	}
	return (count);
}

static char			*malloc_word(char const *str, char sep)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (str[word_len] && !is_sep(str[word_len], sep))
		word_len++;
	if (!(word = (char *)malloc(sizeof(char) * (word_len + 1))))
		return (0);
	while (str[i] && !is_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void			*free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		if (tab[i])
			free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char				**ft_split(char const *str, char sep)
{
	char	**tab;
	int		i;

	if (!str)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(str, sep) + 1))))
		return (0);
	i = 0;
	while (*str)
	{
		while (*str && is_sep(*str, sep))
			str++;
		if (*str && !is_sep(*str, sep))
		{
			if (!(tab[i] = malloc_word(str, sep)))
				return (free_tab(tab, i));
			i++;
			while (*str && !is_sep(*str, sep))
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
