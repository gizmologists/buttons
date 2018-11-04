#define INPUT_BUTTON 2
#define ENTER_BUTTON 3
const int ledPin =  13;

// variables will change:      
byte lastButtonState=0;
char keyPresses[10];
char inputString[10];
int  inputStart,inputStop;
int currentIndex=0;
int currentStringIndex=0;
int resetCount=0;
unsigned long lastInterruptTime=0;
void handleEnter();
char *target = "HOOS";

void setup() {
  Serial.begin(115200);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(INPUT_BUTTON, INPUT);
  attachInterrupt(1, handleEnter, RISING);
}

void loop() {
  byte buttonState;
  if (!strcmp(inputString, target)) success();
  buttonState = digitalRead(INPUT_BUTTON);
  if (buttonState!=lastButtonState){
    if (buttonState == HIGH) {
      digitalWrite(ledPin, HIGH);
      inputStart=millis();
    } else {
      digitalWrite(ledPin, LOW);
      inputStop=millis();
      int inputTime=inputStop-inputStart;
      keyPresses[currentIndex]=inputTime < 300 ? '0' : '1';
      currentIndex++;
    } 
    delay(25);
    lastButtonState=buttonState;
  }
}

void handleEnter() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime < 200) {
    return;
  }
  lastInterruptTime=millis();

  char res = findChar();
  if (res != ' ' && res != 'x') {
    inputString[currentStringIndex] = res;
    currentStringIndex++;
    resetCount=0;
  } else if (res == 'x') {
    Serial.println(resetCount);
    resetCount=resetCount+1;
    if (resetCount >= 3)
      reset();
  }
  currentIndex=0;
  Serial.println(inputString);
  return;
}

void reset() {
  Serial.println("cleared");
  for (int i=0; i < 10; i++) { keyPresses[i] = '\0'; inputString[i] = '\0'; }
  resetCount = currentStringIndex = 0;
}

void success() {
  Serial.println("SUCCESS");
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
    return 'x';
  } else {
    return ' ';
  }
}
