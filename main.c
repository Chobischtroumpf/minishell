/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/04 16:39:21 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_pwd(void)
{
	char cwd[PATH_MAX];

	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}

// int fd_exec_echo();

static int ft_parse_line(char *line)
{
	int ret;
	
	line = ft_strtrim(line, " \t\n\v\f\r");
	if (!strncmp(line, "echo", 4))
		ret = 0;
		// ret = ft_exec_cd();
	if (!ft_strncmp(line, "pwd", 3))
		ret = ft_exec_pwd();
	else if (!ft_strncmp(line, "exit", 4))
		ret = 1;
	else
	{
		ft_putstr_fd("minishell : command not found :", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		return (ret = 0);
	}
	return (ret);
}

int main(void)
{
	int done;
	char *line;
	int i;

	done = 0;
	while (done != 1)
	{
		i = 0;
		ft_printf("%s", "minishell ✗");
		get_next_line(1, &line);
		// ft_printf("%s\n", line);
		done = ft_parse_line(line);
    }
}