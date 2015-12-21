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
#include "layers.h"
#define NO		  0
#define YES		  1

//Animation(Boot Animation) Stopped Handler 
void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    property_animation_destroy((PropertyAnimation*) anim);
}
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
    
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
    
    AnimationHandlers handlers = {
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
    
    animation_schedule((Animation*) anim);
    
}


void show_rect(){
	 layer_set_frame(text_layer_get_layer(text_day_layer), GRect(2, 34, 144 - 6, 30));
	 layer_set_frame(text_layer_get_layer(text_date_layer), GRect(2, 54, 144 - 6, 30));
	 layer_set_frame(text_layer_get_layer(text_time_layer), GRect(2, 70, 144 - 7, 55));
	 layer_set_frame(text_layer_get_layer(text_time_period_info), GRect(2, 108, 144 - 7, 90));
	 layer_set_frame(top_line_layer, GRect(0, 76, 180, 2));
	 layer_set_frame(bottom_line_layer, GRect(0, 108, 180, 2));
	 layer_set_frame(text_layer_get_layer(text_bluetooth_info), GRect(130, 0, 144 - 7, 90));
	 layer_set_frame(text_layer_get_layer(text_battery_info), GRect(2, 0, 144 - 7, 90));

}

void reset_bluetooth_frame(){
	GRect bluetoothRect;
	#ifdef PBL_ROUND
	 if(aInfo.battery == YES){
        bluetoothRect=GRect(-25, 14, 180, 180);
        }else{
        bluetoothRect=GRect(0, 14, 180, 180);
    }
	text_layer_set_text_alignment(text_bluetooth_info, GTextAlignmentCenter);
	layer_set_frame(text_layer_get_layer(text_bluetooth_info), bluetoothRect);
	#else
	layer_set_frame(text_layer_get_layer(text_bluetooth_info), GRect(130, 0, 144 - 7, 90));
	#endif
	
}


void show_round(){
	 layer_set_frame(text_layer_get_layer(text_day_layer), GRect(0, 34, 180, 180));
	 	text_layer_set_text_alignment(text_day_layer, GTextAlignmentCenter);
	 layer_set_frame(text_layer_get_layer(text_date_layer), GRect(0, 54, 180, 180));
		 text_layer_set_text_alignment(text_date_layer, GTextAlignmentCenter);
	 layer_set_frame(text_layer_get_layer(text_time_layer), GRect(0, 70, 180, 180));
		 text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
	 layer_set_frame(text_layer_get_layer(text_time_period_info), GRect(0, 108, 180, 180));
		 text_layer_set_text_alignment(text_time_period_info, GTextAlignmentCenter);
	 layer_set_frame(top_line_layer, GRect(0, 76, 180, 2));
		 text_layer_set_text_alignment(text_day_layer, GTextAlignmentCenter);
	 layer_set_frame(bottom_line_layer, GRect(0, 108, 180, 2));
		 text_layer_set_text_alignment(text_day_layer, GTextAlignmentCenter);
	GRect bluetoothRect;
    if(aInfo.battery == YES){
        bluetoothRect=GRect(-25, 14, 180, 180);
        }else{
        bluetoothRect=GRect(0, 14, 180, 180);

    }
	text_layer_set_text_alignment(text_bluetooth_info, GTextAlignmentCenter);
	 layer_set_frame(text_layer_get_layer(text_bluetooth_info), bluetoothRect);
	
    GRect batteryRect;
    if(aInfo.bluetooth == YES){
        batteryRect=GRect(14, 14, 180, 180);
        }else{
        batteryRect=GRect(0, 14, 180, 180);
    }
	 layer_set_frame(text_layer_get_layer(text_battery_info), batteryRect);
		 text_layer_set_text_alignment(text_battery_info, GTextAlignmentCenter);
	
	


}
//Boot animation... change this to change the boot animation. 
void boot_animation(){
    GRect dayStart  = GRect(350, 34, 144 - 6, 30);
    GRect dayFinish = GRect(2, 34, 144 - 6, 30);
    animate_layer(text_layer_get_layer(text_day_layer), &dayStart, &dayFinish, 1600, 20);
	
    GRect dateStart =  GRect(350, 54, 144 - 6, 30);
    GRect dateFinish = GRect(2, 54, 144 - 6, 30);
    animate_layer(text_layer_get_layer(text_date_layer), &dateStart, &dateFinish, 1600, 10);
    
    GRect clockStart = GRect(-200,70, 144 - 7, 55);
    GRect clockFinish =GRect(2, 70, 144 - 7, 55);
    animate_layer(text_layer_get_layer(text_time_layer), &clockStart, &clockFinish, 1600,20);
    
    GRect periodStart = GRect(2, 300, 144 - 7, 90);
    GRect periodFinish =GRect(2, 108, 144 - 7, 90);
    animate_layer(text_layer_get_layer(text_time_period_info), &periodStart, &periodFinish, 1400, 10);
    
    GRect topLineStart = GRect(200, 76, 180, 2);
    GRect topLineFinish =GRect(0, 76, 180, 2);
    animate_layer(top_line_layer, &topLineStart, &topLineFinish, 1400, 10);
    
    GRect bottomLineStart = GRect(-200, 108, 180, 2);
    GRect bottomLineFinish =GRect(0, 108, 180, 2);
    animate_layer(bottom_line_layer, &bottomLineStart, &bottomLineFinish, 1400, 10);
    
    GRect bluetoothStart = GRect(130, -100, 144 - 7, 90);
    GRect bluetoothFinish =GRect(130, 0, 144 - 7, 90);
    animate_layer(text_layer_get_layer(text_bluetooth_info), &bluetoothStart, &bluetoothFinish, 1400, 10);
	
    GRect batteryStart = GRect(2, -100, 144 - 7, 90);
    GRect batteryFinish =GRect(2, 0, 144 - 7, 90);
    animate_layer(text_layer_get_layer(text_battery_info), &batteryStart, &batteryFinish, 1400, 10);
}


