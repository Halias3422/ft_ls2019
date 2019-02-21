/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_root.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 12:52:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 15:20:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_root(t_info *info, t_args *args)
{
	t_info		*head;
	t_info		*tmp;

	head = info;
	while (head)
	{
		ft_printf("head->file = %s\n", head->file);
		head = head->next;
	}
	head = info;
	if ((args->nb == 2 || (args->nb == 3 && ft_strlen(args->arg) > 0)) &&
			info->type == 1)
	{
		dir_passed_as_arg(info, args);
		info = sort_list(info, args);
		info = info->next;
		while (info)
		{
			ft_printf("%s  ", info->file);
			info = info->next;
		}
	}
	else
	{
		while (info->next)
		{
			if (info->type == 0)
			{
				ft_printf("%s   ", info->file);
			}
			info = info->next;
		}
		ft_printf("\n\n");
		info = head;
		while (info)
		{
			if (info->type == 1 && info->sub_folder == 0)
			{
				tmp = info;
				ft_printf("%s:\n", info->file);
				dir_passed_as_arg(info, args);
				info = sort_list(info, args);
				info = info->next;
				while (info)
				{
					if (info->sub_folder == 1)
						ft_printf("%s  ", info->file);
					info = info->next;
				}
			}
			info = tmp;
//			info = info->next;
//			ft_printf("info = %s\n", info->file);
		}
	}
/*	while (head)
	{
		ft_printf("print root head = %s\n", head->file);
		head = head->next;
	}*/
	
}
