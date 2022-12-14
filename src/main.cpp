#include <GyverOLED.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Типа лого
const uint8_t bitmap_32x32[] PROGMEM = {
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0x7f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,0x7f,
0x1f,0xc1,0xfe,0xff,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0xff,0xff,
0xff,0xff,0xff,0xff,0x1,0x0,0x0,0x0,0x1,0x3,0x7,0x7,0xf,0xf,0xf,0xf,
0x6,0x6,0x6,0x0,0x0,0x0,0xe0,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf0,0xc1,0xf,0x7f,0xff,0xff,0xf3,
0xf,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x7f,0x7,0x0,0xf8,0xff,0xff,0x1f,0x7,0x1,0xc0,0xde,0x8f,0x87,0xc0,
0x1e,0x7,0x3,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0xf8,0xfc,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xf8,0xf0,0xf3,0xff,0xfe,0xfe,
0xf8,0xe0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf8,0xff,0xff,0xff,
0xff,0xf0,0x3,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0x7f,0x7,0x0,0x0,0x0,0x87,0x83,0x83,0x81,0xc0,0x41,0x41,0x41,0x1,0x3,0x7,
0xe,0x9f,0xff,0xff,0x30,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0x7f,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfd,0xf9,0xf9,0xf9,0xd9,0x81,0x0,0x0,0x0,0x0,0x0,0x81,
0xc1,0xe0,0xf0,0xf0,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x0,0x0,0x1,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7,
0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0xf,0xf,0xf,0x0,0x3,0x83,0xc1,0xe0,0xf0,0xf8,0xfc,0xfe,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7e,0x3e,0x3f,0x1f,
0xf,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0xf,0xff,0xff,0xff,0xff,
0xff,0x1f,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0x10,
0x0,0x0,0x0,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc0,0xe0,
0xe0,0xf0,0xf8,0xfc,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xe3,0xc1,0xe0,0xf0,0x38,0xcc,0xe6,
0xe2,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xff,0xff,0xff,0x9f,
0xc,0x4,0x4,0x6,0x2,0x2,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0x7,0x3,0x3,0x0,0x0,
0x0,0x80,0x80,0x83,0x1f,0xff,0xff,0xff,0xfd,0xfb,0xfb,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,0xf0,0xe0,0xc0,0x80,0x3,0xf,0x3f,
0xff,0xe7,0xe3,0xf3,0xff,0xff,0xff,0x3f,0xf,0xf,0x7,0xc1,0xf0,0xfe,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xfc,0xf0,0xf0,0xf0,0xf8,0xfc,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf8,0xf8,0xf8,0xf8,0xf8,
0xf8,0xf8,0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0x1f,0x1f,0x1f,0xff,0xff,0xfe,0xf8,
0xf8,0x7b,0x3f,0xdf,0xcf,0x87,0x0,0x0,0x80,0xf0,0xfe,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};



GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled; //Указываем какой ОЛЕД взят в работу

// Используя OneWire со второго пина забираем данные
#define ONE_WIRE_BUS 2
// настройка объекта oneWire для связи с любым устройством OneWire
OneWire oneWire(ONE_WIRE_BUS);
// передать ссылку на oneWire библиотеке DallasTemperature
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;

void setup() {

sensors.begin();    // запустить библиотеку
  Serial.begin(9600);
  
  oled.init();              // инициализация олед
  oled.clear();
  
  oled.drawBitmap(0, 0, bitmap_32x32, 128, 64);
  oled.update();
  delay(9000);
  oled.clear();
  
  oled.home();
  oled.setScale(1);
  
  // найти устройства на шине
  oled.println("Поиск датчиков ");
  oled.println("температуры...");
  oled.println("Нашёл!");
  deviceCount = sensors.getDeviceCount();
  oled.print(deviceCount, DEC);  
  oled.println(" устройства.");
  delay(500);
  oled.println("");  
  Serial.begin(9600);
  
  
}


void printTest() {
  oled.clear();
  char textWater[] = "Температура воздуха: ";
  char textAir[] = "Температура воды: ";
  float sensorT1 = sensors.getTempCByIndex(0);
  float sensorT2 = sensors.getTempCByIndex(1);
  char lineBreak[] = " ";
  oled.home();
  oled.setScale(1);
  oled.println(textWater);
  oled.println(lineBreak);  
  oled.setScale(2);
  oled.println(sensorT1);
  oled.setScale(1);   
  oled.println(lineBreak); 
  oled.println(textAir);   
  oled.invertText(true);
  oled.setScale(2);
  oled.println(sensorT2);
  oled.invertText(false);
  oled.update();
  delay(5000);
}

void loop() {

  // послать команду всем датчикам для преобразования температуры
  sensors.requestTemperatures(); 

delay(1000);
printTest();
}