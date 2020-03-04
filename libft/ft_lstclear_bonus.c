/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:27:02 by adorigo           #+#    #+#             */
/*   Updated: 2019/10/28 14:03:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*nxt;

	if (lst && *lst && del)
	{
		cur = *lst;
		while (cur)
		{
			nxt = cur->next;
			ft_lstdelone(cur, del);
			cur = nxt;
		}
		*lst = NULL;
	}
}
