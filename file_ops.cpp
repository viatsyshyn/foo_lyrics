#include "stdafx.h"
#include "resource.h"

#include "shell_ops.h"

class file_ops: public file_operation_callback {
public:
  //! p_items is a metadb::path_compare sorted list of files that have been deleted.
  virtual void on_files_deleted_sorted(t_pathlist p_items) {
    for(t_size i = 0; i < p_items.get_count(); ++i) {
      std::string source(p_items.get_item(i));
      shell_move_file(get_txt_file_for(source), true, std::string("NULL"));
    }
  };
  //! p_from is a metadb::path_compare sorted list of files that have been moved, p_to is a list of corresponding target locations.
  virtual void on_files_moved_sorted(t_pathlist p_from,t_pathlist p_to) {
    for(t_size i = 0; i < p_from.get_count(); ++i) {
      std::string source(p_from.get_item(i));
      std::string target(p_to.get_item(i));
      shell_move_file(get_txt_file_for(source), true, get_txt_file_for(target));
    }
  };
  //! p_from is a metadb::path_compare sorted list of files that have been copied, p_to is a list of corresponding target locations.
  virtual void on_files_copied_sorted(t_pathlist p_from,t_pathlist p_to) {
    for(t_size i = 0; i < p_from.get_count(); ++i) {
      std::string source(p_from.get_item(i));
      std::string target(p_to.get_item(i));
      shell_move_file(get_txt_file_for(source), false, get_txt_file_for(target));
    }
  };

};

static service_factory_single_t<file_ops> file_ops_inst;