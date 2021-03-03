/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:20:51 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 04:41:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_cdnoarg(t_envir *envir, char *pwd[4])
{
	if (chdir(ft_get(envir->envp, "HOME")) != 0)
	{
		free(pwd[0]);
		free(pwd[1]);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int		ft_cdtoomany(char **av, char *pwd[4])
{
	int		i;

	i = 0;
	while (av[i])
		i++;
	if (i >= 3)
	{
		free(pwd[0]);
		free(pwd[1]);
		ft_putstr_fd("Error, too many args for cd\n", 2);
		return (1);
	}
	return (0);
}

int		ft_nodir(t_envir *envir, char *pwd[4], char **av)
{
	pwd[3] = ft_get(envir->envp, "PWD");
	if (ft_strcmp(av[1], ".") == 0 || ft_strcmp(av[1], "..") == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot accessparent directories:", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		pwd[2] = ft_catpy("/", av[1]);
		pwd[3] = ft_catpy(pwd[3], pwd[2]);
		free(pwd[2]);
		ft_set_pwd(envir->envp, pwd[3]);
		ft_set_oldpwd(envir->envp, pwd[1]);
		free(pwd[0]);
		free(pwd[1]);
		free(pwd[3]);
		return (0);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	return (1);
}

int		ft_cdtest(t_envir *envir, char **av, char *pwd[4])
{
	if (ft_cdtoomany(av, pwd))
		return (1);
	if (av[1] == NULL)
	{
		if (ft_cdnoarg(envir, pwd))
			return (1);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		if (ft_cdhome(pwd))
			return (1);
	}
	else if (chdir(av[1]) != 0)
	{
		free(pwd[0]);
		free(pwd[1]);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int		ft_cd(char **av, t_envir *envir)
{
	char	*pwd[4];
	char	pwd_buff[10000];

	pwd[0] = ft_strdup(ft_get(envir->envp, "OLDPWD"));
	pwd[1] = ft_strdup(ft_get(envir->envp, "PWD"));
	if (ft_cdtest(envir, av, pwd))
		return (1);
	pwd[3] = getcwd(pwd_buff, 10000);
	if (pwd[3] == NULL)
	{
		if (ft_nodir(envir, pwd, av) == 0)
			return (0);
	}
	ft_set_pwd(envir->envp, pwd[3]);
	ft_set_oldpwd(envir->envp, pwd[1]);
	free(pwd[0]);
	free(pwd[1]);
	return (0);
}
