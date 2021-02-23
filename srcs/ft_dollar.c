/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:50:19 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:26:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_dollar_setlen(int *length, int i, char *str)
{
	if (str[i] == ' ')
	{
		*length = -1;
		return (-1);
	}
	if (ft_isdigit(str[i]))
	{
		*length = 1;
		return (-1);
	}
	return (1);
}

char	*ft_replace_dollar(t_envir *envir, char *str, int *length)
{
	int i;

	i = 0;
	if (str[i] == '?')
	{
		*length = 1;
		return (ft_itoa(envir->exit_code));
	}
	while (envir->envp[i] != NULL)
	{
		if (ft_verif_dollar(envir->envp[i], str) == 1)
			return (ft_strdup(ft_walk_until_equal(envir->envp[i], length)));
		i++;
	}
	i = 0;
	if (ft_dollar_setlen(length, i, str) == -1)
		return (NULL);
	while (ft_isdigit(str[i]) || ft_isalpha_maj(str[i]) ||
	ft_isalpha_min(str[i]) || str[i] == '_')
		i++;
	*length = i;
	return (NULL);
}

char	*ft_dollar_newline(t_envir *envir, char *str, int i, int j)
{
	char	*temp;
	char	*start;
	char	*temp2;

	start = malloc(sizeof(char) * (i + 1));
	j = -1;
	while (++j < i)
		start[j] = str[j];
	start[j] = '\0';
	temp = ft_replace_dollar(envir, str + 1 + i, &j);
	if (temp != NULL)
	{
		temp2 = temp;
		temp = ft_catpy(start, temp2);
		free(temp2);
	}
	else
		temp = ft_strdup(start);
	free(start);
	start = ft_strdup(str + i + j + 1);
	free(str);
	str = ft_catpy(temp, start);
	free(temp);
	free(start);
	return (str);
}

char	*ft_dollar(t_envir *envir, char *str)
{
	int		i;
	int		quote_open;
	int		j;

	j = -1;
	quote_open = 0;
	i = 0;
	while (str[i] && str[i] != ';')
	{
		quote_open = ft_dollar_quote(quote_open, str, i);
		if (quote_open == 0 && (str[i] == '$' && str[i + 1] != '\0' &&
		(ft_isdigit(str[i + 1]) || ft_isalpha_maj(str[i + 1]) ||
		ft_isalpha_min(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')
		&& str[i + 1] != ' ' && (i == 0 || str[i - 1] != '\\')))
		{
			str = ft_dollar_newline(envir, str, i, j);
			i = -1;
		}
		i++;
	}
	return (str);
}

void	ft_dollar_until_next(t_envir *envir, t_token *first)
{
	t_token *token;

	token = first;
	while (token && token->type != NEXT)
	{
		token->string = ft_dollar(envir, token->string);
		token->string = ft_str_remove(token->string);
		token = token->next;
	}
}
