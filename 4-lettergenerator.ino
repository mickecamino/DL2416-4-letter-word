// Print 4-letter word on a DL2416T
// Coded by Mikael Karlsson 2022-01-16
// Requires the https://github.com/ontuo/DL2416-Arduino-library
// I did modified it to suit my needs, hence why it's included in the code
//#include <DL2416T.h>

#define DEBUG false

// Define all pins here
    int D0  = 12; // Data bit 0 = 11 on display
    int D1  = 2;  // Data bit 1 = 12 on display
    int D2  = 3;  // Data bit 2 = 13 on display
    int D3  = 4;  // Data bit 3 = 14 on display
    int D4  = 5;  // Data bit 4 = 17 on display
    int D5  = 6;  // Data bit 5 = 16 on display
    int D6  = 7;  // Data bit 5 = 15 on display
    int BL  = 8;  //            = 18 on display
    int AD0 = 9;  // A0         =  9 on display
    int AD1 = 10; // A1         =  7 on display
    int CE1 = 11; // CE1        =  1 on display, tie #2 to ground (pin 2)
    int CLR = 13; // CLR        =  3 on display
    int WR  = 14; // WR         =  6 on display

    // All words that I could find in Swedish without extended characters
    // NOTE TO MYSELF, NEEDS TO BE UPPER CASE!!!!!!!!!! (don't ask me why I have this note here)
    static const char fourletterwords[] PROGMEM = {"ABERACNEADELADLA...."};

    int randomnumber; // holds the random number
    char myLetter;    // holds a character

// Setup routine
void setup() {
    // Initialize all pins, modified library
    DL2416Tinit(D0, D1, D2, D3, D4, D5, D6, AD0, AD1, WR, CE1, CLR, BL);
    randomSeed(analogRead(A4));  // Get a random value seed fron an empty analog port
}

// And loop away
void loop() {
    // 8488 characters divided by 4 = 2122 words, so 2121 is the largest random number we can have
    randomnumber = random(0,2121); // Get a random number between 0 and 2121 (return is float)
    int wordindex = (int) randomnumber * 4;  // Multiply the randowm word by 4 so we get to the right place in PROGMEM
    int position = 3; // the position of the character, display is backward, 3 is rightmost character

    for (byte i = 0; i < 4; i++) // Loop 4 times to get 4 characters
        {    
        myLetter = pgm_read_byte_near(fourletterwords + (i + wordindex) );  // Read a character from PROGMEM
        DL2416TsetLetter(myLetter, position);   // Display it
        position --; // Count down to 0, display is from right to left, 3 to 0
    }
    delay(4000);    // Wait some time
    // TODO:
    // Add RTC and code for it
} // loop


// set position in display, rightmost = 3 leftmost = 0
void setAdress(int position)
{
    digitalWrite(AD1, (position & 0b10) >> 1);
    digitalWrite(AD0, (position & 0b01) >> 0);
}

//will output the letter in the determined position
void DL2416TsetLetter(char letter, int position)
{
    setAdress(position);
    digitalWrite(WR, 0);
    digitalWrite(D6, (letter & 0b1000000) >> 6);
    digitalWrite(D5, (letter & 0b0100000) >> 5);
    digitalWrite(D4, (letter & 0b0010000) >> 4);
    digitalWrite(D3, (letter & 0b0001000) >> 3);
    digitalWrite(D2, (letter & 0b0000100) >> 2);
    digitalWrite(D1, (letter & 0b0000010) >> 1);
    digitalWrite(D0, (letter & 0b0000001) >> 0);
    digitalWrite(WR, 1);
}

void DL2416Tclear()
{
    digitalWrite(CLR, 0);
    //according to datasheet we need at least 1 sec to clear 
    delay(1000);
    digitalWrite(CLR, 1);
}

//turnOff will not delete anything, only dim the display

void DL2416TOff()
{
    digitalWrite(BL, 0);
}

void DL2416TturnOn()
{
    digitalWrite(BL, 1);
}

void DL2416TPrint(String word)
{
    int len = 0;
    if (word.length() > 4)
    {
        len = 4;
    }
    else
    {
        len = word.length();
    }
    for (int i = 0; i < len; i++)
    {
        int m = len - 1 - i;
        DL2416TsetLetter(word[i], m);
    }
}

void DL2416Tinit(uint8_t D0, uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6, uint8_t AD0, uint8_t AD1, uint8_t WR, uint8_t CE1, uint8_t CLR, uint8_t BL)
{
    // Set pins as outputs
    pinMode(D0,  OUTPUT);
    pinMode(D1,  OUTPUT);
    pinMode(D2,  OUTPUT);
    pinMode(D3,  OUTPUT);
    pinMode(D4,  OUTPUT);
    pinMode(D5,  OUTPUT);
    pinMode(D6,  OUTPUT);
    pinMode(WR,  OUTPUT);
    pinMode(CLR, OUTPUT);
    pinMode(CE1, OUTPUT);
    pinMode(BL,  OUTPUT);
    pinMode(AD0, OUTPUT);
    pinMode(AD1, OUTPUT);

    digitalWrite(WR,  HIGH); 
    digitalWrite(AD0, HIGH);
    digitalWrite(AD1, HIGH);
    digitalWrite(BL,  HIGH);
    digitalWrite(CLR, HIGH);
    digitalWrite(CE1, LOW);
}

