/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 04:10:15 by user42            #+#    #+#             */
/*   Updated: 2020/10/04 15:25:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(char **av, t_envir *envir)
{
	char pwd[10000];

	if(av[1] != NULL)
	{
		ft_putstr("Invalid arg or option for pwd");
		ft_putchar('\n');
		return (0);
	}
	ft_putstr(getcwd(pwd, 10000));
	ft_putchar('\n');
	(void)envir;
	return (1);
}
