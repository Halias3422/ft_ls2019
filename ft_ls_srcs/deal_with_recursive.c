/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_deal_with_recursive.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 08:39:25 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 09:53:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*dir_inside_recursive(t_info *info, t_args *args)
{
	DIR				*dirp;
	t_info			*head;
	t_info			*new;

	new = NULL;
	head = new;
	dirp = opendir(info->path);
	if (dirp == NULL)
	{
		ft_printf("ft_ls: %s: Permission denied\n", info->file);
		info->forbidden = 1;
	}
	else
		new = get_content_of_dir(info, args, dirp, head);
	if (dirp)
		closedir(dirp);
	return (new);

}

void			go_end_folder(t_info *folder, t_args *args, t_info *info)
{
	t_info		*head;

	head = folder;
	if (info->first_link == 0)
		ft_printf("\n");
	ft_printf("{U.}%s:{eoc}\n", info->path);
	print_block_size(folder);
	while (folder)
	{
		if (ft_strcmp(info->path, "./") != 0 || (ft_strcmp(info->path, "./") == 0 && args->dot_arg == 0))
		{
			folder->path = ft_strjoin(info->path, "/");
			folder->path = free_strjoin(folder->path, folder->file);
		}
		else
			folder->path = ft_strjoin(info->path, folder->file);
		if (is_contained_in("a", args->arg, 0) > 0 || (is_contained_in("a", args->arg, 0) <= 0 && folder->file[0] != '.'))
		final_print_inside_fold(folder, 0, args);
		folder = folder->next;
	}
	deal_with_recursive(head, args);
}

void			deal_with_recursive(t_info *info, t_args *args)
{
	t_info		*head;
	t_info		*folder;

	folder = NULL;
	head = info;
	while (info)
	{
		if (ft_strcmp(info->file, ".") != 0 && ft_strcmp(info->file, "..") != 0)
		{
			if (info->type == 1)
			{
				folder = dir_inside_recursive(info, args);
//				free(folder->path);
				folder = sort_root(folder, args);
				go_end_folder(folder, args, info);
				while (folder)
				{
					head = folder;
					folder = folder->next;
					free(head->file);
					free(head->path);
					free(head->date);
					free(head);
				}
			}
		}
		info = info->next;
	}
}
