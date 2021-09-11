/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:50:44 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 14:50:21 by minjakim         ###   ########.fr       */
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

# define HAS_TAKEN_A_RIGHT_FORK	" has taken a \033[36mright\033[0m fork\n"
# define HAS_TAKEN_A_LEFT__FORK	" has taken a \033[33mleft\033[0m  fork\n"
# define IS_EATING				" is  \033[32meating\033[0m\n"
# define IS_SLEEPING			" is  \033[34msleeping\033[0m\n"
# define IS_THINKING			" is  \033[35mthingking\033[0m\n"
# define IS_ALIVED				" is  					alived"
# define IS_DIED				" is  \033[31mdied\033[0m\n"

# define ERR_MALLOC		"\033[31merror:\033[0m malloc failed\n"
# define ERR_PTHREAD	"\033[31merror:\033[0m pthread_create failed\n"
# define ERR_EMPTY		"\033[31merror:\033[0m some arguments are empty\n"
# define ERR_FORMAT		"\033[31merror:\033[0m wrong format\n"
# define ERR_NOGEUST	"\033[31merror:\033[0m there is no philosopher\n"
# define ERR_TOOMANY	"\033[31merror:\033[0m there are too many philosophers\n"

# define U2147483648			0x80000000
# define DONE					0
# define SUCCESS				1
# define FAIL					0

# define ERROR					-1
# define LOOP					1

#endif
