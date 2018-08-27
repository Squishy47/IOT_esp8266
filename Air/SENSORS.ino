JsonObject& getSensorData(){
    Serial.println("Reading sensor data...");
    delay(10);
    float t = dht.readTemperature();
    delay(10);
    float h = dht.readHumidity();

    if(isnan(t))
        t = tempStorage;
    else
        tempStorage = t;
        

    if(isnan(h))
        h = humStorage;
    else
        humStorage = h;

        
    JsonObject& sensorData = jsonBuffer.createObject();
    sensorData["Temperature"] = String(t);
    sensorData["Humidity"] = String(h);

    Serial.println(sensorData["Temperature"].as<char*>());
    Serial.println(sensorData["Humidity"].as<char*>());

    return sensorData;
}
