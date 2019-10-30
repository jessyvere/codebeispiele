var View = function () {

    var flagCounter = 0;
    var body = document.querySelector('body');
    var firstExploded = false;


    var getFieldDiv = function (fieldElement) {
        var x = fieldElement.xPosition;
        var y = fieldElement.yPosition;
        var fieldId = 'field' + x + '-' + y;
        return document.querySelector('#' + fieldId);
    };


    for (var x = 0; x < minefield.rows; x++) {
        for (var y = 0; y < minefield.columns; y++) {
            (function () {
                var savedX = x;
                var savedY = y;
                var fieldElement = minefield.fieldArray[savedX][savedY];


                fieldElement.eventDispatcher.addEventListener('fieldUncoveredEvent', function () {
                    if (fieldElement.falseMine) {
                        getFieldDiv(fieldElement).style.backgroundImage = 'url("falseMine.png")';
                        getFieldDiv(fieldElement).style.borderColor = '#DDDDDD';
                    } else {
                        getFieldDiv(fieldElement).innerHTML = fieldElement.minesAround;
                        getFieldDiv(fieldElement).style.borderColor = '#DDDDDD';
                    }
                });

                fieldElement.eventDispatcher.addEventListener('mineUncoveredEvent', function () {
                    if (fieldElement === minefield.firstMine) {
                        getFieldDiv(fieldElement).style.borderColor = '#e40613';
                        getFieldDiv(fieldElement).style.backgroundImage = 'url("mineExplodedIcon.png")';
                    } else {
                        getFieldDiv(fieldElement).style.borderColor = '#DDDDDD';
                        getFieldDiv(fieldElement).style.backgroundImage = 'url("mineIcon.png")'

                    }
                    document.querySelector('#winOrLoseDiv').innerHTML = 'Game Over';
                    document.querySelector('#winOrLoseDiv').style.display = "block";
                });

                fieldElement.eventDispatcher.addEventListener('addOrRemoveFlagEvent', function () {
                    if (!fieldElement.flagged) {
                        getFieldDiv(fieldElement).style.backgroundImage = 'url("flagIcon.png")';
                        flagCounter++;
                    } else {
                        getFieldDiv(fieldElement).style.backgroundImage = 'none';
                        flagCounter--;
                    }
                    refreshFlagCounter();
                });
            }())
        }
    }


    minefield.eventDispatcher.addEventListener('resetMinefieldEvent', function () {
        for (var x = 0; x < minefield.rows; x++) {
            for (var y = 0; y < minefield.columns; y++) {
                var fieldElement = minefield.fieldArray[x][y];
                getFieldDiv(fieldElement).innerHTML = '';
                getFieldDiv(fieldElement).style.backgroundImage = 'none';
                getFieldDiv(fieldElement).style.borderColor = "#EEEEEE #777777 #777777 #EEEEEE";
            }
            flagCounter = 0;
            firstExploded = false;
            refreshFlagCounter();
        }
        document.querySelector('#winOrLoseDiv').style.display = "none";
    });


    minefield.eventDispatcher.addEventListener('winEvent', function () {
        document.querySelector('#winOrLoseDiv').innerHTML = 'You Won!';
        document.querySelector('#winOrLoseDiv').style.display = "block";
    });

    for (var x = 0; x < minefield.rows; x++) {
        var fieldColumn = document.createElement('div');
        fieldColumn.classList.add('fieldColumn');
        document.querySelector('#minefieldDiv').appendChild(fieldColumn);
        for (var y = 0; y < minefield.columns; y++) {
            var fieldDiv = document.createElement('div');
            fieldDiv.classList.add('fieldDiv');
            fieldDiv.setAttribute('id', 'field' + ('' + x) + '-' + ('' + y));
            fieldColumn.appendChild(fieldDiv);
        }
    }

    document.querySelector('#flagCounterDiv').innerHTML = '0 / ' + minefield.numberOfMines;

    var refreshFlagCounter = function () {
        document.querySelector('#flagCounterDiv').innerHTML = '' + flagCounter + ' / ' + minefield.numberOfMines;
    };


};








