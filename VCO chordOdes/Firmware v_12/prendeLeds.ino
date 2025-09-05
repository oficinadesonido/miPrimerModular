void prendeLeds(){
  switch (formaOnda) {
    case 0://saw Red
    leds[0] = CRGB(220, 0, 0);
    break;
    case 1://sqr Blue
    leds[0] = CRGB(0, 0, 220);
    break;
    case 2://tri Cyan
    leds[0] = CRGB(0, 200, 225);
    break;
    case 3://sin Orange
    leds[0] = CRGB(225, 60, 0);
    break;
    case 4://cheby White
    leds[0] = CRGB::White;
    break;
    case 5://halfsin Green
    leds[0] = CRGB(0, 186, 40);
    break;
    case 6://sigmoid Violet
    leds[0] = CRGB(120, 0, 180);
    break;
    case 7://phasor Yellow
    leds[0] = CRGB(235, 235, 0);
    break;
  
  }

    
}

void ledNota(){
  uint8_t raiz = (Q16n16_to_Q16n0 (notar))%12;
    switch (raiz) {
    case 0://c
    leds[1] = CRGB::Red;
    leds[2] = CRGB::White;
    break;
    case 1://c#
    leds[1] = CRGB::Red;
    leds[2] = CRGB::Red;
    break;
    case 2://d
    leds[1] = CRGB::Blue;
    leds[2] = CRGB::White;
    break;
    case 3://d#
    leds[1] = CRGB::Blue;
    leds[2] = CRGB::Red;
    break;
    case 4://e
    leds[1] = CRGB(225, 60, 0);
    leds[2] = CRGB::White;
    break;
    case 5://f
    leds[1] = CRGB(0, 200, 225);
    leds[2] = CRGB::White;
    break;
    case 6://f#
    leds[1] = CRGB(0, 200, 225);
    leds[2] = CRGB::Red;
    break;
    case 7://g
    leds[1] = CRGB(120, 0, 180);
    leds[2] = CRGB::White;
    FastLED.show();
    break;
    case 8://g#
    leds[1] = CRGB(120, 0, 180);
    leds[2] = CRGB::Red;
    break;
    case 9://a
    leds[1] = CRGB(235, 235, 235);
    leds[2] = CRGB::White;
    
    break;
    case 10://a#
    leds[1] = CRGB(235, 235, 235);
    leds[2] = CRGB::Red;
    break;
    case 11://b
    leds[1] = CRGB(0, 186, 40);
    leds[2] = CRGB::White;
    break;
    }

}
