/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_root.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 12:52:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 13:54:27 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			final_print_inside_fold(t_info *folder, int len, t_args *args)
{
	if (is_contained_in("l", args->arg, 0) <= 0 && is_contained_in("g",
				args->arg, 0) <= 0)
	{
		ft_printf("%s\n", folder->file);
//		len = args->biggest_word - ft_strlen(folder->file);
//		while (len-- >= 0 && folder->next)
//			ft_printf(" ");
	}
	else if ((is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
				args->arg, 0) > 0) && folder->is_error != 1)
		extended_printing_root(folder, args, len);
}

void			print_content_of_single_dir(t_info *info, t_args *args)
{
	t_info		*folder;
	int			len;

	if (is_contained_in("R", args->arg, 0) > 0)
		deal_with_recursive(info, args);
	else
	{
	len = 0;
		folder = dir_passed_as_arg(info, args);
		if (info->forbidden == 0)
			folder = sort_list(folder, args);
	while (folder)
	{
		if (((is_contained_in("a", args->arg, 0) <= 0 && folder->file[0] != '.')
				|| is_contained_in("a", args->arg, 0) > 0) && info->forbidden == 0)
			final_print_inside_fold(folder, len, args);
		folder = folder->next;
	}
	}
}

void			print_dir_content(t_info *info, t_args *args, t_info *folder, int len)
{
	t_info		*tmp;

	while (info)
	{
		if (info->type == 1 && info->sub_folder == 0)
		{
//			ft_printf("\n");
			tmp = info->next;
			ft_printf("%s:\n", info->file);
			folder = dir_passed_as_arg(info, args);
			if (info->forbidden == 0)
				folder = sort_list(folder, args);
			while (folder && args->sub_fold_nb-- >= 0)
			{
				if (folder->sub_folder == 1 && ((is_contained_in("a", args->arg,
					0) <= 0 && folder->file[0] != '.') ||
					is_contained_in("a", args->arg, 0) > 0) && info->forbidden == 0)
					final_print_inside_fold(folder, len, args);
				folder = folder->next;
			}
		if (info->next)
			ft_printf("\n");
		}
		info = info->next;
	}
}

void			print_root_and_dirs(t_info *info, t_args *args, t_info *head, int len)
{
	t_info		*folder;
	int			printed;

	printed = 0;
	folder = NULL;
	while (info)
	{
		if (info->type == 0 && is_contained_in("l", args->arg, 0) <= 0 &&
				is_contained_in("g", args->arg, 0) <= 0 && printed++ >= 0)
			ft_printf("%s\n", info->file);
		else if (info->type == 0 && (is_contained_in("l", args->arg, 0) > 0 ||
				is_contained_in("g", args->arg, 0) > 0) && info->is_error != 1)
			extended_printing_root(info, args, len);
		else if (info->type == 0 && (is_contained_in("l", args->arg, 0) > 0 ||
				is_contained_in("g", args->arg, 0) > 0) && info->is_error == 1)
			ft_printf("%s", info->file);
		info = info->next;
	}
	if (is_contained_in("l", args->arg, 0) <= 0 && printed > 0)
		ft_printf("\n");
	info = head;
	print_dir_content(info, args, folder, len);
	if (is_contained_in("R", args->arg, 0) > 0)
		deal_with_recursive(info, args);
}

void			print_root(t_info *info, t_args *args)
{
	t_info		*head;
	int			len;

	len = 0;
	head = info;
	if ((args->nb_files <= 1 || args->nb == 2 || (args->nb == 3 &&
			ft_strlen(args->arg) > 0)) && info->type == 1)
		print_content_of_single_dir(info, args);
	else
		print_root_and_dirs(info, args, head, len);
}
