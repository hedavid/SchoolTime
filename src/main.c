/*
Copyright (c) 2015 , Ben624

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
THIS APPLICATION CAN BE SHARED ACROSS PEBBLE OWNERS, BUT CAN NOT BE PUBLISHED PUBLICLY ON THE PEBBLE APP STORE.

Permission to use, copy, or modify, this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
*/

#include "pebble.h"
#include "animations.h"
#include "schedules.h"
#include "ui.h"

#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6
#define MINUTES   0
#define SECONDS      1
#define NO          0
#define YES          1
#define DISABLE      2
#define NORMAL      0
#define RELEASE      1
#define DELAY      2
#define TIME(h,s) ((h*60) + s)

//static Layer *s_layer;
int seconds =0;

void handle_battery_change(BatteryChargeState b);
void handle_bluetooth_change(bool isconnected);
void readConfig();
void applyConfig(bool callTimerTick);


bool firstrun = true;
bool canPlay = true;
static bool firstblue = true;
struct classNames {
    char className[20];
    
};

//Number of classes
struct classNames cNames[8];


//Tick handler... Don't mess with this unless you know what to do :)

void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
    
    if (firstrun) {
        firstrun = false;
    }
    static char outline[81];
    static bool between_classes = false;
    static int next_class_at = 0;
    static int time_to_school = 0;
    static char time_text[] = "00:00:00";
    static char date_text[] = "00/00/0000";
    static char day_text[] = "Xxxxxxxxx";
    
    char *time_format;
    
    int hours = tick_time->tm_hour;
    int minutes = tick_time->tm_min;
    seconds = tick_time->tm_sec;
    #ifdef PBL_ROUND
    if(aInfo.clockStyle == SECONDS){
        APP_LOG(APP_LOG_LEVEL_INFO, "HERE S");
        layer_set_hidden(s_layer, false);
        layer_mark_dirty(s_layer);
        
    }
    else if(aInfo.clockStyle == MINUTES){
        APP_LOG(APP_LOG_LEVEL_INFO, "HERE");
        layer_set_hidden(s_layer, true);
    }
    #endif
    int day = tick_time->tm_wday;
    int now = (hours * 60) + minutes + 1;
    if (clock_is_24h_style()) {
        if(aInfo.clockStyle == MINUTES)
        time_format = "%R";
        else
        time_format = "%T";
        } else {
        if(aInfo.clockStyle == MINUTES)
        time_format = "%I:%M";
        else
        time_format = "%I:%M:%S";
    }
    strftime(time_text, sizeof(time_text), time_format, tick_time);
    
    if (!clock_is_24h_style() && (time_text[0] == '0')) {
        memmove(time_text, &time_text[1], sizeof(time_text) - 1);
    }
    
    text_layer_set_text(text_time_layer, time_text);
    if (seconds == 0 || hours == 0 || !firstrun) {
        //UPDATES DATE
        strftime(day_text, sizeof(day_text), "%A", tick_time);
        strftime(date_text, sizeof(date_text), "%D", tick_time);
        text_layer_set_text(text_date_layer, date_text);
        text_layer_set_text(text_day_layer, day_text);
    }
    
    if(aInfo.break_mode == 1){
        text_layer_set_text(text_time_period_info, "Break");
        
        }else{
        
        if (between_classes) {
            if(canPlay){
                canPlay = false;
            }
            if ( next_class_at < now) {
                between_classes = false;
                return;
            }
            if(aInfo.clockStyle == MINUTES)
            snprintf(outline, 80, "Next Class In:\n%d Minutes",next_class_at - now);
            else
            snprintf(outline, 80, "Next Class In:\n%02d:%02d",next_class_at - now,60-seconds);
            text_layer_set_text(text_time_period_info, outline);
            
            if (now == next_class_at){
                between_classes = false;
                canPlay = true;
            }
            return;
        }
        
        if (day == SATURDAY || day == SUNDAY  || (day == FRIDAY && now > school_end)) {
            text_layer_set_text(text_time_period_info, "Weekend");
            
        }
        else if (now >= school_start && now <= school_end) {
            text_layer_set_text(text_time_period_info, outline);
            for (unsigned int i = 0; i < INFO_SIZE; i++) {
                if ((now >= pinfo[i].start) && (now <= pinfo[i].end)) {
                    if(aInfo.clockStyle == MINUTES)
                    snprintf(outline, 80, "%s:\n%d minutes left\n", cNames[i].className, pinfo[i].end - now);
                    else
                    snprintf(outline, 80, "%s:\n%02d:%02d", cNames[i].className, pinfo[i].end - now,60-seconds);
                    break;
                    
                }
                else if ((now > pinfo[i].end) && (now <= pinfo[i].end+5)) {
                    between_classes = true;
                    next_class_at = pinfo[i].end + 5;
                    if(aInfo.clockStyle == MINUTES)
                    snprintf(outline, 80, "Next Class In:\n%d Minutes",next_class_at - now);
                    else
                    snprintf(outline, 80, "Next Class In:\n%02d:%02d",next_class_at - now,60-seconds);
                    text_layer_set_text(text_time_period_info, outline);
                    break;
                }
            }
            text_layer_set_text(text_time_period_info, outline);
            } else {
            if (now >= school_end) {
                time_to_school = (24 * 60) - now + ((7 * 60) + 25);
                } else if (now <= school_start) {
                time_to_school = school_start - now;
            }
            int afterhours = time_to_school / 60;
            int afterminutes = time_to_school % 60;
            if (afterhours > 0) {
                if(aInfo.clockStyle == MINUTES)
                snprintf(outline, 80, "School in:\n%d hours\n%d minutes",afterhours, afterminutes);
                else
                snprintf(outline, 80, "School in:\n%d:%02d:%02d",afterhours, afterminutes,60-seconds);
                } else {
                if(aInfo.clockStyle == MINUTES)
                snprintf(outline,80,"School in:\n%d minutes", afterminutes);
                else
                snprintf(outline,80,"School in:\n%02d:%02d", afterminutes,60-seconds);
                
            }
            if (day == FRIDAY && now >= school_end)
            text_layer_set_text(text_time_period_info, "School's out!");
            else
            text_layer_set_text(text_time_period_info, outline);
        }
    }
}

