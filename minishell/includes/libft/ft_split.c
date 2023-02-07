/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:24:52 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/30 19:36:18 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_len(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			++i;
		if (s[i] != c && s[i])
		{
			++len;
			while (s[i] != c && s[i])
				++i;
		}
	}
	return (len);
}

int	ft_split_malloc(char **split_s, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			++i;
		if (s[i] != c && s[i])
		{
			j = 0;
			while (s[i] && s[i++] != c)
			{
				++j;
			}
			split_s[k] = malloc(sizeof(char) * (j + 1));
			if (!split_s[k++])
				return (-1);
		}
	}
	return (0);
}

void	ft_split_fill(char **split_s, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			++i;
		if (s[i] != c && s[i])
		{
			j = 0;
			while (s[i] != c && s[i])
				split_s[k][j++] = s[i++];
			split_s[k++][j] = '\0';
		}
	}
	split_s[k] = NULL;
}

void	ft_split_free(char **split_s)
{
	int	i;

	i = -1;
	while (split_s[++i])
		free(split_s[i]);
	free (split_s);
}

char	**ft_split(const char *s, char c)
{
	char	**split_s;

	if (!s)
	{
		split_s = malloc(sizeof(char *));
		split_s[0] = NULL;
		return (split_s);
	}
	split_s = malloc(sizeof(char *) * (ft_split_len(s, c) + 1));
	if (!split_s)
		return (NULL);
	if (ft_split_malloc(split_s, s, c) == -1)
	{
		ft_split_free(split_s);
		return (NULL);
	}
	ft_split_fill(split_s, s, c);
	return (split_s);
}
