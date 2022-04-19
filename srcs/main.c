/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:20:31 by mgo               #+#    #+#             */
/*   Updated: 2022/04/15 20:22:02 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_ast *cmd)
{
	// set absolute
	//execve
	return (1);
}

# include <fcntl.h> // O_RDONLY
int	set_redir_and_execute_cmd(t_ast *redir)
{
	int	fd;

	if (ft_strncmp(redir->token, "<", 2))
	{
		fd = open(redir->left->token, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (ft_strncmp(redir->token, "<<", 3))
	{
		fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		// todo: get inputs
		close(fd);
		fd = open(".heredoc", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (ft_strncmp(redir->token, ">", 2))
	{
		fd = open(redir->left->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_strncmp(redir->token, ">>", 3))
	{
		fd = open(redir->left->token, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	/*
	else if (redir->type == TOK_TYPE_CMD)
		execute_cmd(redir); // to remove?
	*/
	if (redir->right->type == TOK_TYPE_REDIR)
		set_redir_and_execute_cmd(redir->right);
	else if (redir->right->type == TOK_TYPE_CMD)
		execute_cmd(redir->right);
	return (1);
}

int	execute_left(t_ast *left, int pipe_here[2], int pipe_above[2])
{
	// fork and save pid(linked list)

	// set pipe
	dup2(pipe_here[READ], STDIN_FILENO);
	close(pipe_here[READ]);
	if (pipe_above != NULL)
	{
		dup2(pipe_above[WRITE], STDOUT_FILENO);
		close(pipe_above[WRITE]);
	}
	if (left->type == TOK_TYPE_REDIR)
		set_redir_and_execute_cmd(left);
	else if (left->type == TOK_TYPE_CMD)
		execute_cmd(left);
	return (1);
}

int	execute_right(t_ast *right, int pipe_here[2])
{
	// fork and save pid(linked list?)

	// set pipe
	close(pipe_here[READ]);
	dup2(pipe_here[WRITE], STDOUT_FILENO);
	close(pipe_here[WRITE]);

	if (right->type == TOK_TYPE_REDIR)
		set_redir_and_execute_cmd(right);
	else if (right->type == TOK_TYPE_CMD)
		execute_cmd(right);
	return (1);
}

int	execute_pipe(t_ast *root, int pipe_above[2])
{
	int	pipe_here[2];

	pipe(pipe_here); // considering...
	if (root->right->type == TOK_TYPE_PIPE)
		execute_pipe(root->right, pipe_here);
	else
		execute_right(root->right, pipe_here);
	close(pipe_here[WRITE]);
	execute_left(root->left, pipe_here, pipe_above);
	close(pipe_here[READ]);
	return (1);
}

/*
	< infile cmd1 | cmd2 | cmd3 > outfile

				cmd1
			<
				infile
		|
			cmd2
	|
			cmd3
		>
			outfile

	root 파이프(마지막이자 두번째 파이프)에서 첫번째 파이프 찾으러 오른쪽 트리로 파이프 더 안 나올 때 까지 내려감
	첫번째 파이프 찾아서 pipe 설정
	cmd1 부분 fork하고 redirection 만나는 순서대로 설정(결국 마지막 redirection으로 설정됨), 명령어 실행
	두번째 파이프에서 가져온 pipe 설정하고 첫번째 파이프 왼쪽에 있는 cmd2 부분 fork하고 위와 같이 진행
	두번째 파이프에서 왼쪽 명령어 cmd3 부분 fork하고 수행
	done

	trip ast with saving data
*/
int	execute_ast(t_ast *root)
{
	int	fd_saver[2];

	fd_saver[0] = dup(STDIN_FILENO);
	fd_saver[1] = dup(STDOUT_FILENO);

	if (root->type == TOK_TYPE_PIPE)
		execute_pipe(root, NULL);
	else if (root->type == TOK_TYPE_REDIR)
		set_redir_and_execute_cmd(root);
	else if (root->type == TOK_TYPE_CMD)
		execute_cmd(root);
	
	// come back to original
	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);
	return (1);
}

int	main(void)
{
	//t_tok_list	*lst;
	//info
	t_ast		*root;

	root = NULL;
	printf("mgoshell: Hello world!\n");

	//set_ast_test();

	execute_ast(root);

	return (0);
}
