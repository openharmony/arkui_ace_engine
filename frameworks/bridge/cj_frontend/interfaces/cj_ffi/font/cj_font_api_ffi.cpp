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

#include "cj_font_api_ffi.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
// UIFontAliasInfo
void FFICJVectorNativeUIFontAliasInfoDelete(VectorUIFontAliasInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAliasInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorNativeUIFontAliasInfoGetSize(VectorUIFontAliasInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAliasInfo>*>(vec);
    return actualVec->size();
}

NativeUIFontAliasInfo FFICJVectorNativeUIFontAliasInfoGetElement(VectorUIFontAliasInfoHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAliasInfo>*>(vec);
    return (*actualVec)[index];
}

// UIFontAdjustInfo
void FFICJVectorNativeUIFontAdjustInfoDelete(VectorUIFontAdjustInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAdjustInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorNativeUIFontAdjustInfoGetSize(VectorUIFontAdjustInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAdjustInfo>*>(vec);
    return actualVec->size();
}

NativeUIFontAdjustInfo FFICJVectorNativeUIFontAdjustInfoGetElement(VectorUIFontAdjustInfoHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontAdjustInfo>*>(vec);
    return (*actualVec)[index];
}

// UIFontGenericInfo
void FFICJVectorNativeUIFontGenericInfoDelete(VectorUIFontGenericInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontGenericInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorNativeUIFontGenericInfoGetSize(VectorUIFontGenericInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontGenericInfo>*>(vec);
    return actualVec->size();
}

NativeUIFontGenericInfo FFICJVectorNativeUIFontGenericInfoGetElement(VectorUIFontGenericInfoHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontGenericInfo>*>(vec);
    return (*actualVec)[index];
}

// UIFontFallbackInfo
void FFICJVectorNativeUIFontFallbackInfoDelete(VectorUIFontFallbackInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorNativeUIFontFallbackInfoGetSize(VectorUIFontFallbackInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackInfo>*>(vec);
    return actualVec->size();
}

NativeUIFontFallbackInfo FFICJVectorNativeUIFontFallbackInfoGetElement(VectorUIFontFallbackInfoHandle vec,
    int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackInfo>*>(vec);
    return (*actualVec)[index];
}

// UIFontFallbackGroupInfo
void FFICJVectorNativeUIFontFallbackGroupInfoDelete(VectorUIFontFallbackGroupInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackGroupInfo>*>(vec);
    delete actualVec;
}

int64_t FFICJVectorNativeUIFontFallbackGroupInfoGetSize(VectorUIFontFallbackGroupInfoHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackGroupInfo>*>(vec);
    return actualVec->size();
}

NativeUIFontFallbackGroupInfo FFICJVectorNativeUIFontFallbackGroupInfoGetElement(
    VectorUIFontFallbackGroupInfoHandle vec, int64_t index)
{
    auto actualVec = reinterpret_cast<std::vector<NativeUIFontFallbackGroupInfo>*>(vec);
    return (*actualVec)[index];
}
}