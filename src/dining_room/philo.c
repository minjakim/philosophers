/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/09 11:36:13 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

inline static uint64_t
	punching(void)
{
	t_timeval	now;
	uint64_t	buffer;

	gettimeofday(&now, NULL);
	buffer = (now.tv_sec << 10) - (now.tv_sec << 4) - (now.tv_sec << 3);
	return ((buffer << 10) - (buffer << 4) - (buffer << 3) + (now.tv_usec));
}

inline static uint64_t
	punch_clock(const uint64_t start, const uint32_t given_time)
{
	const uint64_t now = punching() - start;

	return (0);
}

void
	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

}


//void
//	thinking(const uint64_t time)
//{

//}

//void
//	sleeping(const uint64_t time)
//{

//}

//void
//	eating(const uint64_t time)
//{

//}
