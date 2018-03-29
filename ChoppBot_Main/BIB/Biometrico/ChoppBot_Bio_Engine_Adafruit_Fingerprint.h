

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(12, 13);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
