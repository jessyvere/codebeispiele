var minefield = new Minefield(8, 8, 10);
minefield.placeMines();
minefield.addAllNeighbours();
minefield.countMinesForEveryField();

var view = new View();

var mouseClickListener = new MouseClickListener();




