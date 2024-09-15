#pragma once

#include <windows.h>
#include <evntrace.h>
#include <tdh.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

struct Reader {
    int id;
    wchar_t* SessionName;
    TRACEHANDLE SessionHandle;
    TRACEHANDLE TraceHandle;
};

extern Reader Readers[];



typedef void (WINAPI* EventRecordCallbackFuncPtr)(PEVENT_RECORD);

int InitializeEtwReader(std::vector<HANDLE>& threads);
Reader* SetupTrace(int id, const wchar_t* guid, EventRecordCallbackFuncPtr func, const wchar_t* info);
Reader* SetupTrace_SecurityAuditing(int id);


// Helper
EVENT_TRACE_PROPERTIES* MakeSessionProperties(size_t session_name_len);
void EnableProvider(TRACEHANDLE sessionHandle, const GUID& providerGuid);
void EtwReaderStopAll();
BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType);
DWORD WINAPI TraceProcessingThread(LPVOID param);