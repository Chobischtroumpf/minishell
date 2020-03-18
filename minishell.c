/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/18 13:09:36 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_cmd_count(char *line)
{
	int ck;
	int cnt;

	cnt = 1;
	ck = 0;
	while (*line)
	{
		if (ft_haschr("\"", *line))
		{
			line++;
			while (!ft_haschr("\"", *line) && *line)
			{
				line++;
				if (ft_haschr("\\", *line - 1))	
					line++;
			}
			if (!line)
				return (0);
		}
		else if (ft_haschr("\'", *line))
		{
			line++;
			while (ft_haschr("\"\'", *line) && *line)
				line++;
			if (!line)
				return (0);
		}
		if ((*line == ' ' || *line == '|' || *line == ';') && *line + 1 &&
														 ck == 0 && (ck = 1))
			cnt++;
		line++;
	}
	return(cnt);
}

char
	**ft_tokens_split(int nbr_tokens)
{
	int word_len;
	int i;
	char *line;
	char **tab;
	
	word_len = 0;
	i = 0;
	line = get_minishell()->line;
	if (!(tab = malloc(sizeof(char*) * (nbr_tokens + 1))))
		return(NULL);
	while (*line && i < nbr_tokens)
	{
		word_len = 0;
			if (*(line) == '\"' || *(line) == '\'')
			{
				while ((line[word_len + 1] != '\"' ||
				line[word_len + 1] != '\'') && line[word_len])
					word_len++;
				if (line[word_len] == ' ' || line[word_len] == '\0')
					if (!(tab[i++] = ft_strndup(++line, word_len - 2)))
						return(exit_error());
				line += word_len;
				while (line && *(line) == ' ')
					line++;
			}
			else
			{
				while (line[word_len] != ' ' && line[word_len])
					word_len++;
				if (line[word_len] == ' ' || line[word_len] == ';' || line[word_len]  == '\0')
					if (!(tab[i++] = ft_strndup(line, word_len)))
						return(exit_error());
				line += word_len;
				while (line && *(line) == ' ')
					line++;
			}
	}
	tab[i] = NULL;
	return (tab);
}

void
	signal_handler(int signbr)
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

int
	main(void)
{
	int			done;
	int			nbr_tokens;
	t_minishell	*minishell;
	int x;

	minishell = get_minishell();	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	done = 0;
	while (done == 0)
	{
		x = -1;
		ft_putstr("\n\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &(minishell->line)))
			break;
		minishell->line = ft_strtrim(minishell->line, " \t\n\v\f\r");
		// ft_printf("line : %s\n", minishell->line);		
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			nbr_tokens = ft_cmd_count(minishell->line);
			printf("nbr_tokens : %d\n", nbr_tokens);
			minishell->tokens = ft_tokens_split(nbr_tokens);
			// minishell->cmd = ft_cmd_split
			done = ft_exec_cmd();
			while(minishell->tokens[++x])
				free(minishell->tokens[x]);
			free (minishell->tokens);
			free(minishell->line);
		}
		ft_printf("done : %d\n", done);
    }
	ft_printf("\n");
}