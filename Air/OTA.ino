void otaHandler(){
    #ifdef DEBUG
        ArduinoOTA.onStart([]() {
            Serial.println("Fetching Update...");

            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";
            
            Serial.println("Start updating " + type);
        });
        
        ArduinoOTA.onEnd([]() {
            Serial.println("\nEnd");
            ESP.reset();
        });
        
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        });
        ArduinoOTA.onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) 
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) 
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) 
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) 
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) 
                Serial.println("End Failed");
        });
        ArduinoOTA.begin();
    #else
        Serial.println("Fetching Update...");

        t_httpUpdate_return ret = ESPhttpUpdate.update(updateServerURL);
    
        switch (ret) {
          case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;
    
          case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            break;
    
          case HTTP_UPDATE_OK:
            Serial.println("HTTP_UPDATE_OK");
            ESP.reset();
            break;
        }
    #endif

    delay(1000);
}
