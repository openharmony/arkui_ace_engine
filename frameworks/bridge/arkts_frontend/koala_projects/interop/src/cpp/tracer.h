#ifndef _KOALA_TRACER_
#define _KOALA_TRACER_

#ifdef KOALA_OHOS
#include <hilog/log.h>
#define KOALA_TRACE(msg, str) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "Koala", msg, str)
// Also do
//  hdc shell hilog -p off
//  hdc shell hilog -Q pidoff
// to see the output.
#define KOALA_TRACE_PUBLIC "%{public}s"
#else
#include <stdio.h>
#define KOALA_TRACE(msg, str) fprintf(stderr, "Koala: " msg "\n", str)
#define KOALA_TRACE_PUBLIC "%s"
#endif

class InteropMethodCall {
  private:
    const char* name;
  public:
    InteropMethodCall(const char* name) : name(name) {
        KOALA_TRACE(">>> " KOALA_TRACE_PUBLIC, name);
    }
    ~InteropMethodCall() {
        KOALA_TRACE("<<< " KOALA_TRACE_PUBLIC, name);
    }
};

#endif // _KOALA_TRACER_