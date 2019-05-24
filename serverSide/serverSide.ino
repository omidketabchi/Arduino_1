#include <ESP8266WiFi.h>

WiFiServer server(80);
WiFiClient client;

void setup()
{
	char ssid[32 + 1] = "ESP8266";
	char password[20 + 1] = "11111111";

	Serial.begin(115200);

	while (!WiFi.softAP(ssid, password))
	{
		Serial.print(".");
		delay(500);
	}

	Serial.println();
	Serial.printf("server ip :%s\n", WiFi.softAPIP().toString().c_str());
	Serial.printf("macAddress :%s\n", WiFi.macAddress().c_str());
	//Serial.printf("hostname :%s\n", WiFi.hostname().c_str());

	server.begin();
}

void loop()
{
	char recv[100] = {0};
	int i = 0;
	bool data = false;

	if (!client)
	{
		client = server.available();
	}

	if (client)
	{
		Serial.printf("client connected\n");

		while (client.available())
		{
			sprintf(recv + i, "%c", client.read());
			i++;
			data = true;
		}

		if (data)
		{
			Serial.printf("recv :%s\n", recv);
			client.write("received");
			client.stop();
		}
	}

	delay(500);
}