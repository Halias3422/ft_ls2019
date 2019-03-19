/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_file_infos.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 12:18:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 15:31:32 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void				fill_date_info(t_info *info, time_t ret, char *second)
{
	int				i;
	int				k;

	k = 0;
	i = 4;
	info->date[k++] = ' ';
	if (info->seconds < ret - 15778800 || info->seconds > ret + 15778800)
	{
		while (second[i] && i < 24)
		{
			if (i == 10)
			{
				info->date[k++] = ' ';
				i = 19;
			}
			info->date[k++] = second[i++];
		}
	}
	else
	{
		while (second[i] && i < 16)
			info->date[k++] = second[i++];
	}
}

void				get_date_info(t_info *info, struct stat filestat,
					t_args *args)
{
	time_t			stat_time;
	char			*second;
	time_t			*curr_time;
	time_t			ret;

	curr_time = 0;
	ret = 0;
	ret = time(curr_time);
	info->date = ft_strnew(14);
	if (is_contained_in("u", args->arg, 0) <= 0)
		stat_time = filestat.st_mtime;
	else
		stat_time = filestat.st_atime;
	second = ctime(&stat_time);
	info->seconds = stat_time;
	fill_date_info(info, ret, second);
}

void				get_minor_and_major(t_info *info, struct stat filestat,
					t_args *args)
{
	int				dev;

	dev = filestat.st_rdev;
	info->major = major(dev);
	if (check_num_length(info->major) > args->biggest_major)
		args->biggest_major = check_num_length(info->major);
	info->minor = minor(dev);
	if (check_num_length(info->minor) > args->biggest_minor)
		args->biggest_minor = check_num_length(info->minor);
}

void				fill_file_infos(t_info *info, t_args *args, struct stat
					filestat)
{
	info->printing = 1;
	if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g", args->arg
	, 0) > 0 || is_contained_in("o", args->arg, 0) > 0)
	{
		get_minor_and_major(info, filestat, args);
		info->inodes = filestat.st_nlink;
		if (check_num_length(info->inodes) > args->biggest_inodes)
			args->biggest_inodes = check_num_length(info->inodes);
		fill_file_rights(info, filestat);
		fill_user_info(info, filestat, args);
	}
	info->access = filestat.st_atime;
	get_date_info(info, filestat, args);
	info->size = filestat.st_size;
	info->blk_size = filestat.st_blocks;
	if (check_num_length(info->size) > args->biggest_size && info->is_error < 1)
		args->biggest_size = check_num_length(info->size);
	info->type = S_ISDIR(filestat.st_mode);
	if (S_ISLNK(filestat.st_mode) == 1)
		info->type = 2;
	if (info->type == 1 && args->dir_nb++ >= 0)
		info->printing = -1;
}
