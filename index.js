var wayland = require('./build/Release/wayland');


module.exports = {
  createClient : function() {
    return new (wayland.WaylandClient)();
  }
};
