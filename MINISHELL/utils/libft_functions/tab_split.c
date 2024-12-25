/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:56:10 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:46 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_countlength(char *s)
{
	int	i;
	int	nws;

	i = 0;
	nws = 0;
	while ((s[i] == 32 || s[i] == 9) && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != 32 && s[i] != 9)
		{
			nws++;
			while ((s[i] != 32 && s[i] != 9) && s[i])
				i++;
		}
		else
			i++;
	}
	return (nws);
}

int	ft_eachlength(char *s, int	*p)
{
	int	l;

	l = 0;
	while (s[*p] && (s[*p] == 32 || s[*p] == 9))
		*p += 1;
	while (s[*p])
	{
		if (s[*p] == 32 || s[*p] == 9)
			break ;
		else
		{
			l++;
			*p += 1;
		}
	}
	return (l);
}

int	ft_allocat(char **str, char *s, int nwss)
{
	int		eachlength;
	int		p;
	int		i;

	i = 0;
	p = 0;
	while (nwss != 0 && i < nwss)
	{
		eachlength = ft_eachlength((char *)s, &p);
		str[i] = ft_substr(s, (p - eachlength), eachlength);
		i++;
	}
	str[i] = 0;
	return (1);
}

char	**tab_split(char *s)
{
	char	**str;
	int		nwss;

	nwss = ft_countlength((char *)s);
	str = gc((nwss + 1) * sizeof(char *), 0, 0, 0);
	ft_allocat(str, (char *)s, nwss);
	return (str);
}
