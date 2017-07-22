// =====================================================================
//
// status.cxx
//
// Author(s):
//	Dave Freese, W1HKJ Copyright (C) 2010
//  Robert Stiles, KK5VD Copyright (C) 2013
//
// This file is part of FLIMG.
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// =====================================================================


#include <iostream>
#include <fstream>
#include <string>

#include <FL/Fl_Preferences.H>

#include "status.h"
#include "config.h"
#include "flimg.h"
#include "flimg_dialog.h"
#include "file_io.h"

status progStatus = {
	50,				// int mainX;
	50,				// int mainY;

	"",				// my_call
	"",				// my_info
	"127.0.0.1",	// fldigi socket address
	"7322",			// fldigi socket port
	"127.0.0.1",	// fldigi xmlrpc socket address
	"7362",			// fldigi xmlrpc socket port

	// User Assigned addr/ports not saved.
	"",				// User assigned fldigi socket address
	"",				// User assigned fldigi socket port
	"",				// User assigned fldigi xmlrpc socket address
	"",				// User assigned fldigi xmlrpc socket port

	true,			// use_compression
	BASE256,		// encoder
	"base256",      // encoder string name
	1,				// selected_mode
	64,				// blocksize
	1,				// repeatNN
	1,				// repeat_header

	false,			// bool sync_mode_flimg_fldigi;
	false,			// bool sync_mode_fldigi_flimg;
	false,			// bool fldigi_xmt_mode_change;

	1,				// int repeat_every;
	false,			// bool repeat_at_times;
	"",				// string repeat_times;
	false,			// bool repeat_at_times;

	false, 			// bool use_txrx_interval;
	3, 				// int  tx_interval_minutes;
	10, 			// int  rx_interval_seconds;

	false, 			// bool use_header_modem;
	1,				// int  header_selected_mode;
	false,          // bool disable_header_modem_on_block_fills;

	0,				// int  use_tx_on_report;

	false,			// bool clear_tosend_on_tx_blocks;

	false,          // bool enable_delete_warning;

	false,          // bool enable_tx_unproto
	false,          // bool enable_unproto_markers

	false,          // bool queue_fills_only

	false,          // bool auto_load_queue

	false,          // bool load_from_tx_folder

	"",				// string auto_load_queue_path

	false,          // bool hamcast_mode_cycle

	false,          // bool hamcast_mode_enable_1
	1,              // int hamcast_mode_selection_1

	false,          // bool hamcast_mode_enable_2
	1,              // int hamcast_mode_selection_2

	false,          // bool hamcast_mode_enable_3
	1,              // int hamcast_mode_selection_3

	false,          // bool hamcast_mode_enable_4
	1,              // int hamcast_mode_selection_4

	true,          // bool auto_rx_save
	true,          // bool auto_rx_save_local_time
};

extern std::string selected_encoder_string;

/** ********************************************************
 *
 ***********************************************************/
