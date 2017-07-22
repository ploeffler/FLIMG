//
//  circularQueue.h
//
//  Author(s):
//	Robert Stiles, KK5VD, Copyright (C) 2013, 2015
//	Dave Freese, W1HKJ, Copyright (C) 2013
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

#ifndef flimg_circular_queue_h
#define flimg_circular_queue_h

#include <pthread.h>
#include <string>
#include <exception>
#include <cstring>
#include <time.h>

#include "util.h"
#include "crc16.h"

#define CQUE_HOLD   1
#define CQUE_RESUME 0
#define CQUE_SLEEP_TIME 10

#define TIME_SET 1
#define TIME_COUNT 2

class CircQueException : public std::exception
{
public:
	CircQueException(int err_ = 0)	 : err(err_), msg(err_to_str(err_)) { }
	CircQueException(const char* msg_) : err(1),	msg(msg_)			 { }
	CircQueException(int err_, const std::string& prefix)
	: err(err_), msg(std::string(prefix).append(": ").append(err_to_str(err_))) { }
	virtual ~CircQueException() throw() { }
	const char*	 what(void) const throw() { return msg.c_str(); }
	int			 error(void) const { return err; }

protected:
	const char* err_to_str(int e) {
		return strerror(e);
	}
	int			 err;
	std::string	 msg;
};


class Circular_queue {
private:

	pthread_t thread;
	pthread_mutex_t mutex;
	pthread_cond_t  condition;

	char *buffer;

	int buffer_size;
	int bufferCount;
	int exit_thread;
	int index_mask;
	int read_index;
	int stalled;
	int write_index;

	Ccrc16 crcValidate;

public:

	int inhibitDataOut;
	int thread_running;

	int  (* matchFound)(void *);
	int  (* readData)(void *);
	void * (* queueParser)(void *);

public:

	Circular_queue(void);
	Circular_queue(int po2, int (*_matchFound)(void *),	\
				   int (*_readDataFrom)(void *), void * (*_queueParser)(void *));
	~Circular_queue();

public:

	bool timeOut(time_t &timeValue, time_t seconds, int attribute);

	int  adjustReadQueIndex(int count);
	int  lookAhead(char *_buffer, int _size);
	int  lookAheadCRC(char *_buffer, int _size, unsigned int *crcVal, int *reset);
	int  lookAheadForCharacter(char character, int *found);
	int  lookAheadToTerminator(char *_buffer, char terminator, int maxLen);
	int  queueStalled() { return stalled; }
	int  readQueData(int buffer_count);
	int  thread_exit() { return exit_thread; }

	void addToQueue(char *_buffer, int _size);
	void addToQueueNullFiltered(char *_buffer, int _size);
	void resumeQueue();
	void signal(void);
	void sleep(int seconds, int milliseconds);
	void startDataOut();
	void stopDataOut();
	void stopQueue();

	void milliSleep(int milliseconds)
	{
		sleep(0, milliseconds);
	}

	void setUp(int po2, int (*_matchFound)(void *),	\
			   int (*_readDataFrom)(void *), void * (*_queueParser)(void *));
};


#endif // flimg_circular_queue_h
