/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:02:43 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/17 16:02:05 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbw(const char *str, char c)
{
	int word;

	word = 0;
	if (*str != c && *str)
	{
		str++;
		word++;
	}
	while (*str)
	{
		while (*str == c)
		{
			str++;
			if (*str != c && *str)
				word++;
		}
		str++;
	}
	return (word);
}

static int		ft_ln(const char *str, char c)
{
	int count;

	count = 0;
	while (*str != c && *str)
	{
		count++;
		str++;
	}
	return (count);
}

static void		*is_free(char **spt)
{
	int	i;

	i = 0;
	while (spt[i])
	{
		free(spt[i++]);
	}
	free(spt);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		j;
	int		i;
	char	**spt;

	j = 0;
	i = 0;
	if (!s || (!(spt = (char **)malloc(sizeof(char *) * (ft_nbw(s, c) + 1)))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!(spt[j] = (char *)malloc(sizeof(char) * (ft_ln(s, c) + 1))))
				return (is_free(spt));
			while (*s && *s != c)
				spt[j][i++] = (char)*s++;
			spt[j][i] = '\0';
			j++;
			i = 0;
		}
	}
	spt[j] = NULL;
	return (spt);
}
