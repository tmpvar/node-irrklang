var irrKlang = require(__dirname + "/../lib/irrklang").irrKlang,
    player   = new irrKlang()
    volume   = 0,
    where    = 0;
setInterval(function() {
  where++;

  player.play(__dirname + "/snare.wav", volume);
  volume += 0.001;
  if (volume >= 1) {
    volume = 0;
  }
  
}, 50)