/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:39:52 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 09:38:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_dir(char *bin, char *cmd)
{
	DIR		*dirp;
	struct dirent *r_dir;
	char	*path_ret;
	char	*inter;
	path_ret = NULL;
	dirp = opendir(bin);
	if (!dirp)
		return (ft_strdup(cmd));
	while((r_dir = readdir(dirp)))
	{
		if(strcmp(r_dir->d_name, cmd) == 0)
		{
			inter = ft_catpy(bin, "/");
			path_ret = ft_catpy(inter, cmd);
			free(inter);
		}
	}
	closedir(dirp);
	return (path_ret);
}

/*int		ft_get_exit_code(char *path)
{
	int fd;
	DIR *folder;

	folder = opendir(path);
	fd = open(path, O_WRONLY);
	if(ft_strchr)

}*/

void	ft_exec_nonbuiltin(t_envir *envir, char **cmd)
{
	pid_t	pid;
	char *path;

	envir->exit_code = 0;
	path = ft_get_path(envir, cmd[0]);
	pid = fork();
	if(pid == 0)
	{
		if(strcmp(cmd[0], envir->prog_name) == 0)
			ft_set_shlvl(envir->envp, envir->shlv++);
		if(execve(path, cmd, envir->envp) < 0)
		{
			free(path);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" : ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			if(errno == EAGAIN)
				exit(126);
			else
				exit(127);
		}
	}
	else if(pid == -1)
		ft_putstr_fd(RED"Error, pid = -1\n", 2);
	else
		waitpid(pid, &envir->exit_code, 0);
	if(WIFEXITED(pid))
	{
		envir->exit_code = WEXITSTATUS(pid);
	}
	else if(ctrl_c_called)
	{
		envir->exit_code = 130;
	}
	else
	{
		envir->exit_code = envir->exit_code/256;
	}
	free(path);
}

void	ft_exec_builtin(t_envir *envir, char **cmd)
{
	int (*tab_fonction[])()= {&ft_pwd, &ft_unset, &ft_cd, &ft_echo, &ft_export, &ft_env, NULL};
	char *builtin[] = {"pwd", "unset", "cd", "echo", "export", "env", NULL};
    int i;

	i = 0;
	while(builtin[i] != NULL)
	{
		if (strcmp(builtin[i], cmd[0]) == 0)
			envir->exit_code = tab_fonction[i](cmd, envir);
		i++;
	}
}
