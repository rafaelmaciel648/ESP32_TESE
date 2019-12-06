#include "sigfox.h"
#include "myutils.h"

#ifndef LED_TEST
    #define LED_TEST 13
#endif

#ifndef WAKEUP_PIN
	#define WAKEUP_PIN 12
#endif


#define SIGFOX_FRAME_LENGTH 12

/**
 * Command array
 */
const char *sigfox_AT_cmd[] = {
	"AT",                       // Dummy command / check status
	"AT$SB=",                 	// Send Bit (and downlink flag)
	"AT$SF=",    	            // Send Frame (and bit)
	"AT$SO",                    // send out-of-band message
	"ATS%u?",                   // get register
	"ATS%u=",                 	// set register
	"AT$IF=",                 	// set TX frequency
	"AT$IF?",                   // get TX frequency
	"AT$DR=",                 	// set RX frequency
	"AT$DR?",                   // get RX frequency
	"AT$T?",                    // get temperature
	"AT$V?",                    // get voltages
	"AT$I=",                  	// get chip information
	"AT$P=",          	        // set power module
	"AT$WR",                    // save config
	"AT:P%u?",                  // get gpio pin
	"AT:P%u=?",                 // get gpio pin range
	"AT:P%u=%s",                // set gpio pin mode
};

/**
 * Commands as indexes into command array above.
 * Commands defined here are implemented, the rest is not (yet)
 */
typedef enum {
	CMD_STATUS = 0,
	CMD_SEND_FRAME = 2,
	CMD_GET_REGISTER = 4,
	CMD_SET_REGISTER = 5,
	CMD_GET_TX_FREQ = 7,
	CMD_GET_RX_FREQ = 9,
	CMD_INFORMATION = 12,
	CMD_SET_POWER_MODE = 13
}sigfox_AT_cmd_index;

/**
 * Power modes.
 */
typedef enum {
  SIGFOX_POWER_RESET = 0,
  SIGFOX_POWER_SLEEP = 1,
  SIGFOX_POWER_DEEPSLEEP = 2
} sigfox_power_mode_t;


void NetworkDevice::begin(void){
    sigfox.begin(9600);
	sigfox.setTimeout(100);
};

uint32_t NetworkDevice::getbaud(void){
    return sigfox.baudRate();
};

void NetworkDevice::blink(void){
    digitalWrite(LED_TEST, 1);
	delay(50);
	digitalWrite(LED_TEST, 0);
	delay(50);
}

String NetworkDevice::getData(void){
	String data = "";
	char output;

	while (!sigfox.available()){
		blink();
	}

	while(sigfox.available()){
		output = sigfox.read();
		if ((output != 0x0A) && (output != 0x0D)){//0x0A Line feed | 0x0D Carriage return
			data += output;
    	}
		delay(10);
	}	

	#ifdef DEBUG
		Serial.print("Data: ");
		Serial.println(data);
	#endif

	return data;
}

bool NetworkDevice::ready(void){
	String cmd = String(sigfox_AT_cmd[CMD_STATUS]);
	sigfox.print(cmd + "\r\n");
	String status = getData();

	#ifdef DEBUG
		Serial.print("Status: ");
		Serial.println(status);
	#endif

	return status.equals("OK");
}

String NetworkDevice::getID(void){
	String cmd = String(sigfox_AT_cmd[CMD_INFORMATION]);
	sigfox.print(cmd + "10\r\n");
	String id = getData();

	#ifdef DEBUG
		Serial.print("ID: ");
		Serial.println(id);
	#endif

	return id;
}

String NetworkDevice::getPAC(void){
	String cmd = String(sigfox_AT_cmd[CMD_INFORMATION]);
	sigfox.print(cmd + "11\r\n");
	String pac = getData();

	#ifdef DEBUG
		Serial.print("PAC: ");
		Serial.println(pac);
	#endif

	return pac;
}

bool NetworkDevice::send(const void* payload, uint8_t size){
	if( size > SIGFOX_FRAME_LENGTH ){
		#ifdef DEBUG
			Serial.println("BUFFER TO SEND IS OVERSIZE");
		#endif
		return false;
	}

	String frame = "";

	if( size < SIGFOX_FRAME_LENGTH ){		// fill with zeros
		uint8_t i = SIGFOX_FRAME_LENGTH;
    	while(i > size){
      		frame += "00";
			i--;
    	}
	}

	uint8_t* bytes = (uint8_t*)payload;

	for(uint8_t i = size-1; i < size; i--) {
		if (bytes[i] < 16){
			frame += "0";
		}
		frame += String(bytes[i], HEX);
	}

	#ifdef DEBUG
		Serial.print("FRAME: ");
		Serial.println(frame);
	#endif

	String cmd = String(sigfox_AT_cmd[CMD_SEND_FRAME]);

	sigfox.print(cmd + frame + "\r\n");

	while (!sigfox.available()){
		blink();
	}

	String res = getData();

	if(res.indexOf("OK") >= 0) {
		#ifdef DEBUG
			Serial.println("MESSAGE SENT");
		#endif
		return true;
	}

	return false;
}

bool NetworkDevice::sendString(String str, uint8_t size){
	if( size > 24 ){
		#ifdef DEBUG
			Serial.println("STRING TO SEND IS OVERSIZE");
		#endif
		return false;
	}

	String cmd = String(sigfox_AT_cmd[CMD_SEND_FRAME]);

	sigfox.print(cmd + str + "\r\n");

	while (!sigfox.available()){
		blink();
	}

	String res = getData();

	if(res.indexOf("OK") >= 0) {
		#ifdef DEBUG
			Serial.println("STRING SENT");
		#endif
		return true;
	}

	return false;
}

bool NetworkDevice::setPower(uint8_t mode){
	if( (mode<0) || (mode>2) ){
		return false;
	}

	String cmd = String(sigfox_AT_cmd[CMD_SET_POWER_MODE]);
	sigfox.print(cmd + mode + "\r\n");
	String status = getData();

	#ifdef DEBUG
		Serial.print("POWER MODE: ");
		Serial.println(status);
	#endif

	return status.equals("OK");
}

void NetworkDevice::lightSleep(void){
	setPower(SIGFOX_POWER_SLEEP);

	#ifdef DEBUG
		Serial.println("SIGFOX SLEEP");
	#endif

	return;
}

void NetworkDevice::deepSleep(void){
	setPower(SIGFOX_POWER_DEEPSLEEP);

	#ifdef DEBUG
		Serial.print("SIGFOX DEEP SLEEP");
	#endif

	return;
}

void NetworkDevice::wakeUpDeepSleep(void){
	pinMode(WAKEUP_PIN, INPUT_PULLDOWN);
	delay(50);
	setPower(SIGFOX_POWER_RESET);

	#ifdef DEBUG
		Serial.println("WAKE SIGFOX");
	#endif

	pinMode(WAKEUP_PIN, INPUT_PULLUP);
	return;
}

uint8_t NetworkDevice::getRadioOutPower(void){
	return 1;
}

uint8_t NetworkDevice::setRadioOutPower(uint8_t power){
	return power;
}

void NetworkDevice::resetDevice(void){
	#ifdef DEBUG
		Serial.println("RESET SIGFOX");
	#endif
	setPower(SIGFOX_POWER_RESET);
	return;
}