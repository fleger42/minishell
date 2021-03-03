/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:26:28 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 04:58:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ft_search_dir(char *bin, char *cmd)
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
		if (ft_strcmp(r_dir->d_name, cmd) == 0)
		{
			inter = ft_catpy(bin, "/");
			path_ret = ft_catpy(inter, cmd);
			free(inter);
		}
	}
	closedir(dirp);
	return (path_ret);
}

void		ft_sonexec(t_envir *envir, char **cmd, char *path)
{
	if (ft_strcmp(cmd[0], envir->prog_name) == 0)
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

void		ft_exec_nonbuiltin(t_envir *envir, char **cmd)
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
	else if (g_ctrl_c_called)
		envir->exit_code = 130;
	else
		envir->exit_code = envir->exit_code / 256;
	free(path);
}

void		ft_exec_builtin(t_envir *envir, char **cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp("pwd", cmd[0]) == 0)
		envir->exit_code = ft_pwd(cmd, envir);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		envir->exit_code = ft_unset(cmd, envir);
	else if (ft_strcmp("cd", cmd[0]) == 0)
		envir->exit_code = ft_cd(cmd, envir);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		envir->exit_code = ft_echo(cmd, envir);
	else if (ft_strcmp("export", cmd[0]) == 0)
		envir->exit_code = ft_export(cmd, envir);
	else if (ft_strcmp("env", cmd[0]) == 0)
		envir->exit_code = ft_env(cmd, envir);
	i++;
}
