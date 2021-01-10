/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:36:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/04 05:14:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "../include/minishell.h"

int ft_cd(char **av, t_envir *envir)
{
    int i;

    i = 0;
    while(av[i])
        i++;
    if(i>=3)
       ft_error("Error, too many args for cd");
    else if(av[1] == NULL)
    {
        if(chdir(ft_get(envir->envp, "HOME")) != 0)
           ft_error(strerror(errno));
    }
    else if (strcmp(av[1], "-") == 0)
    {

        ft_putstr(ft_get(envir->envp, "OLDPWD"));
        ft_putchar('\n');
        if(chdir(ft_get(envir->envp, "OLDPWD")) != 0)
            ft_error(strerror(errno));
    }
    else if(chdir(av[1]) != 0)
        ft_error(strerror(errno));
      
    return (1);
}	