/* gstreamermm-gtkmm-media-player
 *
 * Copyright 2008-2015 krz37, loklek-5, loklek-5 and The gstreamermm Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef _PLAYERWINDOW_H
#define _PLAYERWINDOW_H
#include <gtk/gtk.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/scale.h>
#include <gstreamermm/element.h>
#include <gstreamermm/pipeline.h>
#include <gstreamermm/bus.h>
#include <gstreamermm/playbin.h>
#include <gtkmm/volumebutton.h>

class PlayerWindow : public Gtk::Window
{
public:
  /**
   * @param playbin The pipeline that can play media files.
   */
  PlayerWindow(const Glib::RefPtr<Gst::PlayBin>& playbin);
  virtual ~PlayerWindow();

protected:

  //Signal handlers:
  void on_video_area_realize();
  void on_bus_message_sync(const Glib::RefPtr<Gst::Message>& message);
  bool on_bus_message(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
  void on_video_changed();
  Gst::PadProbeReturn on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad, const Gst::PadProbeInfo& data);

  //Functions declaration, comments available in the .cc file
  void on_button_play();
  void on_button_pause();
  void on_button_stop();
  void on_button_rewind();
  void on_button_forward();
  void on_button_open();
  void on_button_full_screen();
  void on_button_unfull_screen();
  void on_button_mute();
  void on_button_unmute();
  bool on_scale_value_changed(Gtk::ScrollType type, double value);
  void on_volume_value_changed(double value);
  bool on_timeout();

  void display_label_progress(gint64 pos, gint64 len);

protected:
  ///GUI Elements declaration
  Gtk::VBox m_vbox;
  Gtk::HButtonBox m_button_box;
  Gtk::DrawingArea m_video_area;
  Gtk::Label m_progress_label;
  Gtk::Label m_volume_label;
  Gtk::HScale m_progress_scale;
  Gtk::HScale m_volume_scale;
  Gtk::Button m_play_button;
  Gtk::Button m_pause_button;
  Gtk::Button m_stop_button;
  Gtk::Button m_rewind_button;
  Gtk::Button m_forward_button;
  Gtk::Button m_open_button; 
  Gtk::Button m_full_screen_button;
  Gtk::Button m_unfull_screen_button;
  Gtk::Button m_mute_button;
  Gtk::Button m_unmute_button;
  Gtk::VolumeButton m_volume_button;
  
  ///Gstreamer-related declarations
  Glib::RefPtr<Gst::PlayBin> m_playbin;
  sigc::connection m_timeout_connection;
  guint m_watch_id;
  gint64 m_duration;
  gulong m_x_window_id;
  gulong m_pad_probe_id;
};

#endif /* _PLAYERWINDOW_H */
