Blume blume;
Fotokreise fotokreise;
GruenMischen gruenMischen;
Kontrast kontrast;
Symbolik symbolik;

int view = 0;
final int BLUME = 0;
final int FOTOKREISE = 1;
final int GRUENMISCHEN = 2;
final int KONTRASTWIRKUNG = 3;
final int SYMBOLE = 4;

PImage HomeButton = new PImage(); // Homebutton
boolean home = false; 
boolean hand = false;

void setup() {
  size(1024, 768);
  colorMode(RGB);
  blume = new Blume();
  fotokreise = new Fotokreise();
  gruenMischen = new GruenMischen();
  kontrast = new Kontrast();
  symbolik = new Symbolik();

  HomeButton = fotokreise.foto[0];
  noStroke();
}

void draw() {


  //Cursor
  if (hand) {
    cursor(HAND);
  } else cursor (ARROW);


  switch(view) {
    case(BLUME):
    background(#F9F9F9);
    blume.switchen();
    blume.mouseOverWechsel();
    break;

    case(FOTOKREISE):
    background(#F9F9F9);
    fotokreise.switchen();
    break;

    case(GRUENMISCHEN):
    background(#F9F9F9);
    gruenMischen.zeige();
    break;

    case(KONTRASTWIRKUNG):
    background(#F9F9F9);
    kontrast.switchen();
    break;

    case(SYMBOLE):
    symbolik.switchen();
    symbolik.checkMouse();
    break;
  }//switch
}

boolean overCircle(float x, float y, float r) {
  if (dist(mouseX, mouseY, x, y) <= r/2) {
    return true;
  } else {
    return false;
  }
}

boolean overRect(float x, float y, float b, float h) {
  if ((mouseX >= x && mouseX <= x+b) && (mouseY >= y && mouseY <= y+h)) {
    return true;
  } else return false;
} 

// Variante: Liste und nur Bild
void placeImage (PImage[] liste, int i, float x, float y) {
  image(liste[i], x-((liste[i].width)/2), y-((liste[i].height)/2));
}
void placeImage (PImage p, float x, float y) {
  image(p, x-((p.width)/2), y-((p.height)/2));
}

// Home Funktion
void comingHome() {
  if (overCircle(65, 65, 64)) { //Cursor ändern
    home = true;
  } else home = false;

  if (home) {
    view = BLUME;
  }
}


void mousePressed() {
  if (view == BLUME) {
    view = blume.touchedLeaf;
  } else if (view == FOTOKREISE) {
    if (fotokreise.farbenBild == fotokreise.FARBENKREISE) {
      comingHome();
      fotokreise.klickFunktion();
    } else fotokreise.klickFunktion();
  } else if (view == GRUENMISCHEN) {
    comingHome();
  } else if (view == KONTRASTWIRKUNG) {
    comingHome();
    kontrast.klickFunktion();
  } else if (view == SYMBOLE) {
    comingHome();
  }

  //für GruenMischen
  gruenMischen.sliderLinks.pressed();
  gruenMischen.sliderRechts.pressed();
  kontrast.slider.pressed();
}


void mouseDragged() {
  gruenMischen.sliderLinks.dragged();
  gruenMischen.sliderRechts.dragged();
  kontrast.slider.dragged();
}

void mouseReleased() {
  gruenMischen.sliderLinks.locked = false;
  gruenMischen.sliderRechts.locked = false;
  kontrast.slider.locked = false;
}

