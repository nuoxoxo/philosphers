/* ************************************************************************** */
/*                                                                            */
/*                                                        ...      :::::::    */
/*   _                                                  ...      :::    :::   */
/*                                                    ... ...         :::     */
/*   By: nuo <marvin@42.fr>                         ...  ...       :::        */
/*                                                ...........   :::           */
/*   Created: ____/__/__ __:__:__ by nuo               ...    :::             */
/*   Updated: ____/__/__ __:__:__ by nuo              ...   ::::::::.fi       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_philo *philo, t_table *table)
{
	int		i;

	if (! philo || ! table)
		ft_clean_exit(philo, table, 1);
	table->t0 = ft_current_ms();
	if (pthread_mutex_init(& table->mtx_death, NULL))
		ft_clean_exit(philo, table, 1);
	if (pthread_mutex_init(& table->mtx_print, NULL))
		ft_clean_exit(philo, table, 1);
	if (pthread_mutex_init(& table->mtx_meals, NULL))
		ft_clean_exit(philo, table, 1);
	if (pthread_mutex_init(& table->mtx_close, NULL))
		ft_clean_exit(philo, table, 1);
	i = -1;
	while (++i < table->total_philo)
		if (pthread_mutex_init (& philo[i].chops[i], NULL))
			ft_clean_exit(philo, table, 1);
}

void	init_routine(t_philo *p, t_table *t, pthread_t *threads)
{
	int		i;

	i = -1;
	while (++i < t->total_philo)
	{
		if (pthread_create(& threads[i], NULL, philo_routine, & p[i]))
		{
			while (i--)
				pthread_join(threads[i], NULL);
			free(threads);
			ft_clean_exit(p, t, 1);
		}
	}
}

void	*philo_routine(void *philo)
{
	t_philo				*p;

	p = (t_philo *) philo;
	while (1)
	{
		if (p->table->meals > 0 && everyone_ate_enough(p))
			break ;
		if (someone_is_dead(p))
			break ;
		if (! philo_eat(p))
			break ;
		if (! philo_sleep_and_think(p))
			break ;
	}
	return (NULL);
}

/******		needed by hierarchy solution	******/

/*
void	*philo_routine(void *philo)
{
	t_philo				*p;

	if (p->id % 2 == 0)
	{
		philo_print_task(p, "is thinking");
		philo_pass_time(p, p->table->time_to_eat);
	}
	p = (t_philo *) philo;
	while (1)
	{
		if (p->table->meals > 0 && everyone_ate_enough(p))
			break ;
		if (someone_is_dead(p))
			break ;
		if (! philo_eat(p))
			break ;
		if (! philo_sleep_and_think(p))
			break ;
	}
	return (NULL);
}
*/

void	main_thread(t_philo *philo, t_table *table)
{
	long long	last_timestamp;
	int			i;

	i = 0;
	while (1)
	{
		if (count_if_all_ate_enough(philo, table))
		{
			set_flag_of_close(table);
			break ;
		}
		pthread_mutex_lock(&table->mtx_meals);
		last_timestamp = philo[i].last_meal;
		pthread_mutex_unlock(& table->mtx_meals);
		if (ft_current_ms() > table->time_to_die + last_timestamp)
		{
			set_flag_of_death(table);
			philo_log(& philo[i], "died");
			break ;
		}
		i = (i + 1) % table->total_philo;
		usleep (100);
	}
}

void	philo_log(t_philo *p, char *msg)
{
	long long	idle_time;

	pthread_mutex_lock(& p->table->mtx_print);
	idle_time = ft_current_ms() - p->table->t0;
	if (*msg == 'd')
		printf("%lld %i %s\n", idle_time, p->id, msg);
	else if (!someone_is_dead(p) && !everyone_ate_enough(p))
		printf("%lld %i %s\n", idle_time, p->id, msg);
	pthread_mutex_unlock(& p->table->mtx_print);
}

/*		deprecated: old task printers		*/

/*
void	philo_log(t_philo *p, char *msg)
{
	long long				idle_time;

	pthread_mutex_lock(& p->table->mtx_print);
	idle_time = ft_current_ms() - p->table->t0;
	if (*msg == 'd')
		printf("%lld\t philo no.%i %s\n", idle_time, p->id, msg);
	else if (*msg == 'e')
		printf("%lld\t %s\n", idle_time, msg);
	else if (!someone_is_dead(p) && !everyone_ate_enough(p))
		printf("%lld\t philo no.%i %s\n", idle_time, p->id, msg);
	pthread_mutex_unlock(& p->table->mtx_print);
}
*/

/* deprecated: pick-up printer */

/*
void	philo_print_pick_up(t_philo *p, int left, int right, int choice)
{
	if (choice == left)
		philo_log(p, "has taken the chopstick one the left");
	else if (choice == right)
		philo_log(p, "has taken the chopstick one the right");
}
*/

/* deprecated: put-down printer */

/*
void	philo_print_put_down(t_philo *p, int left, int right, int choice)
{
	if (choice == left)
		philo_log(p, "has put down the chopstick one the left");
	else if (choice == right)
		philo_log(p, "has put down the chopstick one the right");
}
*/
