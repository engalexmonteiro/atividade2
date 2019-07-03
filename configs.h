/*
 * configs.h
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */

#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <Arduino.h>

#define TEMP_MIN 19.00
#define TEMP_MAX 22.00
#define HUM_MIN 60.00
#define HUM_MAX 80.00
#define PERIODI 1000

#define DHTPIN  A1
#define DHTTYPE DHT11

//Parameters
extern bool  en_log;

extern float temp_min;
extern float temp_max;

extern float hum_min;
extern float hum_max;

//
extern float temp_current;
extern float hum_current;

extern const char nameDevice[];
extern const char SMARTTEMP[];
extern const char LOG[];
extern const char TEMP[];
extern const char TEMPMIN[];
extern const char TEMPMAX[];
extern const char HUMMIN[];
extern const char HUMMAX[];
extern const char PERIOD[];
extern const char UNKN[];

extern const char IP[];
extern const char NETMASK[];
extern const char GW[];
extern const char DNS[];

extern byte ip[];
extern byte netmask[];
extern byte gw[];
extern byte dns[];


extern unsigned int period;

String readStringMEM(char WORD[]);
String ipByteToString(byte ip[]);
void print_configs();



#endif /* CONFIGS_H_ */
