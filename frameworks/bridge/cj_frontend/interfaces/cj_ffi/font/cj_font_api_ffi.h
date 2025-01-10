/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CJ_FONT_API_FFI_H
#define CJ_FONT_API_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"

using VectorUIFontAliasInfoHandle = void*;
using VectorUIFontAdjustInfoHandle = void*;
using VectorUIFontGenericInfoHandle = void*;
using VectorUIFontFallbackInfoHandle = void*;
using VectorUIFontFallbackGroupInfoHandle = void*;
using VectorStringPtr = void*;

extern "C" {
struct NativeUIFontAliasInfo {
    ExternalString name;
    uint32_t weight;
};

struct NativeUIFontAdjustInfo {
    uint32_t weight;
    uint32_t to;
};

struct NativeUIFontGenericInfo {
    ExternalString family;
    std::vector<NativeUIFontAliasInfo>* alias;
    std::vector<NativeUIFontAdjustInfo>* adjust;
};

struct NativeUIFontFallbackInfo {
    ExternalString language;
    ExternalString family;
};

struct NativeUIFontFallbackGroupInfo {
    ExternalString fontSetName;
    std::vector<NativeUIFontFallbackInfo>* fallback;
};

struct NativeUIFontConfig {
    VectorStringPtr fontDir;
    VectorUIFontGenericInfoHandle generic;
    VectorUIFontFallbackGroupInfoHandle fallbackGroups;
};

struct NativeFontInfo4Font {
    ExternalString path;
    ExternalString postScriptName;
    ExternalString fullName;
    ExternalString family;
    ExternalString subfamily;
    uint32_t weight;
    uint32_t width;
    bool italic;
    bool monoSpace;
    bool symbolic;
};

CJ_EXPORT void FFICJVectorNativeUIFontAliasInfoDelete(VectorUIFontAliasInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorNativeUIFontAliasInfoGetSize(VectorUIFontAliasInfoHandle vec);
CJ_EXPORT NativeUIFontAliasInfo FFICJVectorNativeUIFontAliasInfoGetElement(VectorUIFontAliasInfoHandle vec,
    int64_t index);

CJ_EXPORT void FFICJVectorNativeUIFontAdjustInfoDelete(VectorUIFontAdjustInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorNativeUIFontAdjustInfoGetSize(VectorUIFontAdjustInfoHandle vec);
CJ_EXPORT NativeUIFontAdjustInfo FFICJVectorNativeUIFontAdjustInfoGetElement(VectorUIFontAdjustInfoHandle vec,
    int64_t index);

CJ_EXPORT void FFICJVectorNativeUIFontGenericInfoDelete(VectorUIFontGenericInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorNativeUIFontGenericInfoGetSize(VectorUIFontGenericInfoHandle vec);
CJ_EXPORT NativeUIFontGenericInfo FFICJVectorNativeUIFontGenericInfoGetElement(VectorUIFontGenericInfoHandle vec,
    int64_t index);

CJ_EXPORT void FFICJVectorNativeUIFontFallbackInfoDelete(VectorUIFontFallbackInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorNativeUIFontFallbackInfoGetSize(VectorUIFontFallbackInfoHandle vec);
CJ_EXPORT NativeUIFontFallbackInfo FFICJVectorNativeUIFontFallbackInfoGetElement(VectorUIFontFallbackInfoHandle vec,
    int64_t index);

CJ_EXPORT void FFICJVectorNativeUIFontFallbackGroupInfoDelete(VectorUIFontFallbackGroupInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorNativeUIFontFallbackGroupInfoGetSize(VectorUIFontFallbackGroupInfoHandle vec);
CJ_EXPORT NativeUIFontFallbackGroupInfo FFICJVectorNativeUIFontFallbackGroupInfoGetElement(
    VectorUIFontFallbackGroupInfoHandle vec, int64_t index);
}

#endif // CJ_FONT_API_FFI_H