/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_list2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 15:21:27 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 14:58:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info			*add_node_middle_time(t_info *info, t_info *new)
{
	t_info		*head;
	t_info		*tmp;
	t_info		*tmp2;
	int			link;

	tmp = NULL;
	head = info;
	link = 0;
	while (info && info->seconds > new->seconds)
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

t_info			*sort_list_time(t_info *info)
{
	t_info		*head;
	t_info		*tmp;

	head = info;
	while (info && info->next)
	{
		if (info->seconds < info->next->seconds)
		{
			tmp = info->next;
			info->next = info->next->next;
			head = add_node_middle_time(head, tmp);
		}
		else
			info = info->next;
	}
	return (head);
}

t_info			*add_node_middle_s(t_info *info, t_info *new)
{
	t_info		*head;
	t_info		*tmp;
	t_info		*tmp2;
	int			link;

	tmp = NULL;
	head = info;
	link = 0;
	while (info && (info->size > new->size || (info->size == new->size &&
	ft_strcmp(info->file, new->file) < 0)))
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

t_info			*sort_list_s(t_info *info)
{
	t_info		*head;
	t_info		*tmp;

	head = info;
	while (info && info->next)
	{
		if (info->size < info->next->size || (info->size == info->next->size &&
					ft_strcmp(info->file, info->next->file) > 0))
		{
			tmp = info->next;
			info->next = info->next->next;
			head = add_node_middle_s(head, tmp);
		}
		else
			info = info->next;
	}
	return (head);
}
