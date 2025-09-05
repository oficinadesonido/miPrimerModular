// ODES CHORDS v12
// Oficina de sonido 2024


#include <FastLED.h>

#include <MozziGuts.h>
#include <mozzi_midi.h>
#include <Oscil.h> // oscillator template
#include <Bounce2.h>
#include <RollingAverage.h>


// INSTANTIATE A Bounce OBJECT
Bounce bounce = Bounce();

#include <tables/saw2048_int8.h> // saw table for oscillator
#include <tables/square_no_alias512_int8.h> // saw table for oscillator
#include <tables/triangle_hermes_2048_int8.h> // saw table for oscillator
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/waveshape_chebyshev_3rd_256_int8.h> // sine table for oscillator
#include <tables/halfsin256_uint8.h> // sine table for oscillator
#include <tables/waveshape_sigmoid_int8.h> // sine table for oscillator
#include <tables/phasor256_int8.h> // sine table for oscillator

Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw4(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSaw5(SAW2048_DATA);

Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu1(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu2(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu3(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu4(SQUARE_NO_ALIAS512_DATA);
Oscil <SQUARE_NO_ALIAS512_NUM_CELLS, AUDIO_RATE> aSqu5(SQUARE_NO_ALIAS512_DATA);

Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri1(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri2(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri3(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri4(TRIANGLE_HERMES_2048_DATA);
Oscil <TRIANGLE_HERMES_2048_NUM_CELLS, AUDIO_RATE> aTri5(TRIANGLE_HERMES_2048_DATA);

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin4(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin5(SIN2048_DATA);

Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb1(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb2(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb3(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb4(CHEBYSHEV_3RD_256_DATA);
Oscil <CHEBYSHEV_3RD_256_NUM_CELLS, AUDIO_RATE> aChb5(CHEBYSHEV_3RD_256_DATA);

Oscil <HALFSIN256_NUM_CELLS, AUDIO_RATE> ahSin1(HALFSIN256_DATA);
Oscil <HALFSIN256_NUM_CELLS, AUDIO_RATE> ahSin2(HALFSIN256_DATA);
Oscil <HALFSIN256_NUM_CELLS, AUDIO_RATE> ahSin3(HALFSIN256_DATA);
Oscil <HALFSIN256_NUM_CELLS, AUDIO_RATE> ahSin4(HALFSIN256_DATA);
Oscil <HALFSIN256_NUM_CELLS, AUDIO_RATE> ahSin5(HALFSIN256_DATA);

Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig1(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig2(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig3(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig4(WAVESHAPE_SIGMOID_DATA);
Oscil <WAVESHAPE_SIGMOID_NUM_CELLS, AUDIO_RATE> aSig5(WAVESHAPE_SIGMOID_DATA);

Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha1(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha2(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha3(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha4(PHASOR256_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> aPha5(PHASOR256_DATA);
#define CONTROL_RATE 128 // Hz, powers of 2 are most reliable
Q16n16 notar = 69;//base freq
Q16n16 nota1 = 69;
Q16n16 nota2 = 69;
Q16n16 nota3 = 69;
Q16n16 nota4 = 69;
Q16n16 nota5 = 69;
Q16n16 freqi = 110;//base freq
Q16n16 oct = float_to_Q16n16(23.5);  // aqui cambiar segun cuantas octavas arriba
Q16n16 oct2 = float_to_Q16n16(35.5);  // aqui cambiar segun cuantas octavas arriba

RollingAverage <Q16n16, 4> kCvo; // how_many_to_average has to be power of 2
Q16n16 pCvo;
RollingAverage <Q16n16, 8> kPnota; // how_many_to_average has to be power of 2
Q16n16 potO;

Q16n16 voct = 1000; //external V/OCT LSB
Q16n16 potNota = 1000; //external V/OCT LSB


#define NUM_LEDS 3
#define DATA_PIN 7
CRGB leds[NUM_LEDS];

#define SW_PIN_1 4
#define SW_PIN_2 5
int LED_r_PIN = 8;
int LED_g_PIN = 6;
int LED_v_PIN = 7;
uint16_t cvO = 1000;
uint16_t pPnota = 1000;



Q16n16 freqv1 = 440;//apply voct
Q16n16 freqv2 = 440;
Q16n16 freqv3 = 440;
Q16n16 freqv4 = 440;
Q16n16 freqv5 = 440;

Q16n16 inv_conversion_factor = float_to_Q16n16(5.*12/1023.*1); 
Q16n16 inv_conversion_corto = float_to_Q16n16(3.*12/1023.*1.);
Q16n16 inv_conversion_factorN = float_to_Q16n16(5.*12/1023.); 
Q16n16 inv_conversion_cortoN = float_to_Q16n16(3.*12/1023.);
Q16n16 rou = float_to_Q16n16(0.5);
Q16n16 Afi = float_to_Q16n16(0.15);

uint8_t mode = 0;
int formaOnda = 0;
const int debounceDelay = 50;  // Tiempo de debounce en milisegundos
unsigned long lastDebounceTime = 0;  // Último momento en que se cambió el estado del botón
int buttonState ;  // Estado actual del botón (HIGH o LOW)
int lastButtonState = LOW;  // Estado anterior del botón (HIGH o LOW)

byte note1 = 0;//Root
byte note2 = 0;//2nd
byte note3 = 0;//3rd
byte note4 = 0;//4th
byte note5 = 0;//Root

byte inv_aply1 = 0; //0 = no inv , 1 = inv , Root
byte inv_aply2 = 0; //2nd
byte inv_aply3 = 0; //3rd
byte inv_aply4 = 0; //4th
bool inv_aply5 = 0; //0 = no output root sound , 1 = output root sound

int inv = 0;
int inv_knob = 0;
int chord = 0;
byte wave = 0;//0=saw,1=squ,2=tri,3=sin,etc...

const static byte chord_table[8][4]PROGMEM = {
 { 0,  4, 7,  12,  },//Maj
 { 0,  4, 7,  11,  },//Maj7
 { 0,  4, 7,  14,  },//Majadd9
 { 0,  2, 7,  12,  },//sus2
 { 0,  3, 7,  14,  },//minadd9
 { 0,  3, 7,  10,  },//min7
 { 0,  3, 7,  12,  },//min
 { 0,  0, 0,  0,  }//root
};

void setup()
{
 startMozzi(CONTROL_RATE); // :)
 pinMode(LED_r_PIN, OUTPUT);
 pinMode(LED_g_PIN, OUTPUT);
 pinMode(LED_v_PIN, OUTPUT);
 pinMode(SW_PIN_1, INPUT_PULLUP);
 pinMode(SW_PIN_2, INPUT_PULLUP);
 //Serial.begin(9600);
 bounce.attach( 3 ,  INPUT_PULLUP ); // USE INTERNAL PULL-UP
 bounce.interval(10); // interval in ms
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 FastLED.setBrightness(20);


}
void updateControl() {
 //chord setting
 chord = (mozziAnalogRead(3) / 128) + (mozziAnalogRead(5) / 128);
 chord = constrain(chord, 0, 7);
 bounce.update();
if(bounce.changed()){
        int deboucedInput = bounce.read();

    if ( deboucedInput == LOW ) {
              formaOnda = (formaOnda + 1) % 8;

    }
    
   }

if(digitalRead(SW_PIN_1)){
    if(digitalRead(SW_PIN_2)){
      mode = 1;
    }
    else{
      mode = 2;
    }
  }
  else{
    mode = 0;
  }

 // Serial.println(mode);
 //inversion setting
 inv_knob = mozziAnalogRead(1);
 inv = (inv_knob  / 84)+ (mozziAnalogRead(4) / 84);
 inv = constrain(inv, 0, 15);

 
   switch (inv) {
     case 0:
       inv_aply1 = 0;
       inv_aply2 = 0;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 0;
       break;

     case 1:
       inv_aply1 = 1;
       inv_aply2 = 0;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 0;
       break;

     case 2:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 0;
       break;

     case 3:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 0;
       inv_aply5 = 0;
       break;

     case 4:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 0;
       break;

     case 5:
       inv_aply1 = 2;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 0;
       break;

     case 6:
       inv_aply1 = 2;
       inv_aply2 = 2;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 0;
       break;

     case 7:
       inv_aply1 = 2;
       inv_aply2 = 2;
       inv_aply3 = 2;
       inv_aply4 = 1;
       inv_aply5 = 0;
       break;

     case 8:
       inv_aply1 = 2;
       inv_aply2 = 2;
       inv_aply3 = 2;
       inv_aply4 = 1;
       inv_aply5 = 1;
       break;

     case 9:
       inv_aply1 = 2;
       inv_aply2 = 2;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 1;
       break;

     case 10:
       inv_aply1 = 2;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 1;
       break;

     case 11:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 1;
       inv_aply5 = 1;
       break;

     case 12:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 1;
       inv_aply4 = 0;
       inv_aply5 = 1;
       break;

     case 13:
       inv_aply1 = 1;
       inv_aply2 = 1;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 1;
       break;

     case 14:
       inv_aply1 = 1;
       inv_aply2 = 0;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 1;
       break;

     case 15:
       inv_aply1 = 0;
       inv_aply2 = 0;
       inv_aply3 = 0;
       inv_aply4 = 0;
       inv_aply5 = 1;
       break;
   }
 
 //setting chord note

   note1 = (pgm_read_byte(&(chord_table[chord][0])));
   note2 = (pgm_read_byte(&(chord_table[chord][1])));
   note3 = (pgm_read_byte(&(chord_table[chord][2])));
   note4 = (pgm_read_byte(&(chord_table[chord][3])));
   note5 = (pgm_read_byte(&(chord_table[chord][0])));


 //OSC frequency knob
 cvO = mozziAnalogRead(7) ;
 pCvo = kCvo.next(cvO) ;  
 pPnota = mozziAnalogRead(0) ;
 potO = kPnota.next(pPnota) ;
 
 if(mode == 0){
  
        voct = ((pCvo)* inv_conversion_factor);
        potO = mozziAnalogRead(0);
        potNota = (potO)* inv_conversion_factorN ;
        notar = voct + potNota;
          
              }
  if(mode == 1){
        voct = ((cvO) * inv_conversion_factor) ;
        potO = mozziAnalogRead(0);
        potNota = (potO)* inv_conversion_cortoN ;
        notar = voct + potNota + rou + oct;
        notar = (notar >>16) << 16;
          
              }

   if(mode == 2){
        voct = ((cvO) * inv_conversion_factor) ;
        potO = mozziAnalogRead(0);
        potNota = (potO)* inv_conversion_cortoN ;
        notar = voct + rou + potNota + oct2;
         notar = (notar >>16) << 16;
                       }
  

 //Serial.print(Q16n16_to_float(notar),4);
//    Serial.print(voct);

//  Serial.print(freqv1);
//  Serial.print("    ");
//  Serial.println(freqi);
// 

 //set wave
 
 //frequency setting
Q16n16 nota1 = notar + Q16n0_to_Q16n16 (note1 + 12 * inv_aply1);//base freq
 Q16n16 nota2 = notar + Q16n0_to_Q16n16 (note2 + 12 * inv_aply2);
 Q16n16 nota3 = notar + Q16n0_to_Q16n16 (note3 + 12 * inv_aply3);
 Q16n16 nota4 = notar + Q16n0_to_Q16n16 (note4 + 12 * inv_aply4);
 Q16n16 nota5 = notar + Q16n0_to_Q16n16 (note5);


//Serial.print(" ch ");
//  Serial.print((chord));
//  Serial.print(" inver ");
//  Serial.print((inv));
//Serial.print(" inv1 ");
//  Serial.print( (inv_aply1));
//  Serial.print(" inv2 ");
//  Serial.print( (inv_aply2));
//  Serial.print(" inv3 ");
//  Serial.print( (inv_aply3));
//  Serial.print(" inv4 ");
//  Serial.print( (inv_aply4));
//  Serial.print(" inv5 ");
//  Serial.print( (inv_aply5));
// 

//  Serial.print(Q16n16_to_float (nota2));
//  
//  Serial.print(" nota3 ");
//  Serial.print(Q16n16_to_float (nota3));
//  
//  Serial.print(" nota4 ");
//  Serial.print(Q16n16_to_float (nota4));
//  
//  Serial.print(" nota5 ");
//  Serial.println(Q16n16_to_float( nota5));
 
 freqv1 = Q16n16_mtof(nota1+Afi); //ROOT
 freqv2 = Q16n16_mtof(nota2+Afi);
 freqv3 = Q16n16_mtof(nota3+Afi);
 freqv4 = Q16n16_mtof(nota4+Afi);
 freqv5 = Q16n16_mtof(nota5+Afi);
 //freqv2 = Q16n0_to_Q16n16 (freq1 * pow(2, (pgm_read_float(&(voctpow[voct + 205 * inv_aply2 + note2]))))); //2nd
// freqv3 = Q16n0_to_Q16n16 (freq1 * pow(2, (pgm_read_float(&(voctpow[voct + 205 * inv_aply3 + note3]))))); //3rd
// freqv4 = Q16n0_to_Q16n16 (freq1 * pow(2, (pgm_read_float(&(voctpow[voct + 205 * inv_aply4 + note4]))))); //4th
// freqv5 = Q16n0_to_Q16n16 (freq1 * pow(2, (pgm_read_float(&(voctpow[voct + note5]))))); //ROOT

 switch (formaOnda) {
   case 0://saw
     aSaw1.setFreq_Q16n16(freqv1); // set the frequency
     aSaw2.setFreq_Q16n16(freqv2);
     aSaw3.setFreq_Q16n16(freqv3);
     aSaw4.setFreq_Q16n16(freqv4);
     aSaw5.setFreq_Q16n16(freqv5);
    
     break;

   case 1://squ
     aSqu1.setFreq_Q16n16(freqv1); // set the frequency
     aSqu2.setFreq_Q16n16(freqv2);
     aSqu3.setFreq_Q16n16(freqv3);
     aSqu4.setFreq_Q16n16(freqv4);
     aSqu5.setFreq_Q16n16(freqv5);
   
     break;

   case 2://tri
     aTri1.setFreq_Q16n16(freqv1); // set the frequency
     aTri2.setFreq_Q16n16(freqv2);
     aTri3.setFreq_Q16n16(freqv3);
     aTri4.setFreq_Q16n16(freqv4);
     aTri5.setFreq_Q16n16(freqv5);
  
     break;

   case 3://sin
     aSin1.setFreq_Q16n16(freqv1); // set the frequency
     aSin2.setFreq_Q16n16(freqv2);
     aSin3.setFreq_Q16n16(freqv3);
     aSin4.setFreq_Q16n16(freqv4);
     aSin5.setFreq_Q16n16(freqv5);

     break;

   case 4://
     aChb1.setFreq_Q16n16(freqv1); // set the frequency
     aChb2.setFreq_Q16n16(freqv2);
     aChb3.setFreq_Q16n16(freqv3);
     aChb4.setFreq_Q16n16(freqv4);
     aChb5.setFreq_Q16n16(freqv5);

     break;

   case 5://
     ahSin1.setFreq_Q16n16(freqv1); // set the frequency
     ahSin2.setFreq_Q16n16(freqv2);
     ahSin3.setFreq_Q16n16(freqv3);
     ahSin4.setFreq_Q16n16(freqv4);
     ahSin5.setFreq_Q16n16(freqv5);
     break;

   case 6://
     aSig1.setFreq_Q16n16(freqv1); // set the frequency
     aSig2.setFreq_Q16n16(freqv2);
     aSig3.setFreq_Q16n16(freqv3);
     aSig4.setFreq_Q16n16(freqv4);
     aSig5.setFreq_Q16n16(freqv5);

     break;

   case 7://
     aPha1.setFreq_Q16n16(freqv1); // set the frequency
     aPha2.setFreq_Q16n16(freqv2);
     aPha3.setFreq_Q16n16(freqv3);
     aPha4.setFreq_Q16n16(freqv4);
     aPha5.setFreq_Q16n16(freqv5);
 
     break;
 }
 prendeLeds();
 //deBugeo();
 ledNota();
 FastLED.show();

}

int updateAudio() {
 switch (formaOnda) {

   case 0:
     return MonoOutput::from8Bit(aSaw1.next() + aSaw2.next() + aSaw3.next() + aSaw4.next() + aSaw5.next() * inv_aply5)>> 4;
     break;

   case 1:
     return MonoOutput::from8Bit(aSqu1.next()  + aSqu2.next() + aSqu3.next()  + aSqu4.next() + aSqu5.next() * inv_aply5)>> 4;
     break;

   case 2:
     return MonoOutput::from8Bit(aTri1.next()  + aTri2.next()  + aTri3.next()  + aTri4.next() + aTri5.next()  * inv_aply5)>> 4;
     break;

   case 3:
     return MonoOutput::from8Bit(aSin1.next() + aSin2.next()  + aSin3.next() + aSin4.next() + aSin5.next()  * inv_aply5)>> 4;
     break;

   case 4:
     return MonoOutput::from8Bit(aChb1.next() / 8 + aChb2.next() / 8 + aChb3.next() / 8 + aChb4.next() / 8 + aChb5.next() / 8 * inv_aply5)>> 1;
     break; 

   case 5:
     return MonoOutput::from8Bit(ahSin1.next() / 8 + ahSin2.next() / 8 + ahSin3.next() / 8 + ahSin4.next() / 8 + ahSin5.next() / 8 * inv_aply5)>> 1;
     break;

   case 6:
     return MonoOutput::from8Bit(aSig1.next() / 8 + aSig2.next() / 8 + aSig3.next() / 8 + aSig4.next() / 8 + aSig5.next() / 8 * inv_aply5)>> 1;
     break;

   case 7:
     return MonoOutput::from8Bit(aPha1.next() / 8 + aPha2.next() / 8 + aPha3.next() / 8 + aPha4.next() / 8 + aPha5.next() / 8 * inv_aply5)>> 1;
     break;

 }
}
void loop() {
 audioHook(); // required here
}
