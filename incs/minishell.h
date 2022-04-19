/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:21:22 by mgo               #+#    #+#             */
/*   Updated: 2022/04/15 20:24:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include "token.h"
# include "ast.h"
# include "exec.h"


// mgo's header contents
enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_pipe
{
	READ,
	WRITE
};




#endif
