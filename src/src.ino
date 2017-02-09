#define CLK P1_4
#define DAT P1_5
#include "lut.h"
#include "token.h"

#define NVARS (10)
#define MAX_LEN (40)
#define ESC "\033"

int count = 0;
int data = 0;
int o = 0;
String vars[NVARS];
String line;

void setup() {
    Serial.begin(9600);
    Serial.println("OK");
    pinMode(DAT, INPUT);
    lock();
    sleep(3);
    unlock();
}

void loop() {
    int n = digitalRead(CLK);
    if ((!n)&&(n!=o)) {
        data|=digitalRead(DAT)<<(count++);
        if (count >= 11) {
            lock();
            data = data>>1; //kill stop bit
            data &= ~0x100; //kill start bit
            char toAdd = doLut(data);
            if (line.length() < MAX_LEN || toAdd == '\b') {
              if (toAdd != 0) {
                  if (toAdd == 'B')
                      Serial.print(ESC"[32m");
                  Serial.print(toAdd);
                  if (toAdd =='B')
                      Serial.print(ESC"[0m");
              }
              switch (toAdd) {
                  case 0: break;
                  case '\b': Serial.print(" \b"); line = line.substring(0, line.length() - 1); break;
                  case '\n': Serial.print('\r'); scanner(line); line = ""; break;
                  default: line += toAdd; break;
              }
            }
            count = 0;
            data = 0;  
            unlock();
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
    if (wordle.startsWith("CLEAR")) clear();
    if (wordle.startsWith("LIST")) list();
}

void clear() {
    Serial.print(ESC"[2J");
    Serial.print(ESC"[0;0H");
}

void list() {
  for (int i = 0; i < NVARS; i++) {
    Serial.print((char)('A' + i));
    Serial.print(" = ");
    Serial.println(vars[i]);
  }
}

void lock() {
    pinMode(CLK, OUTPUT);
    digitalWrite(CLK, LOW); 
}

void unlock() {
  pinMode(CLK, INPUT);
}
