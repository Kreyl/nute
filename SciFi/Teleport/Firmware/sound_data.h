/* 
 * File:   sound_data.h
 * Author: Kreyl Laurelindo
 *
 * Created on 3 ���� 2011 �., 19:52
 */

#ifndef SOUND_DATA_H
#define	SOUND_DATA_H

#include <inttypes.h>

#ifdef __cplusplus
 extern "C" {
#endif

//#define DEBUG_SHORT_SOUND
     
#ifdef DEBUG_SHORT_SOUND
    #define SND1_LEN    9
#else
    #define SND1_LEN    21683
#endif

extern const uint16_t Snd1[SND1_LEN];



#ifdef __cplusplus
}
#endif

#endif	/* SOUND_DATA_H */

