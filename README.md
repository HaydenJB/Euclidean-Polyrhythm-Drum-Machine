# Euclidean Polyrhythm Drum Machine  

8 Voice Drum Machine capable of easily generating polyrhythmic patterns using Euclids Algorithm or a Step Sequencer Interface.

The main idea of this drum machine is to generate Eculidean Rhythms to easily create complex polyrhythmic drum sequences.

The drum machine is made using a Teensy 4.0 and the Rev-D audio board avaliable from [PRJC](https://www.pjrc.com/store/teensy3_audio.html). As well as 4 rotary encoders with push buttons, two pushbuttons and a 16X2 Character LCD screen (schematics and build information to be added).

## Codebase  
[Link to Code](https://github.com/HaydenJB/Euclidean-Polyrhythm-Drum-Machine)
  
  
### Euclidean Rhythms
Euclidean Rhythms are a set of rhythms that can be generated using [Euclids Algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm) for computing the greatest common divisor of two numbers. Euclidan rhythms were first categorised by Computer Scientest Godfried Toussaint in his 2005 paper 'The Euclidean Algorithm Generates Traditional Musical Rhythms'. (The paper can be found [here](http://cgm.cs.mcgill.ca/~godfried/publications/) for a more in depth explination )

Euclidiean Rhythms can be generated by taking a number of steps in a musical bar and evenly dividing a number of hits into a bar of music. The resulting pattern will have hits that are spread out as evenly as possible through the bar while still falling on steps in the bar.  
Rest = . Hit = x bar of music = ||  
For example with 8 steps and 4 hits the resulting pattern would be |x.x.x.| When numbers that do not divide evenly are used more complex patterns are created. The Tressilo one of the most fundamental rhythms in Latin American Music that is also found commonly in traditional music from Sub-Saharan Africa can be generated using 8 steps and 3 hits giving the following pattern |x..x..x.|
The drum machine also has the ability to change the offset of the pattern which shifts the starting position of the pattern. For example the previous pattern with an offset of 1 would be |.x..x..x|. With an offset of 2 |x.x..x..|. With an offset of 3 |.x.x..x.| ect.  
Below is an example of these patterns played on the drum machine with some more euclidean rhythms added later in the video.

[![Euclidean Rhythm Examples](http://img.youtube.com/vi/eEuRsu0KcMs/0.jpg)](https://www.youtube.com/watch?v=eEuRsu0KcMs "Euclidean Rhythm Examples")
  
  
### Polyrhythms
Polyrhythms are rhythms consisting of two or more parts that are not perceived to originate form the same time division or signiture. Polyrhythms are very common in Afro-Cuban and West African music both of which greatly inspired making this drum machine. A common polyrhythm found throught the world is the Hemiola. A hemiola consists of 4 even hits played over 4 even beats.  
Below is an example of these patterns played on the drum machine with some more polyrhythms added later in the video.  

[![Polyrhythm Examples](http://img.youtube.com/vi/n21XgvG8Wkc/0.jpg)](https://www.youtube.com/watch?v=n21XgvG8Wkc "Polyrhythm Examples")

### Features To Be Added 
Tempo Control  
MIDI output   
Master Volume   
Load different samples from an SD card   
ADSR envelope for each sample  
Allow for sequencing of multiple bars containing different patterns  
Patch bank that allows for storing/retrival of patterns  

Schematics and detials on how to build/modify the project   


