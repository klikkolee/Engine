#ifndef ENGINE_LOG_H
#define ENGINE_LOG_H
#include <string>
#include <fstream>
#include <assert.h>
#include <stdarg.h>
inline void Log(std::string message,...)
{
	va_list args;
	va_start(args,message);
	auto logfile = fopen("Log.txt", "a");
	assert(logfile != nullptr);
	vfprintf(logfile,message.c_str(), args);
	fclose(logfile);
}
#endif //ENGINE_LOG_H
