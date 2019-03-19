/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extended_printing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/22 09:21:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 08:10:40 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_major_minor(t_info *info, int len, t_args *args)
{
	print_spaces(args->biggest_major, check_num_length(info->major), len);
	ft_printf("%d, ", info->major);
	print_spaces(args->biggest_minor, check_num_length(info->minor), len);
	ft_printf("%d %s %s", info->minor, info->date, info->file);
}

void			print_block_size(t_info *info)
{
	int			block;
	int			files_in_dir;

	files_in_dir = 0;
	block = 0;
	while (info)
	{
		files_in_dir++;
		block += info->blk_size;
		info = info->next;
	}
	if (files_in_dir > 0)
		ft_printf("total %d\n", block);
}

void			extended_printing_root_two(t_info *info, t_args *args, int len)
{
	if (info->rights[0] != 'b' && info->rights[0] != 'c')
	{
		if (args->biggest_size > args->biggest_major + args->biggest_minor)
			print_spaces(args->biggest_size, check_num_length(info->size), len);
		else if (info->minor != 0 || info->major != 0)
			print_spaces(args->biggest_major + args->biggest_minor + 2,
					check_num_length(info->size), len);
		ft_printf("%d %s %s%s\033[0m", info->size, info->date, info->color,
		info->file);
	}
	else
		print_major_minor(info, len, args);
	if (info->rights[0] == 'l')
		printing_link(info, args);
	ft_printf("\n");
	args->printed++;
}

void			extended_printing_root_one(t_info *info, t_args *args, int len)
{
	ft_printf("%s", info->rights);
	print_spaces(args->biggest_inodes + 1, check_num_length(info->inodes), len);
	ft_printf("%d", info->inodes);
	if (is_contained_in("g", args->arg, 0) <= 0)
		ft_printf("%s", info->user);
	else
		ft_printf(" ");
	if (is_contained_in("u", args->arg, 0) <= 0)
		print_spaces(args->biggest_usr, ft_strlen(info->user), len);
	if (is_contained_in("o", args->arg, 0) <= 0)
		ft_printf("%s", info->group);
	else
		ft_printf(" ");
	if (is_contained_in("g", args->arg, 0) <= 0)
		print_spaces(args->biggest_grp, ft_strlen(info->group), len);
	extended_printing_root_two(info, args, len);
}