void round_boot_animation(){
    GRect dayStart  = GRect(350, 34, 180, 180);
    GRect dayFinish = GRect(0, 34, 180, 180);
    text_layer_set_text_alignment(text_day_layer, GTextAlignmentCenter);
    animate_layer(text_layer_get_layer(text_day_layer), &dayStart, &dayFinish, 1600, 20);
    
    GRect dateStart =  GRect(350, 54, 180, 180);
    GRect dateFinish = GRect(0, 54, 180, 180);
    text_layer_set_text_alignment(text_date_layer, GTextAlignmentCenter);
    animate_layer(text_layer_get_layer(text_date_layer), &dateStart, &dateFinish, 1600, 10);
    
    GRect clockStart = GRect(-200,70, 180, 180);
    GRect clockFinish =GRect(0, 70, 180, 180);
    text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
    animate_layer(text_layer_get_layer(text_time_layer), &clockStart, &clockFinish, 1600,20);
    
    GRect periodStart = GRect(0, 300, 180, 180);
    GRect periodFinish =GRect(0, 108, 180, 180);
    text_layer_set_text_alignment(text_time_period_info, GTextAlignmentCenter);
    animate_layer(text_layer_get_layer(text_time_period_info), &periodStart, &periodFinish, 1400, 10);
    
    GRect topLineStart = GRect(200, 76, 180, 2);
    GRect topLineFinish =GRect(0, 76, 176, 2);
    animate_layer(top_line_layer, &topLineStart, &topLineFinish, 1400, 10);
    
    GRect bottomLineStart = GRect(-200, 108, 180, 2);
    GRect bottomLineFinish =GRect(0, 108, 176, 2);
    animate_layer(bottom_line_layer, &bottomLineStart, &bottomLineFinish, 1400, 10);
    
	
	GRect bluetoothStart;
	GRect bluetoothFinish;
    if(aInfo.battery == YES){
		bluetoothStart = GRect(-25,-100,180,180);
        bluetoothFinish=GRect(-25, 14, 180, 180);
        }else{
		bluetoothStart = GRect(0,-100,180,180);
        bluetoothFinish=GRect(0, 14, 180, 180);

    }
	text_layer_set_text_alignment(text_bluetooth_info, GTextAlignmentCenter);
	animate_layer(text_layer_get_layer(text_battery_info), &bluetoothStart, &bluetoothFinish, 1400, 10);
	
    GRect batteryStart;
    GRect batteryFinish;
	
    if(aInfo.bluetooth == YES){
        batteryStart = GRect(18, -100, 180, 180);
        batteryFinish=GRect(18, 14, 180, 180);
        }else{
        batteryStart = GRect(0, -100, 180, 180);
        batteryFinish=GRect(0, 14, 180, 180);
    }
    text_layer_set_text_alignment(text_battery_info, GTextAlignmentCenter);
    animate_layer(text_layer_get_layer(text_battery_info), &batteryStart, &batteryFinish, 1400, 10);
    layer_set_hidden(text_layer_get_layer(text_battery_info),false);
    
    text_layer_set_text_alignment(text_battery_info, GTextAlignmentCenter);
    
}