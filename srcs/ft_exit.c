/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:03:07 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:01:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit_tobig(t_envir *envir, char **cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" : argument numérique nécessaire\n", 2);
	envir->exit_code = 2;
}

void	ft_exit_nonum(t_envir *envir, char **cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" : argument numérique nécessaire\n", 2);
	envir->exit_code = 2;
}

int		ft_exit_cmd(t_envir *envir, char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		return (1);
	else if (ft_is_onlynumber(cmd[1]) == 0)
		ft_exit_nonum(envir, cmd);
	else if (i > 2)
	{
		envir->exit_code = 1;
		ft_putstr_fd("minishell: exit: trop d'arguments\n", 2);
		return (0);
	}
	else if (ft_llatoi(cmd[1]) > 9223372036854775807 ||
	(ft_llatoi(cmd[1]) < -9223372036854775807))
		ft_exit_tobig(envir, cmd);
	else if (ft_llatoi(cmd[1]) < 0)
	{
		envir->exit_code = 256 + ft_llatoi(cmd[1]);
	}
	else
		envir->exit_code = ft_llatoi(cmd[1]);
	return (1);
}
