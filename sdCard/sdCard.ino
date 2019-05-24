#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
	Serial.begin(115200);

	if (!SD.begin(4))
	{
		Serial.println("initialize fail");
		return;
	}

	myFile = SD.open("ok.txt", FILE_WRITE);

	if (myFile)
	{
		Serial.println("writing...");
		myFile.println("this is for test");
		myFile.close();
		Serial.println("write ok");
	}
	else
	{
		Serial.println("open fail");
		return;
	}
	 
	myFile = SD.open("ok.txt", FILE_READ);

	if (myFile)
	{
		Serial.println("reading...");
		while (myFile.available())
		{
			Serial.write(myFile.read());
		}

		myFile.close();
		Serial.println("read ok");
	}
	else
	{
		Serial.println("open fail");
		return;
	}
}

void loop()
{
	delay(5000);
}