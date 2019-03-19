/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_root.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 07:54:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 09:10:34 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*sort_root_by_args(t_info *info, t_args *args)
{
	t_info		*head;
	int			check;
	int			i;

	i = 0;
	head = info;
	check = 0;
	while (args->arg[i])
		i++;
	while (i >= 0 && args->arg[i] != 't' && args->arg[i] != 'S' &&
			args->arg[i] != 'u')
		i--;
	info = sort_list_time_acc_size(info, args, i, check);
	if (is_contained_in("r", args->arg, 0) && check++ >= 0)
		info = sort_list_reverse(info);
	head = info;
	return (head);
}

t_info			*sort_root(t_info *info, t_args *args)
{
	t_info		*head;

	info = sort_error(info, args);
	info = print_error(info);
	if (is_contained_in("f", args->arg, 0) <= 0)
		info = sort_root_by_args(info, args);
	head = info;
	return (head);
}
