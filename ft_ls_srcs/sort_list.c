/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 09:19:07 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/19 12:23:45 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*sort_list(t_info *info, t_args *args)
{
	if (is_contained_in("f", args->arg, 0) > 0)
		ft_printf("il y a f\n");
	else
	{
		if (is_contained_in("u", args->arg, 0) > 0)
			ft_printf("il y a u\n");
		if (is_contained_in("t", args->arg, 0) > 0)
			ft_printf("il y a t\n");
		if (is_contained_in("S", args->arg, 0) > 0)
			ft_printf("il y a S\n");
		if (is_contained_in("r", args->arg, 0) > 0)
			ft_printf("il y a r\n");
	}
	return (info);
}
