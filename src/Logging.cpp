#include "pch.h"

static const char* traceFileName = "Trace.log";
static FILE* traceFile;

bool IsFileStatusGood();

void TraceInit()
{
	errno_t err;
	err = fopen_s(&traceFile, traceFileName, "wt");
	if (err != 0)
	{
		char buff[256];
		strerror_s(buff, 100, err);
		std::cout << ("Cannot open traceFile!: %s \n", buff);
		return;
	}
	TraceMessage("TraceInit()");
}

void TraceMessage(const char* formatString, ...)
{
	if (!IsFileStatusGood()) return;

	const char* endofline = "\n";
	va_list args;
	va_start(args, formatString);
	vfprintf(traceFile, formatString, args);
	std::cout << formatString << std::endl;
	va_start(args, endofline);
	vfprintf(traceFile, endofline, args);

}

void TraceShutdown()
{
	if (!IsFileStatusGood()) return;

	TraceMessage("TraceShutdown()");
	fclose(traceFile);
}

bool IsFileStatusGood()
{
	if (traceFile == NULL)
	{
		std::cout << ("TraceFile is NULL!\n");
		return false;
	}
	if (ferror(traceFile))
	{
		char buff[256];
		strerror_s(buff, 100, ferror(traceFile));
		std::cout << ("TraceFile error!: %s \n", buff);
		return false;
	}

	return true;
}
