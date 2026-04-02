#ifndef BUZZER_NOTES_H
#define BUZZER_NOTES_H

// ---------------------------------------------------------------------------
// Structs
// ---------------------------------------------------------------------------

struct Note {
  const char* name;
  int freq;
};

struct SongStep {
  int freq;      // 0 = rest
  int duration;  // milliseconds
};

// ---------------------------------------------------------------------------
// Utility macro
// ---------------------------------------------------------------------------

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

// ---------------------------------------------------------------------------
// Note length constants (ms)
// ---------------------------------------------------------------------------

#define LEN_SIXTEENTH   75
#define LEN_EIGHTH     150
#define LEN_QUARTER    300
#define LEN_HALF       600
#define LEN_WHOLE     1200

// ---------------------------------------------------------------------------
// Natural note table — B3 through C6 (approximate frequencies for buzzer)
// ---------------------------------------------------------------------------

const Note NOTES[] = {
  {"B3",  147},
  {"C4",  202},
  {"D4",  257},
  {"E4",  312},
  {"F4",  367},
  {"G4",  422},
  {"A4",  477},
  {"B4",  532},
  {"C5",  587},
  {"D5",  642},
  {"E5",  697},
  {"F5",  752},
  {"G5",  807},
  {"A5",  862},
  {"B5",  917},
  {"C6",  972}
};

// ---------------------------------------------------------------------------
// Example song: Ode to Joy (Beethoven, Symphony No. 9, 4th movement theme)
// ---------------------------------------------------------------------------

const SongStep ODE_TO_JOY[] = {
  // Bar 1
  {587, LEN_QUARTER},   // C5
  {587, LEN_QUARTER},   // C5
  {642, LEN_QUARTER},   // D5
  {697, LEN_QUARTER},   // E5

  // Bar 2
  {697, LEN_QUARTER},   // E5
  {642, LEN_QUARTER},   // D5
  {587, LEN_QUARTER},   // C5
  {532, LEN_QUARTER},   // B4

  // Bar 3
  {587, LEN_QUARTER},   // C5 (original had C5 here; A4 per strict melody)
  {587, LEN_QUARTER},   // C5
  {642, LEN_QUARTER},   // D5
  {697, LEN_QUARTER},   // E5

  // Bar 4
  {697, LEN_HALF},      // E5
  {642, LEN_EIGHTH},    // D5
  {642, LEN_HALF},      // D5
  {  0, LEN_QUARTER},   // rest

  // Bar 5
  {587, LEN_QUARTER},   // C5
  {587, LEN_QUARTER},   // C5
  {642, LEN_QUARTER},   // D5
  {697, LEN_QUARTER},   // E5

  // Bar 6
  {697, LEN_QUARTER},   // E5
  {642, LEN_QUARTER},   // D5
  {587, LEN_QUARTER},   // C5
  {532, LEN_QUARTER},   // B4

  // Bar 7
  {587, LEN_QUARTER},   // C5
  {587, LEN_QUARTER},   // C5
  {642, LEN_QUARTER},   // D5
  {697, LEN_QUARTER},   // E5

  // Bar 8
  {642, LEN_HALF},      // D5
  {587, LEN_EIGHTH},    // C5
  {587, LEN_HALF}       // C5
};

#endif // BUZZER_NOTES_H
