#include "stdafx.h"
#include "shell_ops.h"

void shell_open_with_notepad(const std::string &file_path, bool exsists_only) {
  if (std::string(file_path.begin(), file_path.begin() + 7) == "file://") {
    std::string fp(file_path.begin() + 7, file_path.end());

    if (!exsists_only || PathFileExistsA(fp.c_str()) == 1)
      ShellExecuteA(NULL, NULL, "notepad.exe", std::string("\"" + fp + "\"").c_str(), NULL, SW_SHOWDEFAULT);
  }
}

void shell_move_file(const std::string & source, bool unlink_source, const std::string & target) {
  if (std::string(source.begin(), source.begin() + 7) == "file://") {
    std::string sfp = std::string(source.begin() + 7, source.end()) + ".txt";

    if (PathFileExistsA(sfp.c_str()) == 1) {
      if (std::string(target.begin(), target.begin() + 7) == "file://") {
        std::string tfp = std::string(target.begin() + 7, target.end()) + ".txt";

        CopyFileA(sfp.c_str(), tfp.c_str(), false);
      }

      if (unlink_source) {
        DeleteFileA(sfp.c_str());
      }
    }
  }
}