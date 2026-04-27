*This project has been created as part
of the 42 curriculum by elino*

## Description

The **Philosophers** project is an implementation of the classic concurrency problem **Dining Philosophers**, proposed by *Edsger Dijkstra* in 1965 to illustrate the challenges of concurrent programming. The purpose of the project is to coordinate all threads (philosophers) so that none starve, the program does not deadlock, and two threads never hold the same fork (mutex) at the same time

---

## Instructions

### Build

```bash
make
```

### Run

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 3 400 200 100 3
```

> ⚠️ All arguments must be positive integers. Very large values may cause undefined behavior or slow down your system depending on the platform. Please do not also test *time_to_die, time_to_eat and time_to_sleep* with values under 60 ms

---

## Program Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time (ms) a philosopher can go without eating before dying |
| `time_to_eat` | Time (ms) it takes to eat |
| `time_to_sleep` | Time (ms) spent sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation ends when all philosophers have eaten this many times |

---

## Resources

- [The Dining Philosophers Problem — Neso Academy](https://www.youtube.com/watch?v=FYUi-u7UWgw)
- [Concurrent Programming: Philosophers' Dinner, Impasse, and Starvation — Fernando dos Santos](https://www.youtube.com/watch?v=LhkDV3cECNY&list=PLnRUDuia_cb0kXHMTmRrqWZc7BEqJNCxz)
- [16.5 - Philosophers' Dinner [SO UFAM] — Andre Carvalho](https://www.youtube.com/watch?v=g9zEqwSZd4o&list=PLnRUDuia_cb0kXHMTmRrqWZc7BEqJNCxz&index=2)
- [Deadlock Explained with the Philosophers' Dinner 🍽 | Operating System Concepts — Nem TI Conto](https://www.youtube.com/watch?v=hYD8raEyhSw&list=PLnRUDuia_cb0kXHMTmRrqWZc7BEqJNCxz&index=3)
- [Thread (understand how your application works) // Programmer's Dictionary — Código Fonte TV](https://www.youtube.com/watch?v=xNBMNKjpJzM&list=PLnRUDuia_cb0kXHMTmRrqWZc7BEqJNCxz&index=5)
- [Medium Guide — The Dining Philosophers Problem](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

---

## AI Usage

AI assistance was used for conceptual clarification, debugging guidance, and concurrency analysis during the development of this project.

Support was provided mainly for understanding and reviewing the logic of the monitoring system and thread synchronization, specifically in the following functions:

- monitor_routine

- check_death

- check_finished

- all_finished

- mutex_locker

The assistance focused on explaining thread interaction, safe access to shared variables, and correct usage of mutexes (death_mutex, meal_mutex and print_mutex).

All design decisions, implementations, and final code were written and validated by the author.