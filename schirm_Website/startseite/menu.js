/**
 * Created by jessy on 06.11.15.
 */
var bildId = '';
var schriftzugId = '';
var ausgewaehlt = undefined; //am anfang undefined da im Startmenue nichts ausgewaehlt
var smartphoneMenue = false;


var ausgewaehltesMenue = function (event) { //wenn mit Maus über:
    if (event.target.getAttribute('class') === 'link') { //Link -> Link Bild + Schriftzug
        bildId = event.target.getAttribute('id');
        bildId = bildId.slice(0, bildId.length - 4);
        schriftzugId = bildId;
        bildId = bildId + 'RegenschirmBild';
        schriftzugId = schriftzugId + 'Schriftzug';

        document.querySelector('#' + bildId).style.display = 'block';
        if(smartphoneMenue === false) {
            document.querySelector('#' + schriftzugId).style.display = 'block';
        }
    } else if (event.target.parentNode.tagName !== 'NAV') { //nicht im NAV Kästchen ->
        if (ausgewaehlt != undefined) { //wenn ausgewaehlt wert bekommt -> dieses Menue immer anzeigen
            document.querySelector('#' + ausgewaehlt + 'RegenschirmBild').style.display = 'block';
            document.querySelector('#' + ausgewaehlt + 'Schriftzug').style.display = 'block';
        }
    } else { //sont alles none
        console.log(event.target.parentNode.tagName);
        document.querySelector('#kunstRegenschirmBild').style.display = 'none';
        document.querySelector('#alternativenRegenschirmBild').style.display = 'none';
        document.querySelector('#aufbauRegenschirmBild').style.display = 'none';
        document.querySelector('#beruehmtRegenschirmBild').style.display = 'none';
        document.querySelector('#geschichteRegenschirmBild').style.display = 'none';

        document.querySelector('#kunstSchriftzug').style.display = 'none';
        document.querySelector('#alternativenSchriftzug').style.display = 'none';
        document.querySelector('#aufbauSchriftzug').style.display = 'none';
        document.querySelector('#beruehmtSchriftzug').style.display = 'none';
        document.querySelector('#geschichteSchriftzug').style.display = 'none';

    }
};

document.addEventListener('mouseover', ausgewaehltesMenue);