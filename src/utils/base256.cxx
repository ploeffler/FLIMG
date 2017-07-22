// =====================================================================
//
// base256 text encoding
//
// Author: Dave Freese, W1HKJ
// Copyright: 2010
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

#include <stdlib.h>

#include "base256.h"

/** ********************************************************
 *
 ***********************************************************/
void base256::init()
{
	iolen = 0;
	iocp = 0;
	ateof = false;
	linelength = 0;
}

/** ********************************************************
 * /brief FLDIGI uses some control codes to alter the program state
 * several digital modems suppress some control and high bit set
 * characters this function substitutes a two character
 * sequence for the offending characters
 ***********************************************************/
void base256::escape(std::string &in, bool encode)
{
	std::string out;
	if (encode) {
		for( size_t i = 0; i < in.length(); i++) {
			switch ((in[i] & 0xFF)) {
				case ':'  : out.append("::"); break;
				case 0x00 : out.append(":0"); break;
				case 0x01 : out.append(":1"); break; // mt63
				case 0x02 : out.append(":2"); break;
				case 0x03 : out.append(":3"); break;
				case 0x04 : out.append(":4"); break;
				case 0x05 : out.append(":5"); break;
				case 0x06 : out.append(":6"); break;
				case 0x07 : out.append(":7"); break;
				case 0x08 : out.append(":8"); break;
				case 0x09 : out.append(":9"); break;
				case '\n' : out.append(":A"); break;
				case '\r' : out.append(":B"); break;
				case '^'  : out.append(":C"); break;
				case 0x7F : out.append(":D"); break;
				case 0xFF : out.append(":E"); break; // mt63
				default: out += in[i];
			}
		}
	} else {
		unsigned char ch = 0;
		for (size_t i = 0; i < in.length(); i++) {
			ch = in[i] & 0xFF;
			if (ch == ':') {
				i++;
				ch = in[i] & 0xFF;
				switch (ch) {
					case ':' : out += ':';  break;
					case '0' : out += ' ';  out[out.length() - 1] = 0x00; break;
					case '1' : out += 0x01; break;
					case '2' : out += 0x02; break;
					case '3' : out += 0x03; break;
					case '4' : out += 0x04; break;
					case '5' : out += 0x05; break;
					case '6' : out += 0x06; break;
					case '7' : out += 0x07; break;
					case '8' : out += 0x08; break;
					case '9' : out += 0x09; break;
					case 'A' : out += '\n'; break;
					case 'B' : out += '\r'; break;
					case 'C' : out += '^';  break;
					case 'D' : out += 0x7F; break;
					case 'E' : out += 0xFF; break;
				}
			} else out += ch;
		}
	}
	in = out;
}

/** ********************************************************
 *
 ***********************************************************/
void base256::addlf(std::string &in)
{
	std::string out;
	int len = 0;
	for (size_t n = 0; n < in.length(); n++) {
		if (len < LINELEN) {out += in[n]; len++;}
		else {out += '\n'; out += in[n]; len = 0;}
	}
	in.assign(out);
}

/** ********************************************************
 *
 ***********************************************************/
void base256::remlf(std::string &in)
{
	std::string out;
	for (size_t n = 0; n < in.length(); n++) {
		if (in[n] != '\n') out += in[n];
	}
	in.assign(out);
}

/** ********************************************************
 *
 ***********************************************************/
std::string base256::encode(std::string &in)
{
	char insize[20];
	snprintf(insize, sizeof(insize), "%d\n", (int)in.length());

	output.assign(insize);
	iocp = 0;
	ateof = false;

	std::string temp (in);
	escape (temp);
	output.append(temp);
	return output;
}

/** ********************************************************
 *
 ***********************************************************/
std::string base256::decode(std::string &in, bool &decode_error)
{
	int temp;
	//size_t nbr = 0;
	std::string output = in;
	decode_error = false;

	size_t p = output.find("\n");
	if (p == std::string::npos) {
		decode_error = true;
		return "ERROR: base256 missing character count";
	}

	sscanf(output.substr(0, p).c_str(), "%d", &temp);
	//nbr = temp;

	output.erase(0, p+1);
	escape(output, false);
	return output;
}
