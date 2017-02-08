#define CLK P1_4
#define DAT P1_5
#include "lut.h"
#include "token.h"

int count = 0;
int data = 0;
int o = 0;
String line;

void setup() {
    Serial.begin(9600);
    Serial.println("OK");
    pinMode(DAT, INPUT);
    pinMode(CLK, OUTPUT);
    digitalWrite(CLK, LOW);
    sleep(3);
    pinMode(CLK, INPUT);
}

void loop() {
    int n = digitalRead(CLK);
    if ((!n)&&(n!=o)) {
        data|=digitalRead(DAT)<<(count++);
        if (count >= 11) {
            data = data>>1; //kill stop bit
            data &= ~0x100; //kill start bit
            char toAdd = doLut(data);
            if (toAdd != 0) {
                Serial.print(toAdd);
            }
            switch (toAdd) {
                case 0: break;
                case '\b': line = line.substring(0, line.length() - 1); break;
                case '\n': Serial.print('\r'); scanner(line); line = ""; break;
                default: line += toAdd; break;
            }
            count = 0;
            data = 0;  
        }
    }
    o = n;
}

void scanner(String &line) {
    String wordle;
    for (int i = 0; i < line.length(); i++) {
      char c = line.charAt(i);
      if (c == ' ') {
        Serial.println(str_token(scan_token(wordle)));
        wordle = "";
      } else
        wordle += c;
    }
    Serial.println(str_token(scan_token(wordle))); 
}
