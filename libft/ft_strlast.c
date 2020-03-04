/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 08:42:45 by adorigo           #+#    #+#             */
/*   Updated: 2020/01/27 08:43:00 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlast(char const *str, char const *last)
{
	int	len;
	int	l_len;

	len = ft_strlen(str);
	l_len = ft_strlen(last);
	if (l_len > len)
		return (0);
	return (!ft_strcmp(str + len - l_len, last));
}
