/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/06 12:53:43 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_arg_count(char *line)
{
	int ck;
	int cnt;

	cnt = 1;
	ck = 0;
	while (*line)
	{
		if (!ft_strncmp(line, "\"", 1))
		{
			line++;
			while (ft_strncmp(line, "\"", 1) && *line)
				line++;
			if (!line)
				return (0);
		}
		if (*line == ' ' && *line + 1 && ck == 0 && (ck = 1))
			cnt++;
		else if (*line == ' ' && ck == 1)
			continue;
		else
			ck = 0;
		line++;
	}
	return(cnt);
}

// char **ft_arg_split(t_minishell *minishell)
// {

// 	int word_len;
// 	char **tab;

// 	word_len = 0;
// 	//split normal :
// 	while (*(minishell->line))
// 	{
// 		while (minishell->line[word_len] != ' ')
// 			word_len++;
// 		if 
// 	}
// 	//split if "" or '' :


// }

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;
		
	return (&minishell);
}

char		**get_built_in(void)
{
	static char* built_in[8] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	return (built_in);
}

int			ft_exec_pwd(void)
{
	char cwd[PATH_MAX];

	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	ft_printf("%s\n", cwd);
	return (1);
}

// int fd_exec_echo();

static int 	ft_parse_line(char *line)
{
	int ret;
	
	if (!strncmp(line, "echo", 4))
		ret = 1;
		// ret = ft_exec_cd();
	if (!ft_strncmp(line, "pwd", 3))
		ret = ft_exec_pwd();
	else if (!ft_strncmp(line, "exit", 4))
		ret = 0;
	else
	{
		ft_printf("minishell : unknown command : %s\n", line);
		ret = 1;
	}
	return (ret);
}

void		signal_handler(int signbr)
{
	if (signbr == SIGINT)
	{
		ft_putstr("\n");
		if (get_minishell()->executed == 1)
			get_minishell()->executed = 0;
		else
			ft_putstr("\033[32mminishell\033[0m$ ");	
	} 
	else if (signbr == SIGQUIT)
	{
		if (get_minishell()->executed == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			get_minishell()->executed = 0;
		}
	}
}


int			main(void)
{
	int			done;
	// int x = 0;
	int			nbr_arg;
	t_minishell	*minishell;

	// init_minishell();
	minishell = get_minishell();	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	done = 1;
	while (done == 1)
	{
		ft_putstr("\n\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &(minishell->line)))
			break;
		minishell->line = ft_strtrim(minishell->line, " \t\n\v\f\r");
		ft_printf("line : %s\n", minishell->line);
		
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			nbr_arg = ft_arg_count(minishell->line);
			printf("nbr_arg : %d\n", nbr_arg);
			if (!(minishell->tokens = malloc(sizeof(char *) * nbr_arg)))
				return (0);
			// ft_arg_split(minishell, nbr_arg);
			minishell->tokens = ft_split(minishell->line, ' ');

			// while (minishell->tokens[x])
			done = ft_parse_line(minishell->line);
		}
		ft_printf("done : %d\n", done);
    }
	ft_printf("\n");
}