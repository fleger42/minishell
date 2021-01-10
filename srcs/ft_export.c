/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:26:49 by user42            #+#    #+#             */
/*   Updated: 2020/10/12 20:28:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sort_doubletab(t_envir *envir)
{
	int i;
	int j;
	char *cpy;

	i = 0;
	while(envir->envp[i] != NULL)
	{
		if(envir->envp[i + 1] != NULL && (envir->envp[i][0] > envir->envp[i + 1][0]))
		{
			cpy = envir->envp[i];
			envir->envp[i] = envir->envp[i + 1];
			envir->envp[i + 1] = cpy;
			i = -1;
		}
		else if(envir->envp[i + 1] != NULL && (envir->envp[i][0] == envir->envp[i + 1][0]))
		{
			j = 0;
			while(envir->envp[i][j] && envir->envp[i + 1][j])
			{
				if(envir->envp[i][j] > envir->envp[i + 1][j])
				{
					cpy = envir->envp[i];
					envir->envp[i] = envir->envp[i + 1];
					envir->envp[i + 1] = cpy;
					i = -1;
					break ;
				}
				else if(envir->envp[i][j] != envir->envp[i + 1][j])
					break ;
				j++;
			}
		}
		i++;
	}
}

int		ft_has_carac(char *str, char c)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_create_exportable(char *str)
{
	int		i;
	char	*cpy;
	int		j;
	
	i = 0;
	j = -1;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=' && str[i + 1] == '\0')
	{
		cpy = malloc(sizeof(char*) * (i + 3));
		while(++j<=i)
			cpy[j] = str[j];
		cpy[i + 1] = 39;
		cpy[i + 2] = 39;
		cpy[i + 3] = '\0';
	}
	else if(str[i] == '\0')
	{
		cpy = malloc(sizeof(char*) * (i + 4));
		while(++j<=i)
			cpy[j] = str[j];
		cpy[i] = '=';
		cpy[i + 1] = 39;
		cpy[i + 2] = 39;
		cpy[i + 3] = '\0';
	}
	else
		cpy = ft_strdup(str);
	return(cpy);
}

void	ft_add_str_tab(t_envir *envir, char *str)
{
	int i;
	char **cpy;

	i = 0;
	while(envir->envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char**) * (i + 2));
	i = 0;
	while(envir->envp[i] != NULL)
	{
		cpy[i] = envir->envp[i];
		i++;
	}
	cpy[i] = ft_create_exportable(str);
	cpy[i + 1] = NULL;
	free(envir->envp);
	envir->envp = cpy;
}

int	ft_cmp_equal(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] != '=')
	{
		if(str1[i] != str2[i])
			return (0);
		i++;
	}
	if(str2[i] == '\0' || str2[i] == '=')
		return (1);
	return (0);
}

int	ft_verif_dupe(t_envir *envir, char *str)
{
	int	i;

	i = 0;
	while(envir->envp[i] != NULL)
	{
		if(ft_cmp_equal(envir->envp[i], str))
			return (1);
		i++;
	}
	return (0);
}

void	ft_replace_line(t_envir *envir, char *str)
{
	int	i;

	i = 0;
	while(envir->envp[i] != NULL)
	{
		if(ft_cmp_equal(envir->envp[i], str))
		{
			free(envir->envp[i]);
			envir->envp[i] = ft_create_exportable(str);
		}
		i++;
	}
}

int ft_export(char **av, t_envir *envir)
{
	int i;

	i = 0;
	if(av[1] == NULL)
	{
		ft_sort_doubletab(envir);
		while(envir->envp[i] != NULL)
		{
			if(envir->envp[i][0] != '_')
			{
				ft_putstr("declare -x ");
				ft_putstr(envir->envp[i]);
				ft_putchar('\n');
			}
			i++;
		}
	}
	else
	{
		int i;

		i = 1;
		while(av[i])
		{
			if(ft_verif_dupe(envir, av[i]) == 1)
			{
				if(ft_has_carac(av[i], '='))
				{
					ft_replace_line(envir, av[i]);
				}
			}
			else
				ft_add_str_tab(envir, av[i]);			
			i++;
		}
	}
	return (1);
}
