/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:43:01 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/04 15:02:09 by alessandro       ###   ########.fr       */
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

// int			beg_shlvl(void)
// {
// 	int		i;
// 	int		shlvl;
// 	char	*shlvl_final;
// 	char	*shlvl_string;

// 	i = 0;
// 	shlvl = 0;
// 	shlvl_string = get_env_var_by_name("SHLVL");
// 	(shlvl_string[0] == '-' || shlvl_string[0] == '+') ? ++i : 0;
// 	while (shlvl_string[i] <= '9' && shlvl_string[i] >= '0')
// 		i++;
// 	if (shlvl_string[i] != '\0')
// 		shlvl = 1;
// 	else if (shlvl_string[0] == '-')
// 		shlvl = 0;
// 	else
// 		shlvl = ft_atoi(shlvl_string) + 1;
// 	(shlvl_string) ? free(shlvl_string) : 0;
// 	shlvl_string = ft_itoa(shlvl);
// 	shlvl_final = ft_strjoin("SHLVL=", shlvl_string);
// 	add_var_to_env(shlvl_final);
// 	(shlvl_string) ? free(shlvl_string) : 0;
// 	(shlvl_final) ? free(shlvl_final) : 0;
// 	return (1);
// }
