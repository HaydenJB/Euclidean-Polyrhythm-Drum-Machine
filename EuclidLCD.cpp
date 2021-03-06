#include "EuclidLCD.h"

EuclidLCD::EuclidLCD(int RS, int Enable, int D4, int D5, int D6, int D7) {
    lcd = new LiquidCrystal(RS, Enable, D4, D5, D6, D7);
    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(parameterScreenTextR0);
    lcd->setCursor(0, 1);
    lcd->print(parameterScreenTextR1);
    lcd->createChar(1, restChar);
    lcd->createChar(2, hitChar);
}

void EuclidLCD::setSteps(uint16_t steps) {  
    lcd->setCursor(stepCol, stepRow);
    lcd->print(getNumString(steps));
    lcd->setCursor(cursorPosition, cursorRow);
}

void EuclidLCD::setHits(uint16_t hits) {
    lcd->setCursor(hitCol, hitRow);
    lcd->print(getNumString(hits));
    lcd->setCursor(cursorPosition, cursorRow);
}

void EuclidLCD::setOffset(uint16_t offset) {
    lcd->setCursor(offsetCol, offsetRow);
    lcd->print(getNumString(offset));
    lcd->setCursor(cursorPosition, cursorRow);  
}

void EuclidLCD::setSequence(uint16_t sequence) {
    lcd->setCursor(sequenceCol, sequenceRow);
    lcd->print(getNumString(sequence));  
    lcd->setCursor(cursorPosition, cursorRow);
}

void EuclidLCD::setVolume(uint16_t volume) {
    lcd->setCursor(volumeCol, volumeRow);
    lcd->print(getNumString(volume)); 
    
}

void EuclidLCD::initEuclidMode(uint16_t steps, uint16_t hits, uint16_t offset) {
    //lcd->noBlink();
    lcd->setCursor(0,0);
    lcd->print(parameterScreenTextR0);
    setSteps(steps);
    setHits(hits);
    setOffset(offset);
    lcd->setCursor(cursorPosition, cursorRow);
}

void EuclidLCD::moveStepCursor(int num, uint16_t steps) {
   if (num == 1 && cursorPosition < steps) {
      cursorPosition++;
      lcd->setCursor(cursorPosition, cursorRow);
   } else    if (num == -1 && cursorPosition > 0) {
      cursorPosition--;
      lcd->setCursor(cursorPosition, cursorRow);
   }
}

void EuclidLCD::initVolMode(uint16_t sequence, uint16_t vol) {
    lcd->noBlink();
    lcd->setCursor(0, 1);
    lcd->print(parameterScreenTextR1);
    setSequence(sequence);
    setVolume(vol);
    cursorPosition = 0;
}

void EuclidLCD::initStepSequencerMode(uint16_t pattern, uint16_t steps) {
    
    lcd->setCursor(0, 1);
    
    lcd->print("                "); 
    byte printArray[16];
    for (int i=0; i < steps; i++) {
        if (pattern & (1U<<i)) {
            printArray[i] = (byte)2U;
        } else {
            printArray[i] = (byte)1U;
        }
    }
    lcd->setCursor(0,1);
    lcd->write(printArray, steps);
    lcd->setCursor(0, 1);
    lcd->blink();
    lcd->setCursor(cursorPosition, 1);
    
}

String EuclidLCD::getNumString(uint16_t num) {
    if (num < 10) {
        return " " + String(num);
    }
    return String(num);
}
