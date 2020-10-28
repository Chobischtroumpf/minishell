/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:05:43 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/28 13:27:30 by alessandro       ###   ########.fr       */
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
#  define PATH_MAX 4096
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

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_minishell
{
	char			*line;
	char			**tokens;
	int				executed : 1;
	unsigned int	nbr_cmd : 11;
	int				was_eof : 1;
	int				gnl_ret : 2;
	t_cmd			*cmd;
	t_env			*env;
} 					t_minishell;



t_minishell			*get_minishell(void);
char				**get_built_in(void);


int 				ft_line_handle(void);

int					ft_tokens_count(char *line);
int					ft_check_sep(char *line, int i, int space);
char				*ft_tokens_split(char *line, int nbr_tokens);
int					ft_brackets(char *line, int i);
int					ft_cmd_parse(char **tokens);
int					ft_check_tokens(char **tokens);
t_cmd				*ft_last_cmd(t_cmd *cmd);
int					ft_is_redir(char *s);
void				ft_add_redir_cmd(t_cmd *cmd,char *redir, char *file);
int					ft_count_arg(char **arr);
void				ft_add_env(t_minishell *minishell, char **keyvalue);


void				ft_init_env(t_minishell *minishell, char **envv);
char				*ft_strjoin_delimiter(char *s1, char *s2, char del);
char 				**ft_env_to_array(void);
void				ft_envadd_back(t_env **head, t_env *new);
int					ft_envsize(t_env *env);
t_env 				*ft_find_by_key(t_minishell *minishell, char *key);

int					ft_exec_pwd(void);
int					ft_exec_echo(t_cmd *cmd);
int					ft_exec_exit(t_cmd *cmd);
int					ft_exec_cmd(void);
int					ft_exec_env(void);
int					ft_exec_unset(t_cmd *cmd);
int					ft_exec_export(t_cmd *cmd);
void				ft_exec_extern(t_cmd *cmd);

int					ft_free_cmd(void);
void				ft_free_env(void);
void				free_node(t_env *env);
void				ft_free_array(char **array);
void				ft_eof_exit(void);


int					ft_too_many_args(char *cmd, int ret);
int					ft_numeric_arg_error(char *cmd,char *arg, int ret);
int					ft_parse_error(char *error, int ret);
int					ft_no_cmd_error(char *cmd, int ret);
int					ft_no_file_error(char *cmd, char *file, int ret);
void 				*ft_exit_error(void);
int					ft_invalid_identifier(char *cmd, char *arg);


#endif
