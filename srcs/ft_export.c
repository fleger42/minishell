/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:26:49 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 07:19:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_print_until_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		ft_putchar(str[i]);
		i++;
	}
	if (str[i] == '=')
	{
		ft_putchar('=');
		ft_putchar('"');
		ft_putstr(str + i + 1);
		ft_putchar('"');
	}
	else
		ft_putstr(str + i);
	return (i);
}

void	ft_print_export(t_envir *envir)
{
	int	i;

	i = 0;
	while (envir->envp[i] != NULL)
	{
		if (envir->envp[i][0] != '_')
		{
			ft_putstr("declare -x ");
			ft_print_until_space(envir->envp[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

int		ft_export(char **av, t_envir *envir)
{
	int	i;

	i = 1;
	if (av[1] == NULL)
	{
		ft_sort_doubletab(envir);
		ft_print_export(envir);
	}
	else
	{
		if (ft_verif_variablename(av))
			return (1);
		while (av[i])
		{
			if (ft_verif_dupe(envir, av[i]) == 1)
			{
				if (ft_strchr(av[i], '='))
					ft_replace_line(envir, av[i]);
			}
			else
				ft_add_str_tab(envir, av[i]);
			i++;
		}
	}
	return (0);
}
