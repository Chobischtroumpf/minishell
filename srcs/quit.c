/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:07:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/06 13:41:41 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_exit_code(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			get_minishell()->excode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minishell()->excode = 128 + WTERMSIG(status);
	}
	else
		get_minishell()->excode = excode;
}


