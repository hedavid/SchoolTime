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
#define TIME(h,s) ((h*60) + s)

struct periodInfo {
	int period;
	int start;
	int end;
};

/*

Enter the times for the normal bell schedule below.

The structs below are in the following format. 
{period number, START TIME(HOURS,MINUTES), END TIME(HOURS,MINUTES)}
**NOTE THAT THE TIMES ARE IN 24HR
**Period Names are set in the app configuration page. 
*/
struct periodInfo normalInfo[] = { 
  {1, TIME(7,50),  TIME(8,35)},
	{2, TIME(8,45),  TIME(9,30)},
	{3, TIME(9,50),  TIME(10,35)},
	{4, TIME(10,45),  TIME(11,30)},
	{5, TIME(11,55),  TIME(12,40)},
	{6, TIME(12,45),  TIME(13,30)},
	{7, TIME(13,50), TIME(14,35)},
	{8, TIME(14,40), TIME(15,25)}
};
#define INFO_SIZE (sizeof(normalInfo)/sizeof(struct periodInfo))
	

#define NORMAL_START TIME(7,50)//Enter Normal Day Start Time
#define NORMAL_END   TIME(15,25)//Enter Normal Day End Time

	
//The Delay info and early release info follow the same format as what was stated above. 
//If your school does  not have either delay or early release, just leave it alone and don't select it in the config page. 
struct periodInfo delayInfo[] = { 
	{1, TIME(9,45),  TIME(10,15)},
	{2, TIME(10,20),  TIME(10,50)},
	{3, TIME(10,55),  TIME(11,30)},
	{5, TIME(11,35),  TIME(12,10)},
	{4, TIME(12,15),  TIME(12,45)},
	{6, TIME(12,50),  TIME(13,20)},
	{7, TIME(13,25), TIME(13,55)},
	{8, TIME(14,00), TIME(14,30)}
};
#define DELAY_START  TIME(9,45)//Enter Delay Day Start Time
#define DELAY_END    TIME(14,30) //Enter Delay Day End Time

struct periodInfo earlyRelInfo[] = {
	{1, TIME(7,50),  TIME(8,20)},
	{2, TIME(8,30),  TIME(9,00)},
	{3, TIME(9,20),  TIME(9,50)},
	{4, TIME(10,00),  TIME(10,30)},
	{6, TIME(10,50),  TIME(11,20)},
	{7, TIME(11,30),  TIME(12,00)},
	{8, TIME(12,25), TIME(12,55)},
	{5, TIME(13,05), TIME(13,35)}
};
#define EARLY_REL_START TIME(7,50) //Enter Early Release Day Start Time
#define EARLY_REL_END   TIME(13,35) //Enter Early Release Day End Time

struct periodInfo *pinfo = normalInfo;
static int school_start = NORMAL_START;
static int school_end   = NORMAL_END;
