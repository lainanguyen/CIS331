// C++ code
//
//Used code from https://www.tutorialkart.com/c-programming/c-find-index-of-specific-element-in-array/ - comment on section

const unsigned int LIGHTUP = 1;

//This function is for printing statements in the serial monitor so we know it is working
void lightOn(int time) {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("LIGHT SHOULD BE ON");
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
}

//This function is for the startup once the board is ran or reset
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

//Alphabet 26 letters and 1 for space
const unsigned int MAX_MESSAGE_LENGTH = 27;

//Letter correlation to morse code
char letters[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};

static unsigned int morse[27] = {0b10111, 0b111010101, 0b11101011101, 0b1110101, 0b1, 0b101011101, 0b111011101, 0b1010101, 0b101, 0b1011101110111, 0b111010111, 0b101110101, 0b1110111, 0b11101, 0b11101110111, 0b10111011101, 0b1110111010111, 0b1011101, 0b10101, 0b111, 0b1010111, 0b101010111, 0b101110111, 0b11101010111, 0b1110101110111, 0b11101110101, 0b1111};

int morsecode[12] = {0,0,0,0,0,0,0,0,0};

 

//source https://www.tutorialkart.com/c-programming/c-find-index-of-specific-element-in-array/
int indexOf(char letter){
    int arrLen = sizeof letters/sizeof letters[0];
    int index = -1;
  char x = letter;

    for (int i = 0; i < arrLen; i++) {
        if (letters[i] == x) {
            index = i;
            break;
        }
    }

    if (index > -1) {
        printf("Index : %d\n", index);
    } else {
        printf("%d is not present in this array.\n", x);
    }
    return index;

}

//This function loops through the letters and outputs the corresponding morse code in blinks
//Code used from class
void loop()
{
  //static means GLOBAL variable, so it will save in between loops
  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int morseCodeLocation = 0;
  static int blinkLight[MAX_MESSAGE_LENGTH];

  //Refers to letters being sent through the serial monitor
  while(Serial.available() > 0) {


    //Takes one char from the serial monitor and stores it
  char inByte = tolower(Serial.read());

    
   if (inByte != '\n' && (morseCodeLocation < MAX_MESSAGE_LENGTH - 1)) {
      message[morseCodeLocation] = inByte;
      blinkLight[morseCodeLocation] = letters[indexOf(inByte)];
      morseCodeLocation++;
   }
  }

  
while(Serial.available() == 0 && morseCodeLocation > 0){
    int charLen = sizeof blinkLight / sizeof blinkLight[0];
    static int locationChar = 0;

    if (locationChar < charLen){
        //For blank spaces in phrase
        if (blinkLight[locationChar] != NULL){
          if (blinkLight[locationChar] == 0b1111){
            delay(4000);
           //For any characters in phrase the light blinks
          }else if (blinkLight[locationChar] & LIGHTUP == 1) {
              lightOn(1000);
            }else{
              delay(1000);
            }

      //This function shifts the morse character to the right by 1
        blinkLight[locationChar] = blinkLight[locationChar] >> 1;
        delay(200);
        } else{
          delay(3000);
            locationChar++;
        }
    }
  }
}
