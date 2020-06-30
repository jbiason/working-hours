#include <stdio.h>
#include <stdlib.h>

#include "hours.h"
#include "period.h"

int main(int argc, char* argv[]) {
	hours *start = NULL;
	hours *lunch_break = NULL;
	hours *lunch_return = NULL;

	if (argc <= 1) {
		printf("Usage: wh START_TIME [LUNCH_BREAK] [LUNCH_RETURN]\n");
		return EXIT_FAILURE;
	}

	if (argc >= 2) {
		start = hours_new(argv[1]);
		if (start == NULL) {
			printf("Invalid START_TIME\n");
			return EXIT_FAILURE;
		}
	}

	if (argc >= 3) {
		lunch_break = hours_new(argv[2]);
		if (lunch_break == NULL) {
			printf("Invalid LUNCH_BREAK\n");
			return EXIT_FAILURE;
		}
	} else {
		lunch_break = hours_new("12:00");
	}

	if (argc >= 4) {
		lunch_return = hours_new(argv[3]);
		if (lunch_return == NULL) {
			printf("Invalid LUNCH_RETURN\n");
			return EXIT_FAILURE;
		}
	} else {
		lunch_return = hours_new("13:00");
	}

	hours* now = hours_right_now();
	hours* so_far = period_worked_so_far(start, lunch_break, lunch_return, now);
	char *display = hours_display(so_far);
	printf("So far, you've worked %s\n", display);
	free(display);

	int extra;
	hours* period = period_calc_time(so_far, &extra);
	char* result_display = hours_display(period);
	if (extra == 1) {
		printf("You did %s of extra work\n", result_display);
	} else {
		printf("You still need to work %s\n", result_display);
	}
	free(result_display);
	hours_free(period);

	hours_free(so_far);
	hours_free(now);
	hours_free(start);
	hours_free(lunch_break);
	hours_free(lunch_return);

	return EXIT_SUCCESS;
}
