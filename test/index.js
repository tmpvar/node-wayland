var wayland = require('../');

var client = wayland.createClient();
console.log(client.draw);
 
console.log(wayland.createClient());
