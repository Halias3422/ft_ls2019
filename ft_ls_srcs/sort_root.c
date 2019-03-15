/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_root.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 07:54:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 06:30:15 by vde-sain    ###    #+. /#+    ###.fr     */
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

	link = 0;
	head = info;
	while (info && info->is_error == 1 && ft_strcmp(info->file, error->file) < 0)
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
	{
		tmp = info;
		info = error;
		error->next = tmp;
		tmp2->next = info;
	}
	return (head);
}

t_info			*sort_error(t_info *info, t_args *args)
{
	t_info		*tmp;
	t_info		*head;

	head = info;
	while (info && info->next)
	{
		if (info->next->is_error == 1 /*&& ft_strcmp(info->file, info->next->file) > 0*/)
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

t_info			*sort_root_by_args(t_info *info, t_args *args)
{
	t_info		*head;
	int			check;
	int			i;

	i = 0;
	head = info;
	check = 0;
	while (args->arg[i])
		i++;
	while (i >= 0 && args->arg[i] != 't' && args->arg[i] != 'S' &&
			args->arg[i] != 'u')
		i--;
	if ((size_t)i < ft_strlen(args->arg))
	{
		if (args->arg[i] == 't' && is_contained_in("S", args->arg, 0) <= 0 &&
				is_contained_in("u", args->arg, 0) <= 0 && check++ >= 0)
			info = sort_list_time(info);
		if (((args->arg[i] == 'u' && is_contained_in("t", args->arg, 0) > 0) ||
				(args->arg[i] == 't' && is_contained_in("u", args->arg, 0) > 0)) &&
				check++ >= 0)
			info = sort_list_access(info);
		if ((args->arg[i] == 'S' || (args->arg[i] == 't' &&
				is_contained_in("S", args->arg, 0) > 0)) && check++ >= 0)
			info = sort_list_s(info);
	}
	if (check == 0)
		info = sort_list_ascii(info);
	if (is_contained_in("r", args->arg, 0) && check++ >= 0)
		info = sort_list_reverse(info);
	head = info;
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

t_info			*sort_root(t_info *info, t_args *args)
{
	t_info		*head;


	if (is_contained_in("f", args->arg, 0) <= 0)
	{
		info = sort_error(info, args);
		info = print_error(info);
		info = sort_root_by_args(info, args);
	}
	head = info;
	return (head);
}
