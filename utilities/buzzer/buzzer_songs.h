#pragma once

#ifndef BUZZER_SONGS_H
#define BUZZER_SONGS_H


#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#include "buzzer_notes2.h"

struct SongStep {
  uint16_t freq;  // uint8_t saves memory vs int
  uint8_t ticks; // number of 1/16 notes
  bool slur; // true or false to slur/tie notes
};

// save more SRAM by forcing to program memory
// not required for esp32, in place for board compatability
const SongStep ODE_TO_JOY[] PROGMEM = {
    // bar 1
  {A4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 1},
  {C5, LEN_QUARTER, 0},
  // bar 2
  {C5, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 1},
  {G4, LEN_QUARTER, 0},
  // bar 3
  {F4, LEN_QUARTER, 0},
  {F4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  // bar 4
  {A4, LEN_QUARTER + LEN_EIGHTH, 0},
  {G5, LEN_EIGHTH, 0},
  {G5, LEN_HALF, 0},
  
  // bar 5
  {A4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 0},
  {C5, LEN_QUARTER, 0},
  // bar 6
  {C5, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  // bar 7
  {F4, LEN_QUARTER, 0},
  {F4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  // bar 8
  {G4, LEN_QUARTER +  LEN_EIGHTH, 0},
  {F4, LEN_EIGHTH, 0},
  {F4, LEN_HALF, 0},
  
  // bar 9
  {G4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  {F4, LEN_QUARTER, 0},
  // bar 10
  {G4, LEN_QUARTER, 0},
  {A4, LEN_EIGHTH, 1},
  {Bb4, LEN_EIGHTH, 0},
  {A4, LEN_QUARTER, 0},
  {F4, LEN_QUARTER, 0},
  // bar 11
  {G4, LEN_QUARTER, 0},
  {A4, LEN_EIGHTH, 1},
  {Bb4, LEN_EIGHTH, 0},
  {A4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  // bar 12
  {F4, LEN_QUARTER, 1},
  {G4, LEN_QUARTER, 0},
  {C4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 1},
  // bar 13
  {A4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 0},
  {C5, LEN_QUARTER, 0},
  // bar 14
  {C5, LEN_QUARTER, 0},
  {Bb4, LEN_QUARTER, 0},
  {A4, LEN_EIGHTH, 1},
  {Bb4, LEN_EIGHTH, 0}, //flare
  {G4, LEN_QUARTER, 0},
  // bar 15
  {F4, LEN_QUARTER, 0},
  {F4, LEN_QUARTER, 0},
  {G4, LEN_QUARTER, 0},
  {A4, LEN_QUARTER, 0},
  // bar 16
  {G4, LEN_QUARTER + LEN_EIGHTH, 0},
  {F4, LEN_EIGHTH, 0},
  {F4, LEN_HALF, 0},
  // end
  {REST, LEN_QUARTER, 0}
};
#endif