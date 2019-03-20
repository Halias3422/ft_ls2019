/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extra_ft_print.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 17:49:57 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 13:12:36 by vde-sain    ###    #+. /#+    ###.fr     */
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

void			printing_link(t_info *info, t_args *args)
{
	int			i;
	ssize_t		len;
	char		*link;

	i = 0;
	if (!(link = (char*)malloc(sizeof(char) * 256)))
	{
		free_list(info, args);
		exit(-1);
	}
	len = readlink(info->path, link, 256);
	link[len] = '\0';
	ft_printf(" -> %s", link);
	free(link);
}

void			final_print_inside_fold(t_info *folder, int len, t_args *args)
{
	if (is_contained_in("l", args->arg, 0) <= 0 && is_contained_in("g",
				args->arg, 0) <= 0 && is_contained_in("o", args->arg, 0) <= 0)
	{
		ft_printf("%s%s\033[0m\n", folder->color, folder->file);
	}
	else if ((is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
	args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0) &&
	folder->is_error != 1)
		extended_printing_root_one(folder, args, len);
}

void			print_content_of_single_dir_two(t_info *info, t_args *args,
				t_info *folder, int len)
{
	t_info		*tmp;

	while (folder)
	{
		if ((((is_contained_in("a", args->arg, 0) <= 0 && folder->file[0]
		!= '.') || is_contained_in("a", args->arg, 0) > 0) &&
		info->forbidden == 0) || is_contained_in("f", args->arg, 0) > 0)
			final_print_inside_fold(folder, len, args);
		tmp = folder;
		folder = folder->next;
		free(tmp->file);
		if (is_contained_in("R", args->arg, 0) > 0 || args->nb_files <= 1)
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

void			print_content_of_single_dir_one(t_info *info, t_args *args)
{
	t_info		*folder;
	int			len;

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
		print_content_of_single_dir_two(info, args, folder, len);
	}
}
