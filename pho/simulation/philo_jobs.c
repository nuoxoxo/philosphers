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

int	philo_eat(t_philo *philo)
{
	if (! philo_pick_up(philo))
		return (0);
	pthread_mutex_lock(& philo->table->mtx_meals);
	philo->last_meal = ft_current_ms();
	if (philo->last_meal == -1)
		return (0);
	philo->eaten += 1;
	pthread_mutex_unlock(& philo->table->mtx_meals);
	if (everyone_ate_enough(philo))
	{
		philo_pass_time(philo, philo->table->time_to_eat);
		philo_put_down(philo);
		return (0);
	}
	philo_pass_time(philo, philo->table->time_to_eat);
	philo_put_down(philo);
	return (1);
}

/*
 *
 *	2 anti-deadlock strategies:
 *
 *
 *	(1/2) Odd & Even Philos Do Different Things
 *
 *
 *	Even-digit philos get their chopsticks in an order they share, 	
 *	while Odd-digit philos get in a reversed order of the even ones. 
 *
 *	so that there won't be "circular wait"
 *
 *
 */

//		Pick up (odd-even strategy)

int	philo_pick_up(t_philo *philo)
{
	int		right;
	int		left;

	right = philo->id % philo->table->total_philo;
	left = philo->id - 1;
	if (left % 2)
	{
		pthread_mutex_lock(& philo->chops[left]);
		philo_log(philo, "has taken a fork");
		pthread_mutex_lock(& philo->chops[right]);
		philo_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(& philo->chops[right]);
		philo_log(philo, "has taken a fork");
		if (left == right)
		{
			return (pthread_mutex_unlock(& philo->chops[right]), 0);
		}
		pthread_mutex_lock(& philo->chops[left]);
		philo_log(philo, "has taken a fork");
	}
	philo_log(philo, "is eating");
	return (1);
}

//		Put down (Odd-even strategy)

int	philo_put_down(t_philo *philo)
{
	int		right;
	int		left;

	right = philo->id % philo->table->total_philo;
	left = philo->id - 1;
	if (left % 2)
	{
		pthread_mutex_unlock(& philo->chops[right]);
		pthread_mutex_unlock(& philo->chops[left]);
	}
	else
	{
		pthread_mutex_unlock(& philo->chops[left]);
		pthread_mutex_unlock(& philo->chops[right]);
	}
	return (1);
}

/*
 *
 *	2 anti-deadlock strategies:
 *
 *
 *	(2/2) Chopstick Hierarchy 
 *
 *
 *	Priority or hierarchy is given to each chopstick at each Pick-UP or Put-DOWN.
 *
 *	In this route, each philosopher must pick up the lowest 
 *	numbered chopstick first.
 *	
 *	Or the highest first - it doesn’t matter as long as we’re consistent. 
 *
 */

//		Pick up (Hierarchy strategy)

/*
int	philo_pick_up(t_philo *philo)
{
	int					choice;
	int					right;
	int					left;

	right = philo->id % philo->table->total_philo;
	left = philo->id - 1;
	choice = ft_minmax(left, right, 0);
	pthread_mutex_lock(& philo->chops[choice]);
	philo_log(philo, "has taken a fork");
	if (left == right)
	{
		pthread_mutex_unlock(& philo->chops[choice]);
		return (0);
	}
	choice = ft_minmax(left, right, 1);
	pthread_mutex_lock(& philo->chops[choice]);
	philo_log(philo, "has taken a fork");
	philo_log(philo, "is eating");
	return (1);
}
*/

//		Put down (Hierarchy strategy)

/*
int	philo_put_down(t_philo *philo)
{
	int					choice;
	int					right;
	int					left;

	right = philo->id % philo->table->total_philo;
	left = philo->id - 1;
	choice = ft_minmax(left, right, 1);
	pthread_mutex_unlock(& philo->chops[choice]);
	choice = ft_minmax(left, right, 0);
	pthread_mutex_unlock(& philo->chops[choice]);
	return (1);
}
*/

int	philo_sleep_and_think(t_philo *p)
{
	philo_log(p, "is sleeping");
	philo_pass_time(p, p->table->time_to_sleep);
	philo_log(p, "is thinking");
	if (p->table->time_to_eat > p->table->time_to_sleep)
	{
		philo_pass_time(p, p->table->time_to_eat
			- p->table->time_to_sleep + 1);
	}
	else
	{
		philo_pass_time(p, 1);
	}
	return (1);
}

void	philo_pass_time(t_philo *philo, long long n)
{
	long long	idle_time;
	long long	start;

	start = ft_current_ms();
	while (!someone_is_dead(philo) && !everyone_ate_enough(philo))
	{
		idle_time = ft_current_ms() - start;
		if (idle_time > n)
			break ;
		usleep(100);
	}
}
