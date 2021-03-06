/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_list2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 10:30:08 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 07:47:02 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*sort_list_reverse(t_info *info)
{
	t_info		*head;
	t_info		*tmp2;
	t_info		*tmp;

	head = info;
	tmp2 = NULL;
	head = info;
	while (info)
	{
		tmp = info->next;
		info->next = tmp2;
		tmp2 = info;
		info = tmp;
	}
	head = tmp2;
	return (head);
}

t_info			*add_node_middle_access(t_info *info, t_info *new)
{
	t_info		*head;
	t_info		*tmp;
	t_info		*tmp2;
	int			link;

	tmp = NULL;
	head = info;
	link = 0;
	while (info && (info->access > new->access || (info->access == new->access
			&& ft_strcmp(info->file, new->file) < 0)))
	{
		link++;
		tmp2 = info;
		info = info->next;
	}
	if (link == 0)
	{
		new->next = info;
		head = new;
	}
	else
		add_node_middle_list(info, new, tmp, tmp2);
	return (head);
}

t_info			*sort_list_access(t_info *info)
{
	t_info		*head;
	t_info		*tmp;

	head = info;
	while (info->next)
	{
		if (info && info->access <= info->next->access)
		{
			tmp = info->next;
			info->next = info->next->next;
			head = add_node_middle_access(head, tmp);
		}
		else
			info = info->next;
	}
	return (head);
}
