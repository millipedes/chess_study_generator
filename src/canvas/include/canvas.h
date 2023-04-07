#ifndef CAN_H
#define CAN_H

#include "node.h"

#define PPM_HEADER "P3"

typedef struct CANVAS_T {
  pixel ** values;
  int height;
  int width;
} * canvas;

canvas init_canvas(int height, int width);
void debug_canvas(canvas the_canvas);
canvas write_node(canvas the_canvas, node the_node);
canvas update_points(canvas the_canvas, node the_node, int x, int y);
void write_canvas(canvas the_canvas, char * file_name);
void free_canvas(canvas the_canvas);

#endif
