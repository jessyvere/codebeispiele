class Fotokreise { 
  PImage[] fotokreis = new PImage[24];
  PImage[] foto = new PImage[4];
  PImage[] farbe = new PImage[24];

  int touchedFoto = 0; // kleines Foto -> großes Foto

  int farbenBild = 0;
  final int FARBENKREISE = 0;
  final int FOTOSMITFARBE = 1;

  Fotokreise() {
    // Fotos laden
    for (int i = 0; i < fotokreis.length; i++) {
      fotokreis[i] = loadImage("fotokreis"+i+".png");
    }

    for (int i = 0; i < farbe.length; i++) {
      farbe[i] = loadImage("farben"+i+".png");
    }

    for (int i = 0; i < foto.length; i++) {
      foto[i] = loadImage("fotos"+i+".png");
    }
  }

  //placeImge(Image Array, Index des gewählten Bildes, xPosition, yPosition) um Bild vom Punkt aus mittg zu setzen 


  void switchen() {
    //switch zwischen Farbenkreisen und angezeigten Bildern in groß
    switch (farbenBild) {

      case(FARBENKREISE):

      //HomeButton
      placeImage(foto, 0, 65, 65);
      if (overCircle(65, 65, 64)) {
        hand = true;
      } else hand = false;

      //Farbkreise
      placeImage(foto, 3, width/2, height/2+20);

      float xKreis = 136.905;
      float yKreis = 160+20;
      // for-schleife für alle Kreise und deren Kollisonen
      for (int i = 0; i < fotokreis.length; i ++) {
        if (overCircle(xKreis, yKreis, 100)) {
          hand = true;
          touchedFoto = i; // für case: FOTOSMITFARBE (Foto in groß
          placeImage(fotokreis, i, xKreis, yKreis); // kleines Foto als Kreis
        }
        // alle Kreispositionen in der Schleife durchgehen
        if (xKreis <= 736.905 ) { 
          xKreis += 150;
        } else {
          xKreis = 136.905;
          yKreis += 150;
        }
      }


      //InfoButton
      if (overCircle(136, 65, 38)) {
        image(foto[2], 136-foto[1].width/2, 65-foto[1].height/2);
      }
      placeImage(foto, 1, 136, 65);
      break;


      //Fotos in groß
      case(FOTOSMITFARBE):
      image(farbe[touchedFoto], 0, 0);
      break;
    }//switch
  }

  void klickFunktion() {


    //zu Bildern wechseln
    if (farbenBild == FARBENKREISE) { 
      //println("touchedFotoIndex: "+touchedFoto);
      float xKreis = 136.905;
      float yKreis = 160+20;

      for (int i = 0; i < fotokreis.length; i ++) {

        if (overCircle(xKreis, yKreis, 100)) {
          farbenBild = FOTOSMITFARBE;
        }
        if (xKreis <= 736.905 ) { 
          xKreis += 150;
        } else {
          xKreis = 136.905;
          yKreis += 150;
        }
      }
    } else farbenBild = FARBENKREISE; //wieder zurück irgendwo
  }
}

