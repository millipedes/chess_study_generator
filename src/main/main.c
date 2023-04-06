#include "../canvas/include/canvas.h"

int main(void) {
  canvas the_canvas = init_canvas(1000, 1000);
  // debug_canvas(the_canvas);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  return 0;
}
