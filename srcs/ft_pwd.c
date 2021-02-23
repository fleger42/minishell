/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 04:10:15 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 07:29:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(char **av, t_envir *envir)
{
	char pwd[10000];
	char *final_pwd;

	if (av[1] != NULL)
	{
		ft_putstr("Invalid arg or option for pwd");
		ft_putchar('\n');
		return (1);
	}
	final_pwd = getcwd(pwd, 10000);
	if (final_pwd == NULL)
		final_pwd = ft_get(envir->envp, "PWD");
	ft_putstr_fd(final_pwd, 1);
	ft_putchar('\n');
	(void)envir;
	return (0);
}
