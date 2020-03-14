/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/14 13:16:31 by adorigo          ###   ########.fr       */
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

char **ft_arg_split(t_minishell *minishell, int nbr_arg)
{

	int word_len;
	int i;
	char *line;
	char **tab;

	word_len = 0;
	i = 0;
	line = minishell->line;
	if (!(tab = malloc(sizeof(char *) * nbr_arg)))
		return(NULL);
	while (*line && i < nbr_arg)
	{
		ft_printf("dans le while\n");
		word_len = 0;
		if (*(line) == '\"' || *(line) == '\'')
		{
			while ((line[++word_len] != '\"' ||
			line[++word_len] != '\'') && line[word_len])
			{
				word_len++;
				ft_printf("dans le while, dans le if, dans le while\n");
			}
			if (line[word_len] == ' ' || line[word_len] == '\0')
				if (!(tab[i++] = ft_strndup(line, word_len)))
					return(exit_error());
			while (*(line) == ' ' && line)
				line++;
			line += word_len;
		}
		else
		{
			while (line[word_len] != ' ' && line[word_len])
			{
				word_len++;
				ft_printf("dans le while, dans le else, dans le while\n");
			}
			if (line[word_len] == ' ' || line[word_len]  == '\0')
				if (!(tab[i++] = ft_strndup(line, word_len)))
					return(exit_error());
			line += word_len;
			ft_printf("line :%s\n", line);
			// ft_printf("%d\n", word_len);
			while (*(line) == ' ' && line)
				line++;
		}
	}
	i = 0;
	return (tab);
	//split if "" or '' :
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
	int			nbr_arg;
	t_minishell	*minishell;
	int x;

	minishell = get_minishell();	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	done = 1;
	while (done == 1)
	{
		x = -1;
		ft_putstr("\n\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &(minishell->line)))
			break;
		minishell->line = ft_strtrim(minishell->line, " \t\n\v\f\r");
		ft_printf("line : %s\n", minishell->line);		
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			nbr_arg = ft_arg_count(minishell->line);
			printf("nbr_arg : %d\n", nbr_arg);
			minishell->tokens = ft_arg_split(minishell, nbr_arg);
			done = ft_exec_cmd(minishell, 0);
		}
		ft_printf("done : %d\n", done);
    }
	ft_printf("\n");
}