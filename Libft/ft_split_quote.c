/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:24:54 by ddychus           #+#    #+#             */
/*   Updated: 2022/12/13 15:32:32 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_count_quote(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			n++;
			if (*s == 39)
			{
				s++;
				while (*s && *s != 39)
					s++;
				s++;
			}
			else
			{
				while (*s && *s != c)
					s++;
			}
		}
	}
	return (n);
}

int	ft_wordlen_quote(char const *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == 39 && s[i + 1])
	{
		i++;
		while (s[i] && s[i] != 39)
			i++;
		i++;
	}
	else if (s[i] != 39)
	{
		while (s[i] && s[i] != c)
		i++;
	}
	if (*s == 39)
		return (i - 2);
	else
		return (i);
}

char	*get_word_quote(char const *s, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = ft_wordlen_quote(s, c);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	if (*s == 39)
	{
		while (++i < len)
			ret[i] = s[i + 1];
	}
	else
	{
		while (++i < len)
			ret[i] = s[i];
	}
	ret[i] = '\0';
	i = 0;
	return (ret);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**ret;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (word_count_quote(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			ret[i] = get_word_quote(s, c);
			s += ft_strlen(ret[i++]) + 1;
			if (*s == 39 && !*(s + 1))
				break ;
		}
	}
	ret[i] = 0;
	return (ret);
}
