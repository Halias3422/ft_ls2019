/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_params.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 12:58:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 12:55:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	CHECK IF OPTION PASSED AS ARG EXISTS
*/

void			check_args(char *arg, t_args *args, t_info *info)
{
	char		*model;
	int			invalid_let;
	char		*tmp;

	ft_printf("arg = %s\n", arg);
	model = "lRartSGufg";
	if ((invalid_let = check_content_equal(model, arg)) == 0)
	{
		tmp = ft_strnew(100);
		tmp = ft_strcpy(tmp, arg);
		args->arg = free_both_strjoin(args->arg, tmp);
	}
	else
	{
		ft_printf("ls: illegal option -- %c\nusage: ls ", invalid_let);
		ft_printf("[-GSRafglrtu] [file ...]\n");
		free_list(info);
		exit (0);
	}
}

/*
**	CHECK IF FILE PASSED AS ARG EXISTS
*/

void			check_file_name(char *arg, t_info *info, t_args *args)
{
	struct stat	fileStat;
	int			stat;

	info->is_error = 0;
	stat = lstat(arg, &fileStat);
	if (stat < 0)
	{
		info->is_error = 1;
		info->file = ft_strjoin("ls: ", arg);
		info->file = free_strjoin(info->file, ": No such file of directory\n");
	}
	else
	{
		info->file = arg;
		fill_file_infos(info, args, fileStat);
	}
	args->is_file = 1;
}

/*
**	CREATE LINK BETWEEN NODES OF LINKED CHAINE
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

/*
**	GO THROUGH ARGS - CHECK IF THEY ARE FILES OR OPTIONS
*/

t_info			*check_params(int ac, char **av, t_info *info, t_args *args)
{
	int			av_nb;
	t_info		*head;

	head = NULL;
	args->arg = ft_strnew(0);
	args->is_file = 0;
	av_nb = 1;
	if (ac == 1)
		info->file = ".";
	else
	{
		while (av_nb < ac && av[av_nb][0] == '-')
			check_args(++av[av_nb++], args, info);
		while (av_nb < ac)
		{
			if (!(info = (t_info*)malloc(sizeof(t_info))))
			{
				free_list(head);
				exit (-1);
			}
			info->file = NULL;
			check_file_name(av[av_nb], info, args);
			info->next = NULL;
			head = ft_list_back(head, info);
			av_nb++;
		}
	}
	return (head);
}
