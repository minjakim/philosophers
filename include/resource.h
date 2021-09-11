/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:50:44 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 16:59:18 by minjakim         ###   ########.fr       */
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

# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE		"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN		"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"

# define MS				"\x1b[33mms\x1b[0m"
# define RIGHT_FORK		" has taken a right fork\n"
# define LEFT__FORK		" \x1b[4mhas taken a left  fork\x1b[0m\n"
# define IS_EATING		" is  \x1b[32meating\x1b[0m\n"
# define IS_SLEEPING	" is  \x1b[2msleeping\x1b[0m\n"
# define IS_THINKING	" is  \x1b[36mthingking\x1b[0m\n"
# define IS_ALIVED		" is  "
# define IS_DIED		" is  \x1b[31mdied\x1b[0m\n"

# define ERR_MALLOC		"\x1b[31merror:\x1b[0m malloc failed\n"
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
# define LOOP			1

#endif
