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

#pragma once

/* 
This header file declares drawing methods that are defined in rect.c or round.c, 
depending on the platform being built. Since the methods share the same function
signature, they can share the same header file, even though the implementations
of the functions themselves are different.
*/

void draw_seconds(GContext *ctx, uint8_t seconds, Layer *layer);
void draw_minutes(GContext *ctx, uint8_t minutes, Layer *layer);
void draw_hours(GContext *ctx, uint8_t hours, Layer *layer);