var Minefield = function (rows, columns, numberOfMines) {

    var self = this;
    self.rows = rows;
    self.columns = columns;
    self.numberOfMines = numberOfMines;
    self.fieldArray = [];
    self.uncoveredFieldsCounter = 0;
    self.allUncovered = false;
    self.firstMineExploded = false;
    self.eventDispatcher = new EventDispatcher();


    for (var x = 0; x < self.rows; x++) {
        self.fieldArray.push([]);
        for (var y = 0; y < this.columns; y++) {
            self.fieldArray[x][y] = new Field();
            self.fieldArray[x][y].xPosition = x;
            self.fieldArray[x][y].yPosition = y;
        }
    }


    this.randomCoordinates = function () {
        return {
            x: Math.floor(Math.random() * self.rows),
            y: Math.floor(Math.random() * self.columns)
        };
    };

    this.testIfMine = function (x, y) {
        return self.fieldArray[x][y].mine;
    };

    this.generateMineCoordinates = function () {
        var coordinates = self.randomCoordinates();
        while (this.testIfMine(coordinates.x, coordinates.y)) {
            var newCoordinates = self.randomCoordinates();
            coordinates.x = newCoordinates.x;
            coordinates.y = newCoordinates.y;
        }
        self.fieldArray[coordinates.x][coordinates.y].mine = true;
    };

    self.placeMines = function () {
        for (var i = 0; i < self.numberOfMines; i++) {
            self.generateMineCoordinates();
        }
    };


    self.addNeighbours = function (object, orderArray) {
        if (!object.mine) {
            var x = object.xPosition;
            var y = object.yPosition;

            for (var i = 0; i < orderArray.length; i++) {
                if (orderArray[i].charAt(0) === 'x') {
                    x += parseInt((orderArray[i].charAt(1) + orderArray[i].charAt(2)));
                    object.neighbours.push(minefield.fieldArray[x][y]);
                }
                else { // wenn y
                    y += parseInt((orderArray[i].charAt(1) + orderArray[i].charAt(2)));
                    object.neighbours.push(minefield.fieldArray[x][y]);
                }
            }
        }

    };

    self.addNeighboursUnderRules = function (object) {
        if (!object.mine) {
            if (object.xPosition === 0 && object.yPosition === 0) {                                         // ---- ⌈
                self.addNeighbours(object, ['x+1', 'y+1', 'x-1']);
            } else if (object.xPosition === (self.rows - 1) && object.yPosition === (self.columns - 1)) {   // ---- ⌋
                self.addNeighbours(object, ['y-1', 'x-1', 'y+1']);
            } else if (object.xPosition === 0 && object.yPosition === (self.columns - 1)) {                 // ---- ⌊
                self.addNeighbours(object, ['y-1', 'x+1', 'y+1']);
            } else if (object.xPosition === (self.rows - 1) && object.yPosition === 0) {                    // ---- ⌉
                self.addNeighbours(object, ['x-1', 'y+1', 'x+1']);
            } else if (object.xPosition === 0) {                                                            // ---- ]
                self.addNeighbours(object, ['y-1', 'x+1', 'y+1', 'y+1', 'x-1']);
            } else if (object.yPosition === 0) {                                                            // ---- ⌊⌋
                self.addNeighbours(object, ['x-1', 'y+1', 'x+1', 'x+1', 'y-1']);
            } else if (object.xPosition === (self.rows - 1)) {                                              // ---- [
                self.addNeighbours(object, ['y-1', 'x-1', 'y+1', 'y+1', 'x+1']);
            } else if (object.yPosition === (self.columns - 1)) {                                           // ---- ⌈⌉
                self.addNeighbours(object, ['x-1', 'y-1', 'x+1', 'x+1', 'y+1']);
            } else {
                self.addNeighbours(object, ['y-1', 'x-1', 'y+1', 'y+1', 'x+1', 'x+1', 'y-1', 'y-1']);
            }
        }
    };

    self.addAllNeighbours = function () {
        for (var i = 0; i < self.rows; i++) {
            for (var j = 0; j < self.columns; j++) {
                self.addNeighboursUnderRules(self.fieldArray[i][j]);
            }
        }
    };

    self.countMinesForEveryField = function () {
        var minesCounter = 0;
        for (var x = 0; x < self.rows; x++) {
            for (var y = 0; y < self.columns; y++) {
                for (var i = 0; i < self.fieldArray[x][y].neighbours.length; i++) {
                    if (self.testIfMine(self.fieldArray[x][y].neighbours[i].xPosition, self.fieldArray[x][y].neighbours[i].yPosition)) {
                        minesCounter += 1;
                    }
                }
                self.fieldArray[x][y].minesAround = minesCounter;
                minesCounter = 0;
            }
        }
    };


    this.uncoverAllFields = function () {
        self.allUncovered = true;
        for (var x = 0; x < self.rows; x++) {
            for (var y = 0; y < self.columns; y++) {
                if (!self.fieldArray[x][y].uncovered) {
                    if (!self.fieldArray[x][y].flagged) {
                        self.fieldArray[x][y].uncover();
                    } else if (self.fieldArray[x][y].flagged && !self.fieldArray[x][y].mine) {
                        self.fieldArray[x][y].falseMine = true;
                        self.fieldArray[x][y].uncover();
                    }

                }
            }
        }
    };


    self.flagNotFlaggedMines = function () {
        for (var x = 0; x < minefield.rows; x++) {
            for (var y = 0; y < minefield.columns; y++) {
                if (minefield.fieldArray[x][y].mine && !minefield.fieldArray[x][y].flagged) {
                    minefield.fieldArray[x][y].addOrRemoveFlag();
                }
            }
        }
    };


    this.resetMinefield = function () {
        for (var x = 0; x < self.rows; x++) {
            for (var y = 0; y < self.columns; y++) {
                this.fieldArray[x][y].mine = false;
                this.fieldArray[x][y].neighbours = [];
                this.fieldArray[x][y].flagged = false;
                this.fieldArray[x][y].uncovered = false;
                this.fieldArray[x][y].falseMine = false;
            }
        }
        self.uncoveredFieldsCounter = 0;
        self.allUncovered = false;
        self.firstMineExploded = false;
        this.placeMines();
        this.addAllNeighbours();
        this.countMinesForEveryField();
        this.eventDispatcher.dispatchEvent('resetMinefieldEvent');
        self.eventDispatcher.dispatchEvent('enableClickEvent');
    };


    for (var x = 0; x < self.rows; x++) {
        for (var y = 0; y < self.columns; y++) {
            (function () {
                var savedX = x;
                var savedY = y;
                var fieldElement = self.fieldArray[savedX][savedY];

                fieldElement.eventDispatcher.addEventListener('mineUncoveredEvent', function () {
                    if (!self.firstMineExploded) {
                        self.eventDispatcher.dispatchEvent('disableClickEvent');
                        self.firstMineExploded = true;
                        self.firstMine = fieldElement;
                    }
                    if (!self.allUncovered) {
                        minefield.uncoverAllFields();
                    }
                });

                fieldElement.eventDispatcher.addEventListener('fieldUncoveredEvent', function () {
                    self.uncoveredFieldsCounter += 1;
                    if (fieldElement.minesAround === 0) {
                        for (var i = 0; i < fieldElement.neighbours.length; i++) {
                            fieldElement.neighbours[i].uncover();
                        }
                    }
                    if (((self.rows * self.columns) - self.numberOfMines) === self.uncoveredFieldsCounter && !self.allUncovered) {
                        self.eventDispatcher.dispatchEvent('disableClickEvent');
                        self.flagNotFlaggedMines();
                        self.eventDispatcher.dispatchEvent('winEvent');
                    }
                });
            }())
        }
    }
};