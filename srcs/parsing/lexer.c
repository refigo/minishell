/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:03 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:42:04 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>

static int	check_special(t_tok *iter, bool *flag)
{
	if (iter->token[0] == '|')
	{
		iter->type = TOK_TYPE_PIPE;
		ft_bzero(flag, sizeof(bool) * 2);
		return (true);
	}
	else if (ft_strchr("<>", iter->token[0]))
	{
		iter->type = TOK_TYPE_REDIR;
		flag[FLAG_REDIR] = true;
		return (true);
	}
	return (false);
}

static void	check_normal(t_tok *iter, bool *flag)
{
	if (flag[FLAG_CMD] || flag[FLAG_REDIR])
	{
		if (flag[FLAG_REDIR])
		{
			iter->type = TOK_TYPE_FILE;
			flag[FLAG_REDIR] = false;
		}
		else
		{
			iter->type = TOK_TYPE_ARG;
		}
	}
	else
	{
		iter->type = TOK_TYPE_CMD;
		flag[FLAG_CMD] = true;
	}
}

/*
	특수문자 관련
	1. minishell은 모든 특수문자를 처리하길 요구하지 않음
	2. 특수문자는 ', ", |, $, <, >, <<, >>만 요구함
	3. 특수문자 $은 토근화전에 처리하였음

	이스케이프 처리
	1. 이스케이프 구문은 이스케이프 문자를 제거한다.
	2. 큰 따옴표 안과 밖는 다른 이스케이프 구문을 가지고 있다.
	3. 문자열임을 표시하는 따옴표는 제거한다.

	@ 몇몇 코드를 보는데 특수문자를 단순 문자열로 처리한 경우도 보임
	@ 과제상 나는 처리해 줘야 한다고 해석함

	렉서 처리 과정
	1. 토큰 의미 부여
	2. 특수문자로써 ", ' 제거
	3. 구문 검사
	4. 이스케이프 구문의 이스케이프 문자 제거
	5. arg 압축

	토큰 의미부여과정
	0. 커멘드 플래그, 리디렉션 플래그 선언.
	1. 해당 토큰이 리디렉션인지 파이프인지 확인.
	2. 해당 토큰이 리디렉션이면 해당 타입으로 지정후 리디렉션 플래그 on.
	3. 해당 토큰이 파이프이면 해당 타입으로 지정후 모든 플래그 off.
	4. (1.)번이 아니면서 커멘드 플래그가 꺼져있으면 커멘드 타입으로 지정하고 플래그 on
	5. (1.)번이 아니면서 커멘드 플래그가 켜져있으면 매개변수 타입으로 지정.
	5. (1.)번이 아니면서 리디렉션 프래그가 켜져있으면 파일 타입으로 지정하고 플래그 off, 두 플래그 중 리디렉션을 더 우선시 한다.

	따옴표, 이스케이프 문자 제거 과정
	1. 이스케이프로 인하여 의미가 지워진 따옴표를 제외한 모든 따옴표 제거.
	2. 모든 이스케이프 문자 제거.
*/

int	lexer(t_tok_list *tok_list)
{
	bool	flag[2];
	bool	type;
	int		cnt;
	t_tok	*it;

	ft_bzero(flag, sizeof(bool) * 2);
	cnt = 0;
	it = tok_list->head;
	while (cnt < tok_list->size)
	{
		type = check_special(it, flag);
		if (type == false)
			check_normal(it, flag);
		remove_quotes(it);
		it = it->next;
		++cnt;
	}
	if (check_syntax(tok_list))
	{
		ft_putendl_fd("Syntax Error", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
