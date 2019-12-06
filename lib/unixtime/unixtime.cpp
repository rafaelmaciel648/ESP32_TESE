#include "unixtime.h"
#include <WiFi.h>
#include <time.h>
#include "myutils.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

/** WIFI settings **/
const char* ssid       = "RUFFIEoMalvado";
const char* password   = "esquadraofirmeza";

/*****Constants to get Unixtimestamp from NTP server*****/
// const char* ntpServer = "pool.ntp.org";     // NTP server
const long  gmtOffset_sec = 0;              // UTC time offset
// const int   daylightOffset_sec = 3600;      // Daylight offset (summer time)
/********************************************************/

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


unsigned long unixtime(){						// NOTA: LIGAR WIFI CASO DESLIGADO
	unsigned long epoch_unix;

	Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");

	timeClient.begin();

	timeClient.setTimeOffset(gmtOffset_sec);

	while(!timeClient.update()) {
		timeClient.forceUpdate();
	}

	epoch_unix = timeClient.getEpochTime();

	#ifdef DEBUG
		Serial.print("Epoch Unix time: "); Serial.println(epoch_unix);
	#endif

	//disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);

	return epoch_unix;
}