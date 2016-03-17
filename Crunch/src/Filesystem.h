/*
 * Filesystem.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Daniel G Billings Jr
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

namespace crunch
{
	//The idea here will be to write a platform independent (through pre-compiler directives) method of doing only what I need to do with the filesystem.
	//Boost was determined to be too large, and other methods also have their drawbacks.  This will be expanded as needed.
class Filesystem
{
public:
	Filesystem();
	virtual ~Filesystem();
};

} /* namespace crunch */

#endif /* FILESYSTEM_H_ */
