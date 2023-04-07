#include "../canvas/include/canvas.h"
#include "../canvas/include/node.h"

int main(void) {
  canvas the_canvas = init_canvas(1000, 1000);
  node the_node = init_node(init_move("e4567", "e5", 1), init_pixel(0, 35, 66), 300, 300, 150);
  node the_node1 = init_node(init_move("e45", "e5", 1), init_pixel(0, 35, 66), 500, 500, 75);
  // debug_canvas(the_canvas);
  the_canvas = write_node(the_canvas, the_node);
  the_canvas = write_node(the_canvas, the_node1);
  write_canvas(the_canvas, "test.ppm");
  free_canvas(the_canvas);
  free_node(the_node);
  free_node(the_node1);
  return 0;
}
