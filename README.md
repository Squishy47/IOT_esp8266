# IOT_esp8266
Read dht11 temp and hum data, create a json object and send json from esp8266/nodeMCU to mqtt broker.

The data will send as a string, to convert the string to valid JSON in Node.js use:```JSON.parse(incomingJsonString)```

This sketch utilises the wifiManager library. 
If it can't connect to wifi then it will open a Wifi AP. Connect to it and either, signin to the wifi on phone, or go to 192.168.4.1 in browser and follow on-screen instructions.
