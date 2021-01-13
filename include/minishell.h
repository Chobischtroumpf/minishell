/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:05:43 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/13 14:55:36 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <time.h>

# define IS_DIR 040000
# define IS_LINK 080000
# define SEP_SPACE " 	<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
# ifdef LINE_MAX
#  undef LINE_MAX
# endif
# define LINE_MAX 50000
# define NO_EXCODE -1
# define NO_STATUS -1

typedef struct		s_rdir
{
	char			*file;
	int				fd;
	int				is_dbl : 2;
	int				std;
	struct s_rdir	*next;
}					t_rdir;

typedef struct		s_cmd
{
	char			**argv;
	int				pipe : 2;
	int				is_rdir : 2;
	int				has_path : 2;
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
	int				executed : 2;
	unsigned int	nbr_cmd : 11;
	int				was_eof : 2;
	int				backslash : 2;
	int				gnl_ret : 2;
	int				exval;
	t_cmd			*cmd;
	t_env			*env;
}					t_minishell;

t_minishell			*get_minishell(void);
char				**get_built_in(void);
int					is_built_in(char *command);
int					ft_exec_builtin(int bltin_pos, t_cmd *cmd);

void				ft_shlvl(void);
long				ft_atoi_pos(const char *str);
long				ft_error_shlvl(long shlvl);
int					ft_line_handle(void);
char				**ft_split_skip_quotes(char const *str, char sep);

char				*check_quote(char *token, int i);
int					process_dollar(char *token, char *buffer, int *j\
															, int quote);
void				check_dollar(t_cmd *cmd);
int					has_dollar(char *arg);
char				*dollar_to_env(char *arg);
char				*remove_char(char *str, char c);
int					free_str_ret(char *str, int ret);
char				**ft_lexing(char *line);
int					ft_tokens_count(char *line);
int					ft_check_sep(char *line, int nbr_token, int space);
char				*ft_tokens_split(char *line, int *indx);
char				*ft_strtrim_integral(char const *s1, char const set);
int					ft_brackets(char *line, int i);
int					ft_backslash_counter(char *str, int i);
int					ft_dollar_quotes(t_cmd *cmd);
void				skip_extra_spaces(char *str);
int					ft_isascii_except(int c);
int					ft_skip_quotes(char *str, int i);
int					ft_skip_double_quotes(char *str, int i);
int					ft_cmd_parse(char **tokens);
int					ft_check_tokens(char **tokens);
t_cmd				*ft_last_cmd(t_cmd *cmd);
int					ft_is_redir(char *s);
t_rdir				*ft_last_rdir(t_rdir *begin);
void				ft_add_redir_cmd(t_cmd *cmd, char *redir, char *file);
int					ft_count_arg(char **arr);
void				open_redirection(t_cmd *cmd);
void				close_redirection(t_cmd *cmd);
int					get_next_char(int fd, char *cptr);
char				*ft_chardup(char c);
char				**ft_split_empty(char const *str, char sep);
int					ft_array_size(char **array);

void				ft_init_env(t_minishell *minishell, char **envv);
char				*ft_strjoin_delimiter(char *s1, char *s2, char del);
char				*ft_strjoin_delimiter_free(char *s1, char *s2, char del);
char				**ft_env_to_array(void);
void				ft_append_env(char **keyvalue);
int					ft_valid_key(char *str);
void				ft_envadd_back(t_env **head, t_env *new);
int					ft_envsize(t_env *env);
t_env				*ft_find_by_key(char *key);
char				*ft_find_by_key2(char *key);
void				ft_add_env(char **keyvalue);
void				ft_add_env2(char *key, char *value);
int					ft_remove_env(t_env **env_list, char *key);

void				main_execution(void);
int					ft_exec_cd(t_cmd *cmd);
int					ft_exec_pwd(void);
int					ft_exec_echo(t_cmd *cmd);
int					ft_exec_exit(t_cmd *cmd);
int					ft_exec_cmd(void);
int					ft_exec_env(void);
int					ft_exec_unset(t_cmd *cmd);
int					ft_exec_export(t_cmd *cmd);
void				ft_exec_extern(t_cmd *cmd);

int					ft_file_readable(char *cmd);
int					ft_file_is_exec(char *cmd);
int					ft_file_is_dir(char *cmd);
int					ft_file_exists(char *cmd);
int					ft_file_is_symlink(char *cmd);

int					ft_free_minishell(void);
void				ft_free_env(void);
void				ft_free_node(t_env *env);
int					ft_free_array(char **array, int ret);
void				ft_free_redir(t_cmd *cmd);
void				ft_free_cmd(t_cmd *cmd);
void				ft_free_line(void);
void				ft_free_all(void);
void				ft_eof_exit(void);
char				**ft_get_exit_code(int status, int exit);

int					ft_error_dispatch(int ret_val, char *cmd, char *arg);
int					ft_too_many_args(char *cmd, int ret);
int					ft_skip_quotes(char *str, int i);
void				ft_numeric_arg_error(char *cmd, char *arg);
int					ft_parse_error(char *error, int ret);
int					ft_no_cmd_error(char *cmd, int ret);
void				*ft_exit_error(void);
int					ft_invalid_id(char *cmd, char *arg);
int					ft_err_file_not_found(char *cmd, char *arg, int ret);
int					ft_err_no_access(char *cmd, char *arg, int ret);
void				ft_err_not_dir(char *cmd, char *arg);
int					ft_err_is_dir(char *cmd, char *arg, int ret);
void				ft_err_file_too_long(char *cmd, char *arg);
void				ft_err_loop(char *cmd, char *arg);
int					ft_eof_error(int nbr_tokens, int ret);
int					ft_err_not_exec(char *cmd, char *arg, int ret);
int					ft_err_read_error(char *arg, int ret);
int					ft_err_is_segfault(char *cmd, char *arg, int ret);
int					ft_err_is_symlink_loop(char *cmd, int ret_val);
int					ft_err_redirect(char *file);

int					count_pipes(t_cmd *cmd);
t_cmd				*handle_pipe(t_minishell *m, t_cmd *cmd, int pipe_nb, int i);
void				exec_cmd(t_cmd *cmd);
int					check_in(t_rdir *in);
int					check_out(t_rdir *out);
void				update_lastcmd(char *last_cmd);
char				*ft_last_arg(char **arg);
void				init_home(void);
char				*check_rdir_space(char *file);


#endif
