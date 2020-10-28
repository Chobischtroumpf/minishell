/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:13:00 by nathan            #+#    #+#             */
/*   Updated: 2020/10/27 14:20:42 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char			**ft_split_once(char const *s, char c)
{
	int		j;
	int		i;
	char	**spt;

	j = 0;
	i = 0;
	if (!s || (!(spt = (char **)malloc(sizeof(char *) * 3))))
		return (NULL);

	if (!(spt[0] = (char *)malloc(sizeof(char) * (ft_ln(s, c) + 1))))
		return (is_free(spt));
	while (*s && *s != c)
		spt[j][i++] = (char)*s++;
	spt[0][i] = '\0';
	j++;
	i = 0;
	if (!(spt[1] = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1)))
		return (is_free(spt));
	while(*++s)
		spt[1][i++] = (char)*s;
	spt[1][i] = '\0';
	spt[2] = NULL;
	return (spt);
}