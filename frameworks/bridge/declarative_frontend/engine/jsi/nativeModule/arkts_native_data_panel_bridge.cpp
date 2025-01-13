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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_data_panel_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"

namespace {
const char* DATA_PANEL_NODEPTR_OF_UINODE = "nodePtr_";
} // namespace
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;

void ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors)
{
    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    auto themeColors = theme->GetColorsArray();
    for (const auto& item : themeColors) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        colors.emplace_back(gradient);
    }
}

bool ConvertResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, OHOS::Ace::NG::Gradient& gradient)
{
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, item, color)) {
        return false;
    }
    OHOS::Ace::NG::GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(color));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    return true;
}

bool ConvertGradientColor(const EcmaVM* vm, const Local<JSValueRef>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    if (!itemParam->IsObject(vm)) {
        return ConvertResourceColor(vm, itemParam, gradient);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        return ConvertResourceColor(vm, itemParam, gradient);
    }

    size_t colorLength = jsLinearGradient->GetGradient().size();
    if (colorLength == 0) {
        return false;
    }
    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void SetTrackShadowObject(ArkUINodeHandle nativeNode, std::vector<OHOS::Ace::NG::Gradient>& shadowColors,
    double radius, double offsetX, double offsetY)
{
    ArkUIGradientType gradient;
    gradient.length = shadowColors.size();
    auto linearLength = std::make_unique<uint32_t[]>(shadowColors.size());
    std::vector<uint32_t> allColor;
    std::vector<ArkUILengthType> allOffset;
    for (uint32_t i = 0; i < shadowColors.size(); i++) {
        linearLength[i] = shadowColors[i].GetColors().size();
        for (uint32_t j = 0; j < linearLength[i]; j++) {
            allColor.emplace_back(shadowColors[i].GetColors()[j].GetLinearColor().GetValue());
            allOffset.emplace_back(ArkUILengthType { .number = shadowColors[i].GetColors()[j].GetDimension().Value(),
                .unit = static_cast<int8_t>(shadowColors[i].GetColors()[j].GetDimension().Unit()) });
        }
    }
    gradient.color = &(*allColor.begin());
    gradient.offset = &(*allOffset.begin());
    gradient.gradientLength = linearLength.get();
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getDataPanelModifier()->setTrackShadow(nativeNode, &gradient, radius, offsetX, offsetY);
}
} // namespace

ArkUINativeModuleValue DataPanelBridge::SetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colors = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        auto colorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, colors);
        for (size_t i = 0; i < colorsArray->Length(vm); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            if (!ConvertGradientColor(vm, item, gradient)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
    }
    ArkUIGradientType gradient;
    gradient.length = shadowColors.size();
    auto linearLength = std::make_unique<uint32_t[]>(shadowColors.size());
    std::vector<uint32_t> allColor;
    std::vector<ArkUILengthType> allOffset;
    for (uint32_t i = 0; i < shadowColors.size(); i++) {
        linearLength[i] = shadowColors[i].GetColors().size();
        for (uint32_t j = 0; j < linearLength[i]; j++) {
            allColor.emplace_back(shadowColors[i].GetColors()[j].GetLinearColor().GetValue());
            allOffset.emplace_back(ArkUILengthType { .number = shadowColors[i].GetColors()[j].GetDimension().Value(),
                .unit = static_cast<int8_t>(shadowColors[i].GetColors()[j].GetDimension().Unit()) });
        }
    }
    gradient.color = &(*allColor.begin());
    gradient.offset = &(*allOffset.begin());
    gradient.gradientLength = linearLength.get();
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setValueColors(nativeNode, &gradient);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetValueColors(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetValueColors(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNull()) {
        nodeModifiers->getDataPanelModifier()->setNullTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!secondArg->IsObject(vm)) {
        nodeModifiers->getDataPanelModifier()->resetTrackShadow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto obj = secondArg->ToObject(vm);
    auto jsRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    auto jsOffsetX = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetX"));
    auto jsOffsetY = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetY"));
    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    double radius = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsRadius, radius) || NonPositive(radius)) {
        radius = theme->GetTrackShadowRadius().ConvertToVp();
    }

    double offsetX = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetX, offsetX)) {
        offsetX = theme->GetTrackShadowOffsetX().ConvertToVp();
    }

    double offsetY = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, jsOffsetY, offsetY)) {
        offsetY = theme->GetTrackShadowOffsetY().ConvertToVp();
    }

    auto colors = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "colors"));
    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    ConvertThemeColor(shadowColors);
    if (!colors.IsEmpty() && colors->IsArray(vm)) {
        shadowColors.clear();
        auto colorsArray = panda::CopyableGlobal<panda::ArrayRef>(vm, colors);
        for (size_t i = 0; i < colorsArray->Length(vm); ++i) {
            auto item = colorsArray->GetValueAt(vm, colors, i);
            OHOS::Ace::NG::Gradient gradient;
            if (!ConvertGradientColor(vm, item, gradient)) {
                shadowColors.clear();
                ConvertThemeColor(shadowColors);
                break;
            }
            shadowColors.emplace_back(gradient);
        }
    }
    SetTrackShadowObject(nativeNode, shadowColors, radius, offsetX, offsetY);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetTrackShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue DataPanelBridge::SetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool boolValue = secondArg->ToBoolean(vm)->Value();
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setCloseEffect(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetCloseEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetCloseEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
        color = theme->GetBackgroundColor();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setDataPanelTrackBackgroundColor(nativeNode, color.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetDataPanelTrackBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    RefPtr<DataPanelTheme> theme = ArkTSUtils::GetTheme<DataPanelTheme>();
    CalcDimension strokeWidth;

    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth)) {
        strokeWidth = theme->GetThickness();
    }

    if (jsValue->IsString(vm) && (jsValue->ToString(vm)->ToString(vm).empty() ||
        !StringUtils::StringToDimensionWithUnitNG(
        jsValue->ToString(vm)->ToString(vm), strokeWidth))) {
        strokeWidth = theme->GetThickness();
    }

    if (strokeWidth.IsNegative() || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = theme->GetThickness();
    }

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->setDataPanelStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int32_t>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::ResetDataPanelStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getDataPanelModifier()->resetDataPanelStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue DataPanelBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (!secondArg->IsObject(vm)) {
        DataPanelModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> globalObj(vm, secondArg);
    auto containerId = Container::CurrentId();
    DataPanelModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, globalObj = std::move(globalObj), containerId](
            DataPanelConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            CHECK_NULL_RETURN(Container::Current(), nullptr);
            CHECK_NULL_RETURN(Container::Current()->GetFrontend(), nullptr);
            auto context = NapiValueToLocalValue(Container::Current()->GetFrontend()->GetContextValue());
            auto obj = panda::ObjectRef::New(vm);
            auto valueArray = panda::ArrayRef::New(vm, config.values_.size());
            for (uint32_t i = 0; i < config.values_.size(); ++i) {
                panda::ArrayRef::SetValueAt(vm, valueArray, i, panda::NumberRef::New(vm, config.values_[i]));
            }
            obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "values"), valueArray);
            obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "maxValue"), panda::NumberRef::New(vm, config.maxValue_));
            obj->SetNativePointerFieldCount(vm, 1);
            obj->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, obj };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = globalObj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            if (!makeFunc->IsFunction(vm)) { return nullptr; }
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            JSNApi::ExecutePendingJob(vm);
            if (result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm)) { return nullptr; }
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr = resultObj->Get(vm,
                panda::StringRef::NewFromUtf8(vm, DATA_PANEL_NODEPTR_OF_UINODE));
            if (nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull()) { return nullptr; }
            auto* node = nodeptr->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
