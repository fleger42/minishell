/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:34:43 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 04:51:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_verif_unset(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] != '=')
	{
		if(str1[i] != str2[i])
			return (0);
		i++;
	}
	if(str2[i] == '\0')
		return (1);
	return (0);
}

void	ft_remove_line(t_envir *envir, char *str)
{
    int i;
	int j;
	char **new_envp;

	j = 0;
    i = 0;
    while(envir->envp[i])
		i++;
	new_envp = malloc(sizeof(char*) * (i));
	i = 0;
	while(envir->envp[i])
    {
        if(!ft_verif_unset(envir->envp[i], str))
		{
            new_envp[j] = ft_strdup(envir->envp[i]);
			j++;
		}
        i++;
    }
	new_envp[j] = NULL;
	ft_free_env(envir->envp);
	envir->envp = new_envp;
}

int ft_cmp_envir(t_envir *envir, char *str)
{
    int i;

    i = 0;
    while(envir->envp[i])
    {
        if(ft_verif_unset(envir->envp[i], str))
            return (1);
        i++;
    }
    return (0);
}

int ft_unset(char **av, t_envir *envir)
{
    int i;

    i = 0;
	while(av[i])
    {
        if(ft_cmp_envir(envir, av[i]))
		{
            ft_remove_line(envir, av[i]);
		}
        i++;
    }
    return (1);
}