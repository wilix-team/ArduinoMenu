/********************
Arduino generic menu system
Rui Azevedo - ruihfazevedo(@rrob@)gmail.com

output: Serial
input: Serial

this is related to the ability of headless (a single focused field)
*/

#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
using namespace Menu;

int test=0;

MENU(welcome,"VarioGPS sensor\nVersion v2.1b")

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,OP("Op1",doNothing,noEvent)
  ,EXIT("<Back")
);

#define MAX_DEPTH 1

MENU_OUTPUTS(out,MAX_DEPTH
  ,SERIAL_OUT(Serial)
  ,NONE//must have 2 items at least
);

serialIn in(Serial);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("menu 4.x test");Serial.flush();
}


void loop() {
  nav.poll();
  delay(100);//simulate a delay when other tasks are done
}
