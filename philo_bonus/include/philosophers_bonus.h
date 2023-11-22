/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 10:17:05 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
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
	sem_t				*sem_print;
	sem_t				*sem_stop;
	sem_t				*sem_eat;
	sem_t				*sem_dead;
	sem_t				*sem_forks;
}						t_data;

typedef struct s_philo
{
	size_t				n;
	long int			eat_count;
	long int			last_eat;
	t_data				*data;
	pid_t				pid;
}						t_philo;

// Exit
void					free_all(t_data *data);

// Init
bool					init_data(t_data *data, char **argv);

// Philosophers
void					philo_handler(t_data *data);

// Utils
void					philo_init(t_data *data, int i);
bool					is_dead(t_philo *philo, bool set_dead);
long int				timestamp(void);
void					msleep(int ms);
void					print(t_philo *philo, char *str);

// Lib
long int				ft_atoi(const char *str);
bool					ft_isdigit(int c);
bool					ft_isspace(int c);
void					*ft_memset(void *s, int c, size_t n);

#endif
