/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:45:38 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/17 09:59:49 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, unsigned int n)
{
	unsigned char	*ptr;

	if (s == 0)
		return ;
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}
