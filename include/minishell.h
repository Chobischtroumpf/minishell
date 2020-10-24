/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:05:43 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/23 16:46:56 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
// # include "wraloc.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define SEP_SPACE " \t<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif
// # define LINE_MAX 1024
# define NO_EXCODE -1
# define NO_STATUS -1

typedef struct		s_rdir
{
	char			*file;
	int				fd : 16;
	int				is_dbl : 1;
	int				std;
	struct s_rdir	*next;
}					t_rdir;

typedef struct		s_cmd
{
	char			**argv;
	int				pipe : 1;
	int				is_rdir : 1;
	int				has_path : 1;
	t_rdir			*in;
	t_rdir			*out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct  s_env
{
	char **tab;
}				t_env;

typedef struct		s_minishell
{
	char			*line;
	char			**tokens;
	int				executed : 1;
	int				nbr_cmd : 11;
	t_cmd			*cmd;
} 					t_minishell;

t_minishell			*get_minishell(void);
t_env				*ft_get_env(void);
char				**get_built_in(void);
void 				*ft_exit_error(void);
int					ft_tokens_count(char *line);
int					ft_check_separator(char *line, int i, int space);
int					ft_brackets(char *line, int i);
char				*ft_tokens_split(char *line, int nbr_tokens);
int					ft_hasnchar(const char *s, char *c);
int					ft_parse_error(char *error, int ret);
int					ft_check_tokens(char **tokens);
int					ft_cmd_parse(char **tokens);
int					ft_is_redir(char *s);
int					ft_count_arg(char **arr);
t_cmd				*ft_last_cmd(t_cmd *cmd);
void				ft_add_redir_cmd(t_cmd *cmd,char *redir, char *file);
int					ft_too_many_args(char *cmd, int ret);
int					ft_numeric_arg_error(char *cmd,char *arg, int ret);
void				ft_free_cmd(void);
void				ft_init_env(char **envv);
void				ft_print_env(t_env *env);
int					ft_exec_cmd(void);
int					ft_exec_env(void);
int					ft_exec_pwd(void);
void				ft_exec_extern(t_cmd *cmd);
int					ft_exec_echo(t_cmd *cmd);
int					ft_exec_exit(t_cmd *cmd);


#endif
