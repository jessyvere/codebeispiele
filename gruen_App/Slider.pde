class Slider extends Farbkreis {
  float xs;
  float ys;
  float d = 23;
  boolean locked = false;
  boolean horizontal;

  float oberesEnde;
  float unteresEnde;  
  float sliderLaenge;

  Slider() {
  }
  // Startpunkt des Kreises angeben
  //Oberes und Unteres Ende der Bar angeben, damit Kreis nur in diesem Bereich folgt
  //Update: einstellen ob horizontaler oder vertikaler Slider
  Slider(float xs, float ys, float oberesEnde, float unteresEnde, boolean horizontal) {
    this.xs = xs;
    this.ys = ys;
    this.oberesEnde = oberesEnde;
    this.unteresEnde = unteresEnde;
    this.horizontal = horizontal;
    sliderLaenge = (unteresEnde - oberesEnde);
  }


  void male() {
    fill(#C6C6C5);
    ellipse(xs, ys, d, d);
    noFill();

    if (locked) {
      hand = true;
    }
  }

  void pressed () {
    if (overCircle(xs, ys, d)) {
      locked = true;
    } else locked = false;
  }

  void dragged() {
    hand = true;
    if (horizontal) {
      if (locked && mouseX >= oberesEnde && mouseX <= unteresEnde) {
        xs = mouseX;
      }
    } else {
      if (locked && mouseY >= oberesEnde && mouseY <= unteresEnde) {
        ys = mouseY;
      }
    }
  }
}

