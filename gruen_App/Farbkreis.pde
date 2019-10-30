class Farbkreis {
  float x;
  float y;
  float r;
  float g;
  float b;

  // braucht leeren Konstruktor, wegen Unterklasse (?)
  Farbkreis() {
  }

  // Farbkreise mit x, y Koordinaten und RGB Werten
  Farbkreis(float x, float y, float r, float g, float b) {
    this.x = x;
    this.y = y;
    this.r = r;
    this.g = g;
    this.b = b;
  }

  void male() {
    fill(r, g, b, 173); // plus festgelegter Transparenz
    ellipse(x, y, 428, 428);
    noFill();
  }
}

