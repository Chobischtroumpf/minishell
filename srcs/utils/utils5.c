/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:07:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/14 00:29:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_get_exit_code(int status, int exit)
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

void		skip_extra_spaces(char *str)
{
	char	*trimmed;
	char	*untrimmed;
	int		prev_space;

	trimmed = str;
	untrimmed = str;
	prev_space = 0;
	while (*untrimmed)
	{
		if (ft_isspace(*untrimmed))
		{
			if (!prev_space)
			{
				*trimmed++ = ' ';
				prev_space = 1;
			}
		}
		else
		{
			*trimmed++ = *untrimmed;
			prev_space = 0;
		}
		++untrimmed;
	}
	*trimmed = '\0';
}

static char	*check_new_size(char **check, char *file)
{
	char *tmp2;

	if (ft_array_size(check) == 1)
	{
		if (!(tmp2 = ft_strdup(check[0])))
		{
			ft_free_array(check, 0);
			return (NULL);
		}
		return (tmp2);
	}
	else
		ft_free_array(check, ft_err_redirect(file));
	return (NULL);
}

static char	*free_ret_str(char *str, char *ret)
{
	if (str)
		free(str);
	return (ret);
}

char		*check_rdir_space(char *file)
{
	char	*tmp;
	char	*tmp2;
	char	**check;

	if (!(tmp = check_quote(file, -1)))
		ft_exit_error();
	if (!ft_strcmp(tmp, ""))
	{
		ft_err_redirect(file);
		free_ret_str(tmp, NULL);
	}
	else if (ft_haschr(tmp, -1))
	{
		if (!(tmp2 = ft_strtrim_integral(tmp, -1)))
			free_ret_str(tmp, NULL);
		free(tmp);
		if (!(check = ft_lexing(tmp2)))
			free_ret_str(tmp2, NULL);
		free(tmp2);
		return (check_new_size(check, file));
	}
	else
		return (tmp);
	return (NULL);
}
