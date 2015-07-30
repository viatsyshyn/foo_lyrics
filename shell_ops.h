#include <string>

std::string get_txt_file_for(const std::string file_path);
void shell_open_with_notepad(const std::string &file_path, bool exists_only = false);
void shell_move_file(const std::string & source, bool unlink_source, const std::string & target);
