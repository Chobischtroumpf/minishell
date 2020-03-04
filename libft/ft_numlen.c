/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:07:45 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/11 16:16:30 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_numlen(int n, int minus)
{
	int numlen;

	numlen = 1;
	while ((n /= 10))
		numlen++;
	return (numlen + minus);
}
