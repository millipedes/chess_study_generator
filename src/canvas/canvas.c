#include "include/canvas.h"

canvas init_canvas(int height, int width) {
  canvas the_canvas = calloc(1, sizeof(struct CANVAS_T));
  the_canvas->height = height;
  the_canvas->width = width;
  the_canvas->values = calloc(height, sizeof(struct PIXEL_T **));
  for(int i = 0; i < height; i++) {
    the_canvas->values[i] = calloc(width, sizeof(struct PIXEL_T *));
    for(int j = 0; j < width; j++)
      the_canvas->values[i][j] = init_pixel(MAX_COL, MAX_COL, MAX_COL);
  }
  return the_canvas;
}

void debug_canvas(canvas the_canvas) {
  printf("[CANVAS]\n");
  printf("Height: %d Width: %d\n", the_canvas->height, the_canvas->width);
  for(int i = 0; i < the_canvas->height; i++)
    for(int j = 0; j < the_canvas->width; j++)
      debug_pixel(the_canvas->values[i][j]);
}

/**
 * This function uses Bresenham's circle drawing algorithm to draw the nodes.
 * @param
 * @return
 */
canvas write_node(canvas the_canvas, node the_node) {
  int x = 0;
  int y = the_node->radius;
  int err = 3 - 2 * the_node->radius;
  update_points(the_canvas, the_node, x, y);
  while(y >= x) {
    x++;
    if(err > 0) {
      y--;
      err = err + 4 * (x - y) + 10;
    } else
      err = err + 4 * x + 6;
    update_points(the_canvas, the_node, x, y);
  }
  FT_Library ft;
  FT_Init_FreeType(&ft);
  FT_Face face;
  FT_New_Face(ft, "fonts/FiraCode-Bold.ttf", 0, &face);
  FT_Set_Pixel_Sizes(face, 0, 48);
  //for(int i = 0; i < strnlen(the_node->white, MAX_MOVE_SIZE); i++) {
    FT_Load_Char(face, (int)the_node->the_move->white[0], FT_LOAD_RENDER);
    FT_GlyphSlot slot = face->glyph;
    for(int j = the_node->radius;
        j < the_node->radius + (int)slot->bitmap.rows; j++)
      for(int k = the_node->radius;
          k < the_node->radius + (int)slot->bitmap.width; k++)
        if(slot->bitmap.buffer[((j - the_node->radius) * (int)slot->bitmap.width) + (k - the_node->radius)] > 0)
          change_color(the_canvas->values[j + the_node->radius - (int)slot->bitmap.rows][k + the_node->radius - (int)slot->bitmap.width], the_node->color);
  //}
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  return the_canvas;
}

canvas update_points(canvas the_canvas, node the_node, int x, int y) {
  if(y + the_node->fy < the_canvas->height
      && y + the_node->fy > 0
      && x + the_node->fx < the_canvas->width
      && x + the_node->fx > 0)
    change_color(the_canvas->values[ y + the_node->fy][ x + the_node->fx],
        the_node->color);
  if(-y + the_node->fy < the_canvas->height
      && -y + the_node->fy > 0
      && x + the_node->fx < the_canvas->width
      && x + the_node->fx > 0)
    change_color(the_canvas->values[-y + the_node->fy][ x + the_node->fx],
        the_node->color);
  if(y + the_node->fy < the_canvas->height
      && y + the_node->fy > 0
      && -x + the_node->fx < the_canvas->width
      && -x + the_node->fx > 0)
    change_color(the_canvas->values[ y + the_node->fy][-x + the_node->fx],
        the_node->color);
  if(-y + the_node->fy < the_canvas->height
      && -y + the_node->fy > 0
      && -x + the_node->fx < the_canvas->width
      && -x + the_node->fx > 0)
    change_color(the_canvas->values[-y + the_node->fy][-x + the_node->fx],
        the_node->color);
  if(x + the_node->fy < the_canvas->height
      && x + the_node->fy > 0
      && y + the_node->fx < the_canvas->width
      && y + the_node->fx > 0)
    change_color(the_canvas->values[ x + the_node->fy][ y + the_node->fx],
        the_node->color);
  if(-x + the_node->fy < the_canvas->height
      && -x + the_node->fy > 0
      && y + the_node->fx < the_canvas->width
      && y + the_node->fx > 0)
    change_color(the_canvas->values[-x + the_node->fy][ y + the_node->fx],
        the_node->color);
  if(x + the_node->fy < the_canvas->height
      && x + the_node->fy > 0
      && -y + the_node->fx < the_canvas->width
      && -y + the_node->fx > 0)
    change_color(the_canvas->values[ x + the_node->fy][-y + the_node->fx],
        the_node->color);
  if(-x + the_node->fy < the_canvas->height
      && -x + the_node->fy > 0
      && -y + the_node->fx < the_canvas->width
      && -y + the_node->fx > 0)
    change_color(the_canvas->values[-x + the_node->fy][-y + the_node->fx],
        the_node->color);
  return the_canvas;
}

void write_canvas(canvas the_canvas, char * file_name) {
  FILE * fp = fopen(file_name, "w");
  fprintf(fp, "%s\n", PPM_HEADER);
  fprintf(fp, "%d %d\n", the_canvas->width, the_canvas->height);
  fprintf(fp, "%d\n", MAX_COL);
  for(int i = 0; i < the_canvas->height; i++)
    for(int j = 0; j < the_canvas->width; j++)
      ppm_print(the_canvas->values[i][j], fp);
  fclose(fp);
}

void free_canvas(canvas the_canvas) {
  if(the_canvas) {
    if(the_canvas->values) {
      for(int i = 0; i < the_canvas->height; i++) {
        for(int j = 0; j < the_canvas->width; j++)
          free_pixel(the_canvas->values[i][j]);
        free(the_canvas->values[i]);
      }
      free(the_canvas->values);
    }
    free(the_canvas);
  }
}
