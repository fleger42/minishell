/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 06:38:27 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 06:04:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_is_charset(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_without_charset(char *str, char *charset)
{
	int i;

	i = 0;
	if(str == NULL)
		return ;
	while(str[i])
	{
		if(!ft_is_charset(str[i], charset))
			ft_putchar(str[i]);
		i++;
	}
}

int ft_is_nstring(char *str)
{
	int j;

	if(str[0] == '-')
	{
		j = 1;
		while(str[j]  != '\0' && str[j] == 'n')
		{
			if(str[j] == ' ')
				return(1);
			j++;
		}
		if(str[j]  == '\0' && str[j - 1] == 'n')
			return(1);
	}
	return(0);
}

int ft_echo(char **av, t_envir *envir)
{
	int i;
	int j;
	int n_option;

	n_option = 0;
	i = 1;
	while(av[i] != NULL && (n_option == 0 || ft_is_nstring(av[i])))
	{
		j = 1;
		while(av[1][j]  != '\0' && av[1][j] == 'n')
		{
			if(av[1][j] == ' ')
				n_option = 1;
			j++;
		}
		if(av[1][j]  == '\0' && av[1][j - 1] == 'n')
			n_option = 1;
		i++;
	}
	if(n_option == 0)
		i = 1;
	while(av[i] != NULL)
	{
		ft_putstr_without_charset(av[i], "\"'");
		if(av[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	if(n_option == 0)
		ft_putchar('\n');
	(void)envir;
	return (1);
}
