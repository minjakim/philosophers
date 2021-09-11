/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:28:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 17:10:36 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int
	dining(t_table *const table, t_thread *const thread, int i)
{
	if (50 < table->option.number_of_philos)
		table->option.offset *= 8;
	if (500 < table->option.number_of_philos)
		table->option.offset *= 8;
	if (1000 < table->option.number_of_philos)
		table->option.offset *= 2;
	table->board.timestamp = get_time();
	while (++i < table->option.number_of_philos)
	{
		pthread_mutex_init(&table->seats[i].right.fork, NULL);
		if (pthread_create(&thread[i], NULL, routine, &table->seats[i])
			&& write(2, ERR_PTHREAD, sizeof(ERR_PTHREAD) - 1))
			return (0);
		pthread_detach(thread[i]);
	}
	return (SUCCESS);
}

void
	set_the_table(t_table *const table, int i)
{
	t_seat *const	seats = table->seats;

	while (++i <= table->option.number_of_philos)
	{
		seats[i - 1].table = table;
		seats[i - 1].number.prev = i - 1;
		seats[i - 1].number.here = i;
		seats[i - 1].number.next = i + 1;
		seats[i - 1].right.authorized_key = seats[i - 1].number.here;
		if (i == table->option.number_of_philos)
		{
			seats[i - 1].left = &seats[0].right;
			seats[i - 1].number.next = 1;
			if (table->option.number_of_philos & 1)
				seats[i - 1].right.authorized_key = i;
		}
		else
			seats[i - 1].left = &seats[i].right;
		if (!(i & 1))
			seats[i - 1].right.authorized_key = seats[i - 1].number.prev;
	}
	seats[0].number.prev = table->option.number_of_philos;
}
