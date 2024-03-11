// #include <Wire.h>

// const byte PinVcc = 5;
// const byte PinGnd = 18;
// const byte PinScl = 19;
// const byte PinSda = 21;

void setupI2c()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nI2C Scanner");

  // pinMode(PinGnd, OUTPUT);
  // digitalWrite(PinGnd, LOW);
  
  // pinMode(PinVcc, OUTPUT);
  // digitalWrite(PinVcc, HIGH);

  // delay(100);

  Wire.begin(PinSda, PinScl);
}

void loopI2c()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(1000);  // wait for next scan
}
