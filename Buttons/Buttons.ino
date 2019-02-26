#include <Wire.h> // maybe we can remove this
#include <LiquidCrystal_I2C.h>

#define INPUT_BUTTON 2
#define ENTER_BUTTON 3
#define LED_PIN 13

// variables will change:      
byte lastButtonState=0, buttonState;
char keyPresses[10], inputString[10];
int  inputStart, inputStop, inputTime;
int  currentIndex = 0, currentStringIndex = 0, resetCount = 0;
unsigned long lastInterruptTime=0;
char *target = "HOOS";

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_BUTTON, INPUT);
  attachInterrupt(1, handleEnter, RISING);
}

void loop() {
  if (!strcmp(inputString, target)) success(); 
  
  buttonState = digitalRead(INPUT_BUTTON);
  if (buttonState!=lastButtonState){
    if (buttonState == HIGH) {
      digitalWrite(LED_PIN, HIGH);
      inputStart=millis();
    } else {
      digitalWrite(LED_PIN, LOW);
      inputStop=millis();
      inputTime=inputStop-inputStart;
      keyPresses[currentIndex] = inputTime < 300 ? '0' : '1';
      currentIndex++;
    } 
    delay(100);
  }
  lastButtonState=buttonState;
}

void handleEnter() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime < 200) {
    return;
  }
  lastInterruptTime=millis();

  char res = findChar();
  if (res == '\0') {
    Serial.println(resetCount);
    resetCount=resetCount+1;
    if (resetCount >= 3) reset();
  }
  else if (res != '!') {
    printLCD(res);
    inputString[currentStringIndex] = res;
    currentStringIndex++;
    resetCount=0;
  }
  else {
    Serial.println("That's not Morse Code!");
    printLCD("NOT MORSE CODE");
  }
  
  currentIndex=0;
  Serial.println(inputString);
  return;
}

void reset() {
  Serial.println("RESET");
  printLCD("RESET");
  for (int i=0; i < 10; i++) { keyPresses[i] = '\0'; inputString[i] = '\0'; }
  resetCount = currentStringIndex = 0;
}

void success() {
  Serial.println("SUCCESS");
  printLCD("SUCCESS");
  exit(0);
}

void printLCD(char c[]) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.printstr(c);
}

// keyPresses is a byte array
// 0 associated with dot
// 1 associated with dash
// returns character represented by some input
char findChar() {
  String morseLetter;
  for(int i=0;i<currentIndex; i++)
    morseLetter+=keyPresses[i];
  if (morseLetter == "01") {
    return 'A';
  } else if (morseLetter == "1000") {
    return 'B';
  } else if (morseLetter == "1010") {
    return 'C';
  } else if (morseLetter == "100") {
    return 'D';
  } else if (morseLetter == "0") {
    return 'E';
  } else if (morseLetter == "0010") {
    return 'F';
  } else if (morseLetter == "110") {
    return 'G';
  } else if (morseLetter == "0000") {
    return 'H';
  } else if (morseLetter == "00") {
    return 'I';
  } else if (morseLetter == "0111") {
    return 'J';
  } else if (morseLetter == "101") {
    return 'K';
  } else if (morseLetter == "0100") {
    return 'L';
  } else if (morseLetter == "11") {
    return 'M';
  } else if (morseLetter == "10") {
    return 'N';
  } else if (morseLetter == "111") {
    return 'O';
  } else if (morseLetter == "0110") {
    return 'P';
  } else if (morseLetter == "1101") {
    return 'Q';
  } else if (morseLetter == "010") {
    return 'R';
  } else if (morseLetter == "000") {
    return 'S';
  } else if (morseLetter == "1") {
    return 'T';
  } else if (morseLetter == "001") {
    return 'U';
  } else if (morseLetter == "0001") {
    return 'V';
  } else if (morseLetter == "011") {
    return 'W';
  } else if (morseLetter == "1001") {
    return 'X';
  } else if (morseLetter == "1011") {
    return 'Y';
  } else if (morseLetter == "1100") {
    return 'Z';
  } else if (morseLetter == "010101") {
    return '.';
  } else if (morseLetter == "110011") {
    return ',';
  } else if (morseLetter == "001100") {
    return '?';
  } else if (morseLetter == "10010") {
    return '/';
  } else if (morseLetter == "011010") {
    return '@';
  } else if (morseLetter == "01111") {
    return '1';
  } else if (morseLetter == "00111") {
    return '2';
  } else if (morseLetter == "00011") {
    return '3';
  } else if (morseLetter == "00001") {
    return '4';
  } else if (morseLetter == "00000") {
    return '5';
  } else if (morseLetter == "10000") {
    return '6';
  } else if (morseLetter == "11000") {
    return '7';
  } else if (morseLetter == "11100") {
    return '8';
  } else if (morseLetter == "11110") {
    return '9';
  } else if (morseLetter == "11111") {
    return '0';
  } else if (morseLetter == "") {
    return '\0';
  } else {
    return '!';
  }
}
