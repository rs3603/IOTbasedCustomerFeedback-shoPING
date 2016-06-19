/******************************************************************************
  MicroOLED_Hello.ino
  SFE_MicroOLED Hello World Demo
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: October 26, 2014
  
  This sketch lights up a familiar pattern on the MicroOLED
  Breakout. It's a great way to prove you've connected everything
  correctly and that your display is in working order.
  
  Hardware Connections:
    We'll be using the SPI interface on the MicroOLED, though it
    also supports I2C (and a really messy parallel). If you want
    to swap in I2C, read through the comments to find out how.
    
    MicroOLED ------------- Arduino
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
    D1/MOSI ----------------- D11 (don't change)
    D0/SCK ------------------ D13 (don't change)
      D2
      D/C ------------------- D8 (can be any digital pin)
      RST ------------------- D9 (can be any digital pin)
      CS  ------------------- D10 (can be any digital pin)
    
  Development environment specifics:
    IDE: Arduino 1.0.5
    Hardware Platform: MicroOLED Breakout
                           Arduino Pro 3.3V/8MHz
  
  Note: The display on the MicroOLED is a 1.8V-3.3V device only.
  Don't try to connect a 5V Arduino directly to it! Use level
  shifters in between the data signals if you have to resort to
  a 5V board.
  
  This code is beerware; if you see me (or any other SparkFun 
  employee) at the local, and you've found our code helpful, 
  please buy us a round!
  
  Distributed as-is; no warranty is given.
*******************************************************************************/
#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_RESET 9  // Connect RST to pin 9 (req. for SPI and I2C)
#define PIN_DC    8  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10 // Connect CS to pin 10 (required for SPI)
#define DC_JUMPER 0
// Also connect pin 13 to SCK and pin 11 to MOSI
int analogPin = 18;     // potentiometer wiper (middle terminal) connected to analog pin 3
int analogPin1 = 2;
int lowpin = 1; 
int button = 3; // button press
                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
// Declare a MicroOLED object. The parameters include:
// 1 - Reset pin: Any digital pin
// 2 - D/C pin: Any digital pin (SPI mode only)
// 3 - CS pin: Any digital pin (SPI mode only, 10 recommended)
MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);
//MicroOLED oled(PIN_RESET, DC_JUMPER); // Example I2C declaration

// I2C is great, but will result in a much slower update rate. The
// slower framerate may be a worthwhile tradeoff, if you need more
// pins, though.
void setup()
{

  pinMode(button,INPUT);
  digitalWrite(button,HIGH);
  pinMode(analogPin1,INPUT);
  digitalWrite(analogPin1,HIGH);
   pinMode(lowpin,OUTPUT);
  digitalWrite(lowpin,LOW);
  //attachInterrupt(0,pin_ISR,FALLING);
  Serial.begin(115200);          //  setup serial
  Serial1.begin(57600); // open internal serial connection to
 //MT7688
  // These three lines of code are all you need to initialize the
  // OLED and print the splash screen.
  
  // Before you can start using the OLED, call begin() to init
  // all of the pins and configure the OLED.
  oled.begin();
  // clear(ALL) will clear out the OLED's graphic memory.
  // clear(PAGE) will clear the Arduino's display buffer.
  oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
  // To actually draw anything on the display, you must call the
  // display() function.
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0, 0);
  oled.print("shoPING"); // Print a const string 
  oled.setCursor(0, 20);
  oled.setFontType(0);
  oled.print("   TURN"); // Print a const string
  oled.print("    THE KNOB"); // Print a const string
  oled.display();   
}

String prevstatedisplay;
String statedisplay;
String str;
int state=0;
char ch;
int val1;
int flag = 0;
void loop()
{
  prevstatedisplay = statedisplay;                                                                                                                                                                                                                               
  val1 = analogRead(analogPin);
  Serial.println(val1);
  if(digitalRead(button)==LOW && state==0)
  {
    state = 1;
    prevstatedisplay = statedisplay;
    Serial.println("pressed");
    val = analogRead(analogPin);    // read the input pin
    Serial.println(val);
    if(val>=0 && val<=255)
    {
      ch = '1';
      str = "option1";
    }
    else if(val>=256 && val <=511)
    {
      ch = '2';
      str = "option2";
    }
    else if(val>=512 && val <=767)
    {
      ch = '3';
      str = "option3";
    }
    else
    {
      ch = '4';
      str = "option4";
    }
    flag=1;
    Serial1.write(ch);
    //while(digitalRead(button)==LOW);
    delay(100);
    oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
  // To actually draw anything on the display, you must call the
  // display() function.
    oled.clear(PAGE);
    int radius = 13;
// Draw a 13-pixel radius (26-pixel diameter) 
// circle centered in the middle of the display:
    oled.pixel((LCDWIDTH/2)-4, (LCDHEIGHT/2)-5);
    oled.pixel((LCDWIDTH/2)+4, (LCDHEIGHT/2)-5);
    oled.pixel((LCDWIDTH/2)-5, (LCDHEIGHT/2)-5);
    oled.pixel((LCDWIDTH/2)+5, (LCDHEIGHT/2)-5);
    oled.pixel((LCDWIDTH/2)-4, (LCDHEIGHT/2)-4);
    oled.pixel((LCDWIDTH/2)+4, (LCDHEIGHT/2)-4);
    oled.pixel((LCDWIDTH/2)-5, (LCDHEIGHT/2)-4);
    oled.pixel((LCDWIDTH/2)+5, (LCDHEIGHT/2)-4);
    
    oled.pixel((LCDWIDTH/2)-7, (LCDHEIGHT/2)+2);
    oled.pixel((LCDWIDTH/2)-6, (LCDHEIGHT/2)+3);
    oled.pixel((LCDWIDTH/2)-5, (LCDHEIGHT/2)+4);
    oled.pixel((LCDWIDTH/2)-4, (LCDHEIGHT/2)+4);
    oled.pixel((LCDWIDTH/2)-3, (LCDHEIGHT/2)+5);
    oled.pixel((LCDWIDTH/2)-2, (LCDHEIGHT/2)+6);
    oled.pixel((LCDWIDTH/2)-1, (LCDHEIGHT/2)+6);
    oled.pixel((LCDWIDTH/2)+0, (LCDHEIGHT/2)+6);
    oled.pixel((LCDWIDTH/2)+1, (LCDHEIGHT/2)+6);
    oled.pixel((LCDWIDTH/2)+2, (LCDHEIGHT/2)+6);
    oled.pixel((LCDWIDTH/2)+3, (LCDHEIGHT/2)+5);
    oled.pixel((LCDWIDTH/2)+4, (LCDHEIGHT/2)+4);
    oled.pixel((LCDWIDTH/2)+5, (LCDHEIGHT/2)+4);
    oled.pixel((LCDWIDTH/2)+6, (LCDHEIGHT/2)+3);
    oled.pixel((LCDWIDTH/2)+7, (LCDHEIGHT/2)+2);    
    oled.circle(LCDWIDTH/2, LCDHEIGHT/2, radius);  

    oled.display();
    delay(1000); 
  }

if(digitalRead(button)==HIGH && state==1)
{
  state=0;
}


    if(val1>=0 && val1<=255)
    {
      str = "option1";
    }
    else if(val1>=256 && val1<=511)
    {
      str = "option2";
    }
    else if(val1>=512 && val1<=767)
    {
      str = "option3";
    }
    else
    {
      str = "option4";
    }



  
    

  statedisplay = str;
  if(statedisplay!=prevstatedisplay && flag==1)
  {
    
    oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
    // To actually draw anything on the display, you must call the
    // display() function.
    oled.clear(PAGE);
    oled.setFontType(1);
    oled.setCursor(0, 0);
    oled.print(str);
    oled.display();
  }
  
  if(digitalRead(analogPin1)==LOW)
  {
    ch = '7';
    Serial1.write(ch);
    //while(digitalRead(button)==LOW);
    delay(200);
    oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)
    // To actually draw anything on the display, you must call the
    // display() function.
    oled.clear(PAGE);
    oled.setFontType(1);
    oled.setCursor(0, 0);
    oled.print("NEED HELP!");
    oled.display();
    delay(1000);
  }

}
