#include <BuzzerESP32.h>
//#include "buzzer_notes.h"
#include "buzzer_songs.h"

#define BUZZER_PIN   25
#define BUTTON_PIN   16
#define TUNE_SWEEP   30   // ±Hz around each note's approximate freq
#define TUNE_STEP_MS 300  // ms per frequency step during sweep

BuzzerESP32 buzzer(BUZZER_PIN);

// ---------------------------------------------------------------------------
// playSong — play an array of SongSteps; freq == 0 is treated as a rest
// ---------------------------------------------------------------------------

void playSong(const SongStep* song, int length) {
  for (int i = 0; i < length; i++) {
    if (song[i].freq == 0) {
      delay(song[i].duration);
    } else {
      buzzer.playTone(song[i].freq, song[i].duration);
    }
  }
}

// ------------------------------------------------
// playSoung2 - alternative, allows for BPM choice
// ------------------------------------------------

void playSong2(const SongStep* song, int bpm) {
  for (auto &step : song) {
    uint32_t dur = (uint32_t)step.duration * ticksMs(bpm);
    if (step.freq == 0) {
      buzzer.stop();  // arbitrary
      delay(dur)
    } else {
      if (step.slur == 1){
        buzzer.playTone(step.freq, step.duration);
      } else {
        // induce slight separation by shaving 10 ms
        buzzer.playTone(step.freq, step.duration - 10)
      }
    }
  }
}

// convert ticks to milliseconds:
// quarter note duration (ms) = 60000 / BPM
// 1/16 note (tick) = (60000 / BPM) / 4 = 15000 / BPM
//
// as math (for clarity):
// 1 tick (ms) = 60000 / BPM * (1/4)
// indicate to compiler the intent to convert long to int
uint16_t tickMs(int bpm) {
  unsigned long t = 60000UL / bpm / 4;
  // uint16_t tms = t  // implicit cast can make the compiler compain, but could work
  uint32_t tms = static_cast<uint16_t>(t);
  return tms;
}

// ---------------------------------------------------------------------------
// runTuner — sweep each note in NOTES[] and capture on button press
// ---------------------------------------------------------------------------

void runTuner() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  int noteCount = ARRAY_LENGTH(NOTES);

  for (int i = 0; i < noteCount; i++) {
    const Note& n = NOTES[i];
    int freqLow  = n.freq - TUNE_SWEEP;
    int freqHigh = n.freq + TUNE_SWEEP;
    Serial.print("Starting note ");
    Serial.println(n.name);

    for (int f = freqLow; f <= freqHigh; f++) {
      buzzer.playTone(f, TUNE_STEP_MS);

      if (digitalRead(BUTTON_PIN) == LOW) {
        Serial.print("Captured note ");
        Serial.print(n.name);
        Serial.print(" captured | Freq: ");
        Serial.print(f);
        Serial.print(" | Original Freq: ");
        Serial.println(n.freq);

        delay(900); // debounce
        break;      // advance to next note
      }
    }
  }
}

// ---------------------------------------------------------------------------
// setup / loop
// ---------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  buzzer.setTimbre(30);
 // buzzer.
  //pinMode(BUTTON_PIN, INPUT_PULLUP);

  //runTuner();

  // Uncomment to play Ode to Joy after tuning completes:
  // playSong(ODE_TO_JOY, ARRAY_LENGTH(ODE_TO_JOY));
  playSong2(ODE_TO_JOY, 120)
}

void loop() {
  // empty — all work done in setup
}
