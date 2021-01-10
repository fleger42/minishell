/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:00:48 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 04:41:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_set_shlvl(char **envp, int shlvl)
{
	int i;
	char	*inter;
	i = 0;
	while(envp[i] != NULL)
	{
		if(envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L' && envp[i][3] == 'V' && envp[i][4] == 'L')
		{
			inter = ft_itoa(shlvl);
			envp[i] = ft_catpy("SHLVL=", inter);
			free(inter);
		}
		i++;
	}
	return (0);
}

void	ft_free_env(char **envp)
{
	int i;

	i = -1;
	while(envp[++i] != NULL)
		free(envp[i]);
	free(envp);
}

void	ft_set_env(char **envp, char *prog_name)
{
	int i;
	char *pwd;
	char *str;
	i = 0;
	while(envp[i] != NULL)
	{
		if(envp[i][0] == '_')
        {
			pwd = ft_catpy(ft_get(envp, "PWD"), "/");
			str = ft_catpy(pwd, prog_name);
			free(pwd);
			free(envp[i]);
			envp[i] = ft_catpy("_=", str);
			free(str);
        }
		i++;
	}	
}