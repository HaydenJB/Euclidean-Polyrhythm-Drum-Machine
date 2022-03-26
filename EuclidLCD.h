#ifndef EuclidLCD_h
#define EuclidLCD_h
#include "Arduino.h"
#include <LiquidCrystal.h>

class EuclidLCD {
     private:
        String getNumString(uint16_t num);
        LiquidCrystal *lcd;
        const String parameterScreenTextR0 = "ST 0  HT 0  OF 0";
        const String parameterScreenTextR1 = "SEQ 1 VOL 70";
        
        const int stepRow = 0;
        const int stepCol = 2;
        const int hitRow = 0;
        const int hitCol = 8;
        const int offsetRow = 0;
        const int offsetCol = 14;
        const int sequenceRow = 1;
        const int sequenceCol = 3;
        const int volumeRow = 1;
        const int volumeCol = 10;
        const int cursorRow = 1;
        // Character maps for rest and hit in sequencer mode
        const byte restChar[8] = {
            0b00000,
            0b11111,
            0b10001,
            0b10001,
            0b10001,
            0b10001,
            0b11111,
            0b00000
        };
        const byte hitChar[8] = {
            0b00000,
            0b11111,
            0b10101,
            0b11011,
            0b11011,
            0b10101,
            0b11111,
            0b00000
        };
        
    public:

        int cursorPosition = 0;
        EuclidLCD(int RS, int Enable, int D4, int D5, int D6, int D7);

        void setSteps(uint16_t steps);
        void setHits(uint16_t hits);
        void setOffset(uint16_t offset);
        void setSequence(uint16_t sequence);
        void setVolume(uint16_t volume);
        void initStepSequencerMode(uint16_t pattern, uint16_t steps);
        void initEuclidMode(uint16_t steps, uint16_t hits, uint16_t offset);
        void initVolMode(uint16_t sequence, uint16_t vol);
        void moveStepCursor(int num, uint16_t steps);
};





#endif
