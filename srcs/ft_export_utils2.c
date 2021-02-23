/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 07:19:08 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 00:16:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_cmp_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] != '=')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str2[i] == '\0' || str2[i] == '=')
		return (1);
	return (0);
}

void	ft_replace_line(t_envir *envir, char *str)
{
	int	i;

	i = 0;
	while (envir->envp[i] != NULL)
	{
		if (ft_cmp_equal(envir->envp[i], str))
		{
			free(envir->envp[i]);
			envir->envp[i] = ft_remove_multiplespace(ft_strdup(str));
		}
		i++;
	}
}

void	ft_error_variablename(char *c)
{
	ft_putstr_fd("export: «", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("» : identifiant non valable\n", 2);
}

int		ft_verif_validchar(char **all_name, int i)
{
	int j;

	j = 1;
	while (all_name[i][j] && all_name[i][j] != '=')
	{
		if (!(ft_isdigit(all_name[i][j]) || ft_isalpha_maj(all_name[i][j])
		|| ft_isalpha_min(all_name[i][j]) || all_name[i][j] == '_'))
		{
			ft_error_variablename(&all_name[i][j]);
			return (1);
		}
		j++;
	}
	return (0);
}

int		ft_verif_variablename(char **all_name)
{
	int	i;
	int	j;

	i = 0;
	while (all_name[i])
	{
		j = 1;
		if (ft_isdigit(all_name[i][0]))
		{
			ft_error_variablename(&all_name[i][0]);
			return (1);
		}
		if (all_name[i][0] == '=')
		{
			ft_error_variablename(&all_name[i][0]);
			return (1);
		}
		if (ft_verif_validchar(all_name, i))
			return (1);
		i++;
	}
	return (0);
}
