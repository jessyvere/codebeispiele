class Kontrast extends Slider {
  PImage[] kontrast = new PImage[5];

  int farbenort = 0;
  final int HINTERGRUND = 0;
  final int SCHRIFT = 1;

  float r = 255;
  float g = 255;
  float b = 255;

  Slider slider = new Slider(263.999, 541.723, 263.999, 763.871, true);

  Kontrast() {
    float sliderLaenge = slider.unteresEnde - slider.oberesEnde;

    for (int i = 0; i < kontrast.length; i++) {
      kontrast[i] = loadImage("kontraste"+i+".png");
    }
  }

  void switchen() {

    switch(farbenort) {

      case (HINTERGRUND):

      hintergrund();
      image(kontrast[2], 238.804, 276.908 );
      vordergrund();
      break;

      case(SCHRIFT):
      hintergrund();
      placeImage(kontrast, 4, width/2, height/2);
      vordergrund();
      break;
    } //switch
  }

  void vordergrund() {

    //Cursor ändern
    if (overCircle(65, 65, 64)) { //Home
      hand = true;
    } else if (overRect(553.131, 276.908, 67.869, 33.289) || overRect(238.804, 310.197, 546.393, 142.817)) {//über GRÜN
      hand = true;
    } else if (overCircle(slider.xs, slider.ys, slider.d)) { //über Slider
      hand = true;
    } else {
      hand = false;
    }

    //HomeButton
    placeImage(HomeButton, 65, 65);


    //InfoButton
    if (overCircle(136, 65, 38)) {
      image(kontrast[1], 136-kontrast[0].width/2, 65-kontrast[0].height/2);
    }
    placeImage(kontrast, 0, 136, 65);

    //Slider
    placeImage(kontrast, 3, 513.935, 541.723);
    slider.male();
  }

  void hintergrund() {
    // Farbenschleife
    float sliderSiebtel = slider.sliderLaenge/7;
    float anfang = slider.oberesEnde;
    for (int i = 0; i < 7; i++) {
      if (i == 0) {
        if (slider.xs >= anfang && slider.xs <= (anfang+sliderSiebtel)) {
          b = map(slider.xs, anfang, (anfang+sliderSiebtel), 255, 0);
        }
      } else {
        if (slider.xs > anfang && slider.xs <= (anfang+sliderSiebtel)) {
          if (i == 1) {
            g = map(slider.xs, anfang, (anfang+sliderSiebtel), 255, 0);
          } else if (i == 2) {
            b = map(slider.xs, anfang, (anfang+sliderSiebtel), 0, 255);
          } else if (i == 3) {
            r = map(slider.xs, anfang, (anfang+sliderSiebtel), 255, 0);
          } else if (i == 4) {
            g = map(slider.xs, anfang, (anfang+sliderSiebtel), 0, 255);
          } else if (i == 5) {
            b = map(slider.xs, anfang, (anfang+sliderSiebtel), 255, 0);
          } else if (i == 6) {
            g = map(slider.xs, anfang, (anfang+sliderSiebtel), 255, 0);
          }
        }
      }
      anfang = anfang+sliderSiebtel;
    }

    background(r, g, b);
  }

  void klickFunktion() {
    slider.pressed();

    if (overRect(553.131, 276.908, 67.869, 33.289) || overRect(238.804, 310.197, 546.393, 142.817)) {
      if (farbenort == HINTERGRUND) {
        farbenort = SCHRIFT;
      } else {
        farbenort = HINTERGRUND;
      }
    }
  }

  /* 
   void pfeilOderHand() {
   if (hand) {
   cursor(HAND);
   } else cursor (ARROW);
   hand = false;
   }
   */
}

