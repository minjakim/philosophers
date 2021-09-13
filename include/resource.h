/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:49:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 15:33:04 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_H
# define RESOURCE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

# ifndef BONUS
#  define BONUS 0
# endif

# if BONUS == 1
#  include <semaphore.h>
#  include <signal.h>
#  define SEM_NAME		"philo"
#  define SEM_RIGHT		"right"
#  define SEM_LEFT		"left"
# endif

# define MS				"\x1b[33mms\x1b[0m "
# define FORKS			" \x1b[4mhas taken a forks\x1b[0m\n"
# define RIGHT			" has taken a right fork\n"
# define LEFT			" \x1b[4mhas taken a left  fork\x1b[0m\n"
# define EAT			" is  \x1b[32meating\x1b[0m\n"
# define SLEEP			" is  \x1b[2msleeping\x1b[0m\n"
# define THINK			" is  \x1b[36mthingking\x1b[0m\n"
# define DIED			" is  \x1b[31mdied\x1b[0m\n"

# define ERR_MALLOC		"\x1b[31merror:\x1b[0m malloc failed\n"
# define ERR_FORK		"\x1b[31merror:\x1b[0m fork failed\n"
# define ERR_SEM		"\x1b[31merror:\x1b[0m semaphore failed\n"
# define ERR_MUTEX		"\x1b[31merror:\x1b[0m mutex failed\n"
# define ERR_PTHREAD	"\x1b[31merror:\x1b[0m pthread_create failed\n"
# define ERR_EMPTY		"\x1b[31merror:\x1b[0m some arguments are empty\n"
# define ERR_FORMAT		"\x1b[31merror:\x1b[0m wrong format\n"
# define ERR_NOGEUST	"\x1b[31merror:\x1b[0m there is no philosopher\n"
# define ERR_TOOMANY	"\x1b[31merror:\x1b[0m there are too many philosophers\n"

# define U2147483648	0x80000000
# define DONE			0
# define SUCCESS		1
# define FAIL			0

# define ERROR			-1
# define UNLIMIT		-1
# define LOOP			1

#endif
