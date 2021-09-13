/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:28:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 13:12:02 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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

static inline void
	check_the_status(const t_table *const table, int i)
{
	const t_option	option = table->option;
	pid_t			pid;
	int				status;
	int				j;

	while (++i < option.number_of_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (status != 0)
		{
			while (++j < table->option.number_of_philos)
				if (pid == table->seats[j] && printf("%llu"MS"%d"DIED, \
							(punch_clock() - table->timestamp) / 1000, j + 1))
					break ;
			j = -1;
			while (++j < table->option.number_of_philos)
				kill(table->seats[j], SIGKILL);
		}
	}
}

static void
	set_the_table(t_table *const table)
{
	int	n;

	n = table->option.number_of_philos >> 1;
	table->timestamp = punch_clock();
	table->number = 0;
	table->voucher = table->option.number_of_times_to_eat;
	sem_unlink(SEM_RIGHT);
	table->right = sem_open(SEM_RIGHT, O_CREAT, 0644, n);
	sem_unlink(SEM_LEFT);
	if (table->option.number_of_philos & 1)
		++n;
	table->left = sem_open(SEM_LEFT, O_CREAT, 0644, n);
}

static void
	philosopher(t_table *const table)
{
	const uint64_t	time_to_die = table->option.time_to_die;
	t_thread	thread;

	if (pthread_create(&thread, NULL, routine, table)
		&& write(2, ERR_PTHREAD, sizeof(ERR_PTHREAD) - 1))
		return ;
	pthread_detach(thread);
	while (LOOP)
	{
		if ((punch_clock() - table->timestamp) > time_to_die)
			exit(1);
		else
			usleep(512);
	}
}

int
	dining(t_table *const table, t_thread *const thread)
{
	int	i;

	i = -1;
	(void)thread;
	set_the_table(table);
	while (++i < table->option.number_of_philos)
	{
		++table->number;
		table->seats[i] = fork();
		if (table->seats[i] < 0 && write(2, ERR_FORK, sizeof(ERR_FORK)))
			exit(1);
		else if (table->seats[i] == 0)
		{
			philosopher(table);
			exit(1);
		}
	}
	check_the_status(table, -1);
	return (0);
}
#endif
