/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_ARKTS_NATIVE_PARSE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_ARKTS_NATIVE_PARSE_H

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
template <class T>
bool ParseArray(const EcmaVM *vm, const Local<JSValueRef> &arg, T *array, int32_t defaultLength,
    std::function<T(const EcmaVM *, const Local<JSValueRef> &)> getValue)
{
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(array, false);
    if (defaultLength <= 0) {
        return false;
    }
    auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, arg);
    int32_t length = handle->Length(vm);
    if (length != defaultLength) {
        return false;
    }
    for (int32_t i = 0; i < length; i++) {
        auto value = handle->GetValueAt(vm, arg, i);
        *(array + i) = getValue(vm, value);
    }
    return true;
}

uint32_t ColorAlphaAdapt(uint32_t origin);

bool ParseJsColor(const EcmaVM *vm, const Local<JSValueRef> &value, Color &result);

bool ParseStringArray(const EcmaVM *vm, const Local<JSValueRef> &arg, char **array, int32_t defaultLength);

bool ParseJsDimensionVp(const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension &result);

bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result);

bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result);

void ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);

bool ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent = true);

bool ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent = true);

bool ParseJsAlignRule(const EcmaVM *vm, const Local<JSValueRef> &arg, std::string& anchor, int8_t &direction);

bool ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit);

bool ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result);

bool ParseJsFontFamilies(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
}

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_ARKTS_NATIVE_PARSE_H
