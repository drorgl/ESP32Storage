#ifndef _IFILESYSTEM_H_
#define _IFILESYSTEM_H_

class IFilesystem {
public:
	virtual int init() = 0;
	virtual int format() = 0;
	virtual int deinit() = 0;

	virtual long get_size() = 0;
	virtual long get_available() = 0;
};

#endif