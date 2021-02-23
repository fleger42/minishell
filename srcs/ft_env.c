/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:59:26 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:54:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_env(char **av, t_envir *envir)
{
	int	i;

	i = 0;
	if (av[1] != NULL)
	{
		ft_putstr("Invalid arg or option for env");
		ft_putchar('\n');
		return (1);
	}
	while (envir->envp[i] != NULL)
	{
		ft_putstr(envir->envp[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}

int		ft_upgrade_shlv(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L' &&
		envp[i][3] == 'V' && envp[i][4] == 'L')
		{
			envp[i] = ft_catpy("SHLVL=", ft_itoa(ft_atoi(envp[i] + 6) + 1));
			return (1);
		}
		i++;
	}
	return (0);
}
