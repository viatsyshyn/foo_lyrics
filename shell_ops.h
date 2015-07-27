#include <string>

void shell_open_with_notepad(const std::string &file_path, bool exists_only = false);
void shell_move_file(const std::string & source, bool unlink_source, const std::string & target);
