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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SYMBOL_SPAN_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SYMBOL_SPAN_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components/text_span/text_span_component.h"

using VectorUInt32Ptr = void*;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanCreate(uint32_t id);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanSetFontColor(VectorUInt32Ptr colors);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanSetFontSize(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanSetFontWeight(const char* weight);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanSetSymbolRenderingStrategy(int32_t strategy);
CJ_EXPORT void FfiOHOSAceFrameworkSymbolSpanSetEffectStrategy(int32_t startegy);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SYMBOL_SPAN_FFI_H