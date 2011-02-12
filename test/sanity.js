var irrKlang = require(__dirname + "/../lib/node-irrklang").irrKlang,
    player   = new irrKlang();

console.log(player.play("monkey"));