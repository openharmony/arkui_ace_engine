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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_gauge_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Color ERROR_COLOR = Color(0xFFE84026);
constexpr uint32_t NUM_0 = 0;
constexpr uint32_t NUM_1 = 1;
constexpr uint32_t NUM_2 = 2;
const char* GAUGE_NODEPTR_OF_UINODE = "nodePtr_";

void ResetColor(ArkUINodeHandle nativeNode)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        nodeModifiers->getGaugeModifier()->resetGradientColors(nativeNode);
    } else {
        nodeModifiers->getGaugeModifier()->resetColors(nativeNode);
    }
}
}

void SortColorStopOffset(std::vector<NG::ColorStopArray>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}

void ConvertResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, std::vector<NG::ColorStopArray>& colors)
{
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, item, color)) {
        color = ERROR_COLOR;
    }
    NG::ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    colors.emplace_back(colorStopArray);
}

void ConvertGradientColor(const EcmaVM* vm, const Local<JSValueRef>& itemParam, std::vector<NG::ColorStopArray>& colors,
    NG::GaugeType& type, bool& isGradientColor)
{
    if (!itemParam->IsObject(vm)) {
        type = NG::GaugeType::TYPE_CIRCULAR_MONOCHROME;
        return ConvertResourceColor(vm, itemParam, colors);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        type = NG::GaugeType::TYPE_CIRCULAR_MONOCHROME;
        return ConvertResourceColor(vm, itemParam, colors);
    }

    type = NG::GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT;
    if (jsLinearGradient->GetGradient().size() == 0) {
        NG::ColorStopArray colorStopArray;
        colorStopArray.emplace_back(std::make_pair(ERROR_COLOR, Dimension(0.0)));
        colors.emplace_back(colorStopArray);
    } else {
        isGradientColor = true;
        colors.emplace_back(jsLinearGradient->GetGradient());
    }
}

void SetGradientColorsObject(const EcmaVM* vm, const Local<JSValueRef>& info, std::vector<NG::ColorStopArray>& colors,
    std::vector<float>& weights, NG::GaugeType& type, ArkUINodeHandle nativeNode)
{
    ArkUIGradientType gradient;
    bool isGradientColor = false;
    ConvertGradientColor(vm, info, colors, type, isGradientColor);
    auto colorStruct = std::make_unique<uint32_t[]>(colors[0].size());
    auto colorResourceIdStruct = std::make_unique<uint32_t[]>(colors[0].size());
    auto offsetStruct = std::make_unique<ArkUILengthType[]>(colors[0].size());
    std::vector<uint32_t> linearLengths { colors[0].size() };
    for (uint32_t i = 0; i < colors[0].size(); i++) {
        colorStruct[i] = colors[0][i].first.GetValue();
        colorResourceIdStruct[i] = colors[0][i].first.GetResourceId();
        offsetStruct[i].number = colors[0][i].second.Value();
        offsetStruct[i].unit = static_cast<int8_t>(colors[0][i].second.Unit());
    }
    gradient.color = colorStruct.get();
    gradient.colorResourceId = colorResourceIdStruct.get();
    gradient.offset = offsetStruct.get();
    gradient.gradientLength = &(*linearLengths.begin());
    gradient.weight = nullptr;
    gradient.type = static_cast<uint32_t>(type);
    gradient.length = 1;
    gradient.isGradientColor = isGradientColor;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getGaugeModifier()->setGradientColors(nativeNode, &gradient, 0);
}

struct GradientParams {
    std::vector<float>& weights;
    std::vector<NG::ColorStopArray>& colors;
    bool& isGradientColor;
};

void SetGradientColorsArray(const EcmaVM* vm, const Local<JSValueRef>& info, ArkUINodeHandle nativeNode,
    NG::GaugeType& type, const GradientParams& params)
{
    ArkUIGradientType gradient;
    uint32_t totalLength = 0;
    std::vector<uint32_t> linearLengths(params.colors.size(), 0);
    for (uint32_t i = 0; i < params.colors.size(); i++) {
        linearLengths[i] = params.colors[i].size();
        totalLength += params.colors[i].size();
    }
    auto colorStruct = std::make_unique<uint32_t[]>(totalLength);
    auto colorResourceIdStruct = std::make_unique<uint32_t[]>(totalLength);
    auto offsetStruct = std::make_unique<ArkUILengthType[]>(totalLength);
    int32_t pos = 0;
    for (uint32_t i = 0; i < params.colors.size(); i++) {
        for (uint32_t j = 0; j < params.colors[i].size(); j++, pos++) {
            colorStruct[pos] = params.colors[i][j].first.GetValue();
            colorResourceIdStruct[pos] = params.colors[i][j].first.GetResourceId();
            offsetStruct[pos].number = params.colors[i][j].second.Value();
            offsetStruct[pos].unit = static_cast<int8_t>(params.colors[i][j].second.Unit());
        }
    }
    gradient.color = colorStruct.get();
    gradient.colorResourceId = colorResourceIdStruct.get();
    gradient.offset = offsetStruct.get();
    gradient.gradientLength = &(*linearLengths.begin());
    gradient.weight = &(*params.weights.begin());
    gradient.type = static_cast<uint32_t>(type);
    gradient.length = params.colors.size();
    gradient.isGradientColor = params.isGradientColor;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getGaugeModifier()->setGradientColors(nativeNode, &gradient, params.weights.size());
}

