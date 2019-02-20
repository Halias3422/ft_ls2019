/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:28:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/20 14:47:37 by vde-sain    ###    #+. /#+    ###.fr     */
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
	info = sort_list(info, & args);
	head = info;
	while (head != NULL)
	{
		ft_printf("racine info->file = %s\ninfo->printing = %d\n", head->file, head->printing);
		head = head->next;
	}
//	info->path = ft_strnew(0);
//	info->path = free_strjoin(info->path, info->file);
//	head = info;
//	head = deal_with_recursive(head, &args);
/*	while (info != NULL)
	{
		ft_printf("info->file = %s\ninfo->type = %d\ninfo->rights = %s\ninfo->user = %s\ninfo->group = %s\ninfo->size = %d\ninfo->date = %s\ninfo->seconds = %d\n\n\n", info->file, info->type, info->rights, info->user, info->group,info->size, info->date, info->seconds);
		info = info->next;
	}
	while (head != NULL)
	{
		ft_printf("head->file = %s\nhead->type = %d\nhead->rights = %s\nhead->user = %s\nhead->group = %s\nhead->size = %d\nhead->date = %s\nhead->seconds = %d\n\n\n", head->file, head->type, head->rights, head->user, head->group,head->size, head->date, head->seconds);
		head = head->next;
	}*/
	return (0);
}
