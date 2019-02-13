/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   deal_with_recursive.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 10:24:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 14:20:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info				*ft_list_back_next2(t_info *dir_head, t_info *info)
{
	t_info			*tmp;

	tmp = NULL;
	if (dir_head == NULL)
		dir_head = info;
	else
	{
		tmp = dir_head;
		while (tmp->next2 != NULL)
		{
			tmp = tmp->next2;
			tmp->next2 = info;
		}
	}
	return (dir_head);
}

t_info				*get_folder_content(t_info *info, t_args *args, char *curr_file)
{
	t_info			*head;
	struct dirent	*read;
	DIR				*dirp;
	
	args->is_file = 1;
	head = info;
	dirp = opendir(curr_file);
	if (dirp == NULL)
		return (NULL);
	while ((read = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..") != 0)
		{
		if (!(info = (t_info*)malloc(sizeof(t_info))))
		{
			free_list(head);
			exit (-1);
		}
		info->file = NULL;
		info->path = ft_strjoin(curr_file, "/");
		info->path = free_strjoin(info->path, read->d_name);
//		if (ft_strcmp(read->d_name, ".") != 0 && ft_strcmp(read->d_name, "..") != 0)
			check_file_name(info->path, info, args);
		info->next = NULL;
		head = ft_list_back(head, info);
//		ft_printf("dossier -> %s\n", read->d_name);
		}
	}
	closedir(dirp);
	return (head);
}

t_info				*deal_with_recursive(t_info *info, t_args *args)
{
	t_info			*head;
	t_info			*dir_head;
	char			*curr_file;

	head = info;
	dir_head = NULL;
	args->is_file = 1;
	if (info->type == 1)
	{
		curr_file = info->file;
		if (!(info->next2 = (t_info*)malloc(sizeof(t_info))))
		{
			free_list(head);
			exit (-1);
		}
		info->file = NULL;
		info->next2 = get_folder_content(info, args, curr_file);
		dir_head = ft_list_back_next2(dir_head, info);
		info->next2->next2 = NULL;
	}
	if ((is_contained_in("R", args->arg, 0) > 0) && info->next != NULL)
		deal_with_recursive(info->next, args);
	return (head);
}
