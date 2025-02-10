/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:26:20 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/05 18:26:20 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

#define BRED "\e[1;31m"
#define BBLK "\e[1;30m"
#define BCYN "\e[1;36m"
#define reset "\e[0m"

# define INIT 0
# define DESTROY 1
# define LOCK 2
# define UNLOCK 3
# define CREATE 4
# define JOIN 5
# define DETACH 6

typedef pthread_mutex_t	t_mtx;// mutex
typedef pthread_t		t_ptd;// pthread
typedef struct s_table	t_table;// ข้อมูลตัวแปรทั้งหมดที่นักปรัชญาใช้ร่วมกัน

typedef struct s_philo
{
	int		id;// หมายเลขของนักปรัชญา
	int		fist_fork;// ส้อมแรก
	int		sec_fork;// ส้อมสุดท้าย
	int		count_meals;// จำนวนมื้ออาหารที่กิน
	long	next_eat;// เวลาที่ต้องกินภายในเวลานั้น
	long	last_eat;// เวลาครั้งสุดท้ายที่กิน
	t_ptd	threads;// เธรดของนักปรัชญา
	t_table	*table;// ข้อมูลที่ใช้ร่วมกัน
}	t_philo;// ข้อมูลของนักปรัชญา

typedef struct s_table
{
	long	amount;// จำนวนนักปรัชญา
	long	t_die;// ระยะเวลาการตายหากยังไม่ได้กิน
	long	t_eat;// ระยะเวลาการกิน
	long	t_sleep;// ระยะเวลาการนอน
	long	option;// จำนวนมื้ออาหารที่ต้องกินให้ครบก่อนอย่างน้อยก่อนการจำลองจะหยุด
	long	time_start;// เวลาเริ่มการจำลอง
	bool	end;// เช็คการจบการจำลอง
	t_mtx	monitor;// เช็คสถานะคนตาย
	t_mtx	print;// เขียนสถานะ กิน,นอน,คิด,ตาย
	t_mtx	*fork;// arrayของส้อม
	t_philo	*philo;// ตัวแทนนักปรัชญา
}	t_table;// ข้อมูลตัวแปรทั้งหมดที่นักปรัชญาใช้ร่วมกัน

//phaser
void	clean_all(t_table *table, int i);
//phaser_data
void	phaser_data(t_table *table, int i);
//simulation
void	start_simulation(t_table *table, int i);
//time
long	current_milliseconds(void);
//solo
void	one_philosopher(t_table *table);

#endif