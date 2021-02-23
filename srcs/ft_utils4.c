/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 00:14:55 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:26:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_str_tab(t_envir *envir, char *str)
{
	int		i;
	char	**cpy;

	i = 0;
	while (envir->envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char**) * (i + 2));
	i = 0;
	while (envir->envp[i] != NULL)
	{
		cpy[i] = envir->envp[i];
		i++;
	}
	cpy[i] = ft_remove_multiplespace(ft_strdup(str));
	cpy[i + 1] = NULL;
	free(envir->envp);
	envir->envp = cpy;
}

int		ft_isalpha_min(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

int		ft_isalpha_maj(char c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

int		ft_dollar_quote(int quote_open, char *str, int i)
{
	if ((str[i] == '\'' && (str == 0 || str[i - 1] != '\\')) &&
		quote_open == 0)
		quote_open = 1;
	else if ((str[i] == '\'' && (str == 0 || str[i - 1] != '\\')) &&
		quote_open == 1)
		quote_open = 0;
	return (quote_open);
}

int		ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int		ft_char_tono_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_is_whitespace(str[i]))
		i++;
	return (i);
}

int		ft_is_onlynumber(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}
