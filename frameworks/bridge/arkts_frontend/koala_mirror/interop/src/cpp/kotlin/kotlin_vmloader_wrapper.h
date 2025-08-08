#ifndef KOTLIN_VMLOADER_WRAPPER_H
#define KOTLIN_VMLOADER_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef bool            kotlin_KBoolean;
#else
typedef _Bool           kotlin_KBoolean;
#endif
typedef unsigned short     kotlin_KChar;
typedef signed char        kotlin_KByte;
typedef short              kotlin_KShort;
typedef int                kotlin_KInt;
typedef long long          kotlin_KLong;
typedef unsigned char      kotlin_KUByte;
typedef unsigned short     kotlin_KUShort;
typedef unsigned int       kotlin_KUInt;
typedef unsigned long long kotlin_KULong;
typedef float              kotlin_KFloat;
typedef double             kotlin_KDouble;
typedef float __attribute__ ((__vector_size__ (16))) kotlin_KVector128;
typedef void*              kotlin_KNativePtr;
struct kotlin_KType;
typedef struct kotlin_KType kotlin_KType;

typedef struct {
  kotlin_KNativePtr pinned;
} kotlin_kref_VMLoaderApplication;
typedef struct {
  kotlin_KNativePtr pinned;
} kotlin_kref_PeerNodeStub;

typedef kotlin_kref_VMLoaderApplication (*application_create_t)(const char* appUrl, const char* appParams);
typedef kotlin_KBoolean (*application_enter_t)(kotlin_kref_VMLoaderApplication app);
typedef kotlin_kref_PeerNodeStub (*application_start_t)(kotlin_kref_VMLoaderApplication app);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* KOTLIN_VMLOADER_WRAPPER_H */
