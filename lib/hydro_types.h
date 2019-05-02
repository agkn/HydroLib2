//
// Created by Andrey on 18.04.2019.
//

#ifndef HYDROLIB2_HYDRO_TYPES_H
#define HYDROLIB2_HYDRO_TYPES_H


#if ARDUINO >= 100
#include <Arduino.h>
typedef unsigned long time_t;
#else
#include <cstdint>
#include <cstdlib>
#include <cstring>
#endif


typedef uint8_t op_id_t;
typedef uint8_t op_result_t;
typedef uint8_t event_id_t;
typedef uint8_t var_id_t;

#ifndef __have_typedef_time_t
//typedef uint32_t time_t;
#endif

#endif //HYDROLIB2_HYDRO_TYPES_H
