/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:33:07 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 15:20:46 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

static int
	initialize(t_table *const table, t_thread **thread)
{
	table->seats = malloc(sizeof(t_seat) * table->option.number_of_philos);
	if (table->seats == NULL && write(2, ERR_MALLOC, sizeof(ERR_MALLOC) - 1))
		return (FAIL);
	*thread = malloc(sizeof(t_thread) * table->option.number_of_philos);
	if (thread == NULL && write(2, ERR_MALLOC, sizeof(ERR_MALLOC) - 1))
		return (FAIL);
	return (SUCCESS);
}

static inline unsigned char
	convert(unsigned char *const a, const char *const str)
{
	return (*a = *str - '0');
}

static uint32_t
	checktoi(const char *str)
{
	int				digit;
	unsigned char	a;
	long			i;

	while (*str == '0')
		if (*(++str) == '\0')
			return (0);
	i = 0;
	digit = 0;
	while (*str && (convert(&a, str) < 10 && ++digit < 11))
		(i = (i << 1) + (i << 3) + a) && str++;
	if (*str && write(2, ERR_FORMAT, sizeof(ERR_FORMAT)))
		return (ERROR);
	if (((10 < digit) || (INT32_MAX < i))
		&& write(2, ERR_FORMAT, sizeof(ERR_FORMAT)))
		return (ERROR);
	return (i);
}

static int
	parse_args(int argc, char **const argv, t_table *const table)
{
	table->option.number_of_times_to_eat = 0;
	while (--argc > -1)
	{
		if (*argv[argc] == '\0' && write(2, ERR_EMPTY, sizeof(ERR_EMPTY) - 1))
			return (FAIL);
		table->option.options[argc] = checktoi(argv[argc]);
		if (table->option.options[argc] == ERROR)
			return (FAIL);
	}
	if (table->option.number_of_philos == 0
		&& write(2, ERR_NOGEUST, sizeof(ERR_NOGEUST) - 1))
		return (FAIL);
	if (table->option.number_of_philos > 3000
		&& write(2, ERR_TOOMANY, sizeof(ERR_TOOMANY) - 1))
		return (FAIL);
	table->option.offset = 32;
	table->option.time_to_die *= 1000;
	table->option.time_to_eat *= 1000;
	table->option.time_to_sleep *= 1000;
	printf("%d %d %d %d %d\n", table->option.number_of_philos, table->option.time_to_die, table->option.time_to_eat, table->option.time_to_sleep, table->option.number_of_times_to_eat);
	return (SUCCESS);
}

int
	main(int argc, char **argv)
{
	t_thread	*thread;
	t_table		table;

	if (--argc == 0 || argc < 4 || 5 < argc
		|| !parse_args(argc, ++argv, &table)
		|| !initialize(&table, &thread))
		return (0);
	set_the_table(&table, 0);
	if (!dining(&table, thread, -1))
		return (0);
	while (LOOP)
	{
		if (table.board.dead)
		{
			printf("%llums %d is  died(%llu)\n", (table.board.time_of_death - table.board.timestamp) / 1000, table.board.dead, get_time() - table.board.time_of_death);
			break ;
		}
		else
			usleep(512);
	}
	return (0);
}
