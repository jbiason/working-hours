#include "period.h"

#define MUST_WORK "08:48"

hours* period_worked_so_far(hours* start, hours* lunch_break, hours* lunch_return, hours* now) {
	hours* so_far;
	if (hours_preceed(now, lunch_return) == -1) {
		so_far = hours_sub(start, now);
	} else {
		hours* before_lunch = hours_sub(start, lunch_break);
		hours* after_lunch = hours_sub(lunch_return, now);

		so_far = hours_add(before_lunch, after_lunch);

		hours_free(before_lunch);
		hours_free(after_lunch);
	}

	return so_far;
}

hours* period_calc_time(hours* so_far, int* extra_indicator) {
	hours* must_work = hours_new(MUST_WORK);
	hours* result;
	if (hours_preceed(so_far, must_work) == -1) {
		*extra_indicator = 0;
		result = hours_sub(so_far, must_work);
	} else {
		*extra_indicator = 1;
		result = hours_sub(must_work, so_far);
	}
	return result;
}
