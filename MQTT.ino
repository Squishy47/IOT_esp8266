void MQTT_connect() {
    if (mqtt.connected())
        return;
        
    int ret;
    int retries = 3;
    
    Serial.print("Connecting to MQTT... ");
    
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       
       if (retries == 0)
            while (1);
    }
    Serial.println("MQTT Connected!");
}

void transmitJsonData(JsonObject& data){
    Serial.println("Transmitting data...");
    
    String sPayload = "";
    data.printTo(sPayload);
    char* cPayload = &sPayload[0u];

    if(!temperaturePub.publish(cPayload))
        Serial.println("Transmit failed!");
    else
        Serial.println("Transmit successful.");
}
