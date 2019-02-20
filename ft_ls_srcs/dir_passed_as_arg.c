/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dir_passed_as_arg.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/20 07:17:00 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/20 07:52:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void				get_content_of_dir(t_info *info, t_args *args, DIR *dirp, t_info *head)
{
	struct dirent	*read;
	char			*curr_file;

	curr_file = info->file;
		while ((read = readdir(dirp)) != NULL)
		{
			if (!(info = (t_info*)malloc(sizeof(t_info))))
			{
				free_list(head);
				exit (-1);
			}
			info->file = ft_strnew(0);
			info->path = ft_strjoin(curr_file, "/");
			info->path = free_strjoin(info->path, read->d_name);
			check_file_name(info->path, info, args);
			info->file = free_strjoin(info->file, read->d_name);
			info->printing = 1;
			info->next = NULL;
			head = ft_list_back(head, info);
		}

}

void				dir_passed_as_arg(t_info *info, t_args *args)
{
	DIR				*dirp;
	t_info			*head;
	char			*curr_file;

	head = info;
	curr_file = info->file;
	dirp = opendir(curr_file);
	if (dirp == NULL)
		ft_printf("ft_ls: %s: Permission denied\n", curr_file);
	else
		get_content_of_dir(info, args, dirp, head);
}
