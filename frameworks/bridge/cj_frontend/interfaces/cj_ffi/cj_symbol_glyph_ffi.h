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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SYMBOL_GLYPH_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SYMBOL_GLYPH_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorUInt32Ptr = void*;

extern "C" {
struct EffectOptions {
    int32_t effectType;
    int32_t effectScope;
    int32_t effectDirection;
    int32_t fillStyle;
    bool isActive;
    int32_t triggerValue;
    bool activeExist;
    bool triggerExist;
};
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphCreate(uint32_t symbolId);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphFontColor(VectorUInt32Ptr colors);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphFontSize(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphRenderingStrategy(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphEffectStrategy(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolGlyphSymbolEffect(EffectOptions effectOptions);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SYMBOL_GLYPH_FFI_H