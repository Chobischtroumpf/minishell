/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_skip_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:47:20 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/08 22:38:53 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	count = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			count++;
		i++;
	}
	return (count + 1);
}

static char			*malloc_word(char const *str, char sep)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (str[word_len] && !is_sep(str[word_len], sep))
	{
		if (str[word_len] == '\'')
			while (str[++word_len] != '\'')
				;
		if (str[word_len] == '"')
			while (str[++word_len] != '"')
				;
		word_len++;
	}
	if (!(word = (char *)malloc(sizeof(char) * (word_len + 1))))
		return (0);
	while (i < word_len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char				**ft_split_skip_quotes(char const *str, char sep)
{
	char	**tab;
	int		i;
	int		j;
	
	if (!str)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(str, sep) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j] && is_sep(str[j], sep))
			j++;
		if (str[j] && !is_sep(str[j], sep))
		{
			if (!(tab[i++] = malloc_word(&str[j], sep)))
				return (ft_free_tab(tab, i));
			j = ft_skip_quotes((char*)str, j);
			j = ft_skip_double_quotes((char*)str, j);
			while (str[j] && !is_sep(str[j], sep))
				j++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
