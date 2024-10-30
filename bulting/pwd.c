/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:26:56 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/28 09:10:47 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_builting(t_env *l)
{
	char BUFFER[1024];
	char *path;

	path = getcwd(BUFFER, sizeof(BUFFER));
	if (path == NULL)
		path = extract_value(l, "PWD");
	get_exit(0, 0);
	printf("%s\n", path);
}