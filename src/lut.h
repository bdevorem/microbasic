#ifndef LUTH_
#define LUTH_
char doLut(char in) {
    static char lshift = 0;
    static char rshift = 0;
    char shift = lshift || rshift;
    switch (in) {
        default  : return   0;
        case 0x1C: return 'A';
        case 0x32: return 'B';
        case 0x21: return 'C';
        case 0x23: return 'D';
        case 0x24: return 'E';
        case 0x2B: return 'F';
        case 0x34: return 'G';
        case 0x33: return 'H';
        case 0x43: return 'I';
        case 0x3B: return 'J';
        case 0x42: return 'K';
        case 0x4B: return 'L';
        case 0x3A: return 'M';
        case 0x31: return 'N';
        case 0x44: return 'O';
        case 0x4D: return 'P';
        case 0x15: return 'Q';
        case 0x2D: return 'R';
        case 0x1B: return 'S';
        case 0x2C: return 'T';
        case 0x3C: return 'U';
        case 0x2A: return 'V';
        case 0x1D: return 'W';
        case 0x22: return 'X';
        case 0x35: return 'Y';
        case 0x1A: return 'Z';
        case 0x45: return shift?')':'0';
        case 0x16: return '1';
        case 0x1E: return '2';
        case 0x26: return '3';
        case 0x25: return '4';
        case 0x2E: return '5';
        case 0x36: return '6';
        case 0x3D: return shift?'&':'7';
        case 0x3E: return shift?'*':'8';
        case 0x46: return shift?'(':'9';
        case 0x29: return ' ';
        case 0x5A: return '\n';
        case 0x66: return '\b';
        case 0x55: return shift?'+':'=';
        case 0x4E: return '-';
        case 0x4A: return '/';
        case 0x52: return '"';
        case 0x13: return shift?'>':'<';
        case 0x5B: return '|';
        case 0x41: return ',';
        case 0x12: lshift = !lshift; return 0; //LSHIFT
        case 0x59: rshift = !rshift; return 0; //RSHIFT
    }
}
#endif






