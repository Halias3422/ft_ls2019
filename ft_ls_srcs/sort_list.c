/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 09:19:07 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/20 14:45:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*add_node_middle(t_info *info, t_info *new)
{
	t_info	*head;
	t_info	*tmp;
	t_info	*tmp2;
	int		link;

	head = info;
	link = 0;
	while (info && info->size > new->size)
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
	{
		tmp = info;
		info = new;
		new->next = tmp;
		tmp2->next = info;
	}
	return (head);
}

int		g_i = 0;

t_info			*sort_list_s(t_info *info)
{
	t_info		*head;
	t_info		*head2;
	t_info		*tmp;
	int			link;

	head = info;
	while (info->next)
	{
		link = 0;
		if (info->size < info->next->size)
		{
			tmp = info->next;
			info->next = info->next->next;
			head = add_node_middle(head, tmp);
		}
		else
			info = info->next;
	}
	head2 = head;
  while (head2 != NULL)
  {
  ft_printf("FIN racine info->file = %s\n", head2->file, head2->printing);
  head2 = head2->next;
  }
  return (head);
}

t_info			*sort_list(t_info *info, t_args *args)
{
	if (is_contained_in("f", args->arg, 0) <= 0)
	{
		if (is_contained_in("t", args->arg, 0) > 0 &&
				is_contained_in("S", args->arg, 0) <= 0)

			if (is_contained_in("u", args->arg, 0) > 0)
				ft_printf("il y a u\n");
		if (is_contained_in("S", args->arg, 0) > 0)
			info->next = sort_list_s(info->next);
		if (is_contained_in("r", args->arg, 0) > 0)
			ft_printf("il y a r\n");
	}
	return (info);
}
