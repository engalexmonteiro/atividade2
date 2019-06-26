/*
 * cli.cpp
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#include <Arduino.h>
#include "cli.h"
#include "configs.h"



int command_cli(String command){

	char buffer[30];

	strcpy_P(buffer, (char *)LED13);
	if(command.equals(String(buffer) + '\r')){
			digitalWrite(13,!digitalRead(13));
			return 0;
	}

	strcpy_P(buffer, (char *)TEMPMAX);
	if(command.equals(String(buffer) + '\r')){
			Serial.print(temp_max);
			return 0;
	}

	strcpy_P(buffer, (char *)TEMPMAX);
	if(command.startsWith(String(buffer) + "=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}

	strcpy_P(buffer, (char *)UNKN);
	Serial.print(String(buffer) + command);

	return -1;
}


int cli_init(){

	String command;

	if(Serial.available()){
		command = Serial.readStringUntil('\n');

		command_cli(command);

		char buffer[30];
		strcpy_P(buffer, (char *)SMARTTEMP);
		Serial.print(buffer);

	}

	return 0;
}


