/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_total.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:02:52 by nathan            #+#    #+#             */
/*   Updated: 2020/11/26 22:51:06 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int count_words(char const *str, char sep)
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

static char *malloc_word(char const *str, char sep)
{
	char *word;
	int word_len;
	int i;

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

static void *free_tab(char **tab, int i)
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

char **ft_split_total(char const *str, char sep)
{
	char **tab;
	int i;

	if (!str)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(str, sep) + 1))))
		return (0);
	i = 0;
	while (*str)
	{
		if (*str && (*str != sep))
		{
			if (!(tab[i] = malloc_word(str, sep)))
				return (free_tab(tab, i));
			i++;
			while (*str && (*str != sep))
				str++;
		}
		else if (*str && (*str == sep))
		{
			if (!(tab[i] = (char *)malloc(sizeof(char) * 2)))
				return (free_tab(tab, i));
			tab[i][0] = sep;
			tab[i][1] = '\0';
			i++;
			str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
