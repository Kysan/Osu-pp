#ifndef keyboard_h
#define keyboard_h


class Keyboard
{
private:
    
public:
    static bool Keys[112];
    
    static void resetKeys() {
        for(int i = 0; i < 112; ++i) {
            Keys[i] = false;
        }
    }
    static void pressKey(int keyCode) {
        Keys[keyCode] = true;
    }

    static void releaseKey(int keyCode) {
        Keys[keyCode] = false;
    }

    static bool isKeyAlreadyPressed(int keyCode) {
        return Keys[keyCode];
    }
};

bool Keyboard::Keys[112]={0};

#endif