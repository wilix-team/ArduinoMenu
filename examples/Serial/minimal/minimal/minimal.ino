/********************
Arduino generic menu system
Rui Azevedo - ruihfazevedo(@rrob@)gmail.com

output: Serial
input: Serial
*/

#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
using namespace Menu;

int test=0;

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,OP("Op1",doNothing,noEvent)
  ,EXIT("<Back")
);

#define MAX_DEPTH 1

// constMEM char op2Text[] MEMMODE="X:";
// constMEM promptShadowRaw op2InfoRaw MEMMODE={doNothing,_noStyle,op2Text,noEvent,noStyle};
// constMEM promptShadow& op2Info=*(promptShadow*)&op2InfoRaw;
// prompt op2(op2Info);

float varioFilterX=0;

// constMEM char varioFilterX_title[] MEMMODE="X:";
// constMEM char varioFilterX_unit[] MEMMODE="";
// constMEM fieldShadowRaw op2InfoRaw MEMMODE={doNothing,_noStyle,op2Text,noEvent,noStyle};
// menuField<typeof(varioFilterX)> varioFielterXField(
//   varioFilterX,
//   varioFilterX_title,varioFilterX_unit,
//   0,1,0.1,0.01,
//   doNothing,noEvent,wrapStyle
// );

MENU_OUTPUTS(out,MAX_DEPTH
  ,SERIAL_OUT(Serial)
  ,NONE//must have 2 items at least
);

serialIn in(Serial);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);

// menuField<typeof(test)> testField(test,"test","%",0,100,10,1,doNothing,noEvent,noStyle);
// navNode testNode[1];
// navRoot testRoot(testField,testNode,1,in,out);//must be a navNode, not a navTarget

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("menu 4.x test");Serial.flush();
  nav.nav2D=true;//this should be input device specific? nah, because they all join
}

void loop() {
  static bool ext=false;//extended keys
  // nav.poll();
  if (Serial.available()) {
    char c=Serial.read();
    //use arrows enter and escape to navigate the menu (use a serial monitor that can send keys instead of lines)
    switch(c) {
      case 0x0D: if (ext) nav.doNav(enterCmd); else nav.doNav(navCmd(textValue,c));break;
      case 0x41: if (ext) nav.doNav(downCmd); else nav.doNav(navCmd(textValue,c));break;
      case 0x42: if (ext) nav.doNav(upCmd); else nav.doNav(navCmd(textValue,c));break;
      case 0x43: if (ext) nav.doNav(rightCmd); else nav.doNav(navCmd(textValue,c));break;
      case 0x44: if (ext) nav.doNav(leftCmd); else nav.doNav(navCmd(textValue,c));break;
      case 0x1B:
        delay(1);//otherwise serial speed might not be enought to detect the second character
        if (Serial.peek()==0x5B) ext=true;
        else {
          ext=false;
          nav.doNav(escCmd);
        }
        break;
      case 0x0A: break;
      case 0x5B: if (!ext) nav.doNav(navCmd(textValue,c));break;
      default:
        // Serial.println(c,HEX);
        ext=false;
        nav.doNav(navCmd(textValue,c));
        break;
    }
  }
  nav.doOutput();//if not doing poll the we need to do output "manualy"
  delay(10);//simulate a delay when other tasks are done
}
