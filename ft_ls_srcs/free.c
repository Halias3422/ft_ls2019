/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 08:53:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 15:54:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_info *lst, t_args *args)
{
	t_info	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->is_error == 1)
			free(lst->file);
		if ((is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g",
		args->arg, 0) > 0 || is_contained_in("o", args->arg, 0) > 0) &&
		args->nb_files > 0)
		{
			free(lst->group);
			free(lst->user);
		}
		free(lst->date);
		free(lst);
		lst = tmp;
	}
	free(args->arg);
	lst = NULL;
}

void		free_one_list(t_info *lst, t_args *args)
{
	if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in(
	"o", args->arg, 0) > 0 || is_contained_in("g", args->arg, 0) > 0)
	{
		free(lst->user);
		free(lst->group);
		free(lst->rights);
	}
	free(lst->file);
	free(lst->date);
	free(lst->path);
	free(lst);
}
