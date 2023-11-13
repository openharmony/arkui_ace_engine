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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int SIZE_OF_FOUR = 4;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

bool ParseJsDimensionVp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
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

bool ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
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

bool ParseJsInteger(const EcmaVM* vm, const Local<JSValueRef>& value, int32_t& result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    // resouce ignore by design
    return false;
}

bool ParseJsDouble(const EcmaVM* vm, const Local<JSValueRef>& value, double& result)
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

void ParseAllBorder(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result)
{
    if (ParseJsDimensionVp(vm, args, result) && result.IsNonNegative()) {
        if (result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
    }
}

bool ParseJsDimensionNG(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, bool isSupportPercent = true)
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

bool ParseJsDimensionVpNG(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result, bool isSupportPercent = true)
{
    return ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}
} // namespace

ArkUINativeModuleValue CommonBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t color = secondArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBackgroundColor(nativeNode, color);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (leftArgs->IsUndefined() && rightArgs->IsUndefined() && topArgs->IsUndefined() && bottomArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension left;
    CalcDimension right;
    CalcDimension top;
    CalcDimension bottom;

    ParseAllBorder(vm, leftArgs, left);
    ParseAllBorder(vm, rightArgs, right);
    ParseAllBorder(vm, topArgs, top);
    ParseAllBorder(vm, bottomArgs, bottom);

    uint32_t size = SIZE_OF_FOUR;
    double values[size];
    int units[size];

    values[NUM_0] = left.Value();
    units[NUM_0] = static_cast<int>(left.Unit());
    values[NUM_1] = right.Value();
    units[NUM_1] = static_cast<int>(right.Unit());
    values[NUM_2] = top.Value();
    units[NUM_2] = static_cast<int>(top.Unit());
    values[NUM_3] = bottom.Value();
    units[NUM_3] = static_cast<int>(bottom.Unit());

    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderWidth(nativeNode, values, units, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (!topLeftArgs->IsString() && !topLeftArgs->IsNumber() && !topRightArgs->IsString() &&
        !topRightArgs->IsNumber() && !bottomLeftArgs->IsString() && !bottomLeftArgs->IsNumber() &&
        !bottomRightArgs->IsString() && !bottomLeftArgs->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;

    ParseAllBorder(vm, topLeftArgs, topLeft);
    ParseAllBorder(vm, topRightArgs, topRight);
    ParseAllBorder(vm, bottomLeftArgs, bottomLeft);
    ParseAllBorder(vm, bottomRightArgs, bottomRight);

    uint32_t size = SIZE_OF_FOUR;
    double values[size];
    int units[size];

    values[NUM_0] = topLeft.Value();
    units[NUM_0] = static_cast<int>(topLeft.Unit());
    values[NUM_1] = topRight.Value();
    units[NUM_1] = static_cast<int>(topRight.Unit());
    values[NUM_2] = bottomLeft.Value();
    units[NUM_2] = static_cast<int>(bottomLeft.Unit());
    values[NUM_3] = bottomRight.Value();
    units[NUM_3] = static_cast<int>(bottomRight.Unit());

    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderRadius(nativeNode, values, units, SIZE_OF_FOUR);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension width;
    if (jsValue->IsUndefined() || !ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetWidth(nativeNode);
    } else {
        if (LessNotEqual(width.Value(), 0.0)) {
            width.SetValue(0.0);
        }
        GetArkUIInternalNodeAPI()->GetCommonModifier().SetWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension height;

    if (jsValue->IsUndefined() || !ParseJsDimensionVpNG(vm, jsValue, height)) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        GetArkUIInternalNodeAPI()->GetCommonModifier().SetHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> sizeX = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeY = runtimeCallInfo->GetCallArgRef(NUM_2);

    CalcDimension x;
    CalcDimension y;
    // param is x and y,parse CalcDimension by utility
    if (!ParseJsDimensionVpNG(vm, sizeX, x, false) && !ParseJsDimensionVpNG(vm, sizeY, y, false)) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetPosition(nativeNode);
    }

    GetArkUIInternalNodeAPI()->GetCommonModifier().SetPosition(
        nativeNode, x.Value(), static_cast<int>(x.Unit()), y.Value(), static_cast<int>(y.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(NUM_1);

    if (!jsValue->IsArray(vm)) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetTransform(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    float matrix[matrix4Len];
    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
    for (size_t i = 0; i < transArray->Length(vm); i++) {
        Local<JSValueRef> value = transArray->GetValueAt(vm, jsValue, i);
        matrix[i] = value->ToNumber(vm)->Value();
    }
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetTransform(nativeNode, matrix, matrix4Len);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetTransform(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rifghtArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (leftArg->IsUndefined() && rifghtArg->IsUndefined() && topArg->IsUndefined() && bottomArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderColor(nativeNode);
    }

    uint32_t leftColor = leftArg->Uint32Value(vm);
    uint32_t rightColor = rifghtArg->Uint32Value(vm);
    uint32_t topColor = topArg->Uint32Value(vm);
    uint32_t bottomColor = bottomArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderColor(
        nativeNode, leftColor, rightColor, topColor, bottomColor);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto styleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto topArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto rightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto leftArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto nativeNode = firstArg->ToNativePointer(vm)->Value();
    if ((!typeArg->IsBoolean()) || (!typeArg->BooleaValue())) {
        int32_t styles[] = { static_cast<int32_t>(BorderStyle::SOLID) };
        GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderStyle(
            nativeNode, styles, (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    if (styleArg->IsInt()) {
        int32_t styles[] = { styleArg->Int32Value(vm) };
        GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderStyle(
            nativeNode, styles, (sizeof(styles) / sizeof(styles[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t styles[] = { -1, -1, -1, -1 }; // styleLeft, styleRight, styleTop, styleBottom
    if (topArg->IsInt()) {
        styles[NUM_0] = topArg->Int32Value(vm); // styleLeft
    }
    if (rightArg->IsInt()) {
        styles[NUM_1] = rightArg->Int32Value(vm); // styleRight
    }
    if (bottomArg->IsInt()) {
        styles[NUM_2] = bottomArg->Int32Value(vm); // styleTop
    }
    if (leftArg->IsInt()) {
        styles[NUM_3] = leftArg->Int32Value(vm); // styleBottom
    }
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBorderStyle(
        nativeNode, styles, (sizeof(styles) / sizeof(styles[NUM_0])));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorderStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto styleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto typeArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto colorArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto fillArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    auto nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t shadowStyle = 0;
    if (ParseJsInteger(vm, styleArg, shadowStyle)) {
        auto style = static_cast<ShadowStyle>(shadowStyle);
        auto shadow = Shadow::CreateShadow(style);
        double shadows[] = { shadow.GetBlurRadius(), shadow.GetSpreadRadius(), shadow.GetOffset().GetX(),
            shadow.GetOffset().GetY(), static_cast<double>(shadow.GetShadowType()),
            static_cast<double>(shadow.GetColor().GetValue()), static_cast<double>(shadow.GetIsFilled()) };
        GetArkUIInternalNodeAPI()->GetCommonModifier().SetBackShadow(
            nativeNode, shadows, (sizeof(shadows) / sizeof(shadows[NUM_0])));
        return panda::JSValueRef::Undefined(vm);
    }
    // BlurRadius, SpreadRadius, OffsetX, OffsetY, ShadowType, Color, IsFilled
    double shadows[] = { 0.0, 0.0, 0.0, 0.0, static_cast<double>(ShadowType::COLOR), 0.0, 0.0 };
    ParseJsDouble(vm, radiusArg, shadows[NUM_0]); // BlurRadius
    shadows[NUM_0] = (LessNotEqual(shadows[NUM_0], 0.0)) ? 0.0 : shadows[NUM_0];
    CalcDimension offsetX;
    if (ParseJsDimensionVp(vm, offsetXArg, offsetX)) {
        shadows[NUM_2] = offsetX.Value(); // OffsetX
    }
    CalcDimension offsetY;
    if (ParseJsDimensionVp(vm, offsetYArg, offsetY)) {
        shadows[NUM_3] = offsetY.Value(); // OffsetY
    }
    if (typeArg->IsInt()) {
        uint32_t shadowType = typeArg->Uint32Value(vm); // ShadowType
        shadows[NUM_4] = static_cast<double>(
            std::clamp(shadowType, static_cast<uint32_t>(ShadowType::COLOR), static_cast<uint32_t>(ShadowType::BLUR)));
    }
    Color color;
    if (ParseJsColor(vm, colorArg, color)) {
        shadows[NUM_5] = color.GetValue(); // Color
    }
    shadows[NUM_6] = static_cast<uint32_t>((fillArg->IsBoolean()) ? fillArg->BooleaValue() : false);
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetBackShadow(
        nativeNode, shadows, (sizeof(shadows) / sizeof(shadows[NUM_0])));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBackShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetHitTestBehavior(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t hitTestModeNG = secondArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetHitTestBehavior(nativeNode, hitTestModeNG);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetHitTestBehavior(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetHitTestBehavior(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetZIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value = secondArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetZIndex(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetZIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetZIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    double opacity = secondArg->ToNumber(vm)->Value();
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0;
    }
    GetArkUIInternalNodeAPI()->GetCommonModifier().SetOpacity(nativeNode, opacity);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CommonBridge::ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
