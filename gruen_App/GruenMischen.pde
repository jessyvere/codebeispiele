class GruenMischen extends Slider {
  PImage[] mischen = new PImage[3];

  Slider sliderLinks = new Slider(99.89, 392.0, 261.68, 506.32, false);
  Slider sliderRechts= new Slider(924.11, 392.0, 261.68, 506.32, false);

  Farbkreis blau = new Farbkreis(395.665, 384.0, 21, 116, 255);
  Farbkreis gelb = new Farbkreis(629.115, 384.0, 255, 255, 13);

  GruenMischen() {
    for (int i = 0; i < mischen.length; i ++) {
      mischen[i] = loadImage("mischen" + i + ".png");
    }
    noStroke();
  }

  void zeige() {
    //HomeButton
    placeImage(HomeButton, 65, 65);
    if (overCircle(65, 65, 64)) { //Cursor ändern
      hand = true;
    } else hand = false;
    noFill();

    //Slideraufhängung
    placeImage(mischen, 2, width/2, height/2);
    sliderLinks.male();
    sliderRechts.male();

    //Farbkreise
    fill(#C6C6C5);
    blau.male();
    gelb.male();

    // Blau Werte mit Slider ändern
    if (sliderLinks.ys >= sliderLinks.oberesEnde && sliderLinks.ys <= 320) {
      blau.r = map(sliderLinks.ys, sliderLinks.oberesEnde, 320, 60, 23);
    } else if (sliderLinks.ys > 321 && sliderLinks.ys <= sliderLinks.unteresEnde) {
      blau.g = map(sliderLinks.ys, 321, sliderLinks.unteresEnde, 23, 255);
    }

    // Gelb Werte mit Slider ändern
    if (sliderRechts.ys >= sliderRechts.oberesEnde && sliderLinks.ys <= sliderRechts.unteresEnde) {
      gelb.g = map(sliderRechts.ys, sliderRechts.oberesEnde, sliderRechts.unteresEnde, 215, 255);
    }

    //Info-Button
    if (overCircle(136, 65, 38)) {
      image(mischen[1], 136-mischen[0].width/2, 65-mischen[0].height/2);
    }
    placeImage(mischen, 0, 136, 65);

    //über Slider
    if (overCircle(sliderRechts.xs, sliderRechts.ys, sliderRechts.d) || overCircle(sliderLinks.xs, sliderLinks.ys, sliderLinks.d)) {
      hand = true;
    }
  } //zeige



    void klickFunktion() {
    if (overCircle(65, 65, 64)) { //Cursor ändern
      home = true;
    } else home = false;

    if (home) {
      view = BLUME;
    }
  }
}

