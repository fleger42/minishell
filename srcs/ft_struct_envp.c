/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:37:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 03:14:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_strdup_doubletab(char **envp)
{
	int i;
	char **cpy;

	i = 0;
	while(envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char**) * (i + 1));
	i = 0;
	while(envp[i] != NULL)
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

t_envir		ft_create_t_envir(char **envp, char **av)
{
	t_envir envir;
	envir.envp = ft_strdup_doubletab(envp);
	envir.shlv = ft_get_shlv(envp) + 1;
	envir.args = NULL;
	envir.prog_name = av[0];
	envir.av = av;
	envir.cmd = NULL;
	envir.all_bin = NULL;
	envir.a_path = NULL;
	envir.return_code = 0;
	return (envir);
}

t_envir		*ft_malloc_t_envir(char **envp, char **av)
{
	t_envir *envir;

	envir = (t_envir*)malloc(sizeof(t_envir));
	*envir = ft_create_t_envir(envp, av);
	return (envir); 
}

void	ft_free_t_envir(t_envir *to_free)
{
	ft_free_env(to_free->envp);
	free(to_free);
}