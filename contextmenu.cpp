#include "stdafx.h"

#include "shell_ops.h"

// Identifier of our context menu group. Substitute with your own when reusing code.
//static const GUID guid_mygroup = { 0x572de7f4, 0xcbdf, 0x479a, { 0x97, 0x26, 0xa, 0xb0, 0x97, 0x47, 0x69, 0xe3 } };


// Switch to contextmenu_group_factory to embed your commands in the root menu but separated from other commands.

//static contextmenu_group_factory g_mygroup(guid_mygroup, contextmenu_groups::root, 0);
//static contextmenu_group_popup_factory g_mygroup(guid_mygroup, contextmenu_groups::root, "Sample component", 0);

//static void RunTestCommand(metadb_handle_list_cref data);
//void RunCalculatePeak(metadb_handle_list_cref data); //decode.cpp

// Simple context menu item class.
class myitem : public contextmenu_item_simple {
public:
	enum {
		cmd_open_txt = 0,
    cmd_total
	};
	//GUID get_parent() {return ;}
	unsigned get_num_items() {return cmd_total;}
	void get_item_name(unsigned p_index,pfc::string_base & p_out) {
		switch(p_index) {
			case cmd_open_txt: p_out = "Create/open lyrics"; break;
			default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
		}
	}
	void context_command(unsigned p_index,metadb_handle_list_cref p_data,const GUID& p_caller) {
		switch(p_index) {
			case cmd_open_txt:
        for(t_size i = 0; i < p_data.get_count(); ++i) {
          std::string filepath(p_data.get_item(i)->get_path());
				  shell_open_with_notepad(get_txt_file_for(filepath));
        }
				break;
			default:
				uBugCheck();
		}
	}
	// Overriding this is not mandatory. We're overriding it just to demonstrate stuff that you can do such as context-sensitive menu item labels.
	bool context_get_display(unsigned p_index,metadb_handle_list_cref p_data,pfc::string_base & p_out,unsigned & p_displayflags,const GUID & p_caller) {
		switch(p_index) {
			case cmd_open_txt:
				if (!__super::context_get_display(p_index, p_data, p_out, p_displayflags, p_caller)) return false;
				// Example context sensitive label: append the count of selected items to the label.
        if (p_data.get_count() != 1) {
				  p_out << " : " << p_data.get_count() << " items selected";
        }
				return true;
			default: uBugCheck();
		}
	}
	GUID get_item_guid(unsigned p_index) {
		// These GUIDs identify our context menu items. Substitute with your own GUIDs when reusing code.
		static const GUID guid_open_txt = { 0x4021c80d, 0x9340, 0x423b, { 0xa3, 0xe2, 0x8e, 0x1e, 0xda, 0x87, 0x13, 0x7f } };
		switch(p_index) {
			case cmd_open_txt: return guid_open_txt;
			default: uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
		}

	}
	bool get_item_description(unsigned p_index,pfc::string_base & p_out) {
		switch(p_index) {
			case cmd_open_txt:
				p_out = "This command opens external lyrics with same path and file name";
				return true;
			default:
				uBugCheck(); // should never happen unless somebody called us with invalid parameters - bail
		}
	}
};

static contextmenu_item_factory_t<myitem> g_myitem_factory;
