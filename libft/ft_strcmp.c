/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:21:16 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/27 16:38:03 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	len;
	size_t	len2;
	int		result;

	len = ft_strlen(s1) + 1;
	len2 = ft_strlen(s2) + 1;
	if (len >= len2)
		len = len2;
	result = ft_memcmp(s1, s2, len);
	return (result);
}
