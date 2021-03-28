#define ARDUINO AVR
#define ESP_32 ESP_32
#if defined (ESP32)
    #define ESP_32 1
#elif   defined(ARDUINO_AVR_ADK)       
    #define AVR 1
#elif defined(ARDUINO_AVR_BT)    // Bluetooth
     #define AVR 1
#elif defined(ARDUINO_AVR_DUEMILANOVE)       
     #define AVR 1
#elif defined(ARDUINO_AVR_ESPLORA)       
     #define AVR 1
#elif defined(ARDUINO_AVR_ETHERNET)       
     #define AVR 1
#elif defined(ARDUINO_AVR_FIO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_GEMMA)
     #define AVR 1
#elif defined(ARDUINO_AVR_LEONARDO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_LILYPAD)
     #define AVR 1
#elif defined(ARDUINO_AVR_LILYPAD_USB)
     #define AVR 1
#elif defined(ARDUINO_AVR_MEGA)       
     #define AVR 1
#elif defined(ARDUINO_AVR_MEGA2560)       
     #define AVR 1
#elif defined(ARDUINO_AVR_MICRO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_MINI)       
     #define AVR 1
#elif defined(ARDUINO_AVR_NANO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_NG)       
     #define AVR 1
#elif defined(ARDUINO_AVR_PRO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_ROBOT_CONTROL)       
     #define AVR 1
#elif defined(ARDUINO_AVR_ROBOT_MOTOR)       
     #define AVR 1
#elif defined(ARDUINO_AVR_UNO)       
     #define AVR 1
#elif defined(ARDUINO_AVR_YUN)       
     #define AVR 1
#endif


#if defined(AVR)
    #include "libs/Encoder/Encoder.h"
#elif defined(ESP_32)
    #include "libs/ESP32Encoder/src/ESP32Encoder.h"
#endif
class UniversalEncoder{
    public:
    int en1, en2,directional_offset;
    
    #if defined(AVR)
        Encoder *encoder = new Encoder(0,0);
    #elif defined(ESP_32)
        ESP32Encoder *encoder = new ESP32Encoder();
    #endif
    UniversalEncoder(int encoder1,int encoder2, int dirOffset = 1){
        en1 = encoder1;
        en2 = encoder2;
        directional_offset = dirOffset;
        #if defined(AVR)
            encoder = new Encoder(en1,en2);
        #elif defined(ESP_32)
            encoder->attachHalfQuad(en1,en2);    
        	ESP32Encoder::useInternalWeakPullResistors=UP;
        #endif
    }

    double getReadings()
    {
        #if defined(AVR)
            return encoder->read()*directional_offset;
        #elif defined(ESP_32)
            return (long)encoder->getCount()*directional_offset;
        #endif
    }
    void setReadings(long readings){
        #if defined(AVR)
            encoder->write(readings);
        #elif defined(ESP_32)
            encoder->setCount(readings);
        #endif
    }
    void reset()
    {
        setReadings(0);
    }
};