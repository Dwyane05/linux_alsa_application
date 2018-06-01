/*
 * volume.h
 *
 *  Created on: Oct 27, 2017
 *      Author: cui
 */

#ifndef ALSA_ALSA_TEST_VOLUME_H_
#define ALSA_ALSA_TEST_VOLUME_H_

#include <alsa/asoundlib.h>

int cset(int argc, char *argv[], int roflag, int keep_handle, long &vol_value);


#endif /* ALSA_ALSA_TEST_VOLUME_H_ */
