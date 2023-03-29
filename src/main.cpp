
/** NimBLE differences highlighted in comment blocks **/

/*******original********
  #include <BLEDevice.h>
  #include <BLEUtils.h>
  #include <BLEScan.h>
  #include <BLEAdvertisedDevice.h>
  #include "BLEEddystoneURL.h"
  #include "BLEEddystoneTLM.h"
  #include "BLEBeacon.h"
***********************/

#include <Arduino.h>

#include <NimBLEDevice.h>
#include <NimBLEAdvertisedDevice.h>
#include "NimBLEEddystoneURL.h"
#include "NimBLEEddystoneTLM.h"
#include "NimBLEBeacon.h"
#include <string>

#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00) >> 8) + (((x)&0xFF) << 8))

int scanTime = 5; //In seconds
BLEScan *pBLEScan;

const int Pin =  25;    // the number of the LED pin


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    /*** Only a reference to the advertised device is passed now
      void onResult(BLEAdvertisedDevice advertisedDevice) { **/
    void onResult(BLEAdvertisedDevice *advertisedDevice)
    {
      String temp = " ";
      if (advertisedDevice->haveName())
      {
        Serial.print("Device name: ");
        temp = advertisedDevice->getName().c_str();
        Serial.println(temp);
        Serial.println("");
      }
     
      //if temo && distance 
      if(temp == "Holy-IOT" ){
        Serial.print("inside holy-IOT if");
      }

      
        // if (advertisedDevice->haveManufacturerData() == true)
        // {
        //   std::string strManufacturerData = advertisedDevice->getManufacturerData();

        //   uint8_t cManufacturerData[100];
        //   strManufacturerData.copy((char *)cManufacturerData, strManufacturerData.length(), 0);

       
         
        //     Serial.println("Found another manusfacturers beacon!");
        //     Serial.printf("strManufacturerData: %d ", strManufacturerData.length());
        //     for (int i = 0; i < strManufacturerData.length(); i++)
        //     {
        //       Serial.printf("[%X]", cManufacturerData[i]);
        //     }
        //     Serial.printf("\n");
          
        // }
        return;
      }

    
};

bool checkShakelConnection(){
      Serial.println("inside check");
      return digitalRead(Pin); // 1 connectd 0 not connectd
}


void setup()
{
  Serial.begin(115200);
  pinMode(Pin, INPUT);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99); // less or equal setInterval value
  
  Serial.println("end init");
}

void loop()
{
  Serial.println("start loop!!");
  // put your main code here, to run repeatedly:
    if(checkShakelConnection()){
        Serial.println("inside if ");
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.println("Scan done!");
    }

  pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
  delay(1000);
}