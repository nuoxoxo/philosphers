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

#ifndef PHILO_H
# define PHILO_H

# include "sys/time.h"
# include "pthread.h"
# include "unistd.h" /* sleep . usleep */
# include "stdlib.h" /* free . malloc */
# include "stdio.h" /* printf */
# include "./utils/print/print.h"

/*	table	*/

typedef struct s_table
{
	pthread_mutex_t			mtx_death;
	pthread_mutex_t			mtx_print;
	pthread_mutex_t			mtx_meals;
	pthread_mutex_t			mtx_close;
	long long				t0;
	int						total_philo;
	int						time_to_eat;
	int						time_to_sleep;
	int						time_to_die;
	int						flag_of_death;
	int						flag_of_close;
	int						meals;
}				t_table;

/*		philo		*/

typedef struct s_philo
{
	pthread_mutex_t			*chops;
	t_table					*table;
	long long				last_meal;
	int						id;
	int						eaten;
}				t_philo;

/*		parsers		*/

void		check_params(const int c, const char **v);
int			parse_table(t_table *t, const int c, const char **v);
int			parse_philo(t_philo *p, t_table *t);

/*		simulation	*/

void		*philo_routine(void *_);
void		init_mutexes(t_philo *p, t_table *t);
void		init_routine(t_philo *p, t_table *t, pthread_t *pt);
void		main_thread(t_philo *p, t_table *t);
// void		join_threads(t_philo *p, t_table *t, pthread_t *pt);

/*		strategy	*/

int			philo_eat(t_philo *p);
int			philo_sleep_and_think(t_philo *p); // new in v10.submit
int			philo_pick_up(t_philo *p);
int			philo_put_down(t_philo *p);
void		philo_pass_time(t_philo *p, long long n);
void		philo_log(t_philo *p, char *message);

/*		checkers	*/

int			count_if_all_ate_enough(t_philo *philo, t_table *t);
int			everyone_ate_enough(t_philo *philo);
int			someone_is_dead(t_philo *philo);
void		set_flag_of_death(t_table *t);
void		set_flag_of_close(t_table *t);

/*		toolkit		*/

long long	ft_current_ms(void);
int			ft_minmax(int x, int y, int either_max_or_down_make_up_your_mind);
int			ft_atoll(const char *_);
int			ft_atoi(const char *_);
int			print(const char *_, ...);

/*		exit		*/

void		ft_mutex_destroyer(t_philo *p, t_table *t); // New in v7
void		ft_clean_exit(t_philo *p, t_table *t, int exit_granted);
void		ft_cleaner(void *_);
void		ft_usage_exit(void);

/*		deprecated		*/

// void		print_params(const int argc, const char **argv);
// void		print_diners(t_philo *philo, int n);
// void		print_table(t_table *table);
// void		print_endl(const char *_);
// void		cout(const char *_);

// void		philo_print_put_down(t_philo *p, int l, int r, int _);
// void		philo_print_pick_up(t_philo *p, int l, int r, int _);
// void		philo_print_chops(t_philo *p, int l, int r, int choice, int side);

#endif
