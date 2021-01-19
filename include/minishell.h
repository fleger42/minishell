/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:48:16 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 06:21:15 by user42           ###   ########.fr       */
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


#define EMPTY 0
#define RIGHT 1
#define DOUBLERIGHT 2
#define LEFT 3
#define PIPE 4
#define NEXT 5
#define CMD 6
#define ARG 7

typedef struct	s_token
{
	char	*string;
	int		type;
	struct s_token *prev;
	struct s_token *next;
}				t_token;

void	ft_free_token(t_token *token);
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
	int		return_code;
}				t_envir;

typedef struct	s_sig
{
	int				sigint;
	int				sigexit;
}				t_sig;
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
#endif