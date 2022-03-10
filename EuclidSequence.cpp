#include "EuclidSequence.h"

EuclidSequence::EuclidSequence(uint16_t number) {
    this->number = number;
    pattern = 0;
    steps = 0;
    hits = 0;
    prevPattern = 0;
    prevSteps = 0;
    prevHits = 0;
    patternOffset = 0;
    volume = 70;
}

void EuclidSequence::updatePattern(uint16_t newSteps, uint16_t newHits, uint16_t newPatternOffset) {
    prevPattern = pattern;
    pattern = 0;
    prevSteps = steps;
    prevHits = hits;
    steps = newSteps;
    hits = newHits;
    patternOffset = newPatternOffset;
    getPattern();
}

bool EuclidSequence::getStep(uint16_t stepNum) {
    return pattern & (1<<stepNum);
}

bool EuclidSequence::getPrevStep(uint16_t stepNum) {
    return prevPattern & (1<<stepNum);
}

bool EuclidSequence::incrementSteps(int value) {
    if (value == 1 && steps < 16) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        ++steps;
        getPattern();
        return true;
    } else if (value == -1 && steps > 0) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        --steps;
        getPattern();
        return true;
    }
    return false;
}

bool EuclidSequence::incrementHits(int value) {
    if (value == 1 && hits < steps) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        ++hits;
        getPattern();
        return true;
    } else if (value == -1 && hits > 0) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        --hits;
        getPattern();
        return true;
    }
    return false;
}

bool EuclidSequence::incrementOffset(int value) {
    if (value == 1 && patternOffset < steps) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        ++patternOffset;
        getPattern();
        return true;
    } else if (value == -1 && patternOffset > 0) {
        prevPattern = pattern;
        pattern = 0;
        prevSteps = steps;
        prevHits = hits;
        --patternOffset;
        getPattern();
        return true;
    }
    return false;
}

bool EuclidSequence::incrementVolume(int value) {
    if (value == 1 && volume < 99) {
        volume++;
        return true;
    } else if (value == -1 && volume > 0) {
        volume--;
        return true;
    }
    return false;
}

float EuclidSequence::getVol() {
    if (volume) return maxSampleVolume * ((float)volume / 99.0);
    return 0.0;
}

void EuclidSequence::getPattern() {

    if (hits == 0) {
        pattern &= 0;  
    } else if (hits == steps) {
        pattern |= 0xFFFF;  
    } else {
        float slope = (float)hits / (float)steps;
        int yCur = 0;
        int yPrev = 0;
        for (int i=0; i < steps; i++) {
            yCur = slope*(float)(i+1);
            if (yCur != yPrev) {
                pattern |= (32768>>(16-steps))>>i;
            }
            yPrev = yCur;
        }
        if (patternOffset) {
            uint16_t upper = 0 | (pattern<<patternOffset);
            uint16_t lower = 0 | (pattern>>(16-patternOffset));
            pattern = 0 | (upper|lower);  
        }
    }
}

void EuclidSequence::flipStep(uint16_t stepNum) {
    prevSteps = steps;
    prevPattern = pattern;
    if (pattern & (1<<stepNum)) {
        pattern ^= (1<<stepNum);
    } else {
        pattern |= (1<<stepNum);
    }
}

String EuclidSequence::getString() {
    return "Steps: " + String(steps) + "  Hits: " + String(hits) + "  Offset: " + String(patternOffset) + "  Pattern: " + String(pattern, BIN);
}