void status::saveLastState()
{
	Fl_Preferences FLIMGpref(flimgHomeDir.c_str(), "w1hkj.com",  PACKAGE_NAME);

	int mX = main_window->x();
	int mY = main_window->y();
	if (mX >= 0 && mX >= 0) {
		mainX = mX;
		mainY = mY;
	}

	FLIMGpref.set("version", PACKAGE_VERSION);
	FLIMGpref.set("mainx", mX);
	FLIMGpref.set("mainy", mY);

	my_call = txt_tx_mycall->value();
	my_info = txt_tx_myinfo->value();

	FLIMGpref.set("mycall", my_call.c_str());
	FLIMGpref.set("myinfo", my_info.c_str());
	FLIMGpref.set("socket_address", socket_addr.c_str());
	FLIMGpref.set("socket_port", socket_port.c_str());
	FLIMGpref.set("xmlrpc_address", xmlrpc_addr.c_str());
	FLIMGpref.set("xmlrpc_port", xmlrpc_port.c_str());
	FLIMGpref.set("blocksize", blocksize);
	FLIMGpref.set("repeatNN", repeatNN);
	FLIMGpref.set("repeat_header", repeat_header);
	FLIMGpref.set("selected_mode", selected_mode);
	FLIMGpref.set("compression", use_compression);
	FLIMGpref.set("encoder", encoder);
	FLIMGpref.set("encoder_string", encoder_string.c_str());
	FLIMGpref.set("sync_mode_flimg_fldigi", sync_mode_flimg_fldigi);
	FLIMGpref.set("sync_mode_fldigi_flimg", sync_mode_fldigi_flimg);
	FLIMGpref.set("fldigi_xmt_mode_change", fldigi_xmt_mode_change);

	FLIMGpref.set("repeat_every", repeat_every);
	FLIMGpref.set("repeat_at_times", repeat_at_times);
	FLIMGpref.set("repeat_times", repeat_times.c_str());

	FLIMGpref.set("repeat_forever", repeat_forever);

	FLIMGpref.set("use_repeater_interval", use_txrx_interval);
	FLIMGpref.set("repeater_tx_minutes", tx_interval_minutes);
	FLIMGpref.set("repeater_rx_seconds", rx_interval_seconds);

	FLIMGpref.set("disable_header_modem_on_block_fills", disable_header_modem_on_block_fills);
	FLIMGpref.set("use_header_modem", use_header_modem);
	FLIMGpref.set("header_selected_mode", header_selected_mode);

	FLIMGpref.set("use_tx_on_report", use_tx_on_report);

	FLIMGpref.set("clear_tosend_on_tx_blocks", clear_tosend_on_tx_blocks);

	FLIMGpref.set("enable_delete_warning", enable_delete_warning);

	FLIMGpref.set("enable_tx_unproto", enable_tx_unproto);
	FLIMGpref.set("enable_unproto_markers", enable_unproto_markers);

	FLIMGpref.set("queue_fills_only", queue_fills_only);

	FLIMGpref.set("auto_load_queue", auto_load_queue);
	FLIMGpref.set("load_from_tx_folder", load_from_tx_folder);

	FLIMGpref.set("auto_load_queue_path", auto_load_queue_path.c_str());

	FLIMGpref.set("hamcast_mode_cycle", hamcast_mode_cycle);

	FLIMGpref.set("hamcast_mode_enable_1", hamcast_mode_enable_1);
	FLIMGpref.set("hamcast_mode_selection_1", hamcast_mode_selection_1);

	FLIMGpref.set("hamcast_mode_enable_2", hamcast_mode_enable_2);
	FLIMGpref.set("hamcast_mode_selection_2", hamcast_mode_selection_2);

	FLIMGpref.set("hamcast_mode_enable_3", hamcast_mode_enable_3);
	FLIMGpref.set("hamcast_mode_selection_3", hamcast_mode_selection_3);

	FLIMGpref.set("hamcast_mode_enable_4", hamcast_mode_enable_4);
	FLIMGpref.set("hamcast_mode_selection_4", hamcast_mode_selection_4);

	FLIMGpref.set("auto_rx_save", auto_rx_save);
	FLIMGpref.set("auto_rx_save_local_time", auto_rx_save_local_time);

}

/** ********************************************************
 *
 ***********************************************************/
