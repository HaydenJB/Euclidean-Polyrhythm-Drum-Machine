/*
 * To Do
 * Add ability to load different samples from SD card
 */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TeensyAudioFlashLoader.h>

#include <Bounce2.h>
#include <RotaryEncoderDebounce.h>
#include <IntervalTimer.h>
#include "EuclidSequence.h"
#include "EuclidLCD.h"

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=91.19999694824219,173
AudioPlayMemory          playMem2;       //xy=93.19999694824219,207
AudioPlayMemory          playMem3;       //xy=93.19999694824219,244
AudioPlayMemory          playMem4;       //xy=94.19999694824219,279
AudioPlayMemory          playMem5;       //xy=95.19999694824219,335
AudioPlayMemory          playMem6;       //xy=97.19999694824219,369
AudioPlayMemory          playMem7;       //xy=97.19999694824219,406
AudioPlayMemory          playMem8;       //xy=98.19999694824219,441
AudioMixer4              mixer1;     //xy=310.20001220703125,177
AudioMixer4              mixer2;     //xy=325.20001220703125,346
AudioMixer4              mainMixer;      //xy=500.20001220703125,295
AudioOutputI2S           i2s1;           //xy=804.2000122070312,293
AudioConnection          patchCord1(playMem1, 0, mixer1, 0);
AudioConnection          patchCord2(playMem2, 0, mixer1, 1);
AudioConnection          patchCord3(playMem3, 0, mixer1, 2);
AudioConnection          patchCord4(playMem4, 0, mixer1, 3);
AudioConnection          patchCord5(playMem5, 0, mixer2, 0);
AudioConnection          patchCord6(playMem6, 0, mixer2, 1);
AudioConnection          patchCord7(playMem7, 0, mixer2, 2);
AudioConnection          patchCord8(playMem8, 0, mixer2, 3);
AudioConnection          patchCord9(mixer1, 0, mainMixer, 0);
AudioConnection          patchCord10(mixer2, 0, mainMixer, 2);
AudioConnection          patchCord11(mainMixer, 0, i2s1, 0);
AudioConnection          patchCord12(mainMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=671.2000122070312,109
// GUItool: end automatically generated code


#include "AudioSampleOne.h"
#include "AudioSampleTwo.h"
#include "AudioSampleThree.h"
#include "AudioSampleFour.h"
#include "AudioSampleCabassa.h"
#include "AudioSampleConga.h"
#include "AudioSampleWoodfeel.h"
#include "AudioSampleWoodmpc.h"

#define NUM_TICKS  4000
#define NUM_SAMPLES 8

void playSamples();
void writeTickStates(EuclidSequence *sequence);

IntervalTimer timer;
RotaryEncoderDebounce rotary1(16, 17);
RotaryEncoderDebounce rotary2(24, 25);
RotaryEncoderDebounce rotary3(28, 29);
RotaryEncoderDebounce rotary4(26, 27);

Bounce rotary1Button = Bounce();
Bounce rotary2Button = Bounce();
Bounce rotary3Button = Bounce();
Bounce rotary4Button = Bounce();

EuclidSequence *sequence1;
EuclidSequence *sequence2;
EuclidSequence *sequence3;
EuclidSequence *sequence4;
EuclidSequence *sequence5;
EuclidSequence *sequence6;
EuclidSequence *sequence7;
EuclidSequence *sequence8;
EuclidSequence *currentSequence;

byte tickStates[NUM_TICKS];
volatile uint16_t tickCount = 0;
Bounce rotButton1 = Bounce();
Bounce rotButton2 = Bounce();

Bounce nextSequenceButton = Bounce();
Bounce prevSequenceButton = Bounce();

EuclidLCD *lcd;

// display mode for line 0
bool volMode = true;

void updateValues();

void setup() {
    Serial.begin(19200);

    lcd = new EuclidLCD(0, 1, 2, 3, 4, 5);
    
    sequence1 = new EuclidSequence(0);
    sequence2 = new EuclidSequence(1);
    sequence3 = new EuclidSequence(2);
    sequence4 = new EuclidSequence(3);
    sequence5 = new EuclidSequence(4);
    sequence6 = new EuclidSequence(5);
    sequence7 = new EuclidSequence(6);
    sequence8 = new EuclidSequence(7);
    currentSequence = sequence1;
    
    
    nextSequenceButton.attach(33, INPUT_PULLUP);
    prevSequenceButton.attach(31, INPUT_PULLUP);

    nextSequenceButton.interval(1);
    prevSequenceButton.interval(1);

    rotary1Button.attach(22, INPUT_PULLUP);
    rotary2Button.attach(14, INPUT_PULLUP);
    rotary3Button.attach(30, INPUT_PULLUP);
    rotary4Button.attach(32, INPUT_PULLUP);

    rotary1Button.interval(1);
    rotary2Button.interval(1);
    rotary3Button.interval(1);
    rotary4Button.interval(1);
    
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.7);
    AudioMemory(20);

    // Set all volumes the same to begin with
    float vol = currentSequence->getVol();
    mixer1.gain(0, vol);
    mixer1.gain(1, vol);
    mixer1.gain(2, vol);
    mixer1.gain(3, vol);

    mixer2.gain(0, vol);
    mixer2.gain(1, vol);
    mixer2.gain(2, vol);
    mixer2.gain(3, vol);

    /* Interupt called every 500 microseconds. A 'tick' represents the finest resolution
     * in time playable by the drum machine. Drum samples are sequenced by playing the 
     * samples at the closest tick. With 4000 ticks a bar and a tick being called every
     * 500 microseconds the tempo is 120BPM with 16 steps representing 16th notes in a 
     * 4/4 time signiture.  
     */
    timer.begin(playSamples, 500);
}
int selectedSample = 1;
int sequenceIncrement = 0;
int sequenceSelect = 0;


