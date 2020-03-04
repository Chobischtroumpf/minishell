/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:59:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/01/21 07:29:29 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, ssize_t r_size)
{
	int		len;
	char	*res;
	ssize_t	i;

	len = ft_strlen(s1) + r_size;
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && *s2 != '\0')
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}
