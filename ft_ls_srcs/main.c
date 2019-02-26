/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:28:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 13:44:42 by vde-sain    ###    #+. /#+    ###.fr     */
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

void			check_nb_files(int ac, char **av, t_args *args)
{
	int			i;

	args->nb_files = 0;
	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-' || (av[i][0] == '-' && av[i][1] == '\0'))
			args->nb_files++;
		i++;
	}
}

int				main(int ac, char **av)
{
	t_info		*info;
	t_args		args;
	t_info		*head;
	
	info = NULL;
//	init_info(info);
	check_nb_files(ac, av, &args);
	info = check_params(ac, av, info, &args);
	head = info;
	while (head)
	{
		head->path = head->file;
		head = head->next;
	}
	if (args.nb_files > 1)
		info = sort_root(info, &args);
//	ft_printf("\n");
	print_root(info, &args);
	head = info;
/*	while (head != NULL)
	{
		ft_printf("racine info->file = %s\n", head->file);
		head = head->next;
	}*/
//	ft_printf("\n");
//	info->path = ft_strnew(0);
//	info->path = free_strjoin(info->path, info->file);
//	head = info;
//	deal_with_recursive(head, &args);
	return (0);
}
