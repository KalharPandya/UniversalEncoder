#include <UniversalEncoder.h>
UniversalEncoder Enc(2,3);
UniversalEncoder NegativeEnc(4,5,-1);

void setup() {
  Serial.begin(115200);
  Enc.directional_offset = 1;//optional
}

void loop() {
  
  Serial.println(Enc.getReadings());
  if(millis()>20000){
    Enc.setReadings(20);
  }

  if(millis()>40000){
    Enc.reset();
  }
  // put your main code here, to run repeatedly:

}