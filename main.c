/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/22 15:37:20 by sho               #+#    #+#             */
/*   Updated: 2015/04/22 18:45:49 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>


int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}

int		ft_countocr(char *str)
{
	int i;
	int	ocr;

	i = 0;
	ocr = 0;
	while(str[i] != '\0')
	{
		if(str[i] == 10 || str[i] == 32)
			ocr++;
		i++;
	}
	return (ocr);
}

char 	**ft_split(char *str)
{
	int 	ocr;
	int		i;
	int		j;
	int		k;
	int		sav;
	char 	**tab;

	i = -1;
	j = 0;
	k = 0;
	sav = 0;
	ocr = ft_countocr(str);
	tab = (char **)malloc(sizeof(char **) * (ocr + 1));
	while(str[++i] != '\0')
	{
		if(str[i] == 32 || str[i] == 10)
		{
			tab[j] = (char *)malloc(sizeof(char *) * (i + 1));
			while(sav < i)
			{
				tab[j][k] = str[sav];
				k++;
				sav++;
			}
			sav++;
			k = 0;
			tab[j][sav+1] = '\0';
			j++; 
		}
	}
	tab[j] = (char *)malloc(sizeof(char *) * (i + 1));
	while(sav < i)
	{
		tab[j][k] = str[sav];
		k++;
		sav++;
	}
	sav++;
	k = 0;
	tab[j][sav+1] = '\0';
	return (tab);
}

int		alphalower(char c)
{
	if (c >= 65 && c <= 90)
		return (c+32);
	else
		return(c);
}

char **ft_sorttab(char **tab, char *str)
{
	int max;
	int	i;
	char	*tmp;

	i = 0;
	max = ft_countocr(str);
	while(i < max)
	{

		if (ft_strlen(tab[i+1]) < ft_strlen(tab[i]))
		{
			tmp = (char *)malloc(sizeof(char *) * (ft_strlen(tab[i])));
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while(i < max)
	{
		if (ft_strlen(tab[i+1]) == ft_strlen(tab[i]))
		{
			if (alphalower(tab[i+1][0]) < alphalower(tab[i][0]))
			{
				tmp = (char *)malloc(sizeof(char *) * (ft_strlen(tab[i])));
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				i = 0;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (tab);
}

void ft_showtab(char **tab, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_countocr(str);
	while(i < len)
	{
		write(1, tab[i], ft_strlen(tab[i]));
		if(ft_strlen(tab[i]) == ft_strlen(tab[i+1]))
			write(1, " ", 1);
		else
			write(1, "\n", 1);
		i++;
	}
	write(1, tab[len], ft_strlen(tab[len]));
}


int main(int ac, char **av)
{
	char **tab;

	if(ac == 2)
	{
		tab = ft_split(av[1]);
		tab = ft_sorttab(tab, av[1]);
		ft_showtab(tab, av[1]);
	}
	write(1, "\n", 1);
	return (0);
}