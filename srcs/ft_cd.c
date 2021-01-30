/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:36:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 19:56:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "../include/minishell.h"

int ft_cd(char **av, t_envir *envir)
{
	int i;
	char *oldpwd;
	char *pwd;
	char *temp;
	char pwd_buff[10000];

	i = 0;
	oldpwd = ft_strdup(ft_get(envir->envp, "OLDPWD"));
	pwd = ft_strdup(ft_get(envir->envp, "PWD"));

	while(av[i])
		i++;
	if(i>=3)
	{
		free(oldpwd);
		free(pwd);
		ft_putstr_fd("Error, too many args for cd\n", 2);
	   return (1);
	}
	if(av[1] == NULL)
	{
		if(chdir(ft_get(envir->envp, "HOME")) != 0)
		{
			free(oldpwd);
			free(pwd);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	else if (strcmp(av[1], "-") == 0)
	{
		write(2, oldpwd, ft_strlen(oldpwd));
		write(2, "\n", 1);
		if(chdir(oldpwd) != 0)
		{
			free(oldpwd);
			free(pwd);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	else if(chdir(av[1]) != 0)
	{
		free(oldpwd);
		free(pwd);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	char *final_pwd = getcwd(pwd_buff, 10000);
	if(final_pwd == NULL)
	{
		final_pwd = ft_get(envir->envp, "PWD");
		if(ft_strcmp(av[1], ".") == 0 || ft_strcmp(av[1], "..") == 0)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			temp = ft_catpy("/", av[1]);
			final_pwd = ft_catpy(final_pwd, temp);
			free(temp);
			ft_set_pwd(envir->envp, final_pwd);
			ft_set_oldpwd(envir->envp, pwd);
			free(oldpwd);
			free(pwd);
			free(final_pwd);
			return (0);
		}
		ft_putstr_fd("No such file or directory\n", 2);
	}
	ft_set_pwd(envir->envp, final_pwd);
	ft_set_oldpwd(envir->envp, pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}	