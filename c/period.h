#ifndef PERIOD_H
#define PERIOD_H

#include "hours.h"

hours* period_worked_so_far(hours* start, hours* lunch_break, hours* lunch_return, hours* now);
hours* period_calc_time(hours* so_far, int* extra_indicator);

#endif /* ifndef PERIOD_H */
