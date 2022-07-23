#include <Keyboard.h>

int upArrow = 229; // Numpad 5
int downArrow = 234; // Numpad 0

char receivedChar; //a vairable for saving a letter transmitted by python

unsigned long lastDebounceTime; //declare a variable for debouncing
unsigned long previousMillis;
unsigned long currentMillis;

volatile int state = false; //declare a variable for using switch

void random_delay(long delay_value,  long random_value) {
    //wait for delay_value +- random_delay
    delay_value = delay_value + random(-random_value, random_value);
    if(delay_value < 0 ) return;
    delay(delay_value);
}

void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    pinMode(2, INPUT_PULLUP); //set pin2 as input
    pinMode(13, OUTPUT); //activate built-in LED
    attachInterrupt(digitalPinToInterrupt(2), isr, FALLING); //operate isr when pin2 gets falling edge signal
    randomSeed(analogRead(A0));
}

void loop() {
    while(!state); //wait until state == true
    recieveChar(); 
}

void isr()  { //activate/deactivate Arduino by using switch
    if ( (millis() - lastDebounceTime) < 200   )  return;  //ignore bouncing occurred within 0.2sec from initial input

    if (state == false) {
        state = true; //activate Arduino
        digitalWrite(13, HIGH); //turn on built-in LED
    }
    else {
        state = false; //deactivate Arduino
        digitalWrite(13, LOW); //turn off built-in LED
    }
    
    lastDebounceTime = millis(); //set the reference point of debouncing as current time
}

void recieveChar() { //a function recieves a letter from python thru serial communication
    if (Serial.available()) {
        receivedChar = Serial.read();
        pressKey();
    }
}

void pressKey() { //a function operates hotkey based on transmitted letter in recievechar()
    switch(receivedChar) {
        case 'a': //블러드 소드
        Keyboard.press(upArrow);
        random_delay(48, 8);
        Keyboard.release(upArrow);
        random_delay(28, 27);
        Keyboard.press('z');
        random_delay(78, 42);
        Keyboard.release('z');
        break;

        case 's': //아웃레이지 브레이크
        Keyboard.press(downArrow);
        random_delay(48, 8);
        Keyboard.release(downArrow);
        random_delay(28, 27);
        Keyboard.press('z');
        random_delay(78, 42);
        Keyboard.release('z');
        break;

        case 'd': //격노
        Keyboard.press(upArrow);
        random_delay(34, 14);
        Keyboard.release(upArrow);
        random_delay(28, 27);
        Keyboard.press('x');
        random_delay(78, 42);
        Keyboard.release('x');
        break;

        case 'f': //버스트 퓨리
        Keyboard.press(downArrow);
        random_delay(48, 8);
        Keyboard.release(downArrow);
        random_delay(28, 27);
        Keyboard.press('x');
        random_delay(78, 42);
        Keyboard.release('x');
        break;

        case 'g': //레이징 퓨리
        Keyboard.press(upArrow);
        random_delay(48, 8);
        Keyboard.release(upArrow);
        random_delay(28, 27);
        Keyboard.press('c');
        random_delay(78, 42);
        Keyboard.release('c');
        break;

        case 'v': //블러디 레이브
        Keyboard.press(downArrow);
        random_delay(48, 8);
        Keyboard.release(downArrow);
        random_delay(28, 27);
        Keyboard.press('c');
        random_delay(78, 42);
        Keyboard.release('c');
        break;

        case 'q': // alt, 페이탈 블러드
        Keyboard.press(upArrow);
        random_delay(48, 8);
        Keyboard.press(downArrow);
        random_delay(27, 12);
        Keyboard.release(upArrow);
        random_delay(59, 21);
        Keyboard.release(downArrow);
        random_delay(19, 18);
        Keyboard.press('z');
        random_delay(72, 35);
        Keyboard.release('z');
        break;

        case 'w': // ctrl, 램펀트 매드니스
        Keyboard.press(upArrow);
        random_delay(64, 42);
        Keyboard.press(downArrow);
        random_delay(27, 12);
        Keyboard.release(upArrow);
        random_delay(59, 21);
        Keyboard.release(downArrow);
        random_delay(19, 18);
        Keyboard.press('x');
        random_delay(72, 35);
        Keyboard.release('x');
        break;

        case 'e': // shift, 블러드붐
        Keyboard.press(upArrow);
        random_delay(64, 42);
        Keyboard.press(downArrow);
        random_delay(27, 12);
        Keyboard.release(upArrow);
        random_delay(59, 21);
        Keyboard.release(downArrow);
        random_delay(19, 18);
        Keyboard.press('c');
        random_delay(72, 35);
        Keyboard.release('c');
        break;
    }

}