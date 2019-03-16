/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 09:19:07 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 15:59:00 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			add_node_middle_list(t_info *info, t_info *new, t_info *tmp,
				t_info *tmp2)
{
	tmp = info;
	info = new;
	new->next = tmp;
	tmp2->next = info;
}

t_info			*add_node_middle_ascii(t_info *info, t_info *new)
{
	t_info		*head;
	t_info		*tmp;
	t_info		*tmp2;
	int			link;

	tmp = NULL;
	head = info;
	link = 0;
	while (info && ft_strcmp(info->file, new->file) < 0)
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

t_info			*sort_list_ascii(t_info *info)
{
	t_info		*head;
	t_info		*tmp;

	head = info;
	while (info && info->next)
	{
		if (ft_strcmp(info->file, info->next->file) > 0)
		{
			tmp = info->next;
			info->next = info->next->next;
			head = add_node_middle_ascii(head, tmp);
		}
		else
			info = info->next;
	}
	return (head);
}

t_info			*sort_list_time_acc_size(t_info *info, t_args *args, int i,
				int check)
{
	if ((size_t)i < ft_strlen(args->arg))
	{
		if (args->arg[i] == 't' && is_contained_in("S", args->arg, 0) <= 0 &&
				is_contained_in("u", args->arg, 0) <= 0 && check++ >= 0)
			info = sort_list_time(info);
		if (((args->arg[i] == 'u' && is_contained_in("t",
		args->arg, 0) > 0) || (args->arg[i] == 't' && is_contained_in("u",
		args->arg, 0) > 0)) && check++ >= 0)
			info = sort_list_access(info);
		if ((args->arg[i] == 'S' || (args->arg[i] == 't' &&
		is_contained_in("S", args->arg, 0) > 0)) && check++ >= 0)
			info = sort_list_s(info);
	}
	if (check == 0)
		info = sort_list_ascii(info);
	return (info);
}

t_info			*sort_list(t_info *info, t_args *args)
{
	int			check;
	int			i;
	t_info		*head;

	i = 0;
	head = info;
	check = 0;
	while (args->arg[i])
		i++;
	while (i >= 0 && args->arg[i] != 't' && args->arg[i] != 'S' &&
			args->arg[i] != 'u')
		i--;
	info = sort_list_time_acc_size(info, args, i, check);
	if (is_contained_in("r", args->arg, 0))
		info = sort_list_reverse(info);
	head = info;
	return (head);
}
