/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:43:01 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/04 17:20:50 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_shlvl(void)
{
	char			*shlvl_str;
	unsigned long	shlvl;
	char			**shlvl_env;

	shlvl_str = ft_find_by_key2("SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi_pos(shlvl_str);
		if (shlvl == 999)
			shlvl_str = ft_strdup("");
		else if (shlvl < 999)
			shlvl_str = ft_itoa(shlvl + 1);
		else if (shlvl > 999)
		{
			ft_error_shlvl(shlvl + 1);
			shlvl_str = ft_strdup("1");
		}
		if (!(shlvl_env = malloc(sizeof(char*) * 3)))
			ft_exit_error();
		shlvl_env[0] = ft_strdup("SHLVL");
		shlvl_env[1] = ft_strdup(shlvl_str);
		shlvl_env[2] = NULL;
		ft_add_env(shlvl_env);
		ft_free_array(shlvl_env);
		// free(shlvl_str);
	}
}