//Bluetooth Connection loss vibration. Change this if you want a different vibration when bluetooth lost.
static const uint32_t segments[] = { 400, 100, 400, 100, 400};
VibePattern pat = {
    .durations = segments,
    .num_segments = ARRAY_LENGTH(segments),
};



//Bluetooth handler. There shouldn't be a need to mess with this.
void handle_bluetooth_change(bool isconnected){
	printf("Bluetooth Connected: %d",isconnected);
	printf("Bluetooth alarm: %d",aInfo.alarm);

	reset_bluetooth_frame();
	if(isconnected){
		aInfo.alarmRung = NO;
		text_layer_set_text(text_bluetooth_info,"B");
	}else{
		text_layer_set_text(text_bluetooth_info," ");
		
	}
	if(aInfo.alarm == YES && !isconnected && aInfo.alarmRung==NO){
		printf("HERE");
		vibes_enqueue_custom_pattern(pat);
		text_layer_set_text(text_bluetooth_info,"LOST");

		#ifdef PBL_RECT
		layer_set_frame(text_layer_get_layer(text_bluetooth_info), GRect(106, 0, 144 - 7, 90));
		#endif
		aInfo.alarmRung = YES;

	}
	
	if(aInfo.bluetooth == NO)
    layer_set_hidden(text_layer_get_layer(text_bluetooth_info), true);
    else
    layer_set_hidden(text_layer_get_layer(text_bluetooth_info), false);
    #ifdef PBL_ROUND
    if(firstblue == false){
        if(aInfo.bluetooth == YES){
            layer_set_frame(text_layer_get_layer(text_battery_info), GRect(18, 14, 180, 180));
            }else{
            layer_set_frame(text_layer_get_layer(text_battery_info), GRect(0, 14, 180, 180));
        }
    }
	#endif
}

