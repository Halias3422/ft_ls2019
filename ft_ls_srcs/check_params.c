/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_params.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 12:58:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 15:43:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			check_args(char *arg, t_args *args)
{
	char		*model;
	int			invalid_let;
	char		*tmp;

	model = "lRartSGufg";
	if ((invalid_let = check_content_equal(model, arg)) == 0)
	{
		tmp = ft_strnew(0);
		tmp = ft_strcpy(tmp, arg);
		args->arg = free_both_strjoin(args->arg, tmp);
		ft_printf("args->arg = /%s/\n", args->arg);
	}
	else
	{
		ft_printf("ls: illegal option -- %c\nusage: ls ", invalid_let);
		ft_printf("[-GSRafglrtu] [file ...]\n");
	}
}

void			check_file_name(char *arg, t_info *info, t_args *args)
{
	struct stat	fileStat;
	int			test;

	info->is_error = 0;
	test= lstat(arg, &fileStat);
	if (test < 0)
	{
		info->is_error = 1;
		info->file = ft_strjoin("ls: ", arg);
		info->file = free_strjoin(info->file, ": No such file of directory\n");
		ft_printf("info->file = %s", info->file);
	}
	else
	{
		info->file = arg;
		ft_printf("info->file = %s\n", info->file);
	}
	args->is_file = 1;
}

void			check_params(int ac, char **av, t_info *info, t_args *args)
{
	int			av_nb;

	args->arg = ft_strnew(0);
	args->is_file = 0;
	av_nb = 1;
	if (ac == 1)
		info->file = ".";
	else
	{
		while (av_nb < ac)
		{
			if (av[av_nb][0] == '-' && args->is_file == 0)
				check_args(++av[av_nb], args);
			else
				check_file_name(av[av_nb], info, args);
			av_nb++;
		}
	}
}
