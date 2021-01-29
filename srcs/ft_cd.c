/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:36:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 09:38:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "../include/minishell.h"

int ft_cd(char **av, t_envir *envir)
{
    int i;
    char *oldpwd;
    char *pwd;
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
        ft_error("Error, too many args for cd");
       return (1);
    }
    else if(av[1] == NULL)
    {
        if(chdir(ft_get(envir->envp, "HOME")) != 0)
        {
            ft_error(strerror(errno));
            return (1);
        }
    }
    else if (strcmp(av[1], "-") == 0)
    {
        write(2, oldpwd, ft_strlen(oldpwd));
        write(2, "\n", 1);
        if(chdir(oldpwd) != 0)
        {
            ft_error(strerror(errno));
            return (1);
        }
    }
    else if(chdir(av[1]) != 0)
    {
        free(oldpwd);
        free(pwd);
        ft_error(strerror(errno));
        return (1);
    }
    ft_set_pwd(envir->envp, getcwd(pwd_buff, 10000));
    ft_set_oldpwd(envir->envp, pwd);
    free(oldpwd);
    free(pwd);
    return (0);
}	