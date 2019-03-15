/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_params.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 12:58:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 13:25:16 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		CHECK IF OPTION PASSED AS ARG EXISTS
*/

void			check_args(char *arg, t_args *args, t_info *info)
{
	char		*model;
	int			invalid_let;
	char		*tmp;

	model = "lRartSufgo";
	if ((invalid_let = check_content_equal(model, arg)) == 0)
	{
		tmp = ft_strnew(100);
		tmp = ft_strcpy(tmp, arg);
		args->arg = free_both_strjoin(args->arg, tmp);
	}
	else
	{
		ft_printf("ls: illegal option -- %c\nusage: ls ", invalid_let);
		ft_printf("[-SRafglrtuo] [file ...]\n");
		free_list(info, args);
		exit (0);
	}
}

/*
**		CHECK IF FILE PASSED AS ARG EXISTS
*/

void			check_file_name(char *arg, t_info *info, t_args *args)
{
	struct stat	fileStat;
	int			stat;

	info->is_error = 0;
//	ft_printf("\narg = %s\n", arg);
	stat = lstat(arg, &fileStat);
	if (stat < 0)
	{
		info->is_error = 1;
		info->file = ft_strjoin("ft_ls: ", arg);
		info->file = free_strjoin(info->file, ": No such file of directory");
	}
	{
		if (info->file == NULL)
			info->file = arg;
		if (ft_strcmp(arg, ".") == 0 && args->dot_arg++ >= 0)
			info->file = "./";
		if (ft_strlen(info->file) > args->biggest_word)
			args->biggest_word = ft_strlen(info->file);
		fill_file_infos(info, args, fileStat);
		add_colors(info, fileStat);
	}
	args->is_file = 1;
}

/*
**		CREATE LINK BETWEEN NODES OF LINKED CHAINE
*/

t_info			*ft_list_back(t_info *head, t_info *info)
{
	t_info		*tmp;

	tmp = NULL;
	if (head == NULL)
		head = info;
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = info;
	}
	return (head);
}

t_info			*check_multiple_params(int ac, char **av, t_info *info,
				t_args *args)
{
	t_info		*head;
	int			link_nb;

	link_nb = 0;
	head = NULL;
	while (args->nb < ac && av[args->nb][0] == '-' && av[args->nb][1] != '\0' && ft_strcmp(av[args->nb], "--") != 0)
		check_args(++av[args->nb++], args, info);
	if (ft_strcmp(av[args->nb], "--") == 0)
		args->nb += 1;
	while (args->nb < ac)
	{
		if (!(info = (t_info*)malloc(sizeof(t_info))))
		{
			free_list(head, args);
			exit (-1);
		}
		info->first_link = link_nb++;
		info->file = NULL;
		info->forbidden = 0;
		check_file_name(av[args->nb], info, args);
		info->sub_folder = 0;
		info->next = NULL;
		head = ft_list_back(head, info);
		args->nb++;
	}
	return (head);
}

t_info			*check_params(int ac, char **av, t_info *info, t_args *args)
{
	t_info		*head;

	head = NULL;
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
	if (args->nb_files == 0)
	{
		if (!(info = (t_info*)malloc(sizeof(t_info))))
			exit (-1);
		info->file = "./";
		info->forbidden = 0;
		check_file_name("./", info, args);
		info->sub_folder = 0;
		info->next = NULL;
		info->type = 1;
		head = ft_list_back(head, info);
		args->dot_arg = 1;
		while (args->nb < ac && av[args->nb][0] == '-' && ft_strcmp(av[args->nb], "--") != 0)
			check_args(++av[args->nb++], args, info);
//		if (ft_strcmp(av[args->nb], "--") == 0)
//			args->nb++;
//		ft_printf("av = %s\n", av[args->nb]);
//		exit (-1);
	}
	else
		head = check_multiple_params(ac, av, info, args);
	return (head);
}
