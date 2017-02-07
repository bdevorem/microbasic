#define CLK P1_0
#define DAT P1_1
#include "lut.h"

int count = 0;
int data = 0;
int o = 0;
String line;


void setup() {
    Serial.begin(9600);
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
            data = data>>1; //kill parity bit
            data &= ~0x100; //kill start bit
            char toAdd = doLut(data);
            if (toAdd != 0) {
                Serial.print(toAdd);
            }
            switch (toAdd) {
                case 0: break;
                case '\b': line = line.substring(0, line.length() - 1); break;
                case '\n': /*RUN THING*/ break;
                default: line += toAdd; break;
            }
            count = 0;
            data = 0;  
        }
    }
    o = n;
}

