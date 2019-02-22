/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extended_printing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/22 09:21:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 11:40:04 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_spaces(size_t nb1, size_t nb2, int len)
{
	len = nb1 - nb2;
	while (len-- > 0)
		ft_printf(" ");
}

void			extended_printing_root(t_info *info, t_args *args, int len)
{
	ft_printf("%s", info->rights);
	print_spaces(args->biggest_inodes + 1, check_num_length(info->inodes), len);
	ft_printf("%d", info->inodes);
	if (is_contained_in("g", args->arg, 0) <= 0)
	{
	ft_printf("%s", info->user);
	print_spaces(args->biggest_usr, ft_strlen(info->user), len);

	}
	print_spaces(args->biggest_grp, ft_strlen(info->group), len);
	ft_printf("%s", info->group);
	print_spaces(args->biggest_size, check_num_length(info->size), len);
	ft_printf("%d %s %s\n", info->size, info->date, info->file);
}
