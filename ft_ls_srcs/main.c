/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:28:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 17:36:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			init_args(t_args *args)
{
	args->arg = ft_strnew(0);
	args->is_file = 0;
	args->nb = 1;
	args->biggest_word = 0;
	args->biggest_inodes = 0;
	args->biggest_usr = 0;
	args->biggest_grp = 0;
	args->biggest_size = 0;
	args->biggest_major = 0;
	args->biggest_minor = 0;
	args->dir_nb = 0;
	args->dot_arg = 0;
}

int				init_info_link(t_info *info, int link_nb)
{
	info->first_link = link_nb++;
	info->file = NULL;
	info->forbidden = 0;
	info->sub_folder = 0;
	info->next = NULL;
	return (link_nb);
}

void			check_nb_files(int ac, char **av, t_args *args)
{
	int			i;
	int			end_args;

	end_args = 0;
	args->nb_files = 0;
	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0)
			end_args++;
		if (av[i][0] != '-' || (av[i][0] == '-' && av[i][1] == '\0') ||
		(end_args > 0 && ft_strcmp(av[i], "--") != 0))
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
	init_args(&args);
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
	print_root(info, &args);
	free_list(info, &args);
	return (0);
}
