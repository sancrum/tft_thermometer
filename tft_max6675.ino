/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Fonts/FreeSans24pt7b.h"
#include "Fonts/FreeSans18pt7b.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


int thermoSO = 12;  // MISO
int thermoCLK = 13; // SCK
int tc1CS = 8;   //SS

//minimal max6675.h inside this project
double readCelsius(uint8_t cs){
    uint16_t v;
    digitalWrite(cs, LOW);
    v = SPI.transfer(0x00);
    v <<= 8;
    v |= SPI.transfer(0x00);
    digitalWrite(cs, HIGH);
    if (v & 0x4) { return NAN;} // uh oh, no thermocouple attached!
    v >>= 3;
    return v*0.25;
}

byte rotation=1; 
long probMillis = 3000;
long prevMillis = -3000;
long signMillis =2000;
uint16_t currentTemp;
uint16_t adjustTemp = -3;

void setup() {
  Serial.begin(9600);

//set max6675 slaves   
  pinMode(tc1CS, OUTPUT);
  digitalWrite(tc1CS, HIGH);

  tft.begin();
tft.setRotation(rotation);
  tft.fillScreen(ILI9341_BLACK);

 tft.setCursor(0,230);
 tft.print("Powered by vladkomarov.tk");

  tft.setFont(&FreeSans24pt7b);

  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.setCursor(30, 50);
  tft.println("Temperature:");
    tft.setFont(&FreeSans18pt7b);
Serial.println(F("Done!"));
}


void loop(void) {
//  for(uint8_t rotation=0; rotation<4; rotation++) {
 if ((millis() - prevMillis) >probMillis){
 currentTemp = readCelsius(tc1CS)+adjustTemp;
//Serial.println(readCelsius(tc1CS));

 prevMillis=millis();
 
 updateTemp(currentTemp);
 }
 if(millis()>signMillis){
  tft.fillRect(0, 230, 320, 10, ILI9341_BLACK);
  }
//    delay(1000);
//  }
}

unsigned long updateTemp (int temperature){
  tft.setCursor(40, 120);
  tft.fillRect(40, 60, 240, 80, ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.print(" ");
  tft.print(temperature);
  tft.println("C");  


}

//unsigned long testFillScreen() {
//  unsigned long start = micros();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  tft.fillScreen(ILI9341_RED);
//  yield();
//  tft.fillScreen(ILI9341_GREEN);
//  yield();
//  tft.fillScreen(ILI9341_BLUE);
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  return micros() - start;
//}
//
//unsigned long testText() {
//
//  unsigned long start = micros();
// 
//  
// 
////  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
////  tft.println(0xDEADBEEF, HEX);
////  tft.println();
////  tft.setTextColor(ILI9341_GREEN);
////  tft.setTextSize(5);
////  tft.println("Groop");
////  tft.setTextSize(2);
////  tft.println("I implore thee,");
////  tft.setTextSize(1);
////  tft.println("my foonting turlingdromes.");
////  tft.println("And hooptiously drangle me");
////  tft.println("with crinkly bindlewurdles,");
////  tft.println("Or I will rend thee");
////  tft.println("in the gobberwarts");
////  tft.println("with my blurglecruncheon,");
////  tft.println("see if I don't!");
//  return micros() - start;
//}
//
//unsigned long testLines(uint16_t color) {
//  unsigned long start, t;
//  int           x1, y1, x2, y2,
//                w = tft.width(),
//                h = tft.height();
//
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  
//  x1 = y1 = 0;
//  y2    = h - 1;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = w - 1;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t     = micros() - start; // fillScreen doesn't count against timing
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = w - 1;
//  y1    = 0;
//  y2    = h - 1;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = 0;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t    += micros() - start;
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = 0;
//  y1    = h - 1;
//  y2    = 0;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = w - 1;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t    += micros() - start;
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = w - 1;
//  y1    = h - 1;
//  y2    = 0;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = 0;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//
//  yield();
//  return micros() - start;
//}
//
//unsigned long testFastLines(uint16_t color1, uint16_t color2) {
//  unsigned long start;
//  int           x, y, w = tft.width(), h = tft.height();
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
//  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);
//
//  return micros() - start;
//}
//
//unsigned long testRects(uint16_t color) {
//  unsigned long start;
//  int           n, i, i2,
//                cx = tft.width()  / 2,
//                cy = tft.height() / 2;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n     = min(tft.width(), tft.height());
//  start = micros();
//  for(i=2; i<n; i+=6) {
//    i2 = i / 2;
//    tft.drawRect(cx-i2, cy-i2, i, i, color);
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
//  unsigned long start, t = 0;
//  int           n, i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n = min(tft.width(), tft.height());
//  for(i=n; i>0; i-=6) {
//    i2    = i / 2;
//    start = micros();
//    tft.fillRect(cx-i2, cy-i2, i, i, color1);
//    t    += micros() - start;
//    // Outlines are not included in timing results
//    tft.drawRect(cx-i2, cy-i2, i, i, color2);
//    yield();
//  }
//
//  return t;
//}
//
//unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
//  unsigned long start;
//  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(x=radius; x<w; x+=r2) {
//    for(y=radius; y<h; y+=r2) {
//      tft.fillCircle(x, y, radius, color);
//    }
//  }
//
//  return micros() - start;
//}
//
//unsigned long testCircles(uint8_t radius, uint16_t color) {
//  unsigned long start;
//  int           x, y, r2 = radius * 2,
//                w = tft.width()  + radius,
//                h = tft.height() + radius;
//
//  // Screen is not cleared for this one -- this is
//  // intentional and does not affect the reported time.
//  start = micros();
//  for(x=0; x<w; x+=r2) {
//    for(y=0; y<h; y+=r2) {
//      tft.drawCircle(x, y, radius, color);
//    }
//  }
//
//  return micros() - start;
//}
//
//unsigned long testTriangles() {
//  unsigned long start;
//  int           n, i, cx = tft.width()  / 2 - 1,
//                      cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n     = min(cx, cy);
//  start = micros();
//  for(i=0; i<n; i+=5) {
//    tft.drawTriangle(
//      cx    , cy - i, // peak
//      cx - i, cy + i, // bottom left
//      cx + i, cy + i, // bottom right
//      tft.color565(i, i, i));
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledTriangles() {
//  unsigned long start, t = 0;
//  int           i, cx = tft.width()  / 2 - 1,
//                   cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(i=min(cx,cy); i>10; i-=5) {
//    start = micros();
//    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//      tft.color565(0, i*10, i*10));
//    t += micros() - start;
//    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//      tft.color565(i*10, i*10, 0));
//    yield();
//  }
//
//  return t;
//}
//
//unsigned long testRoundRects() {
//  unsigned long start;
//  int           w, i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  w     = min(tft.width(), tft.height());
//  start = micros();
//  for(i=0; i<w; i+=6) {
//    i2 = i / 2;
//    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledRoundRects() {
//  unsigned long start;
//  int           i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
//    i2 = i / 2;
//    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
//    yield();
//  }
//
//  return micros() - start;
//}
