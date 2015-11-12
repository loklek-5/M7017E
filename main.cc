#include <gtkmm/main.h>
#include <gstreamermm/init.h>
#include <gstreamermm/element.h>

// Plug-ins:
#include <gstreamermm/playbin.h>

#include <iostream>
#include "player_window.h"

int main(int argc, char** argv)
{
  Gtk::Main kit(argc, argv);
  Gst::init(argc, argv);

  // Create the elements:

  // playbin2 plays any media type, choosing an appropriate set of elements
  // and linking them together.
  Glib::RefPtr<Gst::PlayBin> playbin = Gst::PlayBin::create("playbin");

  if(!playbin)
  {
    std::cerr << "The playbin could not be created." << std::endl;
    return 1;
  }

  //Create our player window and give it the pipeline and video sink:
  PlayerWindow mainWindow(playbin);
  kit.run(mainWindow);

  // Clean up nicely:
  playbin->set_state(Gst::STATE_NULL);

  return 0;
}
