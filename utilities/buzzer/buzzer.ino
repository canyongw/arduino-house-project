#include <BuzzerESP32.h>

BuzzerESP32 buzzer(25); // Initialize buzzer on GPIO25

/*
void setup_tones(){
  //#define A3 92  
  #define B3 147
  #define C4 202
  #define D4 257
  #define E4 532 
  #define F4 312 
  #define G4 367
  #define A4 422  
  #define B4 477
  #define C5 532  // middle c
  #define D5 587
  #define E5 642 
  #define F5 697
  #define G5 752
  #define A5 807   
  #define B5 862
  #define C6 917  
}
*/

/*
void note_leangth(){
  #define sixteenth 75
  #define eighth 150
  #define quarter 300
  #define half 600
  #define whole 1200
}
*/

//[3 (number of rows),4 (number of columns)]
//     name   freq
//1    "A3"   90
//2
//3

//[16 note]
//    note
//    note1
//    note2

class Note{
  public:
    int freq;
    String name;
    // instantiation construtor
    Note(String name_, int freq_) : freq(freq_), name(name_) {}
};

#define ARRAY_LENGTH(arrayName) (sizeof(arrayName) / sizeof(arrayName[0]))
#define testLength 100

void test_tuner(){
  /* 
  *Note notes[] = {
    new Note("A3", 92),
    new Note("A4", 422),
    new Note("B5", 862),
  };
  */

  Note notes[] = {
    {"A3", 92},
    //{"A4", 422},
    //{"B5", 862},
  };
  

  int arrlen = ARRAY_LENGTH(notes);
  for (int i = 0; i < arrlen; i++){
     Note cNote = notes[i];
     int noteLow = cNote.freq - 30;
     int noteHigh = cNote.freq + 30;
     //buzzer.playTone(cNote.freq);
     for (int f = noteLow; f <= noteHigh; f++){
      buzzer.playTone(f,testLength);
      //watching for push button
      //if button push then 
      Serial.print("Note ");
      Serial.print(cNote.name);
      Serial.print(" captured | Freq: ");
      Serial.print(f);
      Serial.print(" Original Freq: ");
      Serial.println(cNote.freq);
     }

  }
}

class BuzzerNotesClass {
  private:
    int octave;
  public:
    BuzzerNotesClass(int initialoctave){
      octave = initialoctave;
    }

    //collection of notes added here
};

BuzzerNotesClass bn(3);

struct BNLength {
  int sixteenth = 75;
  int eighth = 150;
  int quarter = 300;
  int half = 600;
  int whole = 1200;
};

struct BNNote {
  int A3;
  int B3;
  int C4;
  int D4;
  int E4;
  int F4;
  int G4;
  int A4;
};




/*
void ode_to_joy(){
  //buzzer.playTone(C5,quarter);
  buzzer.playTone(C5,BNLength.quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(B4,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(E5,half);
  buzzer.playTone(D5,eighth);
  buzzer.playTone(D5,half);
  delay (quarter); // rest
  buzzer.playTone(C5,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(B4,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(C5,quarter);
  buzzer.playTone(D5,quarter);
  buzzer.playTone(E5,quarter);
  buzzer.playTone(D5,half);
  buzzer.playTone(C5,eighth);
  buzzer.playTone(C5,half);
  }
*/




void setup()
{
  Serial.begin(9600);
  buzzer.setTimbre(30); // Set timbre (sound quality)
  //setup_tones();
  //note_length();
  //ode_to_joy();
  test_tuner();
}
void loop(){

}

  




