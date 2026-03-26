/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:47:03 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 21:37:01 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_full_list	newlst;
	void		*temp;

	newlst = (t_full_list){0};
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		newlst.tempnode = ft_lstnew(temp);
		if (!newlst.tempnode)
		{
			del(temp);
			ft_lstclear(&newlst.start, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst.end, newlst.tempnode);
		if (!newlst.start)
			newlst.start = newlst.end;
		newlst.len++;
		if (newlst.len > 1)
			newlst.end = newlst.end->next;
		lst = lst->next;
	}
	return (newlst.start);
}
