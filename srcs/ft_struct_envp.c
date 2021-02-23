/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:37:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 07:23:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**ft_strdup_doubletab(char **envp)
{
	int		i;
	char	**cpy;

	i = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char**) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

char		**ft_createmini_env(void)
{
	char	**cpy;
	char	buf[10000];

	cpy = malloc(sizeof(char*) * 5);
	cpy[0] = ft_catpy("PWD=", getcwd(buf, 10000));
	cpy[1] = ft_strdup("SHLVL=1");
	cpy[2] = ft_strdup("_=");
	cpy[2] = ft_strdup("OLDPWD=");
	cpy[4] = NULL;
	return (cpy);
}

t_envir		ft_create_t_envir(char **envp, char **av)
{
	t_envir	envir;

	if (envp[0] == NULL)
		envir.envp = ft_createmini_env();
	else
		envir.envp = ft_strdup_doubletab(envp);
	envir.shlv = ft_get_shlv(envp) + 1;
	envir.args = NULL;
	envir.prog_name = av[0];
	envir.av = av;
	envir.cmd = NULL;
	envir.all_bin = NULL;
	envir.a_path = NULL;
	envir.child = 0;
	envir.block_cmd = 0;
	envir.standardin = dup(0);
	envir.standardout = dup(1);
	envir.fdoutput = -1;
	envir.fdinput = -1;
	envir.pipeoutfd = -1;
	envir.pipeinfd = -1;
	envir.exit_code = 0;
	return (envir);
}

t_envir		*ft_malloc_t_envir(char **envp, char **av)
{
	t_envir	*envir;

	envir = (t_envir*)malloc(sizeof(t_envir));
	*envir = ft_create_t_envir(envp, av);
	return (envir);
}

void		ft_free_t_envir(t_envir *to_free)
{
	ft_free_env(to_free->envp);
	free(to_free);
}
