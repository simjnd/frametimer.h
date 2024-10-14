# frametimer.h
### Single-header frametimer utility
---

Very basic utility to lock the execution rate of a function to a specific
frameratei using polling. It is dependency free (even from the standard library)
which makes it very portable. It does not perform any memory allocation.

# Usage
---

Include the header file in every file you want to use it.
```c
#include "frametimer.h"
```

In **ONE** file, define `FRAMETIMER_IMPL` **before** including the header file.
```c
#define FRAMETIMER_IMPL
#include "frametimer.h"
```

Define a function and allocate a frametimer
```c
void print_delta(unsigned int dt) {
  printf("Delta time is %d\n", dt);
}

frametimer_t ft_print_delta = {
  .fps  = 1,
  .func = print_delta
};
```

Then in your update loop call `ft_update` and give it the current time using the
method of your choice. This is platform dependant, the only constraint is that
time must be expressed in milliseconds.
```c
while (true) {
  unsigned int time = get_time()
  int ran = ft_update(&ft_print_delta, time);
}
```
The function `print_delta` will be executed once per second. `ran` will be `1`
if `print_delta` executed, and `0` if it did not. This can be useful to skip
some other actions based on whether or not its dependencies executed.

# Documentation
---

```c
typedef void (*ft_func_t)(unsigned int dt);
```
The function you want to bind to a `frametimer_t` should be of this shape.
It takes an `unsigned int` as an argument which will be the delta between this
execution and the previous one, and returns `void`.


```c
typedef struct {
  ft_func_t func;
  unsigned int fps;
  unsigned int last_run;
  unsigned int run_count;  
} frametimer_t;
```
A `frametimer_t` is a simple struct that stores the pointer to the function to
be executed, the framerate at which it should be executed, the timestamp of the
last run, and the number of time the function has been called since the start of
the program.


```c
int ft_update(frametimer_t* ft, unsigned int time);
```
Calls the function bound to `ft` if the delta between `time` and its last
execution matches the framerate specified.
