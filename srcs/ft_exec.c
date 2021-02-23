/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:39:52 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:28:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_dir(char *bin, char *cmd)
{
	DIR				*dirp;
	struct dirent	*r_dir;
	char			*path_ret;
	char			*inter;

	path_ret = NULL;
	dirp = opendir(bin);
	if (!dirp)
		return (ft_strdup(cmd));
	while ((r_dir = readdir(dirp)))
	{
		if (strcmp(r_dir->d_name, cmd) == 0)
		{
			inter = ft_catpy(bin, "/");
			path_ret = ft_catpy(inter, cmd);
			free(inter);
		}
	}
	closedir(dirp);
	return (path_ret);
}

void	ft_sonexec(t_envir *envir, char **cmd, char *path)
{
	if (strcmp(cmd[0], envir->prog_name) == 0)
		ft_set_shlvl(envir->envp, envir->shlv++);
	if (execve(path, cmd, envir->envp) < 0)
	{
		free(path);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (errno == EAGAIN)
			exit(126);
		else
			exit(127);
	}
}

void	ft_exec_nonbuiltin(t_envir *envir, char **cmd)
{
	pid_t	pid;
	char	*path;

	envir->exit_code = 0;
	path = ft_get_path(envir, cmd[0]);
	pid = fork();
	if (pid == 0)
		ft_sonexec(envir, cmd, path);
	else if (pid == -1)
		ft_putstr_fd(RED"Error, pid = -1\n", 2);
	else
		waitpid(pid, &envir->exit_code, 0);
	if (WIFEXITED(pid))
		envir->exit_code = WEXITSTATUS(pid);
	else if (ctrl_c_called)
		envir->exit_code = 130;
	else
		envir->exit_code = envir->exit_code / 256;
	free(path);
}

void	ft_exec_builtin(t_envir *envir, char **cmd)
{
	int	i;

	i = 0;
	if (strcmp("pwd", cmd[0]) == 0)
		envir->exit_code = ft_pwd(cmd, envir);
	else if (strcmp("unset", cmd[0]) == 0)
		envir->exit_code = ft_unset(cmd, envir);
	else if (strcmp("cd", cmd[0]) == 0)
		envir->exit_code = ft_cd(cmd, envir);
	else if (strcmp("echo", cmd[0]) == 0)
		envir->exit_code = ft_echo(cmd, envir);
	else if (strcmp("export", cmd[0]) == 0)
		envir->exit_code = ft_export(cmd, envir);
	else if (strcmp("env", cmd[0]) == 0)
		envir->exit_code = ft_env(cmd, envir);
	i++;
}

void		ft_exec_cmd(t_envir *envir, t_token *token)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_lst_to_path(token);
	if (cmd == NULL)
		return ;
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_exit_cmd(envir, cmd);
		ft_free_token(envir->start);
		ft_free_t_envir(envir);
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(envir->exit_code);
	}
	if (ft_isbuiltin(cmd[0]))
		ft_exec_builtin(envir, cmd);
	else
		ft_exec_nonbuiltin(envir, cmd);
	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	envir->block_cmd = 1;
}

void		ft_exec_loop(t_envir *envir, t_token *token)
{
	int pid;
	int temp;

	token = ft_token_to_cmd(envir->start);
	if ((envir->start->type == LEFT || envir->start->type == RIGHT ||
	envir->start->type == DOUBLERIGHT))
		token = envir->start->next;
	temp = 0;
	pid = 0;
	while (token != NULL && ctrl_c_called == 0)
	{
		in_child = 0;
		envir->pipe_dad = 0;
		ft_dollar_until_next(envir, token);
		if (token->string && token->string[0])
			ft_exec(envir, token);
		ft_reset(envir);
		waitpid(-1, &pid, 0);
		if (WIFEXITED(pid))
			pid = WEXITSTATUS(pid);
		if (envir->pipe_dad == 1)
		{
			envir->exit_code = pid;
		}
		if (envir->child == 1)
		{
			ft_free_token(envir->start);
			temp = envir->exit_code;
			ft_free_t_envir(envir);
			exit(temp);
		}
		envir->child = 0;
		token = ft_token_to_cmd(token->next);
	}
}

void	ft_exec(t_envir *envir, t_token *token)
{
	int		pid;
	t_token	*previous;
	t_token	*next;

	pid = 0;
	previous = ft_previous_sep(token);
	next = ft_next_sep(token);
	if (previous && previous->type == RIGHT)
		ft_redir_right(envir, token);
	if (previous && previous->type == LEFT)
		ft_redir_left(envir, token);
	if (previous && previous->type == DOUBLERIGHT)
		ft_redir_doubleright(envir, token);
	if (previous && previous->type == PIPE)
		pid = ft_pipe(envir);
	if (next && next->type != NEXT && pid != 1)
		ft_exec(envir, next->next);
	if ((previous == NULL || previous->type == NEXT || previous->type == PIPE)
	&& pid != 1 && envir->block_cmd == 0)
		ft_exec_cmd(envir, token);
}
