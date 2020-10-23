/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:07:45 by nathan            #+#    #+#             */
/*   Updated: 2020/10/22 12:50:59 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_env(void)
{
	static t_env env;

	return (&env);
}

int		ft_env_size(char **envv)
{
	int i;

	i = 0;
	while (envv[i])
		i++;
	return (i);
}

void	ft_print_env(t_env *env)
{
	int i;

	i = 0;
	while (env->tab[i])
	{
		ft_printf("%s\n", env->tab[i]);
		i++;
	}
}

int			ft_exec_env()
{
	t_env *env;

	env = ft_get_env();
	ft_print_env(env);
	return (EXIT_SUCCESS);
}


/*
** Allocate memory for a **char and store the environement
** variables inside.
*/

void	ft_init_env(char **envv)
{
	t_env	*env;
	int		i;

	i = 0;
	env = ft_get_env();
	if (!(env->tab = (char **)malloc(sizeof(char *) * ft_env_size(envv) + 1)))
		exit(0);
	while (envv[i])
	{
		if (!(env->tab[i] = ft_strdup(envv[i])))
			exit(0);
		i++;
	}
	env->tab[i] = NULL;
}
