#include "./debug.hpp"

#include "misc/autocrit.hpp"
#include "misc/critsect.hpp"

#include <time.h>
#include <stdarg.h>
#include <SDL3/SDL.h>

#include "memmgr.hpp"

extern bool gInAssert = false;
extern bool gPopWorkDumpLeakedMem = false;

static FILE *gTraceFile = nullptr;
static int gTraceFileLen = 0;
static int gTraceFileNum = 1;

using namespace PopWork;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct POPWORK_ALLOC_INFO
{
	int size;
	char file[512];
	int line;
};
static bool gShowLeaks = false;
static bool gPopWorkAllocMapValid = false;
class PopWorkAllocMap : public std::map<void *, POPWORK_ALLOC_INFO>
{
  public:
	CritSect mCrit;

  public:
	PopWorkAllocMap()
	{
		gPopWorkAllocMapValid = true;
	}
	~PopWorkAllocMap()
	{
		if (gShowLeaks)
			PopWorkDumpUnfreed();

		gPopWorkAllocMapValid = false;
	}
};
static PopWorkAllocMap gPopWorkAllocMap;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PopWorkTrace(const char *theStr)
{
	if (gTraceFile == nullptr)
	{
		gTraceFileNum = (gTraceFileNum + 1) % 2;
		char aBuf[50];
		sprintf(aBuf, "trace%d.txt", gTraceFileNum + 1);
		gTraceFile = fopen(aBuf, "w");
		if (gTraceFile == nullptr)
			return;
	}

	fprintf(gTraceFile, "%s\n", theStr);
	fflush(gTraceFile);

	gTraceFileLen += strlen(theStr);
	if (gTraceFileLen > 100000)
	{
		fclose(gTraceFile);
		gTraceFile = nullptr;
		gTraceFileLen = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void PopWorkTraceFmt(const PopChar *fmt, ...)
{
	// Does not append a newline by default, also takes vararg parameters

	va_list argList;
	va_start(argList, fmt);
	std::string result = PopStringToStringFast(vformat(fmt, argList));
	va_end(argList);

	if (gTraceFile == nullptr)
	{
		gTraceFileNum = (gTraceFileNum + 1) % 2;
		char aBuf[50];
		sprintf(aBuf, "trace%d.txt", gTraceFileNum + 1);
		gTraceFile = fopen(aBuf, "w");
		if (gTraceFile == nullptr)
			return;
	}

	fprintf(gTraceFile, "%s", result.c_str());
	fflush(gTraceFile);

	gTraceFileLen += result.length();
	if (gTraceFileLen > 100000)
	{
		fclose(gTraceFile);
		gTraceFile = nullptr;
		gTraceFileLen = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PopWorkMemAddTrack(void *addr, int asize, const char *fname, int lnum)
{
	if (!gPopWorkAllocMapValid)
		return;

	AutoCrit aCrit(gPopWorkAllocMap.mCrit);
	gShowLeaks = true;

	POPWORK_ALLOC_INFO &info = gPopWorkAllocMap[addr];
	strncpy(info.file, fname, sizeof(info.file) - 1);
	info.line = lnum;
	info.size = asize;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PopWorkMemRemoveTrack(void *addr)
{
	if (!gPopWorkAllocMapValid)
		return;

	AutoCrit aCrit(gPopWorkAllocMap.mCrit);
	PopWorkAllocMap::iterator anItr = gPopWorkAllocMap.find(addr);
	if (anItr != gPopWorkAllocMap.end())
		gPopWorkAllocMap.erase(anItr);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PopWorkDumpUnfreed()
{
	if (!gPopWorkAllocMapValid)
		return;

	AutoCrit aCrit(gPopWorkAllocMap.mCrit);
	PopWorkAllocMap::iterator i;
	int totalSize = 0;
	char buf[8192];

#ifdef POPWORK_DUMP_LEAKED_MEM
	char hex_dump[1024];
	char ascii_dump[1024];
	int count = 0;
	int index = 0;
#endif

	FILE *f = fopen("mem_leaks.txt", "wt");
	if (!f)
		return;

	time_t aTime = time(nullptr);
	sprintf(buf, "Memory Leak Report for %s\n", asctime(localtime(&aTime)));
	fprintf(f, buf);
	SDL_Log("\n%s", buf);
	for (i = gPopWorkAllocMap.begin(); i != gPopWorkAllocMap.end(); i++)
	{
		sprintf(buf, "%s(%d) : Leak %d byte%s\n", i->second.file, i->second.line, i->second.size,
				i->second.size > 1 ? "s" : "");
		SDL_Log("%s", buf);
		fprintf(f, buf);

#ifdef POPWORK_DUMP_LEAKED_MEM
		unsigned char *data = (unsigned char *)i->first;

		for (index = 0; index < i->second.size; index++)
		{
			unsigned char _c = *data;

			if (count == 0)
				sprintf(hex_dump, "\t%02X ", _c);
			else
				sprintf(hex_dump, "%s%02X ", hex_dump, _c);

			if ((_c < 32) || (_c > 126))
				_c = '.';

			if (count == 7)
				sprintf(ascii_dump, "%s%c ", ascii_dump, _c);
			else
				sprintf(ascii_dump, "%s%c", count == 0 ? "\t" : ascii_dump, _c);

			if (++count == 16)
			{
				count = 0;
				sprintf(buf, "%s\t%s\n", hex_dump, ascii_dump);
				fprintf(f, buf);

				memset((void *)hex_dump, 0, 1024);
				memset((void *)ascii_dump, 0, 1024);
			}

			data++;
		}

		if (count != 0)
		{
			fprintf(f, hex_dump);
			for (index = 0; index < 16 - count; index++)
				fprintf(f, "\t");

			fprintf(f, ascii_dump);

			for (index = 0; index < 16 - count; index++)
				fprintf(f, ".");
		}

		count = 0;
		fprintf(f, "\n\n");
		memset((void *)hex_dump, 0, 1024);
		memset((void *)ascii_dump, 0, 1024);

#endif // POPWORK_DUMP_LEAKED_MEM

		totalSize += i->second.size;
	}

	sprintf(buf, "-----------------------------------------------------------\n");
	fprintf(f, buf);
	SDL_Log("%s", buf);
	sprintf(buf, "Total Unfreed: %d bytes (%dKB)\n\n", totalSize, totalSize / 1024);
	SDL_Log("%s", buf);
	fprintf(f, buf);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void OutputDebug(const PopChar *fmt, ...)
{
	va_list argList;
	va_start(argList, fmt);
	std::string result = PopStringToStringFast(vformat(fmt, argList));
	va_end(argList);

	SDL_Log("%s", result.c_str());
}
