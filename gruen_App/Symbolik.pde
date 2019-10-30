class Symbolik {
  PImage[] symbol = new PImage[9];

  int angezeigt = 0;
  final int NICHTS = 0;
  final int NATUR = 1;
  final int ISLAM = 2;
  final int HOFFNUNG = 3;
  final int GEIST = 4;
  final int BROKKOLI = 5;
  final int JUGEND = 6;
  final int GIFT = 7;
  final int AMPEL = 8;

  Symbolik() {
    for (int i = 0; i < symbol.length; i++) {
      symbol[i] = loadImage("symbol" + i + ".png");
    }
  }

  void switchen() {
    background(#90FF66);

    placeImage(HomeButton, 65, 65);
    if (overCircle(65, 65, 64)) { //Cursor ändern
      hand = true;
    } else hand = false;

    switch(angezeigt) {
    case NICHTS:
      checkMouse();
      image(symbol[0], 139.28, 299.031); 
      break;

    case NATUR:
      checkMouse();
      image(symbol[1], 139.28, 299.031);
      break;

    case ISLAM:
      checkMouse();
      image(symbol[2], 139.28, 299.031);
      break;

    case HOFFNUNG:
      checkMouse();
      image(symbol[3], 139.28, 299.031);
      break;

    case GEIST:
      checkMouse();
      image(symbol[4], 139.28, 299.031);
      break;

    case BROKKOLI:
      checkMouse();
      image(symbol[5], 139.28, 299.031);
      break; 

    case JUGEND:
      checkMouse();
      image(symbol[6], 139.28, 299.031);
      break;

    case GIFT:
      checkMouse();
      image(symbol[7], 139.28, 299.031);
      break;

    case AMPEL:
      checkMouse();
      image(symbol[8], 139.28, 299.031);
      break;
    }//switch
  }

  void checkMouse() {
    if (overCircle(169.871, 371.328, 53.133) || overCircle(190.399, 390.193, 46.343) || overCircle(203.307, 354.265, 53.133) || overRect(141.843, 384.702, 49.265, 55.662)) {
      angezeigt = NATUR;
    } else if (overCircle(222.624, 433.891, 44.635 ) || overCircle(234.735, 419.655, 41.434 ) || overRect(242.452, 382.611, 24.785, 33.411 ) || overRect(262.785, 364.126, 24.785, 33.411 ) || overRect(281, 298.031, 26, 73.297 )) {
      angezeigt = ISLAM;
    } else if (overRect(340.644, 312.094, 79, 143.005 ) || overRect(325.215, 331.64, 24.785, 98.911 ) || overRect(312.822, 356.624, 24.785, 60.228 ) || overRect(297.322, 386.92, 19.388, 19.186 )) {
      angezeigt = HOFFNUNG;
    } else if (overRect(430.333, 312.094, 78.667, 141.313 )) {
      angezeigt = GEIST;
    } else if (overRect(551.95, 405.407, 46.924, 38.955) || overRect(517.788, 324.598, 112.667, 80.809)) {
      angezeigt = BROKKOLI;
    } else if (overCircle(669.445, 438.474, 36.241 ) || overCircle( 660.17, 421.302, 27.574 ) || overRect(644.174, 376.896, 23.779, 33.854 ) || overRect( 639.425, 354.71, 62.823, 25.451 ) || overRect(660.764, 308.527, 22.716, 50.823)) {
      angezeigt = JUGEND;
    } else if (overCircle( 760.509, 384, 108.948 )) {
      angezeigt = GIFT;
    } else if (overRect(828.64, 319.487, 56.703, 129.869 )) {
      angezeigt = AMPEL;
    } else angezeigt = NICHTS;
  }
}

