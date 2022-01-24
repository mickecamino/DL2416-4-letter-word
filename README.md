# DL2416-4-letter-word
Arduino code for DL2416 as a 4-letter word display
Just something I put together, does not need external memory.
No complete wordlist due to copyright reasons.
Add a string of 4-letter words here:
```
static const char fourletterwords[] PROGMEM = {"ABERACNEADELADLA...."};
```
And after you have added all your words, count them and put the result here:
NOTE: I have 8488 characters in my code.
YMMV
```
   // 8488 characters divided by 4 = 2122 words, so 2121 is the largest random number we can have
    randomnumber = random(0,2121); // Get a random number between 0 and 2121 (return is float)
```
Uses this library: https://github.com/ontuo/DL2416-Arduino-library
