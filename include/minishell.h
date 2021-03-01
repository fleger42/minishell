/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:48:16 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:55:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "get_next_line.h"
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include  "../libft/libft.h"
#define BLACK    "\033[0;30m"
#define RED      "\033[0;31m"
#define GREEN    "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define BLUE     "\033[0;34m"
#define PURPLE   "\033[0;35m"
#define CYAN     "\033[0;36m"
#define GREY     "\033[0;37m"
#define NORMAL	"\033[00m"


#define RIGHT 1
#define DOUBLERIGHT 2
#define LEFT 3
#define PIPE 4
#define ARG 5
#define CMD 6
#define NEXT 7

typedef struct	s_token
{
	char	*string;
	int		type;
	struct s_token *prev;
	struct s_token *next;
}				t_token;

typedef struct	s_envir
{
	t_token *start;
	int	child;
	int fdoutput;
	int	fdinput;
	int pipeoutfd;
	int pipeinfd;
	int standardin;
	int standardout;
	int n;
	int block_cmd;
	int		shlv;
	char 	**envp;
	char	**args;
	char	*cmd;
	char	*prog_name;
	char	**av;
	char	**all_bin;
	char	*a_path;
	int		pipe_dad;
	int		exit_code;
}				t_envir;

typedef struct	s_sig
{
	int				sigint;
	int				sigexit;
}				t_sig;
t_token		*ft_previous_sep(t_token *token);
int			ft_get_type_token(t_token *token);
t_token		*ft_get_actual_token(char *line, int *i);
t_token		*ft_tokenize(char *line);
void		ft_free_token(t_token *token);
t_token		*ft_next_end(t_token *token);
void		ft_insert_after(t_token *token, t_token *new);
void		ft_insert_before(t_envir *envir, t_token *token, t_token *new);
void		ft_remove_token(t_envir *envir, t_token *to_supp);
t_token		*ft_dup_token(t_token *token);
void		ft_refresh_type(t_token *start);
int			ft_get_valid(t_token *token);
void		ft_replace_nullstart(t_envir *envir, t_token *token);
int			ft_istype(t_token *token, char *str);
char		*ft_malloc_string_token(char *line, int i);
char		*ft_gst_add(char *line, char *string, int *i);
char		*ft_get_string_token(char *line, int *i);
t_token		*ft_token_to_cmd(t_token *token);
t_token		*ft_next_sep(t_token *token);
void	ft_ctrld(t_envir *envir, char *line);
int		ft_cdhome(char *pwd[4]);
void		ft_exec_cmd(t_envir *envir, t_token *token);
long long int	ft_llatoi(const char *nptr);
int		ft_isalpha_min(char c);
int		ft_isalpha_maj(char c);
int		ctrl_c_called;
int 	in_loop;
int		in_child;
int		ft_set_pwd(char **envp, char *oldpwd);
int		ft_set_oldpwd(char **envp, char *oldpwd);
void	ft_free_token(t_token *token);
char	*ft_get_path(t_envir *envir, char *cmd);
void		ft_error(char *str);
int			ft_verif_unset(char *str1, char *str2);
void		ft_exit(t_envir *envir);
void		ft_free_env(char **envp);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_pwd(char **av, t_envir *envir);
int			ft_cd(char **av, t_envir *envir);
int			ft_env(char **av, t_envir *envir);
int			ft_export(char **av, t_envir *envir);
int			ft_echo(char **av, t_envir *envir);
int			ft_unset(char **av, t_envir *envir);
t_envir		ft_create_t_envir(char **envp, char **av);
t_envir		*ft_malloc_t_envir(char **envp, char **av);
void		ft_free_t_envir(t_envir *to_free);
int			ft_atoi(const char *nptr);
int			ft_get_shlv(char **envp);
char	*ft_get(char **envp, char *str);
char		*ft_catpy(char *first, char *second);
void	ft_set_env(char **envp, char *prog_name);
int			len(long nb);
char		*ft_itoa(int nb);
void		ft_putchar(char c);
void		ft_putstr(char *str);
int			ft_atoi(const char *nptr);
void		ft_verif_cmd(char *str, char *line, t_envir *envir);
int			ft_verif_exit(char *first, char *second);
char		*char_walk(char *str);
char		**ft_split(const char *s, const char *c);
void	ft_exec_nonbuiltin(t_envir *envir, char **cmd);
void	ft_exec_builtin(t_envir *envir, char **cmd);
int			ft_set_shlvl(char **envp, int shlvl);
char		*ft_search_dir(char *bin, char *cmd);
int			ft_compare_space(char *str1, char *str2);
int	ft_signal_status();
void	ft_signal_clear();
void	ft_signal_handler(int signal);
void	ft_signal_register(int *signaltab);
void    ft_signal_init();
void		ft_exec(t_envir *envir, t_token *token);
void	ft_add_str_tab(t_envir *envir, char *str);
int		ft_sdt_loop(t_envir *envir, int i);
void	ft_sort_doubletab(t_envir *envir);
int		ft_rm_count(char *str);
char	*ft_remove_multiplespace(char *str);
int		ft_cmp_equal(char *str1, char *str2);
int		ft_verif_dupe(t_envir *envir, char *str);
void	ft_replace_line(t_envir *envir, char *str);
void	ft_error_variablename(char *c);
int		ft_verif_validchar(char **all_name, int i);
int		ft_verif_variablename(char **all_name);
char				**ft_clear_splitted(char **tab);
char		**ft_lst_to_path(t_token *start);
int		ft_exit_cmd(t_envir *envir, char **cmd);
int			ft_isbuiltin(char *str);
t_token		*ft_token_to_cmd(t_token *token);
int		ft_pipe(t_envir *envir);
void		ft_redir_doubleright(t_envir *envir, t_token *token);
void		ft_redir_right(t_envir *envir, t_token *token);
void		ft_redir_left(t_envir *envir, t_token *token);
void	ft_dollar_until_next(t_envir *envir, t_token *first);
t_token *ft_next_sep(t_token *token);
t_token *ft_previous_sep(t_token *token);
void		ft_reset(t_envir *envir);
int	ft_verif_dollar(char *str1, char *str2);
int		ft_check_quote(char *line);
int			ft_verif_syntax(t_envir *envir);
char		*ft_malloc_string_token(char *line, int i);
char		*ft_get_string_token(char *line, int *i);
t_token		*ft_token_to_cmd(t_token *token);
t_token *ft_next_sep(t_token *token);
t_token *ft_previous_sep(t_token *token);
int			ft_get_type_token(t_token *token);
t_token		*ft_get_actual_token(char *line, int *i);
t_token		*ft_tokenize(char *line);
void	ft_free_token(t_token *token);
t_token		*ft_next_end(t_token *token);
void		ft_insert_after(t_token *token, t_token *new);
void		ft_insert_before(t_envir *envir, t_token *token, t_token *new);
void		ft_remove_token(t_envir *envir, t_token *to_supp);
t_token		*ft_dup_token(t_token *token);
void		ft_refresh_type(t_token *start);
int			ft_get_valid(t_token *token);
void		ft_replace_nullstart(t_envir *envir, t_token *token);
int			ft_istype(t_token *token, char *str);
void		ft_move_token(t_envir *envir, t_token *dup, t_token *prev, t_token *temp);
char	*ft_search_dir(char *bin, char *cmd);
void	ft_sonexec(t_envir *envir, char **cmd, char *path);
void	ft_exec_nonbuiltin(t_envir *envir, char **cmd);
void	ft_exec_builtin(t_envir *envir, char **cmd);
void		ft_exec_cmd(t_envir *envir, t_token *token);
void		ft_exec_set(t_envir *envir, t_token *token);
char	*ft_malloc_new_line(char *line)	;		
char	*ft_str_remove(char *str);
char	*ft_add_spacesep(char *line);
int		ft_get_shlv(char **envp);
char	*ft_get(char **envp, char *str);
char	*ft_get_path(t_envir *envir, char *cmd);
char *ft_walk_until_equal(char *str, int *length);
void	ft_add_str_tab(t_envir *envir, char *str);
int		ft_isalpha_min(char c);
int		ft_isalpha_maj(char c);
void		ft_print_list(t_token *list);
int			ft_is_whitespace(char c);
int			ft_char_tono_space(char *str);
int		ft_is_onlynumber(char *str);
int		ft_issep(char c);
int		ft_upgrade_shlv(char **envp);
int		ft_dollar_quote(int quote_open, char *str, int i);
#endif