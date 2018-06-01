/*
 * main.cpp
 *
 *  Created on: Oct 27, 2017
 *      Author: cui
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include <assert.h>
#include <alsa/asoundlib.h>
#include <sys/poll.h>
#include <stdint.h>
#include "volume.h"

#define DBG_EN		1
#if(DBG_EN == 1)
#define printf_dbg(x,arg...) printf("[Main_debug]"x,##arg)
#else
#define printf_dbg(x,arg...)
#endif

#define printf_info(x,arg...) printf("[Main_info]"x,##arg)
#define printf_warn(x,arg...) printf("[Main_warn]"x,##arg)
#define printf_err(x,arg...) printf("[Main_err]"x,##arg)

int get_current_sound_level( long &value );

int set_sound_level2system( int level );

int main(int argc, char *argv[])
{
	int ret;
	int volume_level = -1;
	long curr_volume = -1;

	if( argc != 2 || ( strlen(argv[1]) != 1 )){
			printf_err( "Usage: %s < 1-8 >\n", argv[0] );
			return -1;
		}
	if( strcmp(argv[1], "1" ) == 0 ) volume_level = 1;
	else if( strcmp(argv[1], "2" ) == 0 ) volume_level = 2;
	else if( strcmp(argv[1], "3" ) == 0 ) volume_level = 3;
	else if( strcmp(argv[1], "4" ) == 0 ) volume_level = 4;
	else if( strcmp(argv[1], "5" ) == 0 ) volume_level = 5;
	else if( strcmp(argv[1], "6" ) == 0 ) volume_level = 6;
	else if( strcmp(argv[1], "7" ) == 0 ) volume_level = 7;
	else if( strcmp(argv[1], "8" ) == 0 ) volume_level = 8;
	else volume_level = -1;

	if( volume_level == -1 ){
		printf_err( "Usage: %s < 1-8 >\n", argv[0] );
		return -1;
	}

	ret = set_sound_level2system( volume_level );
	if( ret < 0 ){
		printf_err( "Set volume to system failed\n" );
	}
	printf( "Set volume to system success\n" );
	system( "aplay /root/music/codeok.wav" );

	ret = get_current_sound_level( curr_volume );
	if( ret < 0 ){
		printf_err( "Get volume from system failed\n" );
	}
	printf( "Get volume from system success, current volume:%li\n", curr_volume );

	printf_dbg( "main exit success\n" );
	return 0;
}

int get_current_sound_level( long &value )
{
	int ret;
	char *get_argument[] = {
				"numid=1,iface=MIXER,name='MERCURY Playback Volume'",
			};

	ret = cset(3, get_argument, 1, 0, value );
	if( (ret != 0) || (value == -1)){
		printf_err( "Get argument error\n" );
		return -1;
	}
	printf_dbg( "get volume success\n" );
	return 0;
}

int set_sound_level2system( int level )
{
	int ret;
	long useless = 0;
	char volume_size[3] = "30";
	if( level > 8 || level < 1 ){
			printf_err( "set sound level error:%d, not in 1-8 \n", level );
			return -1;
		}

	printf_dbg( "volume level = %d\n", level );
	switch( level ){	// 2, 10, 18, 26, 34, 42, 50, 58
	case 1:
		strcpy( volume_size, "2" );
		break;
	case 2:
		strcpy( volume_size, "10" );
		break;
	case 3:
		strcpy( volume_size, "18" );
		break;
	case 4:
		strcpy( volume_size, "26" );
		break;
	case 5:
		strcpy( volume_size, "34" );
		break;
	case 6:
		strcpy( volume_size, "42" );
		break;
	case 7:
		strcpy( volume_size, "50" );
		break;
	case 8:
		strcpy( volume_size, "58" );
		break;
	default:
		printf_err( "vol_level error, not equal 1-8 \n" );
		return -1;
	}

	char * set_argument[] ={
				"numid=1,iface=MIXER,name='MERCURY Playback Volume'",
				volume_size,
			};

	printf( "After copy set_argument[0] = %s\n" "After copy set_argument[1] = %s\n", set_argument[0], set_argument[1] );

	ret = cset(4, set_argument, 0, 0, useless);
	if( ret != 0 ){
		printf_err( "Set argument error\n" );
		return -1;
	}
	printf_dbg( "set volume success, level: %d, volume: %li\n", level, useless );

	return 0;
}
