#ifndef LUTH_
#define LUTH_
char doLut(char in) {
    static char lshift = 0;
    static char rshift = 0;
    char shift = lshift || rshift;
    switch (in) {
        default  : return   0; break;
        case 0x1C: return 'A'; break;
        case 0x32: return 'B'; break;
        case 0x21: return 'C'; break;
        case 0x23: return 'D'; break;
        case 0x24: return 'E'; break;
        case 0x2B: return 'F'; break;
        case 0x34: return 'G'; break;
        case 0x33: return 'H'; break;
        case 0x43: return 'I'; break;
        case 0x3B: return 'J'; break;
        case 0x42: return 'K'; break;
        case 0x4B: return 'L'; break;
        case 0x3A: return 'M'; break;
        case 0x31: return 'N'; break;
        case 0x44: return 'O'; break;
        case 0x4D: return 'P'; break;
        case 0x15: return 'Q'; break;
        case 0x2D: return 'R'; break;
        case 0x1B: return 'S'; break;
        case 0x2C: return 'T'; break;
        case 0x3C: return 'U'; break;
        case 0x2A: return 'V'; break;
        case 0x1D: return 'W'; break;
        case 0x22: return 'X'; break;
        case 0x35: return 'Y'; break;
        case 0x1A: return 'Z'; break;
        case 0x45: return shift?')':'0'; break;
        case 0x16: return '1'; break;
        case 0x1E: return '2'; break;
        case 0x26: return '3'; break;
        case 0x25: return '4'; break;
        case 0x2E: return '5'; break;
        case 0x36: return '6'; break;
        case 0x3D: return '7'; break;
        case 0x3E: return shift?'*':'8'; break;
        case 0x46: return shift?'(':'9'; break;
        case 0x29: return ' '; break;
        case 0x5A: return '\n'; break;
        case 0x66: return '\b'; break;
        case 0x55: return shift?'+':'='; break;
        case 0x4E: return '-'; break;
        case 0x4A: return '/'; break;
        case 0x52: return '"'; break;
        case 0x13: return shift?'>':'<'; break;
        case 0x12: lshift = !lshift; return 0; break; //LSHIFT
        case 0x59: rshift = !rshift; return 0; break; //RSHIFT
    }
}
#endif

