# irrlklang

## How to install

    node-waf configure build install
    install_name_tool -change /usr/local/lib/libirrklang.dylib ./lib/libirrklang.dylib ./lib/node-irrklang.node
    node test/sanity.js

## Usage
    var irrKlang = require(__dirname + "/../lib/node-irrklang").irrKlang,
        player   = new irrKlang();

    player.play(__dirname + "/test/snare.wav");
