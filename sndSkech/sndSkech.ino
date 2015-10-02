//
//
// code for sonic device.
// created by takuma takahashi
// copyright (c)2015 takuma takahahsi all rights reserved.
//
//

//include MIDI library
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#define BUTTON_MAX 8

//  sets pin number
int pushButton[] = {2,3,4,5,6,7,8,9};

// checks if the button is pressed
int buttonState[] = {0,0,0,0,0,0,0,0};

// play / stop notes in relation to buttons pressed
int noteNum[] = {0,0,0,0,0,0,0,0};

// sets note number
int nn[] = {60,61,62,63,64,65,66,67};

// sets velocity parameter
int vel = 127;

// midi flag
bool flag_midi_on = false;
bool sw[] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
bool osw[]= {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};

void setup() {
    // Launch MIDI with default options
    MIDI.begin(4);
    
    // initializes buttons
    for(int i = 0; i < BUTTON_MAX; i++){
        //pinMode(pushButton[i], INPUT_PULLUP);
        pinMode(pushButton[i], INPUT);
    }
}

void loop() {
    // read state of buttons
    for(int i = 0; i < BUTTON_MAX; i++){
        buttonState[i] = digitalRead(pushButton[i]);
        sw[i] = digitalRead(pushButton[i]);
    }
    
    // checks ch.1 - ch.8
    for(int i = 0; i < BUTTON_MAX; i++){
        midiSend(i);
        osw[i] = sw[i];
    }
    
    delay(10);
    
}


// midi send fuction
void midiSend(int pin_num){
    
    // chattering code
    if(osw[pin_num] == HIGH && sw[pin_num] == HIGH){
        // if (buttonState[pin_num] == HIGH)
        if(!flag_midi_on){
            // if note not playing
            if (noteNum[pin_num] == 0) {
                // play note (note number, velocity, channel)
                //MIDI.sendNoteOn(nn[pin_num], vel, pin_num + 1);
                MIDI.sendNoteOn(nn[pin_num], vel, 1);
                // note is playing
                noteNum[pin_num] = 1;
                flag_midi_on = true;
            }
        }else{
            // if note playing
            if (noteNum[pin_num] == 1) {
                // if playing - stop
                //MIDI.sendNoteOff(0,0,pin_num + 1);
                MIDI.sendNoteOff(0,0,1);
            }
            // if button released note is off
            noteNum[pin_num] = 0;
        }
        // when button released
    } else {
        flag_midi_on = false;
        // if note playing
        if (noteNum[pin_num] == 1) {
            // if playing - stop
            //MIDI.sendNoteOff(0,0,pin_num + 1);
            MIDI.sendNoteOff(0,0,1);
        }
        // if button released note is off
        noteNum[pin_num] = 0;
    }
}
