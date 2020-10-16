/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 10:47:56 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/16 13:47:18 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	init_cmd(void)
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
	{
		ft_free_cmd();
		exit_error();
	}
}