//Battery handler. There shouldn't be a need to mess with this.
void handle_battery_change(BatteryChargeState b) {
    static char outline[40];
    if(b.is_charging){
        text_layer_set_text(text_battery_info, "Charging");
        } else if(b.charge_percent == 100){
        text_layer_set_text(text_battery_info, "Charged");
    }
    else{
        #ifdef PBL_RECT
        snprintf(outline,sizeof(outline),"%d%% ",b.charge_percent);
        #elif PBL_ROUND
        if(aInfo.bluetooth == NO)
        snprintf(outline,sizeof(outline),"%d%% ",b.charge_percent);
        else
        snprintf(outline,sizeof(outline),"       %d%% ",b.charge_percent);
        #endif
        text_layer_set_text(text_battery_info,outline);
        
    }
    if(aInfo.battery == NO)
    text_layer_set_text(text_battery_info," ");
    
}


//Configuration handlers start
void in_dropped_handler(AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Message Dropped!");
}


void set_batery_bluetooth(){
    battery_state_service_subscribe(handle_battery_change);
    handle_battery_change(battery_state_service_peek());
    bluetooth_connection_service_subscribe(handle_bluetooth_change);
    handle_bluetooth_change(bluetooth_connection_service_peek());
}

void update_clock(){
    if (aInfo.clockStyle == MINUTES){
        tick_timer_service_unsubscribe();
        tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
    }
    else{
        tick_timer_service_unsubscribe();
        tick_timer_service_subscribe(SECOND_UNIT, handle_tick);
    }
    
    
    if(aInfo.clockStyle == MINUTES){
        text_layer_set_font(text_time_period_info,
        fonts_load_custom_font(
        resource_get_handle(
        RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_17)));
        
        }else{
        #ifdef PBL_RECT
        text_layer_set_font(text_time_period_info,
        fonts_load_custom_font(
        resource_get_handle(
        RESOURCE_ID_FONT_ROBOTO_CONDENSED_REGULAR_SUBSET_22)));
        #endif
    }
}

void update_school_day(){
    switch (aInfo.schoolDay) {
        case NORMAL:
        pinfo        = normalInfo;
        school_start = NORMAL_START;
        school_end   = NORMAL_END;
        APP_LOG(APP_LOG_LEVEL_ERROR, "NORMAL");
        
        break;
        case DELAY:
        pinfo        = delayInfo;
        school_start = DELAY_START;
        school_end   = DELAY_END;
        APP_LOG(APP_LOG_LEVEL_ERROR, "DELAYr");
        
        break;
        case RELEASE:
        pinfo = earlyRelInfo;
        school_start = EARLY_REL_START;
        school_end = EARLY_REL_END;
        APP_LOG(APP_LOG_LEVEL_ERROR, "RELEASE");
        
        break;
        default:
        APP_LOG(APP_LOG_LEVEL_ERROR, "MODE Error");
        break;
    }
    
    
}

void update_colors(){
    #ifdef PBL_COLOR
    window_set_background_color(window, GColorFromHEX(aInfo.backColor));
    text_layer_set_text_color(text_date_layer, GColorFromHEX(aInfo.dateColor));
    text_layer_set_text_color(text_day_layer, GColorFromHEX(aInfo.dateColor));
    text_layer_set_text_color(text_time_layer, GColorFromHEX(aInfo.timeColor));
    text_layer_set_text_color(text_time_period_info, GColorFromHEX(aInfo.periodColor));
    text_layer_set_text_color(text_battery_info, GColorFromHEX(aInfo.batColor));
    text_layer_set_text_color(text_bluetooth_info, GColorFromHEX(aInfo.blueColor));
    #else
    if(aInfo.textColor == WHITE){
        window_set_background_color(window, GColorBlack);
        text_layer_set_text_color(text_date_layer, GColorWhite);
        text_layer_set_text_color(text_day_layer, GColorWhite);
        text_layer_set_text_color(text_time_layer, GColorWhite);
        text_layer_set_text_color(text_time_period_info, GColorWhite);
        text_layer_set_text_color(text_battery_info, GColorWhite);
        text_layer_set_text_color(text_bluetooth_info, GColorWhite);
        
        }else{
        window_set_background_color(window, GColorWhite);
        text_layer_set_text_color(text_date_layer, GColorBlack);
        text_layer_set_text_color(text_day_layer, GColorBlack);
        text_layer_set_text_color(text_time_layer, GColorBlack);
        text_layer_set_text_color(text_time_period_info, GColorBlack);
        text_layer_set_text_color(text_battery_info, GColorBlack);
        text_layer_set_text_color(text_bluetooth_info, GColorBlack);
    }
    #endif
    text_layer_set_background_color(text_date_layer, GColorClear);
    text_layer_set_background_color(text_day_layer, GColorClear);
    text_layer_set_background_color(text_time_layer, GColorClear);
    text_layer_set_background_color(text_time_period_info, GColorClear);
    text_layer_set_background_color(text_bluetooth_info, GColorClear);
    text_layer_set_background_color(text_battery_info, GColorClear);
    layer_set_update_proc(top_line_layer, top_line_layer_update_callback);
    layer_set_update_proc(bottom_line_layer, bottom_line_layer_update_callback);
}

void in_received_handler(DictionaryIterator *received, void *context) {
    vibes_double_pulse();
    for(int x = 0;x<8;x++){
        Tuple *Name = dict_find(received, 21+x);
        if(strcmp(Name->value->cstring, "") == 0){
            char temp[40];
            snprintf(temp,sizeof(temp),"Period %d",x+1);
            strcpy(cNames[x].className,temp);
        }else
        strcpy(cNames[x].className,Name->value->cstring);
    }
	
	
    
    Tuple *sDay = dict_find(received, 29);
    Tuple *wMode = dict_find(received, 30);
    //    Tuple *tColorc = dict_find(received, 48);
    Tuple *blue = dict_find(received, 32);
    Tuple *bluea = dict_find(received, 36);
    Tuple *bat = dict_find(received, 33);
    //Tuple *brk = dict_find(received, 49);
    Tuple *boot = dict_find(received, 37);
    
    Tuple *dcolor = dict_find(received, 41);
    Tuple *lcolor = dict_find(received, 42);
    Tuple *tcolor = dict_find(received,43);
    Tuple *batcolor = dict_find(received, 44);
    Tuple *bluecolor = dict_find(received, 45);
    Tuple *backcolor = dict_find(received, 46);
    Tuple *periodcolor = dict_find(received, 47);
    
    if(strcmp(sDay->value->cstring, "Normal") == 0){
        printf("normal");
        aInfo.schoolDay = 0;
        }else if(strcmp(sDay->value->cstring, "Early Release") == 0){
        printf("Early Release");
        aInfo.schoolDay = 1;
        }else if(strcmp(sDay->value->cstring, "Delay") == 0){
        printf("Delay");
        aInfo.schoolDay = 2;
        }else if(strcmp(sDay->value->cstring, "Break") == 0){
        printf("Break");
        aInfo.schoolDay = 3;
        } else{
        printf("Day Error");
    }
    
    if(aInfo.schoolDay == 3){
        aInfo.break_mode = YES;
        }else{
        aInfo.break_mode = NO;
    }
    
    if(strcmp(wMode->value->cstring, "Minutes") == 0){
        printf("Minutes");
        aInfo.clockStyle = MINUTES;
        }else if(strcmp(wMode->value->cstring, "Seconds") == 0){
        printf("Seconds");
        aInfo.clockStyle = SECONDS;
        }else{
        printf("Watch Mode Error");
    }
    
    if(strcmp(blue->value->cstring, "Yes") == 0){
        printf("Bluetooth On");
        aInfo.bluetooth = YES;
        }else if(strcmp(blue->value->cstring, "No") == 0){
        printf("Bluetooth Off");
        aInfo.bluetooth = NO;
        }else{
        printf("Bluetooth Error");
    }
    
    if(strcmp(bluea->value->cstring, "Yes") == 0){
        printf("Bluetooth Alarm On");
        aInfo.alarm = YES;
        }else if(strcmp(bluea->value->cstring, "No") == 0){
        printf("Bluetooth Alarm Off");
        aInfo.alarm = NO;
        }else{
        printf("Bluetooth Alarm Error");
    }
    
    if(strcmp(bat->value->cstring, "Yes") == 0){
        printf("Battery On");
        aInfo.battery = YES;
        }else if(strcmp(bat->value->cstring, "No") == 0){
        printf("Battery Off");
        aInfo.battery = NO;
        }else{
        printf("Battery Error");
    }
	
	if(strcmp(boot->value->cstring, "Yes") == 0){
        printf("Boot On");
        aInfo.boot = YES;
        }else if(strcmp(boot->value->cstring, "No") == 0){
        printf("Boot Off");
        aInfo.boot = NO;
        }else{
        printf("Boot Error");
    }
    
    aInfo.backColor = backcolor->value->int32;
    aInfo.dateColor = dcolor->value->int32;
    aInfo.timeColor = tcolor->value->int32;
    aInfo.periodColor = periodcolor->value->int32;
    aInfo.lineColor = lcolor->value->int32;
    aInfo.batColor = batcolor->value->int32;
    aInfo.blueColor = bluecolor->value->int32;
    
    update_colors();
    set_batery_bluetooth();
    update_school_day();
    update_clock();
}

