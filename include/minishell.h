/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:05:43 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/04 13:15:20 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <time.h>
# include <termcap.h>
# include "termcaps.h"

# define IS_DIR 040000
# define IS_LINK 080000
# define SEP_SPACE " 	<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# define INVALID_CHAR " 	-!`'\"%^&*()=+|\\<>,./~#@][¬:;$"
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

/*
**   ___ _   _ ___ _  _____   ___ _  _
**  | _ ) | | |_ _| ||_   _|_|_ _| \| |
**  | _ \ |_| || || |__| ||___| || .` |
**  |___/\___/|___|____|_|   |___|_|\_|
*/

/*
** bltin_cd.c
*/

int					ft_array_size(char **array);
int					ft_exec_cd(t_cmd *cmd);

/*
** bltin_echo.c
*/

int					ft_exec_echo(t_cmd *cmd);

/*
** bltin_env.c
*/

int					ft_exec_env(void);

/*
** bltin_exit.c
*/

int					ft_exec_exit(t_cmd *cmd);

/*
** bltin_export.c
*/

int					ft_exec_export(t_cmd *cmd, int i);
int					ft_valid_key(char *str, int i);
void				update_lastcmd(char *last_cmd);

/*
** bltin_pwd.c
*/

int					ft_exec_pwd(void);

/*
** bltin_unset.c
*/

int					ft_exec_unset(t_cmd *cmd);
int					ft_remove_env(t_env **env_list, char *key);

/*
**    ___ __  __ ___
**   / __|  \/  |   \
**  | (__| |\/| | |) |
**   \___|_|  |_|___/
*/

/*
** exec_cmd.c
*/

int					ft_exec_builtin(int bltin_pos, t_cmd *cmd);
int					ft_exec_cmd(void);
int					check_in(t_rdir *in);
int					check_out(t_rdir *out);

/*
** exec_external.c
*/

void				exec_cmd(t_cmd *cmd);
void				ft_exec_extern(t_cmd *cmd);

/*
** get_static.c
*/

t_minishell			*get_minishell(void);
char				**get_built_in(void);

/*
**   ___ _  ___   _____ ___  ___  _  _ __  __ ___ _  _ _____
**  | __| \| \ \ / /_ _| _ \/ _ \| \| |  \/  | __| \| |_   _|
**  | _|| .` |\ V / | ||   / (_) | .` | |\/| | _|| .` | | |
**  |___|_|\_| \_/ |___|_|_\\___/|_|\_|_|  |_|___|_|\_| |_|
*/

/*
** dollar.c
*/

int					process_dollar(char *token, char *buffer, int *j\
															, int quote);

/*
** env.c
*/

void				ft_envadd_back(t_env **head, t_env *new);
int					ft_envsize(t_env *env);
int					ft_free_array(char **array, int ret);
void				ft_free_env(void);
void				ft_init_env(t_minishell *minishell, char **envv);

/*
** env2.c
*/

char				**ft_env_to_array(void);
void				ft_add_env(char **keyvalue);
void				ft_add_env2(char *key, char *value);
t_env				*ft_find_by_key(char *key);
char				*ft_find_by_key2(char *key);

/*
** shlvl.c
*/

void				ft_shlvl(void);

/*
**   ___ ___ ___  ___  ___  ___
**  | __| _ \ _ \/ _ \| _ \/ __|
**  | _||   /   / (_) |   /\__ \
**  |___|_|_\_|_\\___/|_|_\|___/
*/

/*
** errors.c
*/

int					ft_error_dispatch(int ret_val, char *cmd, char *arg);
int					ft_no_cmd_error(char *cmd, int ret);
void				ft_numeric_arg_error(char *cmd, char *arg);
int					ft_too_many_args(char *cmd, int ret);
int					ft_parse_error(char *error, int ret);

/*
** errors2.c
*/

int					ft_check_file(char *cmd, int is_printed);
int					ft_err_file_not_found(char *cmd, char *arg, int ret);
void				ft_err_file_too_long(char *cmd, char *arg);
void				ft_err_loop(char *cmd, char *arg);
int					ft_err_no_access(char *cmd, char *arg, int ret);
void				ft_err_not_dir(char *cmd, char *arg);

/*
** errors3.c
*/

void				*ft_exit_error(void);
int					ft_invalid_id(char *cmd, char *arg);
long				ft_error_shlvl(long shlvl);
int					ft_eof_error(int nbr_tokens, int ret);
int					ft_err_read_error(char *arg, int ret);