void SetGradientColors(const EcmaVM* vm, const Local<JSValueRef>& info, ArkUINodeHandle nativeNode)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    if (info->IsNull() || info->IsUndefined()) {
        nodeModifiers->getGaugeModifier()->resetGradientColors(nativeNode);
        return;
    }
    NG::GaugeType type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    std::vector<NG::ColorStopArray> colors;
    std::vector<float> weights;
    if (!info->IsArray(vm)) {
        SetGradientColorsObject(vm, info, colors, weights, type, nativeNode);
        return;
    }
    auto jsColorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, info);
    if (jsColorsArray.IsEmpty() || jsColorsArray->IsUndefined()
        || jsColorsArray->IsNull() || jsColorsArray->Length(vm) == 0) {
        nodeModifiers->getGaugeModifier()->resetGradientColors(nativeNode);
        return;
    }
    bool isGradientColor = false;
    for (size_t i = 0; i < jsColorsArray->Length(vm); ++i) {
        if (static_cast<int32_t>(i) >= NG::COLORS_MAX_COUNT) {
            break;
        }
        auto jsValue = jsColorsArray->GetValueAt(vm, info, i);
        if (!jsValue->IsArray(vm)) {
            continue;
        }
        auto tempColors = panda::CopyableGlobal<panda::ArrayRef>(vm, jsValue);
        if (tempColors.IsEmpty() || tempColors->IsUndefined() || tempColors->IsNull()) {
            continue;
        }
        // Get weight
        float weight = tempColors->GetValueAt(vm, jsValue, 1)->ToNumber(vm)->Value();
        if (NonPositive(weight)) {
            continue;
        }
        weights.push_back(weight);
        // Get color
        auto jsColorValue = tempColors->GetValueAt(vm, jsValue, 0);
        ConvertGradientColor(vm, jsColorValue, colors, type, isGradientColor);
    }
    type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    SortColorStopOffset(colors);
    SetGradientColorsArray(vm, info, nativeNode, type, { weights, colors, isGradientColor });
}

