/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:28:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 14:21:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*void			init_info(t_info *info)
{
	info->file = NULL;
//	info->is_error = 0;
//	info->type = -1;
	info->rights = NULL;
//	info->inodes = 0;
	info->user = NULL;
	info->group = NULL;
//	info->size = 0;
//	info->date = '\0';
	info->name = NULL;
}*/

int				main(int ac, char **av)
{
	t_info		*info;
	t_args		args;
	t_info		*head;

	info = NULL;
//	init_info(info);
	info = check_params(ac, av, info, &args);
	head = info;
	while (head != NULL)
	{
		ft_printf("info->file = %s\n", head->file);
		head = head->next;
	}
	ft_printf("\n\n\n");
	info = deal_with_recursive(info, &args);
/*	while (info != NULL)
	{
		if (info->next2 != NULL)
		{
			ft_printf("go next2\n");
			while (info->next2 != NULL)
			{
				info = info->next2;
				ft_printf("j'avance dans next2\n");
			}
		}
		ft_printf("info->file fin = %s\n", info->file);
		info = info->next;
	}*/
	while (info != NULL)
	{
		ft_printf("info->file = %s\ninfo->type = %d\ninfo->rights = %s\ninfo->user = %s\ninfo->group = %s\ninfo->size = %d\ninfo->date = %s\ninfo->seconds = %d\n\n\n", info->file, info->type, info->rights, info->user, info->group,info->size, info->date, info->seconds);
		info = info->next;
	}
	return (0);
}
