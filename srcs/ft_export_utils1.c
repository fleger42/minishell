/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 07:18:23 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 00:16:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_verif_dupe(t_envir *envir, char *str)
{
	int	i;

	i = 0;
	while (envir->envp[i] != NULL)
	{
		if (ft_cmp_equal(envir->envp[i], str))
			return (1);
		i++;
	}
	return (0);
}

int		ft_sdt_loop(t_envir *envir, int i)
{
	int		j;
	char	*cpy;

	j = 0;
	while (envir->envp[i][j] && envir->envp[i + 1][j])
	{
		if (envir->envp[i][j] > envir->envp[i + 1][j])
		{
			cpy = envir->envp[i];
			envir->envp[i] = envir->envp[i + 1];
			envir->envp[i + 1] = cpy;
			i = -1;
			break ;
		}
		else if (envir->envp[i][j] != envir->envp[i + 1][j])
			break ;
		j++;
	}
	return (i);
}

void	ft_sort_doubletab(t_envir *envir)
{
	int		i;
	char	*cpy;

	i = 0;
	while (envir->envp[i] != NULL)
	{
		if (envir->envp[i + 1] != NULL && (envir->envp[i][0]
		> envir->envp[i + 1][0]))
		{
			cpy = envir->envp[i];
			envir->envp[i] = envir->envp[i + 1];
			envir->envp[i + 1] = cpy;
			i = -1;
		}
		else if (envir->envp[i + 1] != NULL &&
		(envir->envp[i][0] == envir->envp[i + 1][0]))
		{
			i = ft_sdt_loop(envir, i);
		}
		i++;
	}
}

int		ft_rm_count(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	*ft_remove_multiplespace(char *str)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (ft_rm_count(str) + 1));
	while (str[i])
	{
		if (str[i] == ' ')
		{
			new[j++] = str[i];
			while (str[i] == ' ')
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
	return (new);
}
