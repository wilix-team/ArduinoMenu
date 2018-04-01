/* -*- C++ -*- */
/********************
www.r-site.net
Sep.2014 ~ Sept. 2016 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
Mar.2018 ~

HardwareSerial input driver
***/

#ifndef RSITE_ARDUINO_MENU_HW_SERIALIN
  #define RSITE_ARDUINO_MENU_HW_SERIALIN
  #include "../menu.h"

  // #define SERIAL_CLASS Stream

  namespace Menu {
    class serialIn:public streamIn {
      public:
        Stream& in;
        serialIn(Stream& serial):in(serial) {}
        int available() override {return in.available()?*this:false;}
        navCmd peek() override {return navKeys(in.peek());}
        navCmd getCmd() override {return navKeys(in.read());}
        float parseFloat() override {return in.parseFloat();}
    };

  }

#endif
