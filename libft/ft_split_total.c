/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_total.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:02:52 by nathan            #+#    #+#             */
/*   Updated: 2021/01/09 14:00:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	count_words(char const *str, char sep)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while ((str[i] != sep) && str[i])
			i++;
		count++;
		if ((str[i] == sep))
			count++;
		i++;
	}
	return (count);
}

static char	*malloc_word(char const *str, char sep)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (str[word_len] && (str[word_len] != sep))
		word_len++;
	if (!(word = (char *)malloc(sizeof(char) * (word_len + 1))))
		return (0);
	while (str[i] && (str[i] != sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_total(char const *str, char sep)
{
	char	**tab;
	int		i;

	if (!str || !(tab = (char **)ft_calloc((count_words(str, sep) + 1),
											sizeof(char *))))
		return (0);
	i = -1;
	while (*str)
	{
		if (*str && (*str != sep))
		{
			if (!(tab[++i] = malloc_word(str, sep)))
				return (ft_free_tab(tab, i));
			while (*str && (*str != sep))
				str++;
		}
		else if (*str && (*str == sep))
		{
			if (!(tab[++i] = (char *)ft_calloc(2, sizeof(char))))
				return (ft_free_tab(tab, i));
			tab[i][0] = sep;
			str++;
		}
	}
	return (tab);
}