void loop() {
    updateValues();
}

void updateValues() {
    // Update steps for current sequence
    if (1) {
        // updates only if steps values changes
        if (currentSequence->incrementSteps(rotary1.read())){       
            Serial.println("Steps = " + String(currentSequence->steps));
            writeTickStates(currentSequence);
            lcd->setSteps(currentSequence->steps); 
            if (!volMode) lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);
        }
        
    }

    // Update hits for current sequence
    if (1) {
        // updates only if hits values changes
        if (currentSequence->incrementHits(rotary2.read())){
            Serial.println("Hits = " + String(currentSequence->steps));
            writeTickStates(currentSequence);
            lcd->setHits(currentSequence->hits); 
            if (!volMode) lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);      
        }
        
    } 


    // Update offset for current sequence
    if (1) {
        // updates only if offset values changes
        if (currentSequence->incrementOffset(rotary3.read())){
            //Serial.println("Offset = " + String(currentSequence->steps));
            writeTickStates(currentSequence);
            lcd->setOffset(currentSequence->patternOffset);  
            for (int i=0; i < currentSequence->steps; i++) {
                Serial.print((int)(currentSequence->getStep(i)));   
            }
            Serial.println(""); 
            if (!volMode) lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);
        }
    }   
    
    if (volMode) {
        currentSequence->incrementVolume(rotary4.read());
        if (currentSequence->number < 4) {
            mixer1.gain(currentSequence->number, currentSequence->getVol());
        } else {
            
            mixer2.gain(currentSequence->number - 4, currentSequence->getVol());
        }

        lcd->setVolume(currentSequence->volume);
    } else {
        lcd->moveStepCursor(rotary4.read(), currentSequence->steps);
    }

    nextSequenceButton.update();
    prevSequenceButton.update();
    
    if (nextSequenceButton.fell()) sequenceIncrement = 1;
    if (prevSequenceButton.fell()) sequenceIncrement = -1;

    // change the currently selected sequence
    if (sequenceIncrement) {
        Serial.println("seqIncrement = " + String(sequenceIncrement));
        sequenceSelect += sequenceIncrement;
        if (sequenceSelect > 8) sequenceSelect = 1;
        if (sequenceSelect < 1) sequenceSelect = 8;   
        switch (sequenceSelect) {
            case (1):
                currentSequence = sequence1;
                break;
            case (2):
                currentSequence = sequence2;
                break;
            case (3):
                currentSequence = sequence3;
                break;
            case (4):
                currentSequence = sequence4;
                break;
            case (5):
                currentSequence = sequence5;
                break;
            case (6):
                currentSequence = sequence6;
                break;
            case (7):
                currentSequence = sequence7;
                break;
            case (8):
                currentSequence = sequence8;
                break;
        }
        sequenceIncrement = 0;

        // update display
        if (volMode) {
            lcd->setSequence(sequenceSelect);  
            lcd->setVolume(currentSequence->volume);    
        } else {
            lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);
        }
        lcd->setSteps(currentSequence->steps); 
        lcd->setHits(currentSequence->hits); 
        lcd->setOffset(currentSequence->patternOffset);            
    }

    rotary1Button.update();    
    rotary2Button.update();
    rotary3Button.update();
    rotary4Button.update();
    if (rotary1Button.fell()) {
        volMode = !volMode;
        Serial.println("Rotary Button 1");
        if (volMode) {
            lcd->initVolMode(currentSequence->number + 1, currentSequence->volume); 
        } else {
            lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);
        }
    }

    // Step sequencer mode rotary4 can be used to turn hits on or off manualy
    if (rotary4Button.fell()) {
        Serial.println("Rotary Button 2");
        Serial.println(currentSequence->getString());
        currentSequence->flipStep(lcd->cursorPosition);
        writeTickStates(currentSequence);
        Serial.println(currentSequence->getString());
        lcd->initStepSequencerMode(currentSequence->pattern, currentSequence->steps);
    }

    
