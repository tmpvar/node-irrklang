var irrKlang = require(__dirname + "/../lib/node-irrklang").irrKlang,
    player   = new irrKlang();
setInterval(function() {
  player.play(__dirname + "/snare.wav");
}, 500)