#include "configs.h"
#include <Arduino.h>
#include <DHT.h>
#include "cli.h"


//Parameters SmartTemp
float temp_min=TEMP_MIN;
float temp_max=TEMP_MAX;
float temp_current=-1;

float hum_min=TEMP_MIN;
float hum_max=TEMP_MAX;
float hum_current=-1;

unsigned int period=PERIODI;

byte ip[]={192,168,1,250};


//SmartTemp objects
DHT dht(DHTPIN, DHTTYPE);

void checktemp(){

	  float h = dht.readHumidity();
	  float t = dht.readTemperature();

	  // testa se retorno é valido, caso contrário algo está errado.
	  if (isnan(t) || isnan(h))
	  {
	    Serial.println("Failed to read from DHT");
	  }
	  else{

		temp_current = t;
		hum_current = h;

/*
		if(temp_current<temp_min)
				Serial.println("A-T: "  + String(t) + " ºC / H " + String(h));
   	    if(temp_current>temp_max)
				Serial.println("L-T "  + String(t) + " ºC / H " + String(h));
*/
		 // print_configs();

	  }

	  delay(period);
}


void setup(){

	Serial.flush();
	Serial.begin(9600);


	dht.begin();

	pinMode(13,OUTPUT);

	pinMode(A0,OUTPUT);
	digitalWrite(A0,HIGH);
	pinMode(A3,OUTPUT);
	digitalWrite(A3,LOW);


}

void loop() {

	//checktemp();

	cli_init();
}