void status::loadLastState()
{
	Fl_Preferences FLIMGpref(flimgHomeDir.c_str(), "w1hkj.com", PACKAGE_NAME);

	if (FLIMGpref.entryExists("version")) {
		char *defbuffer;

		FLIMGpref.get("mainx", mainX, mainX);
		FLIMGpref.get("mainy", mainY, mainY);

		FLIMGpref.get("mycall", defbuffer, "");
		my_call = defbuffer; free(defbuffer);

		FLIMGpref.get("myinfo", defbuffer, "");
		my_info = defbuffer; free(defbuffer);

		FLIMGpref.get("socket_address", defbuffer, socket_addr.c_str());
		socket_addr = defbuffer; free(defbuffer);
		FLIMGpref.get("socket_port", defbuffer, socket_port.c_str());
		socket_port = defbuffer; free(defbuffer);

		FLIMGpref.get("xmlrpc_address", defbuffer, xmlrpc_addr.c_str());
		xmlrpc_addr = defbuffer; free(defbuffer);
		FLIMGpref.get("xmlrpc_port", defbuffer, xmlrpc_port.c_str());
		xmlrpc_port = defbuffer; free(defbuffer);

		FLIMGpref.get("blocksize", blocksize, blocksize);
		FLIMGpref.get("repeatNN", repeatNN, repeatNN);
		FLIMGpref.get("repeat_header", repeat_header, repeat_header);

		FLIMGpref.get("selected_mode", selected_mode, selected_mode);

		int i = 0;
		FLIMGpref.get("compression", i, use_compression);
		use_compression = i;

		FLIMGpref.get("sync_mode_flimg_fldigi", i, sync_mode_flimg_fldigi);
		sync_mode_flimg_fldigi = i;

		FLIMGpref.get("sync_mode_fldigi_flimg", i, sync_mode_fldigi_flimg);
		sync_mode_fldigi_flimg = i;


		FLIMGpref.get("fldigi_xmt_mode_change", i, fldigi_xmt_mode_change);
		fldigi_xmt_mode_change = i;

		FLIMGpref.get("encoder", encoder, encoder);
		FLIMGpref.get("encoder_string", defbuffer, encoder_string.c_str());
		encoder_string = defbuffer; free(defbuffer);

		FLIMGpref.get("repeat_every", repeat_every, repeat_every);
		FLIMGpref.get("repeat_at_times", i, repeat_at_times);
		repeat_at_times = i;

		FLIMGpref.get("repeat_times", defbuffer, repeat_times.c_str());
		repeat_times = defbuffer; free(defbuffer);

		FLIMGpref.get("repeat_forever", i, repeat_forever);
		repeat_forever = i;

		FLIMGpref.get("use_repeater_interval", i, use_txrx_interval);
		use_txrx_interval = (bool) i;

		FLIMGpref.get("repeater_tx_minutes", i, tx_interval_minutes);
		tx_interval_minutes = i;

		FLIMGpref.get("repeater_rx_seconds", i, rx_interval_seconds);
		rx_interval_seconds = i;

		FLIMGpref.get("disable_header_modem_on_block_fills", i, disable_header_modem_on_block_fills);
		disable_header_modem_on_block_fills = (bool) i;

		FLIMGpref.get("use_header_modem", i, use_header_modem);
		use_header_modem = (bool) i;

		FLIMGpref.get("header_selected_mode", i, header_selected_mode);
		header_selected_mode = i;

		FLIMGpref.get("use_tx_on_report", i, use_tx_on_report);
		use_tx_on_report = i;

		FLIMGpref.get("clear_tosend_on_tx_blocks", i, clear_tosend_on_tx_blocks);
		clear_tosend_on_tx_blocks = (bool) i;

		FLIMGpref.get("enable_delete_warning", i, enable_delete_warning);
		enable_delete_warning = (bool) i;

		FLIMGpref.get("enable_tx_unproto", i, enable_tx_unproto);
		enable_tx_unproto = (bool) i;

		FLIMGpref.get("enable_unproto_markers", i, enable_unproto_markers);
		enable_unproto_markers = (bool) i;

		FLIMGpref.get("queue_fills_only", i, queue_fills_only);
		queue_fills_only = (bool) i;

		FLIMGpref.get("auto_load_queue", i, auto_load_queue);
		auto_load_queue = (bool) i;

		FLIMGpref.get("load_from_tx_folder", i, load_from_tx_folder);
		load_from_tx_folder = (bool) i;

		FLIMGpref.get("auto_load_queue_path", defbuffer, "");
		auto_load_queue_path.assign(defbuffer);
		free(defbuffer);

		FLIMGpref.get("hamcast_mode_cycle", i, hamcast_mode_cycle);
		hamcast_mode_cycle = (bool) i;

		FLIMGpref.get("hamcast_mode_enable_1", i, hamcast_mode_enable_1);
		hamcast_mode_enable_1 = (bool) i;

		FLIMGpref.get("hamcast_mode_selection_1", i, hamcast_mode_selection_1);
		hamcast_mode_selection_1 = i;

		FLIMGpref.get("hamcast_mode_enable_2", i, hamcast_mode_enable_2);
		hamcast_mode_enable_2 = (bool) i;

		FLIMGpref.get("hamcast_mode_selection_2", i, hamcast_mode_selection_2);
		hamcast_mode_selection_2 = i;

		FLIMGpref.get("hamcast_mode_enable_3", i, hamcast_mode_enable_3);
		hamcast_mode_enable_3 = (bool) i;

		FLIMGpref.get("hamcast_mode_selection_3", i, hamcast_mode_selection_3);
		hamcast_mode_selection_3 = i;

		FLIMGpref.get("hamcast_mode_enable_4", i, hamcast_mode_enable_4);
		hamcast_mode_enable_4 = (bool) i;

		FLIMGpref.get("hamcast_mode_selection_4", i, hamcast_mode_selection_4);
		hamcast_mode_selection_4 = i;

		FLIMGpref.get("auto_rx_save", i, auto_rx_save);
		auto_rx_save = (bool) i;

		FLIMGpref.get("auto_rx_save_local_time", i, auto_rx_save_local_time);
		auto_rx_save_local_time = (bool) i;

		if(auto_load_queue_path.size() < 1)
			auto_load_queue = false;

		if(enable_tx_unproto) {
			use_header_modem = false;
		}
	}
}
