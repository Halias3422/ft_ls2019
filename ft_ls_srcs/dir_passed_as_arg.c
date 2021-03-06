/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dir_passed_as_arg.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/20 07:17:00 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 08:30:10 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info				*fill_content_of_dir(struct dirent *read, t_info *head,
					t_args *args, char *curr_file)
{
	t_info			*new;

	if (!(new = (t_info*)malloc(sizeof(t_info))))
	{
		free_list(head, args);
		exit(-1);
	}
	new->file = ft_strnew(0);
	new->path = ft_strjoin(curr_file, "/");
	new->path = free_strjoin(new->path, read->d_name);
	check_file_name(new->path, new, args);
	new->file = free_strjoin(new->file, read->d_name);
	if (ft_strlen(new->file) > args->biggest_word)
		args->biggest_word = ft_strlen(new->file);
	args->sub_fold_nb++;
	new->printing = 1;
	new->sub_folder = 1;
	new->forbidden = 0;
	new->next = NULL;
	head = ft_list_back(head, new);
	return (head);
}

t_info				*get_content_of_dir(t_info *info, t_args *args, DIR *dirp,
					t_info *head)
{
	struct dirent	*read;
	char			*curr_file;

	args->biggest_word = 0;
	curr_file = info->path;
	args->sub_fold_nb = 0;
	args->biggest_size = 0;
	args->biggest_usr = 0;
	args->biggest_grp = 0;
	while ((read = readdir(dirp)) != NULL)
	{
		if (is_contained_in("a", args->arg, 0) > 0 || (is_contained_in("a",
		args->arg, 0) <= 0 && read->d_name[0] != '.') || is_contained_in("f"
		, args->arg, 0) > 0)
			head = fill_content_of_dir(read, head, args, curr_file);
	}
	return (head);
}

t_info				*dir_passed_as_arg(t_info *info, t_args *args)
{
	DIR				*dirp;
	t_info			*head;
	char			*curr_file;
	t_info			*new;

	new = NULL;
	head = new;
	curr_file = info->file;
	dirp = opendir(curr_file);
	if (dirp == NULL)
	{
		ft_printf("ft_ls: %s: Permission denied\n", curr_file);
		info->forbidden = 1;
	}
	else
		new = get_content_of_dir(info, args, dirp, head);
	if (dirp)
		closedir(dirp);
	return (new);
}