ArkUINativeModuleValue GaugeBridge::SetColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> jsArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SetGradientColors(vm, jsArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!jsArg->IsArray(vm)) {
        ResetColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsColor = panda::CopyableGlobal<panda::ArrayRef>(vm, jsArg);
    if (jsColor.IsEmpty() || jsColor->IsUndefined() || jsColor->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    size_t length = jsColor->Length(vm);
    auto colors = std::make_unique<uint32_t[]>(length);
    auto weights = std::make_unique<float[]>(length);

    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    for (size_t i = 0; i < length; i++) {
        auto jsValue = jsColor->GetValueAt(vm, jsArg, i);
        if (!jsValue->IsArray(vm)) {
            ResetColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, jsValue);
        if (handle.IsEmpty() || handle->IsUndefined() || handle->IsNull()) {
            return panda::JSValueRef::Undefined(vm);
        }
        float weight = handle->GetValueAt(vm, jsValue, 1)->ToNumber(vm)->Value();
        Color selectedColor;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, handle->GetValueAt(vm, jsValue, 1), selectedColor)) {
            selectedColor = ERROR_COLOR;
        }
        colors[i] = selectedColor.GetValue();
        if (weight > 0) {
            weights[i] = weight;
        } else {
            weights[i] = 0.0f;
        }
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->setColors(nativeNode, colors.get(), weights.get(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ResetColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        nodeModifiers->getGaugeModifier()->resetGaugeValue(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float value = static_cast<float>(secondArg->ToNumber(vm)->Value());
    nodeModifiers->getGaugeModifier()->setGaugeValue(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->resetGaugeValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        nodeModifiers->getGaugeModifier()->resetGaugeStartAngle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float value = static_cast<float>(secondArg->ToNumber(vm)->Value());
    nodeModifiers->getGaugeModifier()->setGaugeStartAngle(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->resetGaugeStartAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        nodeModifiers->getGaugeModifier()->resetGaugeEndAngle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    float value = static_cast<float>(secondArg->ToNumber(vm)->Value());
    nodeModifiers->getGaugeModifier()->setGaugeEndAngle(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->resetGaugeEndAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension strokeWidth;
    RefPtr<ResourceObject> strokeWidthResObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth, strokeWidthResObj) ||
        strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = CalcDimension(0);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto strokeWidthRawPtr = AceType::RawPtr(strokeWidthResObj);
    nodeModifiers->getGaugeModifier()->setGaugeStrokeWidthPtr(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()), strokeWidthRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->resetGaugeStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(2);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(3);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(4);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (jsValue->IsNull()) {
        nodeModifiers->getGaugeModifier()->setShadowOptions(nativeNode, DEFAULT_GAUGE_SHADOW_RADIUS,
            DEFAULT_GAUGE_SHADOW_OFFSETX, DEFAULT_GAUGE_SHADOW_OFFSETY, false);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!jsValue->IsObject(vm)) {
        nodeModifiers->getGaugeModifier()->resetShadowOptions(nativeNode);
        nodeModifiers->getGaugeModifier()->setIsShowIndicator(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUIGaugeShadowOptions shadowOptions = { .radius = 0.0, .offsetX = 0.0, .offsetY = 0.0, .isShadowVisible = true };
    ArkUIShadowOptionsResource shadowOptionsResource;
    RefPtr<ResourceObject> radiusResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, radiusArg, shadowOptions.radius, radiusResObj)) {
        shadowOptions.radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }
    if (NonPositive(shadowOptions.radius)) {
        shadowOptions.radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }
    RefPtr<ResourceObject> offsetXResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetXArg, shadowOptions.offsetX, offsetXResObj)) {
        shadowOptions.offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;
    }
    RefPtr<ResourceObject> offsetYResObj;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetYArg, shadowOptions.offsetY, offsetYResObj)) {
        shadowOptions.offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;
    }
    shadowOptionsResource.radiusRawPtr = AceType::RawPtr(radiusResObj);
    shadowOptionsResource.offsetXRawPtr = AceType::RawPtr(offsetXResObj);
    shadowOptionsResource.offsetYRawPtr = AceType::RawPtr(offsetYResObj);

    nodeModifiers->getGaugeModifier()->setShadowOptionsPtr(nativeNode, shadowOptions, shadowOptionsResource);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->resetShadowOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto iconArg = runtimeCallInfo->GetCallArgRef(1);
    auto spaceArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getGaugeModifier()->setIsShowIndicator(nativeNode, true);
    std::string iconPath;
    RefPtr<ResourceObject> iconPathResObj;
    if (ArkTSUtils::ParseJsMedia(vm, iconArg, iconPath, iconPathResObj)) {
        std::string bundleName;
        std::string moduleName;
        auto iconPathRawPtr = AceType::RawPtr(iconPathResObj);
        ArkTSUtils::GetJsMediaBundleInfo(vm, iconArg, bundleName, moduleName);
        nodeModifiers->getGaugeModifier()->setIndicatorIconPathPtr(
            nativeNode, iconPath.c_str(), bundleName.c_str(), moduleName.c_str(), iconPathRawPtr);
    } else {
        nodeModifiers->getGaugeModifier()->resetIndicatorIconPath(nativeNode);
    }
    CalcDimension space;
    RefPtr<ResourceObject> spaceResObj;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, spaceArg, space, false)) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    if (space.IsNegative()) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    auto spaceRawPtr = AceType::RawPtr(spaceResObj);
    nodeModifiers->getGaugeModifier()->setIndicatorSpacePtr(
        nativeNode, space.CalcValue().c_str(), space.Value(), static_cast<int32_t>(space.Unit()), spaceRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto valueArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (valueArg->IsNull()) {
        nodeModifiers->getGaugeModifier()->setIsShowIndicator(nativeNode, false);
    } else if (valueArg->IsUndefined() || (!valueArg->IsObject(vm))) {
        nodeModifiers->getGaugeModifier()->resetIndicatorIconPath(nativeNode);
        nodeModifiers->getGaugeModifier()->resetIndicatorSpace(nativeNode);
        nodeModifiers->getGaugeModifier()->setIsShowIndicator(nativeNode, true);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        GaugeModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    GaugeModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId](
            GaugeConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            const char* keyOfGauge[] = { "value", "min", "max" };
            Local<JSValueRef> valuesOfGauge[] = { panda::NumberRef::New(vm, config.value_),
                panda::NumberRef::New(vm, config.min_), panda::NumberRef::New(vm, config.max_) };
            auto gauge = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keyOfGauge),
                keyOfGauge, valuesOfGauge);
            gauge->SetNativePointerFieldCount(vm, 1);
            gauge->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, gauge };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, GAUGE_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugePrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t sensitive = false;
    if (secondArg->IsBoolean()) {
        sensitive = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->setPrivacySensitive(nativeNode, sensitive);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugePrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getCommonModifier()->resetPrivacySensitive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
