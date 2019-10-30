var MouseClickListener = function () {

    var getFieldElement = function (fieldDiv) {
        var xyString = fieldDiv.getAttribute('id');
        var line = xyString.indexOf('-');
        var x = xyString.slice(5, line);
        var y = xyString.slice(line + 1, xyString.length);//field4-2
        return minefield.fieldArray[x][y];
    };


    var leftClickField = function (event) {
        if (event.target.getAttribute('class') === 'fieldDiv') {
            var fieldElement = getFieldElement(event.target);
            fieldElement.uncover();
        }
    };
    document.querySelector('#minefieldDiv').addEventListener('click', leftClickField);


    var rightClickField = function (event) {
        event.preventDefault();
        if (event.target.getAttribute('class') === 'fieldDiv') {
            var fieldElement = getFieldElement(event.target);
            fieldElement.addOrRemoveFlag();
        }
    };
    document.querySelector('#minefieldDiv').addEventListener('contextmenu', rightClickField);


    minefield.eventDispatcher.addEventListener('disableClickEvent', function () {
        document.querySelector('#minefieldDiv').removeEventListener('click', leftClickField);
        document.querySelector('#minefieldDiv').removeEventListener('contextmenu', rightClickField);
    });


    minefield.eventDispatcher.addEventListener('enableClickEvent', function () {
        document.querySelector('#minefieldDiv').addEventListener('click', leftClickField);
        document.querySelector('#minefieldDiv').addEventListener('contextmenu', rightClickField);
    });


    document.querySelector('#newGameButton').addEventListener('click', function () {
        minefield.resetMinefield();
    });
};