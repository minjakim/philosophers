/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:28:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 07:53:10 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#if BONUS == 1
static inline uint64_t
	punch_clock(void)
{
	t_timeval	tick;
	uint64_t	buffer;

	if (gettimeofday(&tick, NULL) == ERROR)
		exit(1);
	buffer = (tick.tv_sec << 10) - (tick.tv_sec << 4) - (tick.tv_sec << 3);
	return ((buffer << 10) - (buffer << 4) - (buffer << 3) + (tick.tv_usec));
}

static inline int
	check_the_status(const t_table *const table)
{
	const uint64_t	standard = table->timestamp;
	const t_option	option = table->option;
	int				i;

	i = -1;
	while (++i < option.number_of_philos)
	{
		if ((punch_clock() - table->seats[i].timestamp) > option.time_to_die)
		{
			printf("%llu"MS"%d"DIED, (punch_clock() - standard) / 1000, i + 1);
			return (i);
		}
	}
	return (option.number_of_philos);
}

static inline void
	check_the_voucher(const t_table *const table)
{
	const uint64_t	standard = table->timestamp;
	const t_option	option = table->option;
	int32_t			no_voucher;
	int32_t			i;

	while (check_the_status(table) == table->option.number_of_philos)
	{
		usleep(512);
		i = -1;
		no_voucher = 0;
		while (++i < option.number_of_philos)
			if (table->seats[i].voucher == 0)
				++no_voucher;
		if (no_voucher == option.number_of_philos)
			break ;
	}
}

static void
	set_the_table(t_table *const table, int i)
{
	t_seat *const	seats = table->seats;

	while (++i <= table->option.number_of_philos)
	{
		seats[i - 1].table = table;
		seats[i - 1].number = i;
		seats[i - 1].voucher = table->option.number_of_times_to_eat;
	}
	sem_unlink(SEM_NAME);
	table->forks = sem_open(SEM_NAME, O_CREAT, 0644, i);
}

int
	dining(t_table *const table, t_thread *const thread, int i)
{
	(void)thread;
	set_the_table(table, 0);
	table->timestamp = punch_clock();
	while (++i < table->option.number_of_philos)
	{
		table->seats[i].timestamp = table->timestamp;
		table->seats[i].pid = fork();
	}
	return (0);
}
#endif
