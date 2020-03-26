/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:05:43 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 09:57:55 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define SEP_SPACE " \t<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# define PATH_MAX 1024
// # define LINE_MAX 1024
# define NO_EXCODE -1
# define NO_STATUS -1

typedef struct		s_cmd
{
	char			**argv;
	int				pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_minishell
{
	char			*line;
	char			**tokens;
	int				executed;
	int				pos_current_cmd;
	t_cmd			cmd;
} 					t_minishell;

t_minishell			*get_minishell(void);
char				**get_built_in(void);
int					ft_exec_pwd(void);
int 				ft_exec_echo(void);
int					ft_exec_cmd(void);
void 				*exit_error(void);
void 				ft_free_all(void);
int					ft_tokens_count(char *line);
int					ft_check_separator(char *line, int i, int space);
int					ft_brackets(char *line, int i);
char				*ft_tokens_split(char *line, int nbr_tokens);




#endif