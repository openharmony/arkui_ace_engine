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
#include <cstdint>
#include <memory>
#include "securec.h"

#include "bridge/declarative_frontend/engine/jsi/utils/arkts_native_parse.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_image_animator.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

bool ParseJsColor(const EcmaVM *vm, const Local<JSValueRef> &value, Color &result)
{
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString()) {
        return Color::ParseColorString(value->ToString(vm)->ToString(), result);
    }
    // resouce ignore by design
    return false;
}


bool ParseStringArray(const EcmaVM *vm, const Local<JSValueRef> &arg, char **array, int32_t defaultLength)
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
        if (value->IsString()) {
            *(array + i) = const_cast<char *>(value->ToString(vm)->ToString().c_str());
        } else {
            *(array + i) = nullptr;
        }
    }
    return true;
}


bool ParseJsDimensionVp(const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension &result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    // resouce ignore by design
    return false;
}

bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    // resouce ignore by design
    return false;
}

bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result)
{
    if (value->IsNumber()) {
        result = value->ToNumber(vm)->Value();
        return true;
    }
    if (value->IsString()) {
        return StringUtils::StringToDouble(value->ToString(vm)->ToString(), result);
    }
    // resouce ignore by design
    return false;
}

void ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result)
{
    if (ParseJsDimensionVp(vm, args, result) && result.IsNonNegative()) {
        if (result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
    }
}

bool ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString(vm)->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(), result, false, defaultUnit);
    }
    // resouce ignore by design
    return false;
}

bool ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent)
{
    return ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}

bool ParseJsAlignRule(const EcmaVM *vm, const Local<JSValueRef> &arg, std::string& anchor, int8_t &direction)
{
    if (arg->IsString()) {
        std::string directionString = arg->ToString(vm)->ToString();
        if (directionString.empty()) {
            return false;
        }
        size_t pos = directionString.find('|');
        if (pos == std::string::npos) {
            return false;
        }
        char *endPtr = nullptr;
        long alignValue = std::strtol(directionString.substr(0, pos).c_str(), &endPtr, 10);
        direction = static_cast<int8_t>(alignValue);
        anchor = directionString.substr(pos + 1);
        return true;
    }
    return false;
}

bool ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToCalcDimension(jsValue->ToString(vm)->ToString(), false, defaultUnit);
        return true;
    }
    return true;
}

bool ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result)
{
    return ParseJsDimension(vm, jsValue, result, DimensionUnit::FP);
}

bool ParseJsFontFamilies(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result)
{
    result.clear();
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = Framework::ConvertStrToFontFamilies(jsValue->ToString(vm)->ToString());
        return true;
    }
    return true;
}
}
