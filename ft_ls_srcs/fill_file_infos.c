/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_file_infos.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 12:18:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 11:06:19 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void				fill_file_rights(t_info *info, struct stat fileStat)
{
	if (!(info->rights = (char*)malloc(sizeof(char) * 13 + 1)))
	{
		free(info);
		exit (-1);
	}
//	ft_printf("%#b\n", fileStat.st_mode);
	info->rights[0] = (fileStat.st_mode & S_IFDIR) ? 'd' : '-';
	if (info->rights[0] != 'd')
		info->rights[0] = S_ISLNK(fileStat.st_mode) ? 'l' : '-';
	else
		info->rights[0] = (fileStat.st_mode & S_IFLNK) ? 'l' : 'd';
	info->rights[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
 	info->rights[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	info->rights[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	info->rights[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	info->rights[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	info->rights[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	info->rights[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	info->rights[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	info->rights[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
	info->rights[10] = ' ';
	info->rights[11] = ' ';
	info->rights[12] = '\0';
}

void				fill_user_group_info(t_info *info, struct stat fileStat)
{
	int				user_uid;
	struct passwd	*user_name;
	int				user_gid;
	struct group	*user_group;

	info->user = ft_strnew(0);
	info->group = ft_strnew(0);
	user_uid = fileStat.st_uid;
	user_name = getpwuid(user_uid);
	info->user = free_strjoin(info->user, " ");
	info->user = free_strjoin(info->user, user_name->pw_name);
	info->user = free_strjoin(info->user, "  ");
	user_gid = fileStat.st_gid;
	user_group = getgrgid(user_gid);
	info->group = free_strjoin(info->group, user_group->gr_name);
	info->group = free_strjoin(info->group, "  ");
}

void				fill_date_info(t_info *info, struct stat fileStat)
{
	time_t			stat_time;
	char			*second;
	int				i;
	int				k;

	k = 0;
	i = 4;
	info->date = ft_strnew(14);
	stat_time = fileStat.st_mtime;
	second = ctime(&stat_time);
	info->seconds = stat_time;
	info->date[k++] = ' ';
	while (second[i] && i < 16)
		info->date[k++] = second[i++];
	info->date = free_strjoin(info->date, " ");
}

void				fill_file_infos(t_info *info, t_args *args, struct stat fileStat)
{
	if (is_contained_in("l", args->arg, 0) > 0)
	{
		fill_file_rights(info, fileStat);
		fill_user_group_info(info, fileStat);
		info->size = fileStat.st_size;
		fill_date_info(info, fileStat);
	}
	info->type = S_ISDIR(fileStat.st_mode);
	if (S_ISLNK(fileStat.st_mode) == 1)
		info->type = 2;
}
