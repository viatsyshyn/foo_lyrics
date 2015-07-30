#include "stdafx.h"
#include "resource.h"

#include "shell_ops.h"

class playback_state : public play_callback_static {
public:
	enum {IDD = IDD_PLAYBACK_STATE};

private:
  virtual unsigned get_flags() { return flag_on_playback_new_track; }

	// Playback callback methods.
	virtual void on_playback_new_track(metadb_handle_ptr p_track) {
    std::string filepath(p_track->get_path());
    shell_open_with_notepad(get_txt_file_for(filepath), true);
  }

  virtual void on_playback_starting(play_control::t_track_command p_command,bool p_paused) {}  
  virtual void on_playback_stop(play_control::t_stop_reason p_reason) { uDebugLog() << "on_playback_stop()"; }
  virtual void on_playback_seek(double p_time) {}
  virtual void on_playback_pause(bool p_state) {}
  virtual void on_playback_edited(metadb_handle_ptr p_track) {}
  virtual void on_playback_dynamic_info(const file_info & p_info) {}
  virtual void on_playback_dynamic_info_track(const file_info & p_info) {}
  virtual void on_playback_time(double p_time) {}
  virtual void on_volume_change(float p_new_val) {}
};

static play_callback_static_factory_t<playback_state> foobar;