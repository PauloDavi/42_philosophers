/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 10:17:45 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					philo_eat;
	int					n_philo;
	long int			t_die;
	long int			t_eat;
	long int			t_sleep;
	long int			n_eat;
	long int			t_start;
	bool				stop;
	t_philo				*philo;
	pthread_mutex_t		print;
	pthread_mutex_t		m_stop;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		dead;
}						t_data;

typedef struct s_philo
{
	size_t				n;
	long int			eat_count;
	long int			last_eat;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		fork_l;
}						t_philo;

// Exit
void					free_all(t_data *data);

// Philosophers
bool					philo_handler(t_data *data);

// Init
bool					init_data(t_data *data, char **argv);

// Utils
void					msleep(int ms);
bool					is_dead(t_philo *philo, bool set_dead);
long int				timestamp(void);
void					print(t_philo *philo, char *str);
bool					philo_init(t_data *data, int i);

// Lib
long int				ft_atoi(const char *str);
bool					ft_isdigit(int c);
bool					ft_isspace(int c);
void					*ft_memset(void *s, int c, size_t n);

#endif