//    if (rotary3Button.fell()) Serial.println("Rotary Button 3");
//    if (rotary4Button.fell()) Serial.println("Rotary Button 4");
    
}

// Interupt to be called every 4000th of a bar
void playSamples() {
    // if any bit is 1 some sample/s should be played
    if (tickStates[tickCount]) {
        if (tickStates[tickCount] & 1U) {
            playMem1.play(AudioSampleCabassa);       
            
        }
        if (tickStates[tickCount] & 2U){
            playMem2.play(AudioSampleConga);
            
        }
        if (tickStates[tickCount] & 4U){
            playMem3.play(AudioSampleWoodfeel);
            
        }
        if (tickStates[tickCount] & 8U){
            playMem4.play(AudioSampleWoodmpc);
        }
        if (tickStates[tickCount] & 16U) {
            playMem5.play(AudioSampleOne);        
        }
        if (tickStates[tickCount] & 32U){
            playMem6.play(AudioSampleTwo);
        }
        if (tickStates[tickCount] & 64U){
            playMem7.play(AudioSampleThree);
        }
        if (tickStates[tickCount] & 128U){
            playMem8.play(AudioSampleFour);
        }
    }

    // End of bar reached go back to start
    if (++tickCount >= NUM_TICKS) tickCount = 0;
}

/*
 * The drum machines resultant pattern for each sequence is stored in tickStates[]
 * each byte represents if a sample should be played on that 'tick' when the interupt
 * is called. The nth bit of each byte represents the nth sequence with the drum machine
 * having a total of 8 sequences. Each sequence plays a single sample. 
 * e.g if tickStates[0] = 0b00010001 then the sequence1 and sequence2's sample should
 * be played at the start of the bar
 * 
 * The drum machine patterns are stored this way for greater memory efficiancy since
 * the 8 samples stored in RAM take a significant amount of the avaliable memory.
 * By using a single byte to store if the seuquences are played on any tick using this 
 * method takes up only 4kB. If a 2D boolean array were used which would be 
 * easier to program it would take up 32kB. 
 * It also reduces the time the interupt is called for. Only one comparison is required
 * to check if anything needs to be played. This is preferable since the interupt is
 * called frequently and the majority of the time nothing is played 
 */
void writeTickStates(EuclidSequence *sequence) {
    uint16_t count = 0;
    // Check if hits from previous pattern should be removed
    if (sequence->prevSteps != 0) {
        // Divides number of steps evenly into a bar 
        for (int i=0; i < NUM_TICKS; i += NUM_TICKS / sequence->prevSteps) {
            if (sequence->getPrevStep(count++)) tickStates[i] ^= 1<<sequence->number;
        }
    }
    
    count = 0;
    // Add new hits to tickStates
    if (sequence->steps != 0) {
         // Divides number of steps evenly into a bar 
         for (int i=0; i < NUM_TICKS; i += NUM_TICKS / sequence->steps) {
            if (sequence->getStep(count++)) tickStates[i] |= 1 << sequence->number;
        }   
    }
}
