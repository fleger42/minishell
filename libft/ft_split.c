/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleger <fleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:35 by fleger            #+#    #+#             */
/*   Updated: 2019/11/09 14:45:35 by fleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		number_of_word(char *str, char c)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if ((str[i - 1] == c && str[i] != c) || (i == 0 && str[i] != c))
		{
			nbr++;
		}
		i++;
	}
	return (nbr);
}

int		fin(char **tab, int k)
{
	if (!(tab[k] = (char *)malloc(sizeof(char))))
		return (0);
	tab[k] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	if (!(tab = (char **)malloc(sizeof(char *) *
	(number_of_word((char *)s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (!(tab[k] = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
				return (NULL);
			j = 0;
			while (s[i] != c && s[i])
				tab[k][j++] = s[i++];
			tab[k++][j] = '\0';
		}
	}
	return ((fin(tab, k) == 0) ? NULL : tab);
}
