#include <stdio.h>
#include <stdlib.h>

#include "hours.h"

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

	char *display = hours_display(so_far);

	printf("So far, you've worked %s\n", display);

	hours* must_work = hours_new("08:48");
	if (hours_preceed(so_far, must_work) == -1) {
		hours* remaining = hours_sub(so_far, must_work);
		char *still = hours_display(remaining);
		printf("You still need to work %s\n", still);
		free(still);
		hours_free(remaining);
	} else {
		hours* exceeding = hours_sub(must_work, so_far);
		char* extra = hours_display(exceeding);
		printf("You did %s of extra work\n", extra);
		free(extra);
		hours_free(exceeding);
	}

	free(display);
	hours_free(so_far);
	hours_free(now);
	hours_free(start);
	hours_free(lunch_break);
	hours_free(lunch_return);

	return EXIT_SUCCESS;
}
