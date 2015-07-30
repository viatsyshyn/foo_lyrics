#include "stdafx.h"
#include "shell_ops.h"

std::string get_txt_file_for(const std::string file_path) {
  auto it = file_path.rbegin();
  for (; it != file_path.rend() && *it != '.'; ++it);
  if (it == file_path.rend())
    return file_path + ".txt";
  else
    return std::string(file_path.begin(), file_path.end() - (it - file_path.rbegin())) + "txt";
}

void shell_open_with_notepad(const std::string &file_path, bool exsists_only) {
  if (std::string(file_path.begin(), file_path.begin() + 7) == "file://") {
    const std::string fp(file_path.begin() + 7, file_path.end());

    wchar_t soure_buff[MAX_PATH];
    soure_buff[MultiByteToWideChar(CP_UTF8, 0, fp.c_str(), fp.size(), soure_buff, MAX_PATH)] = '\0';

    wchar_t params_buff[MAX_PATH];
    params_buff[MultiByteToWideChar(CP_UTF8, 0, std::string("\"" + fp + "\"").c_str(), fp.size() + 2, params_buff, MAX_PATH)] = '\0';

    if (!exsists_only || PathFileExistsW(soure_buff) == TRUE)
      ShellExecuteW(NULL, NULL, L"notepad.exe", params_buff, NULL, SW_SHOWDEFAULT);
  }
}

void shell_move_file(const std::string & source, bool unlink_source, const std::string & target) {
  if (std::string(source.begin(), source.begin() + 7) == "file://") {
    const std::string sfp(source.begin() + 7, source.end());

    wchar_t soure_buff[MAX_PATH];
    soure_buff[MultiByteToWideChar(CP_UTF8, 0, sfp.c_str(), sfp.size(), soure_buff, MAX_PATH)] = '\0';

    if (PathFileExistsW(soure_buff) == TRUE) {
      if (std::string(target.begin(), target.begin() + 7) == "file://") {
        const std::string tfp(target.begin() + 7, target.end());

        wchar_t target_buff[MAX_PATH];
        target_buff[MultiByteToWideChar(CP_UTF8, 0, tfp.c_str(), tfp.size(), target_buff, MAX_PATH)] = '\0';

        CopyFileW(soure_buff, target_buff, false);
      }

      if (unlink_source) {
        DeleteFileW(soure_buff);
      }
    }
  }
}