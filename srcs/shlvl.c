/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:43:01 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/03 15:21:23 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_shlvl(void)
{
	t_env   *shlvl;
	char    **tmp;

	if (!(shlvl = ft_find_by_key("SHLVL")))
	{
		if (!(tmp = (char**)malloc(sizeof(char **) * 3)))
			ft_exit_error();
		tmp[0] = ft_strdup("SHLVL");
		tmp[1] = ft_strdup("1");
		tmp[2] = NULL;
		ft_add_env(tmp);
	}
	
}