

ausgewaehlt = 'beruehmt';



//marryPoppinsText

var bilderArray = document.querySelectorAll('.bild');

for (var i = 0; i < bilderArray.length; i++) {
    bilderArray[i].addEventListener('click', function(event) {
        var name = event.target.getAttribute('id');
        name = name.slice(0, name.length-4);
        var nameText = '#'+name+'Text';
        console.log('#'+name+'Text');
        document.querySelector(nameText).style.display = 'block';
    });
}
