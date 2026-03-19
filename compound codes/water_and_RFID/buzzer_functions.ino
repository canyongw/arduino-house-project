#include <BuzzerESP32.h>

BuzzerESP32 gas_buzzer(25); // Initialize buzzer on GPIO25

#define beep_short 50
#define beep_med 250
#define beep_long 500
#define beep_reallylong 1000
int bpm = 120
// test to determine note length at 120 bpm
// start with whole note - buzzer should stop on 5th clap
// multiplier 0.83
#define note_sixteenth 100
#define note_eighth 200
#define note_quarter 400
#define note_half 800
#define note_whole 1600

boolean buzzer_buzzing = 0;  // prevent double-play

void setup_gas_buzzer()
{
  gas_buzzer.setTimbre(30); // Set timbre (sound quality)
}

// finish defining notes
#define C5 532 //slightly sharp
#define D5 587 //
#define E5 642
#define rest 0 // reste
#define C6

//canyonMusicCalc musicControler(120)
//gas_buzzer.playTone(musicControler.Tone.C5,musicControler.Note.Whole);
//gas_buzzer.playTone(musicControler.Tone.E5,musicControler.Note.Sixteenth);

void siren_buzzer(){
  if (buzzer_buzzing == 0){
    buzzer_buzzing = 1;
    for(int loop = 0; loop <= 3; loop++){
      for(int i = 0; i < 800; i++){
        gas_buzzer.playTone(i,4);

      }
      for(int i = 800; i > 0 ; i--){
        gas_buzzer.playTone(i,4);
      }
    }
    buzzer_buzzing = 0;
  }
}

void test_card_confirmation_beep(){
  if (buzzer_buzzing == 0) {
    buzzer_buzzing = 1;
    gas_buzzer.playTone(C5, note_whole);  // C5
    buzzer_buzzing = 0;
  }
}

void birthday()
{
  // Play birthday melody - parameters are (frequency, duration)
  gas_buzzer.playTone(294, 250);  // D4
  gas_buzzer.playTone(440, 250);  // A4
  gas_buzzer.playTone(392, 250);  // G4
  gas_buzzer.playTone(532, 250);  // C5 (slightly sharp)
  gas_buzzer.playTone(494, 250);  // B4
  gas_buzzer.playTone(392, 250);  // G4
  gas_buzzer.playTone(440, 250);  // A4
  gas_buzzer.playTone(392, 250);  // G4
  gas_buzzer.playTone(587, 250);  // D5
  gas_buzzer.playTone(532, 250);  // C5 (slightly sharp)
  gas_buzzer.playTone(392, 250);  // G4
  gas_buzzer.playTone(784, 250);  // G5
  gas_buzzer.playTone(659, 250);  // E5
  gas_buzzer.playTone(532, 250);  // C5 (slightly sharp)
  gas_buzzer.playTone(494, 250);  // B4
  gas_buzzer.playTone(440, 250);  // A4
  gas_buzzer.playTone(698, 250);  // F5
  gas_buzzer.playTone(659, 250);  // E5
  gas_buzzer.playTone(532, 250);  // C5 (slightly sharp)
  gas_buzzer.playTone(587, 250);  // D5
  gas_buzzer.playTone(532, 500);  // C5 (slightly sharp) - longer duration
  gas_buzzer.playTone(0, 0);      // Turn off buzzer
}