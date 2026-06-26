#pragma once

#ifndef BUZZER_NOTES_H
#define BUZZER_NOTES_H



#define REST 0
// =============================================================
// Note Frequencies (Hz) - C4 to B5
// Rounded to nearest whole number integer values
// Naming Convention:
//   Natural : C4, D4, E4, F4, G4, A4, B4
//   Sharp   : Cs4 (C#4), Ds4 (D#4), etc.
//   Flat    : Db4 (Db4), Eb4 (Eb4), etc.
// =============================================================

// --- Octave 4 ---
// --- Octave  
#define C4 ((uint16_t)262)  // C4 = 261.63 Hz
#define Cs4 ((uint16_t)277)  // C#4 = 277.18 Hz
#define Db4 ((uint16_t)277)  // Db4 = 277.18 Hz
#define D4 ((uint16_t)294)  // D4 = 293.66 Hz
#define Ds4 ((uint16_t)311)  // D#4 = 311.13 Hz
#define Eb4 ((uint16_t)311)  // Eb4 = 311.13 Hz
#define E4 ((uint16_t)330)  // E4 = 329.63 Hz
// no e-sharp       
#define F4 ((uint16_t)349)  // F4 = 349.23 Hz
#define Fs4 ((uint16_t)370)  // F#4 = 369.99 Hz
#define Gb4 ((uint16_t)370)  // Gb4 = 369.99 Hz
#define G4 ((uint16_t)392)  // G4 = 392 Hz
#define Gs4 ((uint16_t)415)  // G#4 = 415.3 Hz
#define Ab4 ((uint16_t)415)  // Ab4 = 415.3 Hz
#define A4 ((uint16_t)440)  // A4 = 440 Hz
#define As4 ((uint16_t)466)  // A#4 = 466.16 Hz
#define Bb4 ((uint16_t)466)  // Bb4 = 466.16 Hz
#define B4 ((uint16_t)494)  // B4 = 493.88 Hz
       
// --- Octave       
#define C5 ((uint16_t)523)  // C5 = 523.25 Hz
#define Cs5 ((uint16_t)554)  // C#5 = 554.37 Hz
#define Db5 ((uint16_t)554)  // Db5 = 554.37 Hz
#define D5 ((uint16_t)587)  // D5 = 587.33 Hz
#define Ds5 ((uint16_t)622)  // D#5 = 622.25 Hz
#define Eb5 ((uint16_t)622)  // Eb5 = 622.25 Hz
#define E5 ((uint16_t)659)  // E5 = 659.25 Hz
// no e-sharp       
#define F5 ((uint16_t)698)  // F5 = 698.46 Hz
#define Fs5 ((uint16_t)740)  // F#5 = 739.99 Hz
#define Gb5 ((uint16_t)740)  // Gb5 = 739.99 Hz
#define G5 ((uint16_t)784)  // G5 = 783.99 Hz
#define Gs5 ((uint16_t)831)  // G#5 = 830.61 Hz
#define Ab5 ((uint16_t)831)  // Ab5 = 830.61 Hz
#define A5 ((uint16_t)880)  // A5 = 880 Hz
#define As5 ((uint16_t)932)  // A#5 = 932.33 Hz
#define Bb5 ((uint16_t)932)  // Bb5 = 932.33 Hz
#define B5 ((uint16_t)988)  // B5 = 987.77 Hz

// Note lengths in ticks (defining a "tick" as 1/16th note)
// This will allow us to control BPM
// since there are 60,000 ms in a minute, considering 60 bpm, 1/16th note = 1000 ms = 1 second
//                                        considering 120 bpm, 1/16th note = 250 ms = .25 seconds
//see tickMs(uint8_t) function
#define LEN_WHOLE ((uint8_t)16)
#define LEN_HALF ((uint8_t)8)     
#define LEN_QUARTER ((uint8_t)4)  
#define LEN_EIGHTH ((uint8_t)2)   
#define LEN_SIXTEENTH ((uint8_t)1)

#endif