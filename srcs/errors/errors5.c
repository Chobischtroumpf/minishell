/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:13:03 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/21 20:44:01 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_redir(char *file)
{
	if (!ft_file_is_exec(file) || !ft_file_readable(file))
		return (ft_err_no_access(file, NULL, 0));
	else if (ft_file_is_dir(file))
		return (ft_err_is_dir(file, NULL, 0));
	else if (!ft_file_exists(file))
		return (ft_err_file_not_found(file, NULL, 0));
	return (1);
}
