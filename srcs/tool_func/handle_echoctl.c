/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echoctl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:22:44 by mgo               #+#    #+#             */
/*   Updated: 2022/04/26 12:22:46 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>

void	on_echoctl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag = attr.c_lflag | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	tcgetattr(STDOUT_FILENO, &attr);
}

void	off_echoctl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag = attr.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	tcgetattr(STDOUT_FILENO, &attr);
}
