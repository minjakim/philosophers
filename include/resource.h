/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:50:44 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 10:23:47 by minjakim         ###   ########.fr       */
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

# define HAS_TAKEN_A_RIGHT_FORK	" has taken a right fork\n"
# define HAS_TAKEN_A_LEFT__FORK	" has taken a left  fork\n"
# define IS_EATING				" is  eating\n"
# define IS_SLEEPING			" is  sleeping\n"
# define IS_THINKING			" is  thinking\n"
# define IS_ALIVED				" is  alived"
# define IS_DIED				" is  died\n"

# define ERR_MALLOC				"Error! malloc failed\n"
# define ERR_PTHREAD			"Error! pthread_create failed\n"
# define ERR_EMPTY				"Error! some arguments are empty.\n"
# define ERR_FORMAT				"Error! wrong format.\n"
# define ERR_RANGE				"Error! outside the range.\n"

# define U2147483648			0x80000000
# define DONE					0
# define SUCCESS				1
# define FAIL					0

# define ERROR					-1
# define LOOP					1

#endif
