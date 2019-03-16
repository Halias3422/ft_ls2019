/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_error.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 15:41:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 15:55:38 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*move_error_back(t_info *info, t_info *error)
{
	t_info		*head;
	t_info		*tmp;
	t_info		*tmp2;
	int			link;

	tmp = NULL;
	link = 0;
	head = info;
	while (info && info->is_error == 1 &&
	ft_strcmp(info->file, error->file) < 0)
	{
		link++;
		tmp2 = info;
		info = info->next;
	}
	if (link == 0)
	{
		error->next = info;
		head = error;
	}
	else
		add_node_middle_list(info, error, tmp, tmp2);
	return (head);
}

t_info			*print_error(t_info *info)
{
	t_info		*tmp;

	while (info && info->is_error == 1)
	{
		ft_printf("%s\n", info->file);
		tmp = info;
		info = info->next;
		free(tmp->file);
		free(tmp->date);
		free(tmp);
	}
	return (info);
}

t_info			*sort_error(t_info *info, t_args *args)
{
	t_info		*tmp;
	t_info		*head;

	head = info;
	while (info && info->next)
	{
		if (info->next->is_error == 1)
		{
			tmp = info->next;
			info->next = info->next->next;
			head = move_error_back(head, tmp);
			args->nb_files--;
		}
		else
			info = info->next;
	}
	return (head);
}
