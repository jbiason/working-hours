#ifndef HOURS_H
#define HOURS_H

typedef struct hoursStruct hours;

hours* hours_new(char *input);
hours* hours_right_now();
hours* hours_sub(hours* self, hours* other);
hours* hours_add(hours* self, hours* other);
char* hours_display(hours* self);
void hours_free(hours* self);
int hours_preceed(hours* self, hours* other);

#endif
