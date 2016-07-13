#ifndef ENGINE_LOG_H
#define ENGINE_LOG_H
#include <string>
#include <fstream>
#include <assert.h>
inline void Log(std::string message)
{
	auto logfile = fopen("Log.txt", "a");
	assert(logfile != nullptr);
	fputs(message.c_str(), logfile);
	fclose(logfile);
}
inline auto LogFile()
{
	return fopen("Log.txt", "a");
}
#endif //ENGINE_LOG_H
