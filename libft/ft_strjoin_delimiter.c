/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:16:14 by alessandro        #+#    #+#             */
/*   Updated: 2020/12/13 14:18:33 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Joins *char 's1' and *char 's2' with a character 'del' between the two.
*/

char	*ft_strjoin_delimiter(char *s1, char *s2, char del)
{
	char	*str;
	char	*to_free;
	int		total;
	int		i;

	i = 0;
	to_free = s1;
	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	if (!(str = (char *)malloc(total * sizeof(char))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	str[i++] = del;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
