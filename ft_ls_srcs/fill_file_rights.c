/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_file_rights.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 07:38:42 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 07:40:24 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_type_info_rights(t_info *info, struct stat fileStat)
{
	if	(fileStat.st_mode & S_IFIFO)
		info->rights[0] = 'p';
	if (fileStat.st_mode & S_IFCHR)
		info->rights[0] = 'c';
	if (fileStat.st_mode & S_IFDIR)
		info->rights[0] = 'd';
	if (fileStat.st_mode & S_IFREG)
		info->rights[0] = '-';
	if (fileStat.st_mode & S_IFCHR && fileStat.st_mode & S_IFDIR)
		info->rights[0] = 'b';
	if (fileStat.st_mode & S_IFREG && fileStat.st_mode & S_IFCHR)
		info->rights[0] = 'l';
	if (fileStat.st_mode & S_IFREG && fileStat.st_mode & S_IFDIR)
		info->rights[0] = 's';
	info->rights[10] = ' ';
	info->rights[11] = '\0';
	return (info->rights);
}

void		fill_file_rights(t_info *info, struct stat fileStat)
{
	if (!(info->rights = (char*)malloc(sizeof(char) * 12)))
		return ;
	get_type_info_rights(info, fileStat);
	info->rights[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
	info->rights[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	info->rights[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	if (info->rights[3] != 'x')
		info->rights[3] = (fileStat.st_mode & 04000) ? 'S' : info->rights[3];
	else
		info->rights[3] = (fileStat.st_mode & 04000) ? 's' : info->rights[3];
	info->rights[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	info->rights[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	info->rights[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	if (info->rights[6] != 'x')
		info->rights[6] = (fileStat.st_mode & 02000) ? 'S' : info->rights[6];
	else
		info->rights[6] = (fileStat.st_mode & 02000) ? 's' : info->rights[6];
	info->rights[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	info->rights[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	info->rights[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
	if (info->rights[9] != 'x')
		info->rights[9] = (fileStat.st_mode & 01000) ? 'T' : info->rights[9];
	else
		info->rights[9] = (fileStat.st_mode & 01000) ? 't' : info->rights[9];
}
