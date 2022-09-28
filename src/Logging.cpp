#include "Logging.h"
#include <iostream>
#include <string>
#include <cerrno>
#include <cstdarg>


static const char* traceFileName = "Trace.log";
static FILE* traceFile;


void TraceInit()
{
	errno_t err;
	err = fopen_s(&traceFile, traceFileName, "wt");
	if (err != 0)
	{
		char buff[256];
		strerror_s(buff, 100, err);
		std::cout<<("Cannot open traceFile!: %s \n", buff);
	}

}

void TraceMessage(const char* formatString, ...)
{
	if (traceFile == NULL)
	{
		std::cout << ("TraceFile is NULL!\n");
		return;
	}
	if (ferror(traceFile))
	{
		char buff[256];
		strerror_s(buff, 100, ferror(traceFile));
		std::cout << ("TraceFile error!: %s \n", buff);
		return;
	}

	const char* endofline = "\n";
	va_list args;
	va_start(args, formatString);
	vfprintf(traceFile, formatString, args);

	va_start(args, endofline);
	vfprintf(traceFile, endofline, args);

}

void TraceShutdown()
{

	if (traceFile == NULL)
	{
		std::cout << ("TraceFile is NULL!\n");
		return;
	}
	if (ferror(traceFile))
	{
		char buff[256];
		strerror_s(buff, 100, ferror(traceFile));
		std::cout << ("TraceFile error!: %s \n", buff);
		return;
	}

	fclose(traceFile);
}


