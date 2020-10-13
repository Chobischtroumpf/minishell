/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 10:47:56 by adorigo           #+#    #+#             */
/*   Updated: 2020/04/09 11:11:23 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd init_cmd()
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
	{
		// ft_free_all();
		exit_error();
	}
	// cmd->nbr_token = 0;
	cmd->argv = 0;
	
}

