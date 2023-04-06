#ifndef CAN_H
#define CAN_H

#include "pixel.h"

#define PPM_HEADER "P3"

typedef struct CANVAS_T {
  pixel ** values;
  int height;
  int width;
} * canvas;

canvas init_canvas(int height, int width);
void debug_canvas(canvas the_canvas);
void write_canvas(canvas the_canvas, char * file_name);
void free_canvas(canvas the_canvas);

#endif
