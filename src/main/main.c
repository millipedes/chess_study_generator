#include "../canvas/include/canvas.h"
#include "../canvas/include/node.h"

int main(void) {
  canvas the_canvas = init_canvas(1000, 1000);
  node the_node = init_node(init_move("e4", "e5", 1), init_pixel(0, 35, 66), 100, 100, 150);
  // debug_canvas(the_canvas);
  the_canvas = write_node(the_canvas, the_node);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  free_node(the_node);
  return 0;
}
