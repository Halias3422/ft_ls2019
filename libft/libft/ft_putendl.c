/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 13:32:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/07 08:56:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	int		a;

	a = 0;
	if (s)
	{
		while (s[a])
			ft_putchar(s[a++]);
		ft_putchar('\n');
	}
}