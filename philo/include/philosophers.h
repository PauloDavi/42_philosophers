/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by paulo             #+#    #+#             */
/*   Updated: 2023/11/20 09:42:27 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
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
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	bool				stop;
	long int			t_start;
	t_philo				*philo;
	pthread_mutex_t		print;
	pthread_mutex_t		m_stop;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		dead;
}						t_data;

typedef struct s_philo
{
	int					n;
	int					m_count;
	bool				is_eating;
	pthread_t			thread;
	long int			last_eat;
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
void					ft_usleep(int ms);
bool					is_dead(t_philo *philo, int nb);
long long				timestamp(void);
void					print(t_philo *philo, char *str);

// Lib
int						ft_atoi(const char *str);
bool					ft_isdigit(int c);
bool					ft_isspace(int c);
void					*ft_memset(void *s, int c, size_t n);

#endif
