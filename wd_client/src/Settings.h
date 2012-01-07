/*
 * Settings.h
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include<string>
using namespace std;
class Settings {
public:
	static const string SERVER_ADDR;
	static const string SERVER_PORT;
	static const string LOCK_TIME;
	static const string BASE_PATH;
	static const string FILELISTFILE_PATH;
	static const string TEXT_FILE_TYPE;
};

#endif /* SETTINGS_H_ */
