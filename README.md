# Philosophers — concurrency in C with threads and mutexes

A solution to the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), written in C as part of the 42 curriculum.

`N` philosophers sit around a table with one fork between each pair. To eat, a philosopher needs both forks next to them. They eat, sleep, think, and starve if they go too long without eating. The program simulates them with **one thread per philosopher** and **one mutex per fork**, without deadlocks or garbled output, and stops as soon as one of them dies or everyone has eaten enough.

## Build & run

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Times are in milliseconds. Every argument must be a strictly positive integer.

```bash
./philo 5 800 200 200      # nobody should die, runs until stopped
./philo 5 800 200 200 7    # stops once every philosopher has eaten 7 times
./philo 4 310 200 100      # a philosopher dies
./philo 1 800 200 200      # only one fork: the philosopher dies at 800 ms
```

Each state change is printed as `timestamp_in_ms philosopher_id action`. Output of `./philo 4 310 200 100`:

```
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
...
312 1 died
```

## How it works

- **Avoiding deadlock**: forks are not all picked up in the same order. Even and odd philosophers take their left and right fork in opposite order, so two neighbours always compete for the *same* first fork and a circular wait can't form.
- **Protecting shared state**: each philosopher's last meal time and meal count, plus the "simulation over" flags, are only read and written under a dedicated `end` mutex.
- **Clean output**: a `write` mutex serialises `printf`, and nothing is printed once the simulation is over, so no message appears after `died`.
- **Monitoring**: the main thread checks every 100 µs whether a philosopher has gone longer than `time_to_die` without eating, or whether everyone has reached the meal target.
- **Responsive sleeping**: instead of one long `usleep`, `ft_usleep` sleeps in 100 µs steps and checks whether the simulation has ended, so all threads stop quickly and are joined cleanly.
- **Fairness**: when `time_to_eat ≥ time_to_sleep`, a philosopher thinks a little longer before reaching for forks again, leaving time for its neighbours to eat.
- **Edge case**: with a single philosopher there is only one fork, which is handled separately.

## Project structure

```
.
├── Makefile
├── includes/philosophers.h
└── srcs/
    ├── main.c          # creates the threads and runs the monitor loop
    ├── init.c          # argument parsing, mutexes, fork assignment
    ├── routine.c       # philosopher life cycle (eat → sleep → think)
    ├── eat.c           # taking forks and eating
    ├── monitoring.c    # death and meal-count detection
    ├── utils.c         # time, printing, sleeping, joining
    ├── free.c          # cleanup
    └── atoi_bool.c, ft_*.c   # input validation helpers
```

## Tech

C · POSIX threads (`pthread`) · mutexes · Linux
