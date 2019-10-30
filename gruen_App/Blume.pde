class Blume {
  PImage[] blume = new PImage[5];
  int startscreen = 0;
  final int NICHTS = 0;
  final int FOTOS = 1;
  final int FARBKREISE = 2;
  final int ROT = 3;
  final int SYMBOL = 4;
  int touchedLeaf = 0;


  Blume() {
    // Fotos laden
    for (int i = 0; i < 5; i++) {
      blume[i] = loadImage("blume0"+i+".png");
    }
  }

  void switchen () {
    switch(startscreen) {
      case(NICHTS):
      blumeNummer(0);
      break;

      case(FOTOS):
      blumeNummer(1);
      break;

      case(FARBKREISE):
      blumeNummer(2);
      break;

      case(ROT):
      blumeNummer(3);
      break;

      case(SYMBOL):
      blumeNummer(4);
      break;
    }
  }

  // Wechsel der Bilder bei mouseOver
  void mouseOverWechsel() {
    if (overEllipse(409, 283, 387, 228, 354, 261, 345, 218, 463.149, 335.054)) {
      startscreen = FOTOS;
      touchedLeaf = FOTOS;
    } else if (overEllipse(614, 281, 679, 217, 636, 226, 669, 259, 564.754, 335.054)) {
      startscreen = FARBKREISE;
      touchedLeaf = FARBKREISE;
    } else if (overEllipse(410, 486, 345, 550, 388, 541, 355, 508, 460.766, 435.227  )) {
      startscreen = ROT;
      touchedLeaf = ROT;
    } else if (overEllipse(614, 485, 678, 550, 669, 507, 636, 540, 564.754, 435.227 )) {
      startscreen = SYMBOL;
      touchedLeaf = SYMBOL;
    } else {
      startscreen = NICHTS;
      touchedLeaf = NICHTS;
    }
  }

  // Bild in die Mitte
  void blumeNummer (int i) {
    image(blume[i], width/2-((blume[i].width)/2), height/2-((blume[i].height)/2));
  }

  // gebasteltes Hitpanel
  boolean overEllipse(float x, float y, float a, float s, float q, float w, float e, float r, float t, float z) {
    if (overCircle(x, y, 128) || overCircle(a, s, 58) || overCircle(q, w, 58) || overCircle(e, r, 58) ||  overCircle(t, z, 92.468)) {
      hand = true;
      return true;
    } else {
      hand = false;
      return false;
    }
  }
}

