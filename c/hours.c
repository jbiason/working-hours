#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hours.h"

struct hoursStruct {
	int minutes;
};

/**
 * Create a new hours structure.
 */
hours* hours_new(char *input)
{
	struct hoursStruct* result = NULL;

	char *duplicate = malloc(sizeof(char) * strlen(input) + 1);
	sprintf(duplicate, "%s", input);

	char *colon = strchr(duplicate, ':');
	if (colon == NULL) {
		goto cleanup;
	}

	char* minutes_pos = colon + 1;
	*colon = '\0';

	int hours = atoi(duplicate);
	int minutes = atoi(minutes_pos);

	if (hours < 0 || hours > 23) {
		goto cleanup;
	}

	if (minutes < 0 || minutes > 59) {
		goto cleanup;
	}

	int total_minutes = hours * 60 + minutes;

	result = malloc(sizeof(struct hoursStruct));
	result->minutes = total_minutes;

cleanup:
	free(duplicate);
	return result;
}

/**
 * Create an Hours with the current time.
 */
hours* hours_right_now()
{
	struct hoursStruct* result = malloc(sizeof(struct hoursStruct));
	time_t right_now;
	time(&right_now);
	struct tm* local = localtime(&right_now);

	result->minutes = local->tm_hour * 60 + local->tm_min;
	return result;
}

/**
 * Substract one hour from another. Returns a new hours struct.
 */
hours* hours_sub(hours* self, hours* other)
{
	struct hoursStruct* result = malloc(sizeof(struct hoursStruct));
	result->minutes = other->minutes - self->minutes;
	return result;
}

/**
 * Add one hour to to another. Returns a new hours struct.
 */
hours* hours_add(hours* self, hours* other)
{
	struct hoursStruct* result = malloc(sizeof(struct hoursStruct));
	result->minutes = other->minutes + self->minutes;
	return result;
}

/**
 * Pretty display for hours.
 */
char *hours_display(hours* self)
{
	int hours = (int)ceil(self->minutes / 60);
	int minutes = self->minutes - (hours * 60);

	char* result = malloc(sizeof(char) * 6);	// XX:XX\0
	sprintf(result, "%02d:%02d", hours, minutes);
	return result;
}

/**
 * Checks if the hours happens before the other; returns -1 if it is earlier or 1 if it is later.
 */
int hours_preceed(hours* self, hours* other) {
	return self->minutes < other->minutes
		? -1
		: 1;
}

/**
 * Free the memory used by the hours.
 */
void hours_free(hours* self) {
	free(self);
}
