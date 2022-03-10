#ifndef EuclidSequence_h
#define EuclidSequence_h

#include "Arduino.h"
#include <math.h>

class EuclidSequence {
public:

    
    const float maxSampleVolume = 0.4;
    uint16_t number;
    uint16_t pattern;
    uint16_t steps;
    uint16_t hits;
    uint16_t prevPattern;
    uint16_t prevSteps;
    uint16_t prevHits;
    uint16_t patternOffset;
    uint16_t sampleNum;
    uint16_t volume;
    unsigned int *sample;

public:
    EuclidSequence(uint16_t number);
    void updatePattern(uint16_t newSteps, uint16_t newHits, uint16_t newPatternOffset);
    bool getStep(uint16_t stepNum);
    bool getPrevStep(uint16_t stepNum);
    void getPattern();
    bool incrementSteps(int value);
    bool incrementHits(int value);
    bool incrementOffset(int value);
    bool incrementVolume(int value);
    float getVol();
    String getString();
    void flipStep(uint16_t stepNum);
    
};

#endif
