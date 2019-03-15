/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_root.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 12:52:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 15:26:54 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			final_print_inside_fold(t_info *folder, int len, t_args *args)
{
	if (is_contained_in("l", args->arg, 0) <= 0 && is_contained_in("g",
				args->arg, 0) <= 0 && is_contained_in("o", args->arg, 0) <= 0)
	{
		ft_printf("%s%s\033[0m\n", folder->color, folder->file);
//		len = args->biggest_word - ft_strlen(folder->file);
//		while (len-- >= 0 && folder->next)
//			ft_printf(" ");
	}
	else if ((is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
				args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0) && folder->is_error != 1)
		extended_printing_root(folder, args, len);
}

void			print_content_of_single_dir(t_info *info, t_args *args)
{
	t_info		*folder;
	int			len;
	t_info		*tmp;

	if (is_contained_in("R", args->arg, 0) > 0)
		deal_with_recursive(info, args);
	else
	{
		len = 0;
			folder = dir_passed_as_arg(info, args);
			if (is_contained_in("f", args->arg, 0) <= 0 && info->forbidden == 0)
				folder = sort_list(folder, args);
			if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
				args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0)
				print_block_size(folder);
		while (folder)
		{
			if ((((is_contained_in("a", args->arg, 0) <= 0 && folder->file[0] != '.')
				|| is_contained_in("a", args->arg, 0) > 0) && info->forbidden == 0) || is_contained_in("f", args->arg, 0) > 0)
				final_print_inside_fold(folder, len, args);
			tmp = folder;
			folder = folder->next;
			free(tmp->file);
			if (is_contained_in("R", args->arg, 0) > 0)
				free(tmp->path);
			if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
			args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0)
			{
				free(tmp->user);
				free(tmp->group);
				free(tmp->rights);
			}
			free(tmp->date);
			free(tmp);
		}
	}
}

void			print_dir_content(t_info *info, t_args *args, t_info *folder, int len)
{
	t_info		*tmp;
	t_info		*free_fold;
	
//	ft_printf("\n");
	while (info)
	{
		if (info->type == 1 && info->sub_folder == 0)
		{
			tmp = info->next;
			ft_printf("{U.}%s:{eoc}\n", info->file);
			folder = dir_passed_as_arg(info, args);
			if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g", args->arg, 0) > 0 || is_contained_in("o", args->arg, 0))
			print_block_size(folder);
			if (is_contained_in("f", args->arg, 0) <= 0 && info->forbidden == 0)
				folder = sort_list(folder, args);
			while (folder && args->sub_fold_nb-- >= 0)
			{
				if (folder->sub_folder == 1 && ((is_contained_in("a", args->arg,
	0) <= 0 && folder->file[0] != '.') ||
					is_contained_in("a", args->arg, 0) > 0  || is_contained_in("f", args->arg, 0) > 0) && info->forbidden == 0)
					final_print_inside_fold(folder, len, args);
				free_fold = folder;
				folder = folder->next;
				free_one_list(free_fold, args);
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
				is_contained_in("g", args->arg, 0) <= 0 && is_contained_in("o", args->arg, 0) <= 0 && printed++ >= 0)
			ft_printf("%s%s\033[0m\n", info->color, info->file);
		else if (info->type == 0 && (is_contained_in("l", args->arg, 0) > 0 ||
				is_contained_in("g", args->arg, 0) > 0 || (is_contained_in("o", args->arg, 0) > 0)) && info->is_error != 1 && printed++ >= 0)
			extended_printing_root(info, args, len);
		else if (info->type == 0 && (is_contained_in("l", args->arg, 0) > 0 ||
				is_contained_in("g", args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0) && info->is_error == 1)
			ft_printf("%s", info->file);
		info = info->next;
	}
	if (/*is_contained_in("l", args->arg, 0) <= 0 &&*/ printed > 0 && args->dir_nb > 0)
		ft_printf("\n");
	info = head;
	if (info->next)
		print_dir_content(info, args, folder, len);
}

void			print_root(t_info *info, t_args *args)
{
	t_info		*head;
	int			len;

	if (is_contained_in("R", args->arg, 0) > 0)
	{
		print_rec_files(info, args);
		deal_with_recursive(info, args);
	}
	else
	{
		len = 0;
		head = info;
		if ((args->nb_files <= 1 || args->nb == 2 || (args->nb == 3 &&
				ft_strlen(args->arg) > 0)) && info->type == 1)
			print_content_of_single_dir(info, args);
		else
			print_root_and_dirs(info, args, head, len);
	}
}
