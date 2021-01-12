/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:07:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/12 17:07:50 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_exit_code(int status, int exit)
{
	if (exit == -1)
	{
		if (WIFEXITED(status))
			get_minishell()->exval = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minishell()->exval = 128 + WTERMSIG(status);
	}
	else
		get_minishell()->exval = exit;
	return (NULL);
}
