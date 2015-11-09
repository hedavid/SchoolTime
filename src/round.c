/*
Copyright (c) 2015 , Ben624

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, 
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
THIS APPLICATION CAN BE SHARED ACROSS PEBBLE OWNERS, BUT CAN NOT BE PUBLISHED PUBLICLY ON THE PEBBLE APP STORE. 

Permission to use, copy, or modify, this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
*/


#if defined(PBL_ROUND)

#include <pebble.h>
#include "ui.h"

#define TIME_ANGLE(time) time * (TRIG_MAX_ANGLE / 60)
#define HOUR_ANGLE(hour) hour * (TRIG_MAX_ANGLE / 12)

// Draw an arc with given inner/outer radii 
static void draw_arc(GContext *ctx, GRect rect, uint16_t thickness, uint32_t end_angle) {
  if(end_angle == 0) {
    graphics_fill_radial(ctx, rect, GOvalScaleModeFitCircle, thickness, 0, TRIG_MAX_ANGLE);
  } else {
    graphics_fill_radial(ctx, rect, GOvalScaleModeFitCircle, thickness, 0, end_angle); 
  }
}

static GRect calculate_rect(Layer *layer, uint8_t arc_id) {
  uint8_t padding = 10;
  return grect_inset(layer_get_bounds(layer), GEdgeInsets(padding*(3*arc_id)));
}

// Handle representation for seconds
void draw_seconds(GContext *ctx, uint8_t seconds, Layer *layer) {
  draw_arc(ctx, calculate_rect(layer, 0), 6, TIME_ANGLE(seconds));
}

#endif