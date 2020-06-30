#include <string.h>
#include <stdlib.h>

#include "check.h"
#include "hours.h"
#include "period.h"

int main(int argc, char *argv[]) {
	describe("Hours", {
		context("new", {
			it("Create a structure if valid", {
				hours* test = hours_new("12:00");
				check(test != NULL);
				hours_free(test);
			});

			it("Fails on invalid hours", {
				hours* test = hours_new("25:00");
				check(test == NULL);
			});

			it("Fails on invalid minutes", {
				hours* test = hours_new("12:61");
				check(test == NULL);
			});

			it("Fails on invalid format", {
				hours* test = hours_new("1200");
				check(test == NULL);
			});
		});

		context("sub", {
			it("Substracts times", {
				hours* first = hours_new("13:00");
				hours* second = hours_new("15:00");
				hours* diff = hours_sub(first, second);
				char *test = hours_display(diff);
				check(strcmp(test, "02:00") == 0);
				free(test);
				hours_free(diff);
				hours_free(second);
				hours_free(first);
			});
		});

		context("add", {
			it("Adds times", {
				hours* first = hours_new("01:30");
				hours* second = hours_new("01:30");
				hours* diff = hours_add(first, second);
				char *test = hours_display(diff);
				check(strcmp(test, "03:00") == 0);
				free(test);
				hours_free(diff);
				hours_free(second);
				hours_free(first);
			});
		});

		context("preceeds", {
			it("First time is earlier", {
				hours* first = hours_new("13:00");
				hours* second = hours_new("15:00");
				check(hours_preceed(first, second) == -1);
				hours_free(second);
				hours_free(first);
			});

			it("Second time is earlier", {
				hours* first = hours_new("15:00");
				hours* second = hours_new("13:00");
				check(hours_preceed(first, second) == 1);
				hours_free(second);
				hours_free(first);
			});
		});
	});

	describe("Periods", {
		context("So far", {
			it("Is in the morning", {
				hours* start = hours_new("08:00");
				hours* going_lunch = hours_new("12:00");
				hours* back_from_lunch = hours_new("13:00");
				hours* now = hours_new("09:33");

				hours* so_far = period_worked_so_far(start, going_lunch, back_from_lunch, now);
				char* display = hours_display(so_far);
				check(strcmp(display, "01:33") == 0);
				free(display);
				hours_free(so_far);

				hours_free(now);
				hours_free(back_from_lunch);
				hours_free(going_lunch);
				hours_free(start);
			});

			it("Is in the lunch break", {
				hours* start = hours_new("08:10");
				hours* going_lunch = hours_new("12:08");
				hours* back_from_lunch = hours_new("13:00");
				hours* now = hours_new("12:30");

				hours* so_far = period_worked_so_far(start, going_lunch, back_from_lunch, now);
				char* display = hours_display(so_far);
				check(strcmp(display, "04:20") == 0);
				free(display);
				hours_free(so_far);

				hours_free(now);
				hours_free(back_from_lunch);
				hours_free(going_lunch);
				hours_free(start);
			});

			it("Back from lunch", {
				hours* start = hours_new("08:20");
				hours* going_lunch = hours_new("12:20");
				hours* back_from_lunch = hours_new("13:40");
				hours* now = hours_new("14:40");

				hours* so_far = period_worked_so_far(start, going_lunch, back_from_lunch, now);
				char* display = hours_display(so_far);
				check(strcmp(display, "05:00") == 0);
				free(display);
				hours_free(so_far);

				hours_free(now);
				hours_free(back_from_lunch);
				hours_free(going_lunch);
				hours_free(start);
			});
		});

		context("Extra hours", {
			it("Still have to work", {
				hours* so_far = hours_new("07:20");

				int extra;
				hours* remaining = period_calc_time(so_far, &extra);
				check(extra == 0);
				char* display = hours_display(remaining);
				check(strcmp(display, "01:28") == 0);
				free(display);
				hours_free(remaining);

				hours_free(so_far);
			});

			it("Extra time", {
				hours* so_far = hours_new("09:00");

				int extra;
				hours* extra_time = period_calc_time(so_far, &extra);
				check(extra == 1);
				char* display = hours_display(extra_time);
				check(strcmp(display, "00:12") == 0);
				free(display);
				hours_free(extra_time);

				hours_free(so_far);
			});
		});
	});

	check_print_stats();
}
