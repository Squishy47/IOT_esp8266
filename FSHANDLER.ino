
// not currently used as it causes a crash and boot loop
void saveDataToFile(){
    Serial.println("Saving params...");
    
    JsonObject& json = jsonBuffer.createObject();
    json["ID"]          = deviceID;
    json["Type"]        = deviceType;
    json["name"]        = deviceName;
    json["location"]    = deviceLocation;
    json["email"]       = userEmail;

    File configFile = SPIFFS.open("/config.json", "w");
    
    if (!configFile) 
        Serial.println("failed to open config file for writing");
    
    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
}
