/* SIGFOX_H */

#ifndef SIGFOX_H
#define SIGFOX_H

#include <Arduino.h>

#define SIGFOX_DEBUG

#ifdef __cplusplus
extern "C" {
#endif

class NetworkDevice{
    public:
        /**
         * Begin the serial communication between device and the Sigfox module.
         * Set baudrate to 9600 and 100ms timeout.
         */
        void begin(void);

        /**
         * Get the baudrate of communication.
         * @return 	baudrate
         */
        uint32_t getbaud(void);

        /**
         * Function to blink LED of waiting answer.
         */
        void blink(void);

        /**
         * Read data from the serial port.
         * @return 	String with data.
         */
		String getData(void);

        /**
         * Sends dummy/check command to Sigfox module and checks for "OK" response.
         * @return	true if answer is "OK", false otherwise;
         */
		bool ready(void);

        /**
         * Get the module ID.
         * @return String with the ID;
         */
        String getID(void);

        /**
         * Get the module PAC number.
         * @return String with the PAC;
         */
        String getPAC(void);


		bool send(const void* payload, uint8_t size);

        bool sendString(String str, uint8_t size);

        /**
         * Sets the power mode
         * @param mode  power mode to be set.
         * 				0: software reset (settings will be reset to values in flash)
         *				1: sleep (send a break to wake up)
         *				2: deep sleep (toggle GPIO9 or RESET_N pin to wake up; all settings will be reset)
         * @return true if mode corrected setted
         */
        bool setPower(uint8_t mode);

        /**
         * Enter in sleep mode. Need Serial break to wake up;
         */
        void lightSleep(void);

        /**
         * Enter deep sleep mode. Need to toogle GPIO9 or RESET_N pin to wake up;
         */
        void deepSleep(void);

        /**
         * Wake up function. Reset the module;
         */
        void wakeUpDeepSleep(void);
    
        /**
         * Get radio power transmision
         * @return power in dBm
         */
        uint8_t getRadioOutPower(void);


        uint8_t setRadioOutPower(uint8_t power);

        /**
         * Reset Sigfox module with settings in the flash
         */
        void resetDevice(void);

        void hardwareResetDevice(void);

    private:
        HardwareSerial sigfox = HardwareSerial(2);
};


#ifdef __cplusplus
}
#endif

#endif

/*
TODO:
-review functions:
    send
    sendString

-implement:
    sigfox__get_tx_freq();
    sigfox__get_rx_freq();
    reset
    buildMessages()
*/