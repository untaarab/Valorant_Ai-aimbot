#include <hidmouserptparser.h>

#include <hidboot.h>
#include <usbhub.h>
#include <Mouse.h>
#include "hidmouserptparser.h"
#include "ard.h"




// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi3teensy3.h>
#endif
#include <SPI.h>

int v_x = 0;
int v_y = 0;
String received_code;
int index1;
int index2;
int index3;
int index4;


class MouseRptParser : public MouseReportParser
{
protected:
  void OnMouseMove  (MOUSEINFO *mi); 
  void OnLeftButtonUp (MOUSEINFO *mi);
  void OnLeftButtonDown (MOUSEINFO *mi);
  void OnRightButtonUp  (MOUSEINFO *mi);
  void OnRightButtonDown  (MOUSEINFO *mi);
  void OnMiddleButtonUp (MOUSEINFO *mi);
  void OnMiddleButtonDown (MOUSEINFO *mi);
  void OnWheelMove (MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
  Mouse.move(mi->dX,mi->dY,0);
};
void MouseRptParser::OnWheelMove (MOUSEINFO *mi)
{
  Mouse.begin();
  Mouse.move(0, 0, mi->dZ);
  Mouse.end();
};


void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi)
{
    Mouse.release();
};
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi)
{
    Mouse.press();
};
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi)
{
    Mouse.release(MOUSE_RIGHT);
};
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)
{
    Mouse.press(MOUSE_RIGHT);
};
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
    Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
    Serial.println("M Butt Dn");
};




MouseRptParser                               Prs;

void setup()
{
    /*Serial.begin( 115200 );
    Mouse.begin();
#if !defined(_MIPSEL_)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
    Serial.println("Start");

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    delay( 200 );
    HidMouse.SetReportParser(0, &Prs);*/

  delay(5000); 
  Mouse.begin(); 
  Serial.begin(115200); 
  Serial.setTimeout(1);
   
  Usb.Init(); 
  HidMouse.SetReportParser(0, &Prs); 


}

void loop()
{
  Usb.Task();
    while(Serial.available()){
    char c = Serial.read();
    if(c == '*'){
      index1 = received_code.indexOf(',');
      String x_direction = received_code.substring(0,index1);
      index2 = received_code.indexOf(',',index1+1);
      String x_value = received_code.substring(index1+1,index2+1);
      index3 = received_code.indexOf(',',index2+1);
      String y_direction = received_code.substring(index2+1,index3+1);
      index4 = received_code.indexOf(',',index3+1);
      String y_value = received_code.substring(index3+1);
      
      String x_d = String(x_direction);
      String y_d = String(y_direction);
      int x_v = x_value.toInt();
      int y_v = y_value.toInt();
      //Serial.print(x_d);
     //Serial.print(y_d);
     //Setup speed aimbot :
      int a =  4;
      int b = -4;
      
      if(x_d == "p" && y_d=="p,"){
        while(x_v > 0 || y_v > 0){
          if(x_v > 0){
            Mouse.move(a,0,0);
            x_v -= 1;
          }
          if(y_v > 0){
            Mouse.move(0,a,0);
            y_v -= 1;
          }
        }
      }
      if(x_d == "p" && y_d=="n,"){
        while(x_v > 0 || y_v > 0){
          if(x_v > 0){
            Mouse.move(a,0,0);
            x_v -= 1;
          }
          if(y_v > 0){
            Mouse.move(0,b,0);
            y_v -= 1;
          }
        }
      }
      if(x_d == "n" && y_d=="p,"){
        while(x_v > 0 || y_v > 0){
          if(x_v > 0){
            Mouse.move(b,0,0);
            x_v -= 1;
          }
          if(y_v > 0){
            Mouse.move(0,a,0);
            y_v -= 1;
          }
        }
      }
      if(x_d == "n" && y_d=="n,"){
        while(x_v > 0 || y_v > 0){
          if(x_v > 0){
            Mouse.move(b,0,0);
            x_v -= 1;
          }
          if(y_v > 0){
            Mouse.move(0,b,0);
            y_v -= 1;
          }
        }
      }
     
      received_code = "";
    }
      else if (lmb == 1){ 
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.move(-1, 23);
    delay(100);
    Mouse.move(-1, 24);
    delay(100);
    Mouse.move(-1, 24);
    delay(100);
    Mouse.move(-1, 21);
    delay(100);
    Mouse.move(-1, 23);
    delay(100);
    Mouse.move(-1, 27);
    delay(100);
    Mouse.move(-1, 26);
    delay(100);
    Mouse.move(-1, 25);
    delay(100);
    Mouse.move(-10, 8);
    }

    else{
      received_code += c;
    }
  }
}
