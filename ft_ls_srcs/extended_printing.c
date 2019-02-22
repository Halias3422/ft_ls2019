/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extended_printing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/22 09:21:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 13:41:42 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_spaces(size_t nb1, size_t nb2, int len)
{
	len = nb1 - nb2;
	while (len-- > 0)
		ft_printf(" ");
}

void			printing_link(t_info *info)
{
	int			i;
	ssize_t		len;
	char		*link;

	i = 0;
	if (!(link = (char*)malloc(sizeof(char) * 256)))
		exit (-1);
	len = readlink(info->path, link, 256);
	link[len - 1] = '\0';
	ft_printf(" -> %s", link);
}

void			extended_printing_root(t_info *info, t_args *args, int len)
{
	ft_printf("%s", info->rights);
	print_spaces(args->biggest_inodes + 1, check_num_length(info->inodes), len);
	ft_printf("%d", info->inodes);
	if (is_contained_in("g", args->arg, 0) <= 0)
	{
	ft_printf("%s", info->user);
	print_spaces(args->biggest_usr, ft_strlen(info->user), len);

	}
	ft_printf("%s", info->group);
	print_spaces(args->biggest_grp, ft_strlen(info->group), len);
	print_spaces(args->biggest_size, check_num_length(info->size), len);
	ft_printf("%d %s %s", info->size, info->date, info->file);
	if (info->rights[0] == 'l')
		printing_link(info);
	ft_printf("\n");
}
