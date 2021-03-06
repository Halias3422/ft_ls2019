/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcat.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 18:19:04 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 08:58:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (s1[a])
		a++;
	while (s2[b])
		s1[a++] = s2[b++];
	s1[a] = '\0';
	return (s1);
}
