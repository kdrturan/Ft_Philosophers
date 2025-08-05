# 🧠 Philosophers

An implementation of Edsger Dijkstra’s classic **Dining Philosophers** concurrency problem, developed in C for the **42 Cursus**.

The goal is to simulate philosophers who share forks, eat, think, and sleep — all while avoiding deadlocks and starvation using multithreading and proper synchronization primitives.

---

## 📁 Directory Layout

| Path               | Purpose                                                                 |
|--------------------|-------------------------------------------------------------------------|
| `philo/Makefile`   | Builds the project; compiles sources, links binary `philo`.             |
| `philo/includes/`  | Public headers (`philo.h`) defining `t_philo`, `t_program`, and helpers.|
| `philo/srcs/`      | Source files (`main.c`, `init.c`, `routine.c`, `utils.c`, etc.).        |
| `philo/objs/`      | Auto-generated object files (ignored by Git).                           |
| `.gitignore`       | Excludes build artefacts and temp files.                                |

---

## 🛠️ Compilation

```bash
cd philo
make         # Builds ./philo
make clean   # Deletes object files
make fclean  # Deletes object files + binary
make re      # Full rebuild
```

✅ No external libraries are required except for `pthread`, which is linked automatically via the Makefile.  
The code is written in pure ANSI C, and any modern GCC or Clang compiler will work.

---

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep         [number_of_times_each_philosopher_must_eat]
```

| Argument                                  | Description                                                                 |
|-------------------------------------------|-----------------------------------------------------------------------------|
| `number_of_philosophers`                 | Number of philosophers and forks (1–200).                                   |
| `time_to_die`                            | Time in ms a philosopher can go without eating before dying.               |
| `time_to_eat`                            | Time in ms a philosopher spends eating (forks held).                        |
| `time_to_sleep`                          | Time in ms a philosopher spends sleeping.                                   |
| `number_of_times_each_philosopher_must_eat` *(optional)* | If provided, simulation ends when all philosophers eat this many times. |

---

## 📌 Example

```bash
$ ./philo 5 310 200 100
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
...
```

---

## 🧩 Algorithm Overview

### 🔹 Initialization
- Parse and validate CLI arguments.
- Allocate a `t_program` instance.
- Create `n` mutexes (forks) and spawn one thread per philosopher.

### 🔹 Philosopher Routine (`philo_routine`)
- Loop: `think → take forks → eat → sleep`.
- Odd and even philosopher IDs pick up forks in opposite order to avoid circular wait (deadlock).

### 🔹 Monitor Thread (`routine_check`)
- Continuously checks if any philosopher has exceeded `time_to_die`.
- Ends simulation if:
  - A philosopher dies, OR  
  - All philosophers have eaten `meals_to_finish` times.

### 🔹 Shutdown
- Join/detach all threads.
- Destroy all mutexes and free allocated memory.

---

## 🧠 Deadlock Avoidance

This implementation prevents deadlocks by varying fork acquisition order between even and odd philosophers.  
It respects the four necessary conditions for deadlock and breaks the **circular wait** condition intentionally.

---

## 🧪 Testing & Debugging

| Tool              | Command                                               | Purpose                                         |
|-------------------|--------------------------------------------------------|-------------------------------------------------|
| **Valgrind**      | `valgrind --leak-check=full ./philo …`                | Detects memory leaks and invalid accesses.      |
| **AddressSanitizer** | `CFLAGS='-g -fsanitize=address' make re`           | Fast runtime checks for memory issues.          |
| **strace/ltrace** | `strace -c ./philo …`                                 | Traces system calls and mutex/futex behavior.   |

---

## 📚 License

This project is developed as part of the **42 Network** curriculum.  
**For academic purposes only.**

---