void read_config() {
    if(persist_exists(34)){
        persist_read_data(34,&aInfo,sizeof(aInfo));
        update_school_day();
        
        }else{
        aInfo.bluetooth = YES;
        aInfo.battery = YES;
        #ifdef PBL_COLOR
        aInfo.backColor = 0x000000;
        aInfo.dateColor = 0xFFFFFF;
        aInfo.lineColor = 0xFFFFFF;
        aInfo.timeColor = 0xFFFFFF;
        aInfo.batColor = 0xFFFFFF;
        aInfo.blueColor = 0xFFFFFF;
        aInfo.periodColor = 0xFFFFFF;
        #else
        aInfo.textColor = WHITE;
        #endif
        
    }
    
    
    if(persist_exists(35)){
        persist_read_data(35,cNames,sizeof(cNames));
        }else{
        //change the x<8 to however many classes you have.
        for(int x = 0;x<8;x++){
            char temp[40];
            snprintf(temp,sizeof(temp),"Period %d",x+1);
            strcpy(cNames[x].className,temp);
            
        }
    }
}


//Appmessage for receiving js code.
static void app_message_init(void) {
    app_message_register_inbox_received(in_received_handler);
    app_message_register_inbox_dropped(in_dropped_handler);
    app_message_open(app_message_inbox_size_maximum(),app_message_inbox_size_maximum());
    
}

//Watchface close handler
void handle_deinit(void) {
    persist_write_data(34, &aInfo, sizeof(aInfo));
    persist_write_data(35, cNames,sizeof(cNames));// Saves class names
    tick_timer_service_unsubscribe();
    window_destroy(window);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Deinit Saved!");
    
    
}


#ifdef PBL_ROUND
// Set the color for drawing routines
static void set_color(GContext *ctx, GColor color) {
    graphics_context_set_fill_color(ctx, color);
}

// Update the watchface display
static void update_display(Layer *layer, GContext *ctx) {
    set_color(ctx, GColorFromHEX(aInfo.timeColor));
    draw_seconds(ctx, seconds, layer);
}
#endif

// Initial Init handler
void handle_init(void) {
    window = window_create();
    window_stack_push(window, true);
    window_set_background_color(window, GColorWhite);
    
    Layer *window_layer = window_get_root_layer(window);
    app_message_init();
    read_config();
    //Date
    text_date_layer = text_layer_create(GRect(350, 54, 144 - 6, 30));
    text_layer_set_text_color(text_date_layer, GColorBlack);
    text_layer_set_background_color(text_date_layer, GColorClear);
    text_layer_set_font(text_date_layer,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_19)));
    layer_add_child(window_layer, text_layer_get_layer(text_date_layer));
    
    //DAY
    text_day_layer = text_layer_create(GRect(350, 34, 144 - 6, 30));
    text_layer_set_text_color(text_day_layer, GColorBlack);
    text_layer_set_background_color(text_day_layer, GColorClear);
    text_layer_set_font(text_day_layer,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_17)));
    layer_add_child(window_layer, text_layer_get_layer(text_day_layer));
    
    //time
    text_time_layer = text_layer_create(GRect(-200,70, 144 - 7, 55));
    text_layer_set_text_color(text_time_layer, GColorBlack);
    text_layer_set_background_color(text_time_layer, GColorClear);
    text_layer_set_font(text_time_layer,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_36)));
    layer_add_child(window_layer, text_layer_get_layer(text_time_layer));
    
    //Period
    text_time_period_info = text_layer_create(GRect(2, 300, 144 - 7, 90));
    text_layer_set_text_color(text_time_period_info, GColorBlack);
    text_layer_set_background_color(text_time_period_info, GColorClear);
    text_layer_set_font(text_time_period_info,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_19)));
    layer_add_child(window_layer, text_layer_get_layer(text_time_period_info));
    //Battery
    text_battery_info = text_layer_create(GRect(70, -1000, 144 - 7, 90));
    text_layer_set_text_color(text_battery_info, GColorBlack);
    text_layer_set_background_color(text_battery_info, GColorClear);
    text_layer_set_font(text_battery_info,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_16)));
    text_layer_set_text(text_battery_info, " ");
    layer_add_child(window_layer, text_layer_get_layer(text_battery_info));
    
    //BLUETOOTH
    text_bluetooth_info = text_layer_create(GRect(-10, -100, 48, 48));
    text_layer_set_text_color(text_bluetooth_info, GColorBlack);
    text_layer_set_background_color(text_bluetooth_info, GColorClear);
    text_layer_set_font(text_bluetooth_info,
    fonts_load_custom_font(
    resource_get_handle(
    RESOURCE_ID_FONT_ROBOTO_CONDENSED_SUBSET_16)));
    layer_add_child(window_layer, text_layer_get_layer(text_bluetooth_info));
    text_layer_set_text(text_bluetooth_info, " ");
    
    GRect top_line_frame = GRect(200, 76, 180, 2);
    GRect bottom_line_frame = GRect(-200, 108, 180, 2);
    top_line_layer = layer_create(top_line_frame);
    bottom_line_layer = layer_create(bottom_line_frame);
    layer_set_update_proc(top_line_layer, top_line_layer_update_callback);
    layer_set_update_proc(bottom_line_layer, bottom_line_layer_update_callback);
    layer_add_child(window_layer, top_line_layer);
    layer_add_child(window_layer, bottom_line_layer);
    update_colors();
    set_batery_bluetooth();
    update_clock();
    firstblue = false;
	if(aInfo.boot == YES){
    #ifdef PBL_RECT
    boot_animation();
    #elif PBL_ROUND
    round_boot_animation();
    #endif
	}else{
	#ifdef PBL_RECT
    show_rect();
    #elif PBL_ROUND
    show_round();
    #endif
	}
    if (aInfo.clockStyle == MINUTES){
        tick_timer_service_unsubscribe();
        tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
    }
    else{
        tick_timer_service_unsubscribe();
        tick_timer_service_subscribe(SECOND_UNIT, handle_tick);
    }
    
    
    #ifdef PBL_ROUND
    s_layer = layer_create(layer_get_bounds(window_get_root_layer(window)));
    layer_add_child(window_get_root_layer(window), s_layer);
    layer_set_update_proc(s_layer, update_display);
    #endif
    
    
}

//Main
int main(void) {
    handle_init();
    
    app_event_loop();
    
    handle_deinit();
}