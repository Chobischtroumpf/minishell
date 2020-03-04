/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:21:16 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/11 15:53:44 by adorigo          ###   ########.fr       */
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
	len = (len <= len2) ? len : len2;
	result = ft_memcmp(s1, s2, len);
	return (result);
}
