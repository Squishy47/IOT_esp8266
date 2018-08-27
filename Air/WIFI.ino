void setupWifi(){
    if(wifiManager.autoConnect(deviceID)){
        Serial.println("Wifi connected.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.println("failed to connect and hit timeout");
        ESP.reset();
        delay(5000);
    }
}
