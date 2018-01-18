#line 2 "TelescopeController.ino"
#include <ArduinoUnit.h>

test(simple1)
{
  assertTrue(true);
}


void setup()
{
  Serial.begin(9600);
  while(!Serial); // for the Arduino Leonardo/Micro only
}

void loop()
{
  Test::run();
}
