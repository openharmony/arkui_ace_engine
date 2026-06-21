/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "frameworks/core/components_ng/pattern/progress/bridge/arkts_native_progress_bridge.h"

#include <optional>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/text/text_theme.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_progress_theme.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t ARG_NUM_NATIVE_NODE = 0;
constexpr int32_t ARG_NUM_VALUE = 1;
constexpr int32_t ARG_COLOR_INDEX_VALUE = 1;
constexpr int32_t ARG_NUM_STYLE_STROKE_WIDTH = 1;
constexpr int32_t ARG_NUM_STYLE_BORDER_WIDTH = 6;
constexpr int32_t ARG_NUM_STYLE_PROGRESS_STATUS = 16;
constexpr int32_t ARG_NUM_STYLE_FONT_STYLE = 11;
constexpr int32_t ARG_NUM_STYLE_SCALE_COUNT = 2;
constexpr int32_t ARG_NUM_STYLE_SCALE_WIDTH = 3;
constexpr int32_t ARG_NUM_STYLE_FONT_SIZE = 8;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT = 4;
constexpr int32_t ARG_NUM_STYLE_BORDER_COLOR = 5;
constexpr int32_t ARG_NUM_STYLE_CONTENT = 7;
constexpr int32_t ARG_NUM_STYLE_FONT_WEIGHT = 9;
constexpr int32_t ARG_NUM_STYLE_FONT_COLOR = 12;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SCAN_EFFECT = 13;
constexpr int32_t ARG_NUM_STYLE_SHADOW = 15;
constexpr int32_t ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAGE = 14;
constexpr int32_t ARG_NUM_STYLE_FONT_FAMILY = 10;
constexpr int32_t ARG_NUM_STYLE_STROKE_RADIUS = 17;
constexpr int32_t ARG_NUM_STYLE_BORDER_RADIUS = 18;
constexpr int32_t ARG_SECOND = 2;
constexpr int32_t ARG_THIRD = 3;
const char* PROGRESS_NODEPTR_OF_UINODE = "nodePtr_";
constexpr double DEFAULT_PROGRESS_VALUE = 0;
constexpr double DEFAULT_STROKE_WIDTH = 4;
constexpr double DEFAULT_BORDER_WIDTH = 1;
constexpr double DEFAULT_SCALE_WIDTH = 2;
constexpr double DEFAULT_STROKE_RADIUS = 0;
constexpr int32_t DEFAULT_SCALE_COUNT = 120;
constexpr Color DEFAULT_BORDER_COLOR = Color(0x33006cde);
constexpr double DEFAULT_CAPSULE_FONT_SIZE = 12;
constexpr NG::ProgressStatus DEFAULT_PROGRESS_STATUS = NG::ProgressStatus::PROGRESSING;
constexpr DimensionUnit DEFAULT_CAPSULE_FONT_UNIT = DimensionUnit::FP;
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<NG::ProgressStatus> STATUS_STYLES = { NG::ProgressStatus::PROGRESSING, NG::ProgressStatus::LOADING };
constexpr double DEFAULT_BORDER_RADIUS = 0;
constexpr double DEFAULT_TOTAL_VALUE = 100.0;
ProgressType g_progressType = ProgressType::LINEAR;

namespace {

FrameNode* GetProgressFrameNode(ArkUINodeHandle nativeNode)
{
    return nativeNode ?
        reinterpret_cast<FrameNode*>(nativeNode) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

bool ConvertProgressRResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, OHOS::Ace::NG::Gradient& gradient)
{
    Color color;
    if (!ArkTSUtils::ParseJsColor(vm, item, color)) {
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

bool ConvertProgressResourceColor(
    const EcmaVM* vm, const Local<JSValueRef>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    if (!itemParam->IsObject(vm)) {
        return ConvertProgressRResourceColor(vm, itemParam, gradient);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        return ConvertProgressRResourceColor(vm, itemParam, gradient);
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
} // namespace

NodeInfo MakeProgressNodeInfo(ArkUINodeHandle nativeNode)
{
    auto* frameNode = GetProgressFrameNode(nativeNode);
    if (!frameNode) {
        return ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    }
    return { frameNode->GetTag(), frameNode->GetLocalColorMode(), frameNode->GetForceDarkAllowed() };
}

RefPtr<ResourceObject> CloneResourceObject(const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(resObj, nullptr);
    auto clonedResObj = AceType::MakeRefPtr<ResourceObject>(
        resObj->GetId(), resObj->GetType(), resObj->GetParams(), resObj->GetBundleName(),
        resObj->GetModuleName(), resObj->GetInstanceId());
    clonedResObj->SetColor(resObj->GetColor());
    clonedResObj->SetNodeTag(resObj->GetNodeTag());
    clonedResObj->SetIsResource(resObj->IsResource());
    clonedResObj->SetColorMode(resObj->GetColorMode());
    clonedResObj->SetHasDarkRes(resObj->HasDarkResource());
    return clonedResObj;
}

ArkUINativeModuleValue ProgressBridge::ResetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_VALUE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        ArkUI_Float32 value = secondArg->ToNumber(vm)->Value();
        if (std::isnan(value)) {
            if (!isJsView) {
                nodeModifiers->getProgressModifier()->setProgressValue(nativeNode, DEFAULT_PROGRESS_VALUE);
            }
            return panda::JSValueRef::Undefined(vm);
        }
        if (value < DEFAULT_PROGRESS_VALUE) {
            value = DEFAULT_PROGRESS_VALUE;
        }
        nodeModifiers->getProgressModifier()->setProgressValue(nativeNode, value);
    } else if (!isJsView) {
        nodeModifiers->getProgressModifier()->resetProgressValue(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetGradientColorToModifier(ArkUINodeHandle& nativeNode, NG::Gradient& gradient, bool isNeedSetResObj)
{
    std::vector<uint32_t> colorValues;
    std::vector<ArkUILengthType> offsetValues;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    auto progressModifier = nodeModifiers->getProgressModifier();
    CHECK_NULL_VOID(progressModifier);
    auto colorlength = gradient.GetColors().size();
    if (colorlength <= 0) {
        progressModifier->resetProgressColor(nativeNode);
        return;
    }
    if (isNeedSetResObj && progressModifier->setProgressGradientColorWithResourceObj) {
        progressModifier->setProgressGradientColorWithResourceObj(nativeNode, reinterpret_cast<void*>(&gradient));
        return;
    }
    for (int32_t i = 0; i < static_cast<int32_t>(colorlength); i++) {
        colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
        offsetValues.push_back(ArkUILengthType { .number = gradient.GetColors()[i].GetDimension().Value(),
            .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
    }
    ArkUIGradientType gradientObj;
    gradientObj.color = colorValues.data();
    gradientObj.offset = offsetValues.data();
    progressModifier->setProgressGradientColor(nativeNode, &gradientObj, colorlength);
}

void ParseGradientOffset(NG::Gradient& gradient, RefPtr<ResourceObject>& offsetResObj, int32_t& indx)
{
    CHECK_NULL_VOID(offsetResObj);
    auto&& updateFunc = [indx](const RefPtr<ResourceObject>& offsetResObj, NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = static_cast<int32_t>(colorVector.size());
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                CalcDimension offset;
                ResourceParseUtils::ParseResDimensionVp(offsetResObj, offset);
                gradColor.SetDimension(offset);
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "LinearGradient.gradient.offset" + std::to_string(indx);
    gradient.AddResource(key, offsetResObj, std::move(updateFunc));
}

void ParseGradientColor(
    NG::Gradient& gradient, RefPtr<ResourceObject>& colorResObj, Color& color, int32_t indx, const NodeInfo& nodeInfo)
{
    ArkTSUtils::CompleteResourceObjectFromColor(colorResObj, color, true, nodeInfo);
    CHECK_NULL_VOID(colorResObj);
    auto&& updateFunc = [indx](const RefPtr<ResourceObject>& colorResObj, NG::Gradient& gradient) {
        std::vector<NG::GradientColor> colorVector = gradient.GetColors();
        int32_t colorLength = static_cast<int32_t>(colorVector.size());
        gradient.ClearColors();
        for (int32_t index = 0; index < colorLength; index++) {
            NG::GradientColor gradColor = colorVector[index];
            if (index == indx) {
                Color color;
                ResourceParseUtils::ParseResColor(colorResObj, color);
                gradColor.SetLinearColor(LinearColor(color));
            }
            gradient.AddColor(gradColor);
        }
    };
    std::string key = "LinearGradient.gradient.color" + std::to_string(indx);
    gradient.AddResource(key, colorResObj, std::move(updateFunc));
}

bool ConvertGradientColor(const Local<JSValueRef>& colorArg, NG::Gradient& gradient, const EcmaVM* vm,
    const NodeInfo& nodeInfo)
{
    if (colorArg->IsNull() || colorArg->IsUndefined() || !colorArg->IsObject(vm)) {
        return false;
    }

    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(colorArg->ToObject(vm)->GetNativePointerField(vm, 0));

    if (!jsLinearGradient || jsLinearGradient->GetGradient().empty()) {
        return false;
    }
    auto jsGradient = jsLinearGradient->GetGradient();
    auto jsGradientResObj = jsLinearGradient->GetGradientResObj();

    size_t size = jsGradient.size();
    for (size_t i = 0; i < size; i++) {
        NG::GradientColor gradientColor;
        Color color = jsGradient.at(i).first;
        CalcDimension offset = jsGradient.at(i).second;
        if (SystemProperties::ConfigChangePerform()) {
            int32_t indx = static_cast<int32_t>(i);
            RefPtr<ResourceObject> colorResObj;
            if (i < jsGradientResObj.size()) {
                colorResObj = jsGradientResObj.at(i).first;
            }
            if (colorResObj) {
                ResourceParseUtils::ParseResColor(colorResObj, color);
                if (!colorResObj->IsResource()) {
                    colorResObj = nullptr;
                } else {
                    colorResObj = CloneResourceObject(colorResObj);
                }
            }
            ParseGradientColor(gradient, colorResObj, color, indx, nodeInfo);
            if (jsGradientResObj.at(i).second) {
                ResourceParseUtils::ParseResDimensionVp(jsGradientResObj.at(i).second, offset);
                ParseGradientOffset(gradient, jsGradientResObj.at(i).second, indx);
            }
        }
        if (Negative(offset.ConvertToVp())) {
            offset = Dimension(0.0, DimensionUnit::VP);
        }

        if (GreatNotEqual(offset.ConvertToVp(), 1.0)) {
            offset = Dimension(1.0, DimensionUnit::VP);
        }
        gradientColor.SetLinearColor(LinearColor(color));
        gradientColor.SetDimension(offset);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void GetBeginColorAndEndOffset(
    Color& beginColor, Color& endColor, const Color& color, const RefPtr<ProgressTheme>& theme)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        endColor = (g_progressType == ProgressType::RING || g_progressType == ProgressType::SCALE)
            ? theme->GetRingProgressEndSideColor() : color;
        beginColor = (g_progressType == ProgressType::RING || g_progressType == ProgressType::SCALE)
            ? theme->GetRingProgressBeginSideColor() : color;
    } else {
        endColor = theme->GetRingProgressEndSideColor();
        beginColor = theme->GetRingProgressBeginSideColor();
    }
}

void ParseJSColor(
    Local<JSValueRef>& colorArg, const EcmaVM* vm, ArkUINodeHandle& nativeNode, const NodeInfo& nodeInfo)
{
    Color color;
    OHOS::Ace::NG::Gradient gradient;
    bool gradientColorByUser = true;
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    if (SystemProperties::ConfigChangePerform()) {
        nodeModifiers->getProgressModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(JsProgressResourceType::COLOR), nullptr);
    }
    if (ConvertGradientColor(colorArg, gradient, vm, nodeInfo)) {
        SetGradientColorToModifier(nativeNode, gradient, true);
    } else {
        RefPtr<ResourceObject> resObj;
        Color endColor;
        Color beginColor;
        if (colorArg->IsNull() || colorArg->IsUndefined() || !ArkTSUtils::ParseJsColor(vm, colorArg, color, resObj)) {
            color = (g_progressType == ProgressType::CAPSULE) ? theme->GetCapsuleSelectColor()
                : theme->GetTrackSelectedColor();
            GetBeginColorAndEndOffset(beginColor, endColor, color, theme);
            gradientColorByUser = false;
        } else {
            endColor = color;
            beginColor = color;
        }
        if (SystemProperties::ConfigChangePerform()) {
            nodeModifiers->getProgressModifier()->createWithResourceObj(nativeNode, static_cast<int32_t>(
                JsProgressResourceType::COLOR), reinterpret_cast<void*>(AceType::RawPtr(resObj)));
        }

        NG::GradientColor endSideColor;
        NG::GradientColor beginSideColor;
        endSideColor.SetLinearColor(LinearColor(endColor));
        endSideColor.SetDimension(Dimension(0.0f));
        beginSideColor.SetLinearColor(LinearColor(beginColor));
        beginSideColor.SetDimension(Dimension(1.0f));
        gradient.AddColor(endSideColor);
        gradient.AddColor(beginSideColor);

        SetGradientColorToModifier(nativeNode, gradient, false);
        nodeModifiers->getProgressModifier()->setProgressColorJS(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        nodeModifiers->getProgressModifier()->setGradientColorByUser(nativeNode, gradientColorByUser);
    }
}

ArkUINativeModuleValue ProgressBridge::SetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(ARG_COLOR_INDEX_VALUE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nativeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    Color color;
    OHOS::Ace::NG::Gradient gradient;
    RefPtr<ResourceObject> colorResObj;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto nodeInfo = MakeProgressNodeInfo(nativeNode);
    if (ArkTSUtils::IsJsView(vm, nativeArg)) {
        ParseJSColor(colorArg, vm, nativeNode, nodeInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        nodeModifiers->getProgressModifier()->setProgressColorPtr(nativeNode, color.GetValue(), colorRawPtr);
    } else if (ConvertProgressResourceColor(vm, colorArg, gradient)) {
        ArkUIGradientType gradientObj;
        auto colorlength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        if (colorlength <= 0) {
            nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        for (int32_t i = 0; i < static_cast<int32_t>(colorlength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(ArkUILengthType { .number = gradient.GetColors()[i].GetDimension().Value(),
                .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }

        gradientObj.color = &(*colorValues.begin());
        gradientObj.offset = &(*offsetValues.begin());
        nodeModifiers->getProgressModifier()->setProgressGradientColor(nativeNode, &gradientObj, colorlength);
    } else {
        nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseStrokeWidth(const EcmaVM* vm,
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index, bool isJsView)
{
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension strokeWidth = CalcDimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP);
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    if ((strokeWidthArg->IsNull() || strokeWidthArg->IsUndefined()) && isJsView) {
        strokeWidth = theme->GetTrackThickness();
    } else if (strokeWidthArg->IsString(vm)) {
        const std::string& value = strokeWidthArg->ToString(vm)->ToString(vm);
        strokeWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_STROKE_WIDTH);
    } else {
        RefPtr<ResourceObject> resObj;
        ArkTSUtils::ParseJsDimension(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP, resObj, false);
        if (resObj) {
            progressStyle.styleResource.strokeWidthRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
    }

    if ((LessOrEqual(strokeWidth.Value(), 0.0f) || strokeWidth.Unit() == DimensionUnit::PERCENT) && theme) {
        strokeWidth = theme->GetTrackThickness();
    }
    if (strokeWidth.IsNegative()) {
        progressStyle.strokeWidthValue = DEFAULT_STROKE_WIDTH;
        progressStyle.strokeWidthUnit = static_cast<uint8_t>(DimensionUnit::VP);
    } else {
        progressStyle.strokeWidthValue = strokeWidth.Value();
        progressStyle.strokeWidthUnit = static_cast<uint8_t>(strokeWidth.Unit());
    }
}

void ParseBorderWidth(const EcmaVM* vm,
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index, bool isJsView)
{
    Local<JSValueRef> borderWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension borderWidth = CalcDimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP);
    RefPtr<ResourceObject> resObj;
    if (isJsView) {
        auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(theme);
        bool state = ArkTSUtils::ParseJsDimension(vm, borderWidthArg, borderWidth, DimensionUnit::VP, resObj, false);
        if (!state || LessNotEqual(borderWidth.Value(), 0.0) || borderWidth.Unit() == DimensionUnit::PERCENT) {
            borderWidth = theme->GetBorderWidth();
        }
        progressStyle.borderWidthValue = borderWidth.Value();
        progressStyle.borderWidthUnit = static_cast<uint8_t>(borderWidth.Unit());
        if (resObj) {
            progressStyle.styleResource.borderWidthRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
        return;
    }

    if (borderWidthArg->IsString(vm)) {
        const std::string& value = borderWidthArg->ToString(vm)->ToString(vm);
        borderWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_BORDER_WIDTH);
    } else {
        ArkTSUtils::ParseJsDimension(vm, borderWidthArg, borderWidth, DimensionUnit::VP, resObj, false);
        if (resObj) {
            progressStyle.styleResource.borderWidthRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
    }
    if (borderWidth.IsNegative()) {
        progressStyle.borderWidthValue = DEFAULT_BORDER_WIDTH;
        progressStyle.borderWidthUnit = static_cast<uint8_t>(DimensionUnit::VP);
    } else {
        progressStyle.borderWidthValue = borderWidth.Value();
        progressStyle.borderWidthUnit = static_cast<uint8_t>(borderWidth.Unit());
    }
}

void ParseScaleCount(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> scaleCountArg = runtimeCallInfo->GetCallArgRef(index);
    int32_t scaleCount = DEFAULT_SCALE_COUNT;
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    if (theme) {
        scaleCount = theme->GetScaleNumber();
    }

    if (scaleCountArg->IsNull() || !ArkTSUtils::ParseJsInteger(vm, scaleCountArg, scaleCount)) {
        scaleCount = DEFAULT_SCALE_COUNT;
    }
    if (scaleCount > 1) {
        progressStyle.scaleCount = scaleCount;
    } else if (theme) {
        progressStyle.scaleCount = theme->GetScaleNumber();
    }
}

void ParseProgressStatus(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> ProgressStatusArg = runtimeCallInfo->GetCallArgRef(index);
    NG::ProgressStatus progressStatus = DEFAULT_PROGRESS_STATUS;
    std::string statusStr;
    if (ProgressStatusArg->IsUndefined() || ProgressStatusArg->IsNull() ||
        !ArkTSUtils::ParseJsString(vm, ProgressStatusArg, statusStr)) {
        progressStatus = DEFAULT_PROGRESS_STATUS;
    } else {
        if (statusStr.compare("LOADING") == 0) {
            progressStatus = NG::ProgressStatus::LOADING;
        } else {
            progressStatus = NG::ProgressStatus::PROGRESSING;
        }
    }
    progressStyle.status = static_cast<int8_t>(progressStatus);
}

void ParseScaleWidth(const EcmaVM* vm,
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index, bool isJsView)
{
    Local<JSValueRef> scaleWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension scaleWidth = CalcDimension(DEFAULT_SCALE_WIDTH, DimensionUnit::VP);
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);

    if (scaleWidthArg->IsString(vm)) {
        const std::string& value = scaleWidthArg->ToString(vm)->ToString(vm);
        scaleWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_SCALE_WIDTH);
    } else {
        RefPtr<ResourceObject> resObj;
        bool state = ArkTSUtils::ParseJsDimension(vm, scaleWidthArg, scaleWidth, DimensionUnit::VP, resObj, false);
        if (!state && isJsView) {
            scaleWidth = theme->GetScaleWidth();
        }
        if (resObj) {
            progressStyle.styleResource.scaleWidthRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
    }

    if (isJsView && (LessOrEqual(scaleWidth.Value(), 0.0f) ||
        scaleWidth.Unit() == DimensionUnit::PERCENT || scaleWidth.Value() > progressStyle.strokeWidthValue)) {
        scaleWidth = theme->GetScaleWidth();
    }

    if (scaleWidth.IsNegative() && !isJsView) {
        scaleWidth = CalcDimension(DEFAULT_SCALE_WIDTH, DimensionUnit::VP);
    }

    progressStyle.scaleWidthValue = scaleWidth.Value();
    progressStyle.scaleWidthUnit = static_cast<uint8_t>(scaleWidth.Unit());
}

void ParseStrokeRadius(const EcmaVM* vm,
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index, bool isJsView)
{
    Local<JSValueRef> strokeRadiusArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension strokeRadius = CalcDimension(DEFAULT_STROKE_RADIUS, DimensionUnit::PERCENT);
    if (isJsView) {
        if (strokeRadiusArg->IsUndefined() || strokeRadiusArg->IsNull()) {
            return;
        }
    }
    if (strokeRadiusArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, strokeRadiusArg, strokeRadius, DimensionUnit::VP, true)) {
        if (isJsView) {
            strokeRadius.SetUnit(DimensionUnit::PERCENT);
        }
    }

    if (isJsView && (LessNotEqual(strokeRadius.Value(), 0.0f) || strokeRadius.Unit() == DimensionUnit::PERCENT)) {
        return;
    }

    progressStyle.strokeRadiusValue = strokeRadius.Value();
    progressStyle.strokeRadiusUnit = static_cast<uint8_t>(strokeRadius.Unit());
}

void ParseBorderColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index,
    const NodeInfo& nodeInfo, bool isJsView, ArkUINodeHandle& nativeNode)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    bool borderColorByUser = true;
    Local<JSValueRef> borderColorArg = runtimeCallInfo->GetCallArgRef(index);
    Color borderColor = DEFAULT_BORDER_COLOR;
    RefPtr<ResourceObject> resObj;
    if (borderColorArg->IsNull() ||
        !ArkTSUtils::ParseJsColorAlpha(vm, borderColorArg, borderColor, resObj, nodeInfo)) {
        borderColor = DEFAULT_BORDER_COLOR;
        borderColorByUser = false;
    }

    if (resObj) {
        progressStyle.styleResource.borderColorRawPtr = AceType::RawPtr(resObj);
        resObj->IncRefCount();
    }

    progressStyle.borderColor = borderColor.GetValue();
    nodeModifiers->getProgressModifier()->setBorderColorSetByUser(nativeNode, borderColorByUser);
}

void ParseFontColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index,
    const NodeInfo& nodeInfo, bool isJsView)
{
    Local<JSValueRef> fontColorArg = runtimeCallInfo->GetCallArgRef(index);
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    Color fontColor = theme->GetTextColor();

    RefPtr<ResourceObject> colorResObj;
    bool state = ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, fontColor, colorResObj, nodeInfo);
    if (isJsView) {
        if (!state) {
            fontColor = theme->GetTextColor();
        }
        progressStyle.fontColor = fontColor.GetValue();
        if (colorResObj) {
            progressStyle.styleResource.fontColorRawPtr = AceType::RawPtr(colorResObj);
            colorResObj->IncRefCount();
        }
        progressStyle.fontColorSetByUser = state;
        return;
    }

    if (fontColorArg->IsNull() || !state) {
        fontColor = theme->GetTextColor();
        progressStyle.fontColorSetByUser = false;
    } else {
        progressStyle.fontColorSetByUser = true;
    }
    if (colorResObj) {
        progressStyle.styleResource.fontColorRawPtr = AceType::RawPtr(colorResObj);
        colorResObj->IncRefCount();
    }

    progressStyle.fontColor = fontColor.GetValue();
}

void ParseEnableSmoothEffect(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> enableSmoothEffectArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.enableSmoothEffect =
        (enableSmoothEffectArg->IsBoolean()) ? enableSmoothEffectArg->ToBoolean(vm)->Value() : true;
}

void ParseContent(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(index);
    std::string content = contentArg->ToString(vm)->ToString(vm);
    progressStyle.content = (contentArg->IsString(vm)) ? content.c_str() : nullptr;
}

void ParseEnableScanEffect(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> enableScanEffectArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.enableScanEffect =
        (enableScanEffectArg->IsBoolean()) ? enableScanEffectArg->ToBoolean(vm)->Value() : false;
}

void ParseShadow(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> shadowArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.shadow = (shadowArg->IsBoolean()) ? shadowArg->ToBoolean(vm)->Value() : false;
}

void ParseShowDefaultPercentage(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> showDefaultPercentageArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.showDefaultPercentage =
        (showDefaultPercentageArg->IsBoolean()) ? showDefaultPercentageArg->ToBoolean(vm)->Value() : false;
}

void ParseCapsuleFontSize(const EcmaVM* vm,
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index, bool isJsView)
{
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(index);

    CalcDimension fontSize;
    RefPtr<ResourceObject> resObj;
    bool state = ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, resObj);
    if (isJsView) {
        auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(theme);
        if (!state || LessNotEqual(fontSize.Value(), 0.0f) || fontSize.Unit() == DimensionUnit::PERCENT) {
            fontSize = theme->GetTextSize();
        }
        progressStyle.fontInfo.fontSizeNumber = fontSize.Value();
        progressStyle.fontInfo.fontSizeUnit = static_cast<int8_t>(fontSize.Unit());
        if (resObj) {
            progressStyle.styleResource.fontResource.fontSizeRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
        return;
    }
    if (sizeArg->IsNull() || !state ||
        fontSize.Unit() == DimensionUnit::PERCENT) {
        progressStyle.fontInfo.fontSizeNumber = DEFAULT_CAPSULE_FONT_SIZE;
        progressStyle.fontInfo.fontSizeUnit = static_cast<int8_t>(DEFAULT_CAPSULE_FONT_UNIT);
    } else {
        progressStyle.fontInfo.fontSizeNumber = fontSize.Value();
        progressStyle.fontInfo.fontSizeUnit = static_cast<int8_t>(fontSize.Unit());
        if (resObj) {
            progressStyle.styleResource.fontResource.fontSizeRawPtr = AceType::RawPtr(resObj);
            resObj->IncRefCount();
        }
    }
}

void ParseCapsuleFontWeight(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(index);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    std::string weight;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
        }
        progressStyle.fontInfo.fontWeight = static_cast<uint8_t>(Framework::ConvertStrToFontWeight(weight));
    } else {
        progressStyle.fontInfo.fontWeight = static_cast<uint8_t>(theme->GetTextStyle().GetFontWeight());
    }
}

void ParseCapsuleFontStyle(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(index);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    uint8_t style = static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle());
    if (!styleArg->IsNull() && styleArg->IsInt()) {
        style = static_cast<uint8_t>(styleArg->Int32Value(vm));
        if (style <= 0 || style > static_cast<uint8_t>(FONT_STYLES.size())) {
            style = static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle());
        }
    }

    progressStyle.fontInfo.fontStyle = style;
}

void ParseCapsuleFontFamily(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo,
    ArkUIProgressStyle& progressStyle, std::vector<std::string>& fontFamilies,
    std::unique_ptr<const char*[]>& families)
{
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_STYLE_FONT_FAMILY);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    if (familyArg->IsNull() || !ArkTSUtils::ParseJsFontFamilies(vm, familyArg, fontFamilies)) {
        fontFamilies = theme->GetTextStyle().GetFontFamilies();
    }

    families.reset();
    families = std::make_unique<const char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = fontFamilies[i].c_str();
    }

    progressStyle.fontInfo.fontFamilies = families.get();
    progressStyle.fontInfo.familyLength = fontFamilies.size();
}

void ParseBorderRadius(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> borderRadiusArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension borderRadius = CalcDimension(DEFAULT_BORDER_RADIUS, DimensionUnit::PERCENT);
    if (borderRadiusArg->IsNull() || !ArkTSUtils::ParseJsLengthMetrics(vm, borderRadiusArg, borderRadius)) {
        // Set illegal units, and the background will be handled according to the default value.
        borderRadius.SetUnit(DimensionUnit::PERCENT);
    }
    progressStyle.borderRadiusValue = borderRadius.Value();
    progressStyle.borderRadiusUnit = static_cast<uint8_t>(borderRadius.Unit());
}

void ParseLinearStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle,
    bool isJsView, ArkUINodeHandle& nativeNode)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH, isJsView);
    ParseStrokeRadius(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_RADIUS, isJsView);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseRingStyle(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, bool isJsView)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH, isJsView);
    ParseShadow(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHADOW);
    ParseProgressStatus(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_PROGRESS_STATUS);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseCapsuleStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle,
    std::vector<std::string>& fontFamilies, std::unique_ptr<const char*[]>& families, const NodeInfo& nodeInfo,
    bool isJsView, ArkUINodeHandle& nativeNode)
{
    ParseBorderColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_COLOR, nodeInfo, isJsView, nativeNode);
    ParseBorderWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_WIDTH, isJsView);
    ParseFontColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_COLOR, nodeInfo, isJsView);
    ParseCapsuleFontSize(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_SIZE, isJsView);
    ParseCapsuleFontWeight(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_WEIGHT);
    ParseCapsuleFontStyle(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_STYLE);
    ParseCapsuleFontFamily(vm, runtimeCallInfo, progressStyle, fontFamilies, families);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseShowDefaultPercentage(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAGE);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
    ParseBorderRadius(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_RADIUS);
}

void ParseProgressStyle(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, bool isJsView)
{
    auto progressTheme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH, isJsView);
    ParseScaleCount(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_COUNT);
    ParseScaleWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_WIDTH, isJsView);
    if ((progressStyle.scaleWidthValue <= 0.0) ||
        (progressStyle.scaleWidthValue > progressStyle.strokeWidthValue) ||
        progressStyle.scaleWidthUnit == static_cast<int8_t>(DimensionUnit::PERCENT)) {
        progressStyle.scaleWidthValue = progressTheme->GetScaleWidth().Value();
        progressStyle.scaleWidthUnit = static_cast<int8_t>(progressTheme->GetScaleWidth().Unit());
    }
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

ArkUINativeModuleValue ProgressBridge::SetProgressStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);

    auto fontFamilies = theme->GetTextStyle().GetFontFamilies();
    auto families = std::make_unique<const char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = fontFamilies[i].c_str();
    }
    auto progressTheme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_RETURN(progressTheme, panda::JSValueRef::Undefined(vm));

    ArkUIProgressStyle progressStyle = { DEFAULT_STROKE_WIDTH, static_cast<int8_t>(DimensionUnit::VP),
        DEFAULT_BORDER_WIDTH, static_cast<int8_t>(DimensionUnit::VP), DEFAULT_SCALE_COUNT,
        static_cast<uint8_t>(DEFAULT_PROGRESS_STATUS), DEFAULT_SCALE_WIDTH, static_cast<int8_t>(DimensionUnit::VP),
        DEFAULT_STROKE_RADIUS, static_cast<int8_t>(DimensionUnit::PERCENT), true,
        static_cast<ArkUI_Uint32>(DEFAULT_BORDER_COLOR.GetValue()), nullptr,
        static_cast<ArkUI_Uint32>(progressTheme->GetTextColor().GetValue()), false, false, false, false,
        { DEFAULT_CAPSULE_FONT_SIZE, static_cast<int8_t>(DEFAULT_CAPSULE_FONT_UNIT),
            static_cast<uint8_t>(theme->GetTextStyle().GetFontWeight()),
            static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle()), families.get(), fontFamilies.size() } };

    std::optional<ProgressType> progresstype = g_progressType;
    if (!isJsView) {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
        CHECK_NULL_RETURN(progressLayoutProperty, panda::JSValueRef::Undefined(vm));
        progresstype = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
    }
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_STYLE_CONTENT);
    std::string content;
    RefPtr<ResourceObject> contentResObj;
    ArkTSUtils::ParseJsString(vm, contentArg, content, contentResObj);
    if (contentResObj) {
        progressStyle.styleResource.contentRawPtr = AceType::RawPtr(contentResObj);
    }
    if (progresstype == ProgressType::LINEAR) {
        ParseLinearStyle(vm, runtimeCallInfo, progressStyle, isJsView, nativeNode);
    } else if (progresstype == ProgressType::RING) {
        ParseRingStyle(vm, runtimeCallInfo, progressStyle, isJsView);
    } else if (progresstype == ProgressType::CAPSULE) {
        auto nodeInfo = MakeProgressNodeInfo(nativeNode);
        ParseCapsuleStyle(vm, runtimeCallInfo, progressStyle, fontFamilies, families, nodeInfo, isJsView, nativeNode);
        progressStyle.content = (contentArg->IsString(vm) || contentArg->IsObject(vm)) ? content.c_str() : nullptr;
    } else {
        ParseProgressStyle(vm, runtimeCallInfo, progressStyle, isJsView);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->setProgressStyle(nativeNode, &progressStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nativeNodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    Color color;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = MakeProgressNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, resObj, nodeInfo)) {
        if (ArkTSUtils::IsJsView(vm, nativeNodeArg)) {
            auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
            CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX) &&
                SystemProperties::ConfigChangePerform()) {
                nodeModifiers->getProgressModifier()->resetProgressBackgroundColorWithColorSpace(nativeNode);
            } else {
                color = (g_progressType == ProgressType::CAPSULE) ? theme->GetCapsuleBgColor()
                        : (g_progressType == ProgressType::RING)  ? theme->GetRingProgressBgColor()
                                                                  : theme->GetTrackBgColor();
                // nullptr is passed to indicate that the background color is not set by user,
                // and it will be handled according to the default value from theme.
                nodeModifiers->getProgressModifier()->setProgressBackgroundColorWithColorSpace(
                    nativeNode, color.GetValue(), color.GetColorSpace(), nullptr);
            }
        } else {
            nodeModifiers->getProgressModifier()->resetProgressBackgroundColor(nativeNode);
        }
    } else {
        auto colorRawPtr = AceType::RawPtr(resObj);
        auto headRoomOptional = color.GetHeadRoomColor();
        if (headRoomOptional.has_value()) {
            auto colorWithHeadRoom = headRoomOptional.value();
            ArkUI_Float32 hdrValues[5] = {
                static_cast<ArkUI_Float32>(colorWithHeadRoom.red),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.green),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.blue),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.alpha),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.headRoom)
            };
            nodeModifiers->getProgressModifier()->setBackgroundColorForHDR(
                nativeNode, color.GetColorSpace(), hdrValues, colorRawPtr);
        } else {
            nodeModifiers->getProgressModifier()->setProgressBackgroundColorWithColorSpace(
                nativeNode, color.GetValue(), color.GetColorSpace(), colorRawPtr);
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        ProgressModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    ProgressModelNG::SetBuilderFunc(frameNode, [vm, frameNode, obj = std::move(obj),
        containerId = Container::CurrentId()](ProgressConfiguration config) -> RefPtr<FrameNode> {
        panda::LocalScope pandaScope(vm);
        ContainerScope scope(containerId);
        auto context = ArkTSUtils::GetContext(vm);
        CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
        const char* keysOfProgress[] = { "value", "total", "enabled"};
        Local<JSValueRef> valuesOfProgress[] = { panda::NumberRef::New(vm, config.value_),
            panda::NumberRef::New(vm, config.total_), panda::BooleanRef::New(vm, config.enabled_)};
        auto progress = panda::ObjectRef::NewWithNamedProperties(vm,
            ArraySize(keysOfProgress), keysOfProgress, valuesOfProgress);
        progress->SetNativePointerFieldCount(vm, 1);
        progress->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
        panda::Local<panda::JSValueRef> params[ARG_SECOND] = { context, progress };
        panda::TryCatch trycatch(vm);
        auto jsObject = obj.ToLocal();
        auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
        CHECK_NULL_RETURN(makeFunc->IsFunction(vm), nullptr);
        panda::Local<panda::FunctionRef> func = makeFunc;
        auto result = func->Call(vm, jsObject, params, 2);
        panda::JSNApi::ExecutePendingJob(vm);
        if (result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm)) {
            return nullptr;
        }
        auto resultObj = result->ToObject(vm);
        panda::Local<panda::JSValueRef> nodeptr = resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm,
            PROGRESS_NODEPTR_OF_UINODE));
        if (nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull()) {
            return nullptr;
        }
        auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
        CHECK_NULL_RETURN(frameNode, nullptr);
        return AceType::Claim(frameNode);
    });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressInitialize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> totalArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(4);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto value = 0;
    if (valueArg->IsNumber()) {
        value = valueArg->ToNumber(vm)->Value();
    }
    auto total = 100;
    if (totalArg->IsNumber() && totalArg->ToNumber(vm)->Value() > 0) {
        total = totalArg->Int32Value(vm);
    }
    if (value > total) {
        value = total;
    } else if (value < 0) {
        value = 0;
    }
    auto type = 0;
    if (styleArg->IsNull() || styleArg->IsUndefined()) {
        if (typeArg->IsNumber()) {
            type = typeArg->Int32Value(vm);
        }
    } else if (styleArg->IsNumber()) {
        type = styleArg->Int32Value(vm);
    }
    auto progressStyle = static_cast<Framework::ProgressStyle>(type);
    if (progressStyle == Framework::ProgressStyle::Eclipse) {
        g_progressType = NG::ProgressType::MOON;
    } else if (progressStyle == Framework::ProgressStyle::Ring) {
        g_progressType = NG::ProgressType::RING;
    } else if (progressStyle == Framework::ProgressStyle::ScaleRing) {
        g_progressType = NG::ProgressType::SCALE;
    } else if (progressStyle == Framework::ProgressStyle::Capsule) {
        g_progressType = NG::ProgressType::CAPSULE;
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->setProgressInitialize(
        nativeNode, value, total, static_cast<int>(g_progressType));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
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

ArkUINativeModuleValue ProgressBridge::ResetProgressPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
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

ArkUINativeModuleValue ProgressBridge::CreateProgress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> value = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> total = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> style = runtimeCallInfo->GetCallArgRef(ARG_SECOND);
    Local<JSValueRef> type = runtimeCallInfo->GetCallArgRef(ARG_THIRD);

    double progressValue = 0.0;
    if (value->IsNumber()) {
        progressValue = static_cast<double>(value->ToNumber(vm)->Value());
        if (std::isnan(progressValue) || LessNotEqual(progressValue, 0.0)) {
            progressValue = 0.0;
        }
    }

    double progressTotal = DEFAULT_TOTAL_VALUE;
    if (total->IsNumber()) {
        progressTotal = static_cast<double>(total->ToNumber(vm)->Value());
        if (std::isnan(progressTotal) || LessOrEqual(progressTotal, 0.0)) {
            progressTotal = DEFAULT_TOTAL_VALUE;
        }
    }

    if (GreatNotEqual(progressValue, progressTotal)) {
        progressValue = progressTotal;
    }

    auto progressStyleValue = type;
    if (progressStyleValue->IsNull() || progressStyleValue->IsUndefined()) {
        progressStyleValue = style;
    }

    auto progressStyle = Framework::ProgressStyle::Linear;
    if (progressStyleValue->IsNumber()) {
        progressStyle = static_cast<Framework::ProgressStyle>(progressStyleValue->ToNumber(vm)->Value());
    }
    if (progressStyle == Framework::ProgressStyle::Eclipse) {
        g_progressType = NG::ProgressType::MOON;
    } else if (progressStyle == Framework::ProgressStyle::Ring) {
        g_progressType = NG::ProgressType::RING;
    } else if (progressStyle == Framework::ProgressStyle::ScaleRing) {
        g_progressType = NG::ProgressType::SCALE;
    } else if (progressStyle == Framework::ProgressStyle::Capsule) {
        g_progressType = NG::ProgressType::CAPSULE;
    } else {
        g_progressType = NG::ProgressType::LINEAR;
    }

    GetArkUINodeModifiers()->getProgressModifier()->
        createModel(0.0, progressValue, 0.0, progressTotal, static_cast<int32_t>(g_progressType));
    Framework::JSProgressTheme::ApplyTheme(progressStyle);
    return panda::JSValueRef::Undefined(vm);
}

void ProgressBridge::RegisterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "setProgressInitialize", "resetProgressInitialize", "setProgressValue", "resetProgressValue",
        "setProgressColor", "resetProgressColor", "setProgressStyle", "resetProgressStyle",
        "setProgressBackgroundColor", "resetProgressBackgroundColor", "setContentModifierBuilder",
        "setProgressPrivacySensitive", "resetProgressPrivacySensitive"
    };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::CreateProgress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressValue),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressValue),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressPrivacySensitive),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressPrivacySensitive)
    };

    auto progress = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "progress"), progress);
}
} // namespace OHOS::Ace::NG
