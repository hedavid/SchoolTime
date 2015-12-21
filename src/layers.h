/*
Copyright (c) 2015 , Ben624

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
THIS APPLICATION CAN BE SHARED ACROSS PEBBLE OWNERS, BUT CAN NOT BE PUBLISHED PUBLICLY ON THE PEBBLE APP STORE.

Permission to use, copy, or modify, this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
*/

/*
The structs and methods shown below take the passed in color string and return the actual color.
It isn't recommended to change this unless more colors are added.
*/

#include <pebble.h>

#define WHITE      0
#define BLACK      1
Window *window;
TextLayer *text_date_layer;
TextLayer *text_day_layer;
TextLayer *text_time_layer;
TextLayer *text_time_period_info;
TextLayer *text_battery_info;
TextLayer *text_bluetooth_info;
static Layer *second_round_layer;
static Layer *s_layer;
static char battery[10];
static char blue[2];

Layer *top_line_layer;
Layer *bottom_line_layer;

struct appearanceInfo {
    
    int schoolDay;
    int clockStyle;
    int textColor;
    int bluetooth;
    int alarm;
    int battery;
    int boot;
	int alarmRung;
    int break_mode;
    int dateColor;
    int lineColor;
    int timeColor;
    int batColor;
    int blueColor;
    int backColor;
    int periodColor;
    //    char dateColor[10];
    //char lineColor[10];
    //char timeColor[10];
    //char batColor[10];
    //char blueColor[10];
    //char backColor[10];
    //char periodColor[10];
    
};
struct appearanceInfo aInfo;


//Top line across screen below date.
void top_line_layer_update_callback(Layer *layer, GContext* ctx) {
    #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorFromHEX(aInfo.lineColor));
    #else
    if(aInfo.textColor == WHITE) graphics_context_set_fill_color(ctx, GColorWhite);
    
    else graphics_context_set_fill_color(ctx, GColorBlack);
    #endif
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}
//Bottom line across screen below time.
void bottom_line_layer_update_callback(Layer *layer, GContext* ctx) {
    #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorFromHEX(aInfo.lineColor));
    #else
    if(aInfo.textColor == WHITE) graphics_context_set_fill_color(ctx, GColorWhite);
    else graphics_context_set_fill_color(ctx, GColorBlack);
    #endif
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}