/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KONAN_KOTLIN_KOALA_H
#define KONAN_KOTLIN_KOALA_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            kotlin_koala_KBoolean;
#else
typedef _Bool           kotlin_koala_KBoolean;
#endif
typedef unsigned short     kotlin_koala_KChar;
typedef signed char        kotlin_koala_KByte;
typedef short              kotlin_koala_KShort;
typedef int                kotlin_koala_KInt;
typedef long long          kotlin_koala_KLong;
typedef unsigned char      kotlin_koala_KUByte;
typedef unsigned short     kotlin_koala_KUShort;
typedef unsigned int       kotlin_koala_KUInt;
typedef unsigned long long kotlin_koala_KULong;
typedef float              kotlin_koala_KFloat;
typedef double             kotlin_koala_KDouble;
typedef float __attribute__ ((__vector_size__ (16))) kotlin_koala_KVector128;
typedef void*              kotlin_koala_KNativePtr;
struct kotlin_koala_KType;
typedef struct kotlin_koala_KType kotlin_koala_KType;

typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Byte;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Short;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Int;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Long;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Float;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Double;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Char;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Boolean;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_Unit;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_UByte;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_UShort;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_UInt;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_kotlin_ULong;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_koala_PeerNodeStub;
typedef struct {
  kotlin_koala_KNativePtr pinned;
} kotlin_koala_kref_koala_Application;


typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(kotlin_koala_KNativePtr ptr);
  void (*DisposeString)(const char* string);
  kotlin_koala_KBoolean (*IsInstance)(kotlin_koala_KNativePtr ref, const kotlin_koala_KType* type);
  kotlin_koala_kref_kotlin_Byte (*createNullableByte)(kotlin_koala_KByte);
  kotlin_koala_KByte (*getNonNullValueOfByte)(kotlin_koala_kref_kotlin_Byte);
  kotlin_koala_kref_kotlin_Short (*createNullableShort)(kotlin_koala_KShort);
  kotlin_koala_KShort (*getNonNullValueOfShort)(kotlin_koala_kref_kotlin_Short);
  kotlin_koala_kref_kotlin_Int (*createNullableInt)(kotlin_koala_KInt);
  kotlin_koala_KInt (*getNonNullValueOfInt)(kotlin_koala_kref_kotlin_Int);
  kotlin_koala_kref_kotlin_Long (*createNullableLong)(kotlin_koala_KLong);
  kotlin_koala_KLong (*getNonNullValueOfLong)(kotlin_koala_kref_kotlin_Long);
  kotlin_koala_kref_kotlin_Float (*createNullableFloat)(kotlin_koala_KFloat);
  kotlin_koala_KFloat (*getNonNullValueOfFloat)(kotlin_koala_kref_kotlin_Float);
  kotlin_koala_kref_kotlin_Double (*createNullableDouble)(kotlin_koala_KDouble);
  kotlin_koala_KDouble (*getNonNullValueOfDouble)(kotlin_koala_kref_kotlin_Double);
  kotlin_koala_kref_kotlin_Char (*createNullableChar)(kotlin_koala_KChar);
  kotlin_koala_KChar (*getNonNullValueOfChar)(kotlin_koala_kref_kotlin_Char);
  kotlin_koala_kref_kotlin_Boolean (*createNullableBoolean)(kotlin_koala_KBoolean);
  kotlin_koala_KBoolean (*getNonNullValueOfBoolean)(kotlin_koala_kref_kotlin_Boolean);
  kotlin_koala_kref_kotlin_Unit (*createNullableUnit)(void);
  kotlin_koala_kref_kotlin_UByte (*createNullableUByte)(kotlin_koala_KUByte);
  kotlin_koala_KUByte (*getNonNullValueOfUByte)(kotlin_koala_kref_kotlin_UByte);
  kotlin_koala_kref_kotlin_UShort (*createNullableUShort)(kotlin_koala_KUShort);
  kotlin_koala_KUShort (*getNonNullValueOfUShort)(kotlin_koala_kref_kotlin_UShort);
  kotlin_koala_kref_kotlin_UInt (*createNullableUInt)(kotlin_koala_KUInt);
  kotlin_koala_KUInt (*getNonNullValueOfUInt)(kotlin_koala_kref_kotlin_UInt);
  kotlin_koala_kref_kotlin_ULong (*createNullableULong)(kotlin_koala_KULong);
  kotlin_koala_KULong (*getNonNullValueOfULong)(kotlin_koala_kref_kotlin_ULong);

  /* User functions. */
  struct {
    struct {
      struct {
        struct {
          kotlin_koala_KType* (*_type)(void);
          kotlin_koala_kref_koala_PeerNodeStub (*PeerNodeStub)();
        } PeerNodeStub;
        struct {
          kotlin_koala_KType* (*_type)(void);
          kotlin_koala_kref_koala_Application (*Application)(const char* appUrl, const char* appParams);
          kotlin_koala_KBoolean (*enter)(kotlin_koala_kref_koala_Application thiz, kotlin_koala_KInt arg0, kotlin_koala_KInt arg1);
          kotlin_koala_kref_koala_PeerNodeStub (*start)(kotlin_koala_kref_koala_Application thiz);
        } Application;
      } koala;
    } root;
  } kotlin;
} kotlin_koala_ExportedSymbols;
extern kotlin_koala_ExportedSymbols* kotlin_koala_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* KONAN_KOTLIN_KOALA_H */
