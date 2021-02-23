/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:49:40 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:27:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_issep(char c)
{
	if (c == ';' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		ft_verif_dollar(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != '=')
	{
		if (str1[i] != str2[i])
		{
			return (0);
		}
		i++;
	}
	if (!(ft_isdigit(str2[i]) || ft_isalpha_maj(str2[i]) ||
	ft_isalpha_min(str2[i]) || str2[i] == '_'))
		return (1);
	return (0);
}

int		ft_check_quote(char *line)
{
	int i;
	int quote_open;

	quote_open = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' && (line == 0 || line[i - 1] != '\\'))
		&& quote_open == 0)
			quote_open = 1;
		else if ((line[i] == '\'' && (line == 0 || line[i - 1] != '\\'))
		&& quote_open == 1)
			quote_open = 0;
		if ((line[i] == '\"' && (line == 0 || line[i - 1] != '\\'))
		&& quote_open == 0)
			quote_open = 2;
		else if ((line[i] == '\"' && (line == 0 || line[i - 1] != '\\')) &&
		quote_open == 2)
			quote_open = 0;
		i++;
	}
	return (quote_open);
}

int		ft_verif_syntax(t_envir *envir)
{
	t_token *token;

	token = envir->start;
	while (token)
	{
		if (ft_istype(token, "LDR") && (token->next == NULL ||
		ft_istype(token->next, "LDRPN")))
		{
			envir->exit_code = 2;
			ft_putstr_fd("minishell: erreur de ", 2);
			ft_putstr_fd("syntaxe près du symbole inattendu « ", 2);
			if (token->next)
				ft_putstr_fd(token->next->string, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd(" »\n", 2);
			return (1);
		}
		else if (ft_istype(token, "PN") && (token->next == NULL ||
		ft_istype(token->next, "LDRPN") || token->prev == NULL))
		{
			envir->exit_code = 2;
			ft_putstr_fd("minishell: erreur de syntaxe", 2);
			ft_putstr_fd(" près du symbole inattendu « ", 2);
			ft_putstr_fd(token->string, 2);
			ft_putstr_fd(" »\n", 2);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
