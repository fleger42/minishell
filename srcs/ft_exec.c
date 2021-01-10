/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:39:52 by user42            #+#    #+#             */
/*   Updated: 2020/10/06 18:24:58 by user42           ###   ########.fr       */
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
		return (NULL);
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

void	ft_exec_nonbuiltin(t_envir *envir, char *path)
{
	pid_t	pid;

	pid = fork();
	if(pid == 0)
	{
		if(strcmp(envir->cmd, envir->prog_name) == 0)
			ft_set_shlvl(envir->envp, envir->shlv++);
		if(execve(path, envir->args, envir->envp) == -1)
		{
			ft_putstr(path);
			ft_putchar(':');
			ft_putstr(RED"Command not found\n");
		}
		exit(1);
	}
	else if(pid == -1)
		ft_putstr(RED"Error, pid = -1\n");
	else
		wait(&pid);
	
}

void	ft_exec_builtin(t_envir *envir)
{
	int (*tab_fonction[])()= {&ft_pwd, &ft_unset, &ft_cd, &ft_echo, &ft_export, &ft_env, NULL};
	char *builtin[] = {"pwd", "unset", "cd", "echo", "export", "env", NULL};
    int i;

	i = 0;
	while(builtin[i] != NULL)
	{
		if (strcmp(builtin[i], envir->cmd) == 0)
			tab_fonction[i](envir->args, envir);
		i++;
	}
}
