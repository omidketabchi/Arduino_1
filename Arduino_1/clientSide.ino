#include <ESP8266WiFi.h>

WiFiClient client;
char serverIp[50] = "www.google.com";

#define PORT	80

void setup()
{
	char ssid[32 + 1] = "G1";
	char password[64 + 1] = "12345678";

	Serial.begin(115200);

	WiFi.disconnect();

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);

	}

	Serial.printf("localIp :%s\n", WiFi.localIP().toString().c_str());
	Serial.printf("gatewayIP :%s\n", WiFi.gatewayIP().toString().c_str());
	Serial.printf("subnetMask :%s\n", WiFi.subnetMask().toString().c_str());
	Serial.printf("macAddress :%s\n", WiFi.macAddress().c_str());
	Serial.printf("BSSIDstr :%s\n", WiFi.BSSIDstr().c_str());
	Serial.printf("hostname :%s\n", WiFi.hostname().c_str());
	Serial.printf("SSID :%s\n", WiFi.SSID().c_str());
	Serial.printf("psk :%s\n", WiFi.psk().c_str());

}

void loop()
{
	if (client.connect(serverIp, PORT))
	{
		Serial.println("client connected");

		client.println("GET /search?q=omid+ketabchi HTTP/1.0");
		client.println();

		while (client.connected())
		{
			if (client.available())
			{
				Serial.println(client.readStringUntil('\n'));
			}
		}
	}
	else
	{
		Serial.println("client not connected");
	}


	delay(3000);

}