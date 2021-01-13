/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:45:10 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/09 13:28:40 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(char const *str, char sep)
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

static char	*malloc_word(char const *str, char sep)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (str[word_len] && !is_sep(str[word_len], sep))
		word_len++;
	if (!(word = (char *)calloc((word_len + 1), sizeof(char))))
		return (0);
	while (str[i] && !is_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void		split_helper(char *buff, char *str, char sep)
{
	int i;
	int j;

	i = -1;
	j = 0;
	bzero(buff, LINE_MAX);
	while (str[++i])
	{
		if (is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			buff[j++] = -1;
		buff[j++] = str[i];
		if (is_sep(str[i], sep) && !str[i + 1])
			buff[j++] = -1;
	}
}

char		**ft_split_empty(char const *str, char sep)
{
	char	**tab;
	int		i;
	int		j;
	char	buff[LINE_MAX];

	i = 0;
	j = 0;
	split_helper(buff, (char*)str, sep);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(buff, sep) + 1))))
		return (0);
	while (buff[j])
	{
		while (buff[j] && is_sep(buff[j], sep))
			j++;
		if (buff[j] && (!is_sep(buff[j], sep)))
		{
			if (!(tab[i] = malloc_word(&buff[j], sep)))
				return (ft_free_tab(tab, i));
			i++;
			while (buff[j] && !is_sep(buff[j], sep))
				j++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