/*
** errors4.c
*/

int					ft_err_is_dir(char *cmd, char *arg, int ret);
int					ft_err_not_exec(char *cmd, char *arg, int ret);
int					ft_err_is_segfault(char *cmd, char *arg, int ret);
int					ft_err_is_symlink_loop(char *cmd, int ret_val);
int					ft_err_redirect(char *file);

/*
** errors5.c
*/

int					ft_error_redir(char *file);

/*
**   ___  _   ___  ___ ___ _  _  ___
**  | _ \/_\ | _ \/ __|_ _| \| |/ __|
**  |  _/ _ \|   /\__ \| || .` | (_ |
**  |_|/_/ \_\_|_\|___/___|_|\_|\___|
*/

/*
** bracket.c
*/

char				*check_quote(char *token, int i);
void				ft_dollar_quotes(t_cmd *cmd);

/*
** cmd_parser_1.c
*/

int					ft_is_redir(char *s);
int					ft_check_tokens(char **tokens);

/*
** cmd_parser_2.c
*/

int					ft_cmd_parse(char **tokens);

/*
** lexing.c
*/

int					ft_check_sep(char *line, int nbr_token, int space);
int					ft_brackets(char *line, int i);
int					ft_tokens_count(char *line);
char				*replace_tilde(char *token);
char				*ft_tokens_split(char *line, int *idx, int ck, int is_dlr);

/*
** line_handle.c
*/

char				**ft_lexing(char *line, int is_dollar);
int					get_next_char(int fd, char *cptr);
int					ft_line_handle(int ret);

/*
**   ___ ___ ___ ___ ___ ___ ___ _____ ___ ___  _  _ ___
**  | _ \ __|   \_ _| _ \ __/ __|_   _|_ _/ _ \| \| / __|
**  |   / _|| |) | ||   / _| (__  | |  | | (_) | .` \__ \
**  |_|_\___|___/___|_|_\___\___| |_| |___\___/|_|\_|___/
*/

/*
** cmd_add_rdir.c
*/

t_rdir				*ft_last_rdir(t_rdir *begin);
void				ft_add_redir_cmd(t_cmd *cmd, char *redir, char *file);

/*
** pipe.c
*/

t_cmd				*handle_pipe(t_minishell *m, t_cmd *cmd, int pipe_nb,
								int i);

/*
** redirections.c
*/

void				open_redirection(t_cmd *cmd);
void				close_redirection(t_cmd *cmd);

/*
**   _   _ _____ ___ _    ___
**  | | | |_   _|_ _| |  / __|
**  | |_| | | |  | || |__\__ \
**   \___/  |_| |___|____|___/
*/

/*
** exit.c
*/

void				ft_free_line(void);
void				ft_free_redir(t_cmd *cmd);
int					ft_free_minishell(void);
void				ft_eof_exit(void);

/*
** files.c
*/

int					ft_file_readable(char *cmd);
int					ft_file_is_exec(char *cmd);
int					ft_file_is_dir(char *cmd);
int					ft_file_exists(char *cmd);
int					ft_file_is_symlink(char *cmd);

/*
** free.c
*/

void				ft_free_cmd(t_cmd *cmd);
void				ft_free_all(void);

/*
** ft_split_empty.c
*/

char				**ft_split_empty(char const *str, char sep);

/*
** ft_split_skip_quotes.c
*/

char				**ft_split_skip_quotes(char const *str, char sep);

/*
** utils.c
*/

int					ft_count_arg(char **arr);
char				*remove_char(char *str, char c);
int					ft_isascii_except(int c);
int					free_str_ret(char *str, int ret);
void				ft_append_env(char **keyvalue);

/*
** utils2.c
*/

int					is_built_in(char *command);
long				ft_atoi_pos(const char *str);

/*
** utils3.c
*/

char				*ft_strtrim_integral(char const *s1, char const set);
int					ft_backslash_counter(char *str, int i);
int					ft_skip_quotes(char *str, int i);
int					ft_skip_double_quotes(char *str, int i);
t_cmd				*ft_last_cmd(t_cmd *cmd);

/*
** utils4.c
*/

int					count_pipes(t_cmd *cmd);
char				*ft_last_arg(char **arg);
char				*ft_chardup(char c);
void				ft_free_node(t_env *env);
void				init_home(void);

/*
** utils5.c
*/

char				**ft_get_exit_code(int status, int exit);
void				skip_extra_spaces(char *str);
char				*check_rdir_space(char *file);

#endif
