#ifndef FRAMETIMER_H
#define FRAMETIMER_H

typedef unsigned int ft_u32;
typedef int ft_i32;

typedef void (*ft_func_t)(ft_u32 dt);
typedef void (*ft_time_func_t)(void);

typedef struct {
  ft_func_t func;
  ft_time_func_t time;
  ft_u32 fps;
  ft_u32 last_run;
  ft_u32 run_count;
} frametimer_t;

ft_u32 ft_update(frametimer_t* ft, ft_u32 time);
ft_u32 ft_autoupdate(frametimer_t* ft);

#endif // FRAMETIMER_H

#if defined(FRAMETIMER_IMPL) && !defined(FRAMETIMER_IMPLEMENTED)
#define FRAMETIMER_IMPLEMENTED

// Executes
ft_u32 ft_update(frametimer_t* ft, ft_u32 time) {
  ft_u32 dt = time - ft->last_run;
  if (dt >= (1000 / ft->fps)) {
    ft->func(dt);
    ft->last_run = time;
    ft->run_count++;
    return 1;
  }
  return 0;
}

ft_u32 ft_autoupdate(frametimer_t* ft) {
  ft_u32 time = ft->time();
  return ft_update(ft, time);
}

#endif // FRAMETIMER_IMPL


