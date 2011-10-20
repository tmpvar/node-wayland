#include <node.h>
#include <node_buffer.h>

#include "wayland-client.h"
#include "window.h"

using namespace v8;
using namespace node;


class WaylandClient : public ObjectWrap {
  public:
    static void Initialize(Handle<Object> target);
  
    WaylandClient();
    ~WaylandClient();

    static Handle<Value>New(const Arguments& args);
    static Handle<Value>Draw(const Arguments& args);
    static Handle<Value>GetSurfacePointer(const Arguments& args);
  protected:
    static Persistent<FunctionTemplate> func_tmpl;
    struct display *m_display;
    struct window *m_window;
    cairo_surface_t *surface;
}; 

Persistent<FunctionTemplate> WaylandClient::func_tmpl;

void WaylandClient::Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate>func = FunctionTemplate::New(WaylandClient::New);
  func_tmpl = Persistent<FunctionTemplate>::New(func);
  func_tmpl->InstanceTemplate()->SetInternalFieldCount(1);
  func_tmpl->SetClassName(String::NewSymbol("WaylandClient"));

  NODE_SET_PROTOTYPE_METHOD(func_tmpl, "draw", WaylandClient::Draw);
  NODE_SET_PROTOTYPE_METHOD(func_tmpl, "surfacePointer", WaylandClient::GetSurface);

  target->Set(String::NewSymbol("WaylandClient"), func_tmpl->GetFunction());
}

WaylandClient::WaylandClient() {


}

WaylandClient::~WaylandClient() {


}

Handle<Value> WaylandClient::New(const Arguments& args) {
  HandleScope scope;

  WaylandClient *instance = new WaylandClient();
  instance->Wrap(args.Holder());
  return (args.This());

}

Handle<Value>WaylandClient::Draw(const Arguments& args) {
  HandleScope scope;

  return scope.Close(Undefined());
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  WaylandClient::Initialize(target);
}

