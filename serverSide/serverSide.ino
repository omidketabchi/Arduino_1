#include <ESP8266WiFi.h>

WiFiClient	client;
WiFiServer server(80);

IPAddress serverIp = { 192,168,244,1 };
IPAddress gateway = { 192,168,1,1 };
IPAddress subnetMask = { 255,255,255,0 };

void setup()
{
	char mainSsid[20] = "G";
	char ssid[20] = "espServer";
	char password[20] = "12345678";

	Serial.begin(115200);


	while (!WiFi.softAP(ssid, password))
	{
		delay(500);
	}

	//WiFi.softAPConfig(serverIp, gateway, subnetMask);

	Serial.printf("server ip :%s\n", WiFi.softAPIP().toString().c_str());
	Serial.printf("server ip :%s\n", WiFi.softAPmacAddress().c_str());

	WiFi.begin(mainSsid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}

	Serial.printf("\n");
	Serial.printf("localIP :%s\n", WiFi.localIP().toString().c_str());
	Serial.printf("gatewayIP :%s\n", WiFi.gatewayIP().toString().c_str());
	Serial.printf("subnetMask :%s\n", WiFi.subnetMask().toString().c_str());
	Serial.printf("client mac address :%s\n", WiFi.macAddress().c_str());
	Serial.printf("---- everything is ok ----\n");

	server.begin();
}

void loop()
{
	char		recv[100] = { 0 };
	int			i = 0;
	bool        data = false;

	if (!client)
	{
		client = server.available();
	}

	if (client)
	{
		//Serial.println("clinet connected");

		while (client.available())
		{
			sprintf(recv + i, "%c", client.read());
			i++;
			data = true;
		}

		if (data)
		{
			Serial.printf("received buffer :%s\n", recv);

			if (strcmp(recv, "salam") == 0)
			{
				client.write("received");
				client.stop();
			}
		}
	}

	delay(500);
}
