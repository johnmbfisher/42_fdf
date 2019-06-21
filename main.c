/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:52:32 by mbutt             #+#    #+#             */
/*   Updated: 2019/06/21 15:06:08 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** ft_read does the following:
** 1. If the file specified by user is a folder, returns an error message.
** 2. If the file exists, reads and stores the file in a temporary placeholder
** 3. Counts the number of words stored in temporary placeholder.
** 4. Stores from temporary placeholder to a sturct.
** 5. 
*/

void ft_read(int fd, char *argv)
{
	int ft_return;
	int wordcount;
	int temp_wordcount;
	char *one_line;

	ft_zero(&temp_wordcount, &wordcount, &ft_return, &ft_return);
	ft_return = get_next_line(fd, &one_line);
	if(ft_return == -1)
		ft_exit(argv);
	if(ft_return == 1)
	{
		wordcount = ft_wordcount(one_line, ' ');
		printf("|%d||%d|line:|%s|\n", ft_return, wordcount, one_line);
		free(one_line);
	}
	while((ft_return= get_next_line(fd, &one_line) == 1))
	{
		temp_wordcount = ft_wordcount(one_line, ' ');
		if(temp_wordcount != wordcount)
			ft_exit_success("Error: Invalid file. Exiting program.\n");
		printf("|%d||%d|line:|%s|\n", ft_return, wordcount, one_line);
		free(one_line);
	}
	printf("%d\n", ft_return);
}

int main(int argc, char **argv)
{
	int fd;

	if(argc == 1)
		ft_usage("Usage: ./fdf resources/test_maps\n");
	fd = open(argv[1], O_RDONLY);
	if(fd  == -1)
	{
		ft_exit("Main error 1");
//		ft_exit(argv[1]);
	}
	ft_read(fd, argv[1]);
	close(fd);
	return(0);
}
