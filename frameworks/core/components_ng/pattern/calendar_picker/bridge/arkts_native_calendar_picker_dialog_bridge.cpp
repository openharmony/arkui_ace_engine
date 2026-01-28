/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "arkts_native_calendar_picker_dialog_bridge.h"

#include "calendar_picker_utils.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/date_util.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/picker/picker_data.h"
#include "core/pipeline/pipeline_context.h"

using namespace OHOS::Ace::NG::CalendarPickerConstants;

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM2 = 2;
double GetMSByDate(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return 0.0f;
    }

    std::tm dateTime {};
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.tm_year = year->GetInt() - 1900; // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.tm_mon = month->GetInt() - 1;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.tm_mday = day->GetInt();
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    CHECK_NULL_RETURN(local, 0.0f);
    dateTime.tm_hour = local->tm_hour;
    dateTime.tm_min = local->tm_min;
    dateTime.tm_sec = local->tm_sec;
    return Date::GetMilliSecondsByDateTime(dateTime);
}

inline panda::Local<panda::StringRef> GetCachedString(EcmaVM* vm, Framework::ArkUIIndex index)
{
    return panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(index));
}
} // namespace

void CalendarPickerDialogBridge::ParseFontOfButtonStyle(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& pickerButtonParamObject, ButtonInfo& buttonInfo)
{
    CalcDimension fontSize;
    panda::Local<panda::JSValueRef> sizeProperty =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontSize"));
    if (ArkTSUtils::ParseJsDimensionVp(vm, sizeProperty, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        if (ArkTSUtils::ParseJsDimensionFp(vm, sizeProperty, fontSize)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    panda::Local<panda::JSValueRef> fontColorValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontColor"));
    Color fontColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, fontColorValue, fontColor)) {
        buttonInfo.fontColor = fontColor;
    }
    panda::Local<panda::JSValueRef> fontWeightValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontWeight"));
    if (fontWeightValue->IsString(vm) || fontWeightValue->IsNumber()) {
        std::string fontWeightStr = fontWeightValue->ToString(vm)->ToString(vm);
        buttonInfo.fontWeight = Framework::ConvertStrToFontWeight(fontWeightStr, FontWeight::MEDIUM);
    }
    panda::Local<panda::JSValueRef> styleValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontStyle"));
    if (styleValue->IsNumber()) {
        auto value = styleValue->ToNumber(vm)->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(Ace::FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<Ace::FontStyle>(value);
        }
    }
    panda::Local<panda::JSValueRef> familyValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontFamily"));
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, familyValue, fontFamilies)) {
        buttonInfo.fontFamily = fontFamilies;
    }
}

std::optional<NG::BorderRadiusProperty> CalendarPickerDialogBridge::HandleDifferentRadius(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    if (!args->IsObject(vm)) {
        return prop;
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;

    auto object = args->ToObject(vm);
    CalcDimension topLeft;
    panda::Local<panda::JSValueRef> topLeftValue = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "topLeft"));
    if (ArkTSUtils::ParseJsDimensionVp(vm, topLeftValue, topLeft)) {
        radiusTopLeft = topLeft;
    }

    CalcDimension topRight;
    panda::Local<panda::JSValueRef> topRightValue = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "topRight"));
    if (ArkTSUtils::ParseJsDimensionVp(vm, topRightValue, topRight)) {
        radiusTopRight = topRight;
    }

    CalcDimension bottomLeft;
    panda::Local<panda::JSValueRef> bottomLeftValue = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottomLeft"));
    if (ArkTSUtils::ParseJsDimensionVp(vm, bottomLeftValue, bottomLeft)) {
        radiusBottomLeft = bottomLeft;
    }

    CalcDimension bottomRight;
    panda::Local<panda::JSValueRef> bottomRightValue =
        object->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottomRight"));
    if (ArkTSUtils::ParseJsDimensionVp(vm, bottomRightValue, bottomRight)) {
        radiusBottomRight = bottomRight;
    }

    if (!radiusTopLeft.has_value() && !radiusTopRight.has_value() && !radiusBottomLeft.has_value() &&
        !radiusBottomRight.has_value()) {
        return prop;
    }

    NG::BorderRadiusProperty borderRadius;
    if (radiusTopLeft.has_value()) {
        borderRadius.radiusTopLeft = radiusTopLeft;
    }
    if (radiusTopRight.has_value()) {
        borderRadius.radiusTopRight = radiusTopRight;
    }
    if (radiusBottomLeft.has_value()) {
        borderRadius.radiusBottomLeft = radiusBottomLeft;
    }
    if (radiusBottomRight.has_value()) {
        borderRadius.radiusBottomRight = radiusBottomRight;
    }
    borderRadius.multiValued = true;
    prop = borderRadius;

    return prop;
}

std::optional<NG::BorderRadiusProperty> CalendarPickerDialogBridge::ParseBorderRadiusAttr(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    CalcDimension radiusDim;
    if (!args->IsObject(vm) && !args->IsNumber() && !args->IsString(vm)) {
        return prop;
    }
    if (ArkTSUtils::ParseJsDimensionVp(vm, args, radiusDim)) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
    } else if (args->IsObject(vm)) {
        prop = HandleDifferentRadius(vm, args);
    }
    return prop;
}

void CalendarPickerDialogBridge::ParseBackgroundOfButtonStyle(EcmaVM* vm,
    const panda::Local<panda::ObjectRef>& pickerButtonParamObject, ButtonInfo& buttonInfo)
{
    panda::Local<panda::JSValueRef> backgroundColorValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundColor"));
    Color backgroundColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorValue, backgroundColor)) {
        buttonInfo.backgroundColor = backgroundColor;
    }
}

ButtonInfo CalendarPickerDialogBridge::ParseButtonStyle(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& pickerButtonParamObject)
{
    ButtonInfo buttonInfo;
    panda::Local<panda::JSValueRef> typeValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (typeValue->IsNumber()) {
        auto buttonTypeIntValue = typeValue->ToNumber(vm)->Int32Value(vm);
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }

    panda::Local<panda::JSValueRef> styleValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    if (styleValue->IsNumber()) {
        auto styleModeIntValue = styleValue->ToNumber(vm)->Int32Value(vm);
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }

    panda::Local<panda::JSValueRef> roleValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "role"));
    if (roleValue->IsNumber()) {
        auto buttonRoleIntValue = roleValue->ToNumber(vm)->Int32Value(vm);
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }

    ParseFontOfButtonStyle(vm, pickerButtonParamObject, buttonInfo);

    ParseBackgroundOfButtonStyle(vm, pickerButtonParamObject, buttonInfo);

    panda::Local<panda::JSValueRef> borderRadiusValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "borderRadius"));
    auto radius = ParseBorderRadiusAttr(vm, borderRadiusValue);
    if (radius.has_value()) {
        buttonInfo.borderRadius = radius.value();
    }

    panda::Local<panda::JSValueRef> primaryValue =
        pickerButtonParamObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "primary"));
    if (primaryValue->IsBoolean()) {
        buttonInfo.isPrimary = primaryValue->ToBoolean(vm)->Value();
    }

    return buttonInfo;
}

std::vector<ButtonInfo> CalendarPickerDialogBridge::ParseButtonStyles(
    panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param)
{
    std::vector<ButtonInfo> buttonInfos;
    if (!param->IsObject(vm)) {
        return buttonInfos;
    }
    auto paramObj = param->ToObject(vm);
    auto acceptButtonStyle = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "acceptButtonStyle"));
    if (acceptButtonStyle->IsObject(vm)) {
        auto acceptButtonStyleParamObject = acceptButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, acceptButtonStyleParamObject));
        buttonInfos[0].isAcceptButton = true;
    } else {
        ButtonInfo buttonInfo;
        buttonInfos.emplace_back(buttonInfo);
    }
    auto cancelButtonStyle = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "cancelButtonStyle"));
    if (cancelButtonStyle->IsObject(vm)) {
        auto cancelButtonStyleParamObject = cancelButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, cancelButtonStyleParamObject));
    }
    return buttonInfos;
}

ArkUINativeModuleValue CalendarPickerDialogBridge::Show(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    auto param = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (!param->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        CalendarPickerDialogShow(vm, param);
    }
    return panda::JSValueRef::Undefined(vm);
}

std::map<std::string, NG::DialogEvent> CalendarPickerDialogBridge::ChangeDialogEvent(
    panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param)
{
    std::map<std::string, NG::DialogEvent> dialogEvent;
    if (!param->IsObject(vm)) {
        return dialogEvent;
    }
    auto paramObj = param->ToObject(vm);
    panda::Local<panda::JSValueRef> onChangeValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onChange"));
    if (!onChangeValue->IsUndefined() && onChangeValue->IsFunction(vm)) {
        NG::DialogEvent onChangeEvent;
        panda::Local<panda::FunctionRef> func = onChangeValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onChangeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](const std::string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onChange");
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::DateRef> dateObj = panda::DateRef::New(vm, GetMSByDate(info));
            panda::Local<panda::JSValueRef> params[] = { dateObj };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogEvent["changeId"] = onChangeEvent;
    }

    panda::Local<panda::JSValueRef> onAcceptValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onAccept"));
    if (!onAcceptValue->IsUndefined() && onAcceptValue->IsFunction(vm)) {
        NG::DialogEvent onAcceptEvent;
        panda::Local<panda::FunctionRef> func = onAcceptValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onAcceptEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](const std::string& info) {
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onAccept");
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::DateRef> dateObj = panda::DateRef::New(vm, GetMSByDate(info));
            panda::Local<panda::JSValueRef> params[] = { dateObj };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogEvent["acceptId"] = onAcceptEvent;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> CalendarPickerDialogBridge::DialogCancelEvent(
    panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (!param->IsObject(vm)) {
        return dialogCancelEvent;
    }
    auto paramObj = param->ToObject(vm);
    panda::Local<panda::JSValueRef> onCancelValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onCancel"));
    if (!onCancelValue->IsUndefined() && onCancelValue->IsFunction(vm)) {
        NG::DialogGestureEvent onCancelEvent;
        panda::Local<panda::FunctionRef> func = onCancelValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onCancelEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](
                            const GestureEvent& /* info */) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onCancel");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogCancelEvent["cancelId"] = onCancelEvent;
    }
    return dialogCancelEvent;
}

void CalendarPickerDialogBridge::AppearDialogEvent(panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param,
    std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    if (!param->IsObject(vm)) {
        return;
    }
    auto paramObj = param->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppearValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onDidAppear"));
    if (!onDidAppearValue->IsUndefined() && onDidAppearValue->IsFunction(vm)) {
        NG::DialogCancelEvent onDidAppearEvent;
        panda::Local<panda::FunctionRef> func = onDidAppearValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onDidAppearEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogLifeCycleEvent["didAppearId"] = onDidAppearEvent;
    }
    auto onWillAppearValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onWillAppear"));
    if (!onWillAppearValue->IsUndefined() && onWillAppearValue->IsFunction(vm)) {
        NG::DialogCancelEvent onWillAppearEvent;
        panda::Local<panda::FunctionRef> func = onWillAppearValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onWillAppearEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogLifeCycleEvent["willAppearId"] = onWillAppearEvent;
    }
}

void CalendarPickerDialogBridge::DisappearDialogEvent(panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param,
    std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    if (!param->IsObject(vm)) {
        return;
    }
    auto paramObj = param->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappearValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onDidDisappear"));
    if (!onDidDisappearValue->IsUndefined() && onDidDisappearValue->IsFunction(vm)) {
        NG::DialogCancelEvent onDidDisappearEvent;
        panda::Local<panda::FunctionRef> func = onDidDisappearValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onDidDisappearEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogLifeCycleEvent["didDisappearId"] = onDidDisappearEvent;
    }
    auto onWillDisappearValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onWillDisappear"));
    if (!onWillDisappearValue->IsUndefined() && onWillDisappearValue->IsFunction(vm)) {
        NG::DialogCancelEvent onWillDisappearEvent;
        panda::Local<panda::FunctionRef> func = onWillDisappearValue->ToObject(vm);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

        onWillDisappearEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("CalendarDialog.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
        dialogLifeCycleEvent["willDisappearId"] = onWillDisappearEvent;
    }
}

std::map<std::string, NG::DialogCancelEvent> CalendarPickerDialogBridge::LifeCycleDialogEvent(
    panda::ecmascript::EcmaVM* vm, const Local<JSValueRef>& param)
{
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    if (!param->IsObject(vm)) {
        return dialogLifeCycleEvent;
    }
    AppearDialogEvent(vm, param, dialogLifeCycleEvent);
    DisappearDialogEvent(vm, param, dialogLifeCycleEvent);
    return dialogLifeCycleEvent;
}

bool CalendarPickerDialogBridge::ParseJsShadowColorStrategy(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue, ShadowColorStrategy& strategy)
{
    if (jsValue->IsString(vm)) {
        std::string colorStr = jsValue->ToString(vm)->ToString(vm);
        if (colorStr.compare("average") == 0) {
            strategy = ShadowColorStrategy::AVERAGE;
            return true;
        } else if (colorStr.compare("primary") == 0) {
            strategy = ShadowColorStrategy::PRIMARY;
            return true;
        }
    }
    return false;
}

bool CalendarPickerDialogBridge::GetShadowFromTheme(
    EcmaVM* vm, ShadowStyle shadowStyle, Shadow& shadow, const bool configChangePerform)
{
    GetArkUINodeModifiers()->getCalendarPickerDialogModifier()->jsRemoveResObj("shadowStyle");
    auto colorMode = Container::CurrentColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    if (configChangePerform) {
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(frameNode, false);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [shadowStyle, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto colorMode = Container::CurrentColorMode();
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
            if (!shadowTheme) {
                return;
            }
            Shadow shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, shadow, frameNode);
        };
        updateFunc(resObj);
        pattern->AddResObj("shadowStyle", resObj, std::move(updateFunc));
        return false;
    }
    return true;
}

void CalendarPickerDialogBridge::ParseShadowPropsUpdate(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, double& radius, Shadow& shadow)
{
    if (jsObj->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> radiusResObj;
    auto radiusValue = jsObj->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::RADIUS));
    ArkTSUtils::ParseJsDouble(vm, radiusValue, radius, radiusResObj);
    if (SystemProperties::ConfigChangePerform() && radiusResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& radiusResObj, Shadow& shadow) {
            double radiusResObjValue = 0.0;
            ResourceParseUtils::ParseResDouble(radiusResObj, radiusResObjValue);
            if (LessNotEqual(radiusResObjValue, 0.0)) {
                radiusResObjValue = 0.0;
            }
            shadow.SetBlurRadius(radiusResObjValue);
        };
        shadow.AddResource("shadow.radius", radiusResObj, std::move(updateFunc));
    }
}

void CalendarPickerDialogBridge::ParseShadowOffsetXY(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, Shadow& shadow)
{
    CalcDimension offsetX;
    RefPtr<ResourceObject> xResObj;

    auto offsetXValue = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetX"));
    if (ArkTSUtils::ParseJsResource(vm, offsetXValue, offsetX, xResObj)) {
        if (SystemProperties::ConfigChangePerform() && xResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& xResObj, Shadow& shadow) {
                CalcDimension xValue;
                ResourceParseUtils::ParseResResource(xResObj, xValue);
                shadow.SetOffsetX(xValue.Value());
            };
            shadow.AddResource("shadow.offsetX", xResObj, std::move(updateFunc));
        }
        shadow.SetOffsetX(offsetX.Value());
    } else {
        if (ArkTSUtils::ParseJsDimensionVp(vm, offsetXValue, offsetX)) {
            shadow.SetOffsetX(offsetX.Value());
        }
    }
    CalcDimension offsetY;
    RefPtr<ResourceObject> yResObj;
    auto jsOffsetY = jsObj->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::OFFSET_Y));
    if (ArkTSUtils::ParseJsResource(vm, jsOffsetY, offsetY, yResObj)) {
        if (yResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& yResObj, Shadow& shadow) {
                CalcDimension yValue;
                ResourceParseUtils::ParseResResource(yResObj, yValue);
                shadow.SetOffsetY(yValue.Value());
            };
            shadow.AddResource("shadow.offsetY", yResObj, std::move(updateFunc));
        }
        shadow.SetOffsetY(offsetY.Value());
    } else {
        if (ArkTSUtils::ParseJsDimensionVp(vm, jsOffsetY, offsetY)) {
            shadow.SetOffsetY(offsetY.Value());
        }
    }
}

void CalendarPickerDialogBridge::ParseShadowColor(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsObj, Shadow& shadow, const bool configChangePerform,
    bool needResObj)
{
    RefPtr<ResourceObject> colorResObj;
    Color color;
    ShadowColorStrategy shadowColorStrategy;
    auto jsColor = jsObj->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::COLOR));
    if (ParseJsShadowColorStrategy(vm, jsColor, shadowColorStrategy)) {
        shadow.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ArkTSUtils::ParseJsColor(vm, jsColor, color, colorResObj)) {
        if (needResObj && colorResObj) {
            auto jsObj = jsColor->ToObject(vm);
            ArkTSUtils::CompleteResourceObject(vm, jsObj);
            colorResObj = ArkTSUtils::GetResourceObject(vm, jsObj);
        }
        if ((SystemProperties::ConfigChangePerform() || needResObj) && colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, Shadow& shadow) {
                Color colorValue;
                ResourceParseUtils::ParseResColor(colorResObj, colorValue);
                shadow.SetColor(colorValue);
            };
            shadow.AddResource("shadow.colorValue", colorResObj, std::move(updateFunc));
        }
        shadow.SetColor(color);
    }
}

bool CalendarPickerDialogBridge::ParseShadowProps(EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsValue,
    Shadow& shadow, const bool configChangePerform, bool needResObj)
{
    int32_t shadowStyle = 0;
    if (ArkTSUtils::ParseJsInteger(vm, jsValue, shadowStyle)) {
        auto style = static_cast<ShadowStyle>(shadowStyle);
        return GetShadowFromTheme(vm, style, shadow, configChangePerform);
    }
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    double radius = 0.0;
    ParseShadowPropsUpdate(vm, jsObj, radius, shadow);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    shadow.SetBlurRadius(radius);
    ParseShadowOffsetXY(vm, jsObj, shadow);
    ParseShadowColor(vm, jsObj, shadow, configChangePerform, needResObj);
    int32_t type = static_cast<int32_t>(ShadowType::COLOR);
    auto jsType = jsObj->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TYPE));
    ArkTSUtils::ParseJsInt32(vm, jsType, type);
    if (type != static_cast<int32_t>(ShadowType::BLUR)) {
        type = static_cast<int32_t>(ShadowType::COLOR);
    }
    shadow.SetShadowType(static_cast<ShadowType>(type));
    auto fillValue = jsObj->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::FILL));
    bool isFilled = false;
    if (fillValue->IsBoolean()) {
        isFilled = fillValue->ToBoolean(vm)->Value();
    }
    shadow.SetIsFilled(isFilled);
    return true;
}

void CalendarPickerDialogBridge::SetDialogHoverModeProperties(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties)
{
    auto enableHoverModeValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableHoverMode"));
    if (enableHoverModeValue->IsBoolean()) {
        properties.enableHoverMode = enableHoverModeValue->ToBoolean(vm)->Value();
    }

    // Parse hoverModeArea
    auto hoverModeAreaValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "hoverModeArea"));
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->ToNumber(vm)->Int32Value(vm);
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            properties.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }
}

void ParseSelectedStartEndDate(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, NG::CalendarSettingData& settingData)
{
    auto disabledDateRange = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disabledDateRange"));
    CalendarPickerUtils::ParseDisabledDateRange(vm, disabledDateRange, settingData);
    PickerDate::SortAndMergeDisabledDateRange(settingData.disabledDateRange);

    auto selectedDate = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    auto parseSelectedDate = CalendarPickerUtils::ParseDate(vm, selectedDate, true);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        auto startDate = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
        auto endDate = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "end"));
        auto parseStartDate = CalendarPickerUtils::ParseDate(vm, startDate);
        auto parseEndDate = CalendarPickerUtils::ParseDate(vm, endDate);
        if (parseEndDate.GetYear() > 0 && parseStartDate.ToDays() > parseEndDate.ToDays()) {
            parseStartDate = PickerDate();
            parseEndDate = PickerDate();
        }
        settingData.startDate = parseStartDate;
        settingData.endDate = parseEndDate;
        parseSelectedDate = PickerDate::AdjustDateToRange(parseSelectedDate, parseStartDate, parseEndDate);
    }

    if (parseSelectedDate.GetYear() != 0) {
        settingData.selectedDate = parseSelectedDate;
    }
}

void ParseMarkToday(EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, NG::CalendarSettingData& settingData)
{
    auto markToday = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "markToday"));
    bool isMarkToday = false;
    if (markToday->IsBoolean()) {
        isMarkToday = markToday->ToBoolean(vm)->Value();
    }
    settingData.markToday = isMarkToday;
}

DialogProperties CalendarPickerDialogBridge::BuildDialogProperties(EcmaVM* vm,
    const panda::Local<panda::ObjectRef>& paramObj)
{
    DialogProperties properties;
    auto theme = GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(theme, properties);
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, properties);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, properties);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();

    properties.alignment = theme->GetAlignment();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        properties.alignment = DialogAlignment::CENTER;
    }
    
    auto backgroundColorValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundColor"));
    Color backgroundColor;
    if (ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorValue, backgroundColor)) {
        properties.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundBlurStyle"));
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber(vm)->Int32Value(vm);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            properties.backgroundBlurStyle = blurStyle;
        }
    }

    auto shadowValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "shadow"));
    Shadow shadow;
    if ((shadowValue->IsObject(vm) || shadowValue->IsNumber()) && ParseShadowProps(vm, shadowValue, shadow)) {
        properties.shadow = shadow;
    }
    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
        NG::BorderRadiusProperty dialogRadius;
        dialogRadius.SetRadius(calendarTheme->GetDialogBorderRadius());
        properties.borderRadius = dialogRadius;
    }
    properties.hoverModeArea = HoverModeAreaType::BOTTOM_SCREEN;
    SetDialogHoverModeProperties(vm, paramObj, properties);
    ParseCalendarPickerDialogBlurStyleOption(vm, paramObj, properties);
    ParseCalendarPickerDialogEffectOption(vm, paramObj, properties);
    return properties;
}

void CalendarPickerDialogBridge::CalendarPickerDialogShow(EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj)
{
    auto buttonInfos = ParseButtonStyles(vm, paramObj);
    auto dialogEvent = ChangeDialogEvent(vm, paramObj);
    auto dialogCancelEvent = DialogCancelEvent(vm, paramObj);
    auto dialogLifeCycleEvent = LifeCycleDialogEvent(vm, paramObj);

    NG::CalendarSettingData settingData;
    ParseMarkToday(vm, paramObj, settingData);
    ParseSelectedStartEndDate(vm, paramObj, settingData);
    CalcDimension radius;
    auto hintRadiusValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "hintRadius"));
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, hintRadiusValue, radius)) {
        settingData.dayRadius = radius;
    }

    auto properties = BuildDialogProperties(vm, paramObj);
    CalendarPickerDialogOption option;
    option.dialogProperties = const_cast<DialogProperties*>(&properties);
    option.settingData = const_cast<CalendarSettingData*>(&settingData);
    option.dialogEvent = const_cast<std::map<std::string, NG::DialogEvent>*>(&dialogEvent);
    option.dialogCancelEvent = const_cast<std::map<std::string, NG::DialogGestureEvent>*>(&dialogCancelEvent);
    option.dialogLifeCycleEvent = const_cast<std::map<std::string, NG::DialogCancelEvent>*>(&dialogLifeCycleEvent);
    option.buttonInfos = const_cast<std::vector<ButtonInfo>*>(&buttonInfos);
    GetArkUINodeModifiers()->getCalendarPickerDialogModifier()->show(&option);
}

void CalendarPickerDialogBridge::ParseBlurOption(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsBlurOption, BlurOption& blurOption)
{
    auto blurOptionProperty = jsBlurOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "grayscale"));
    if (blurOptionProperty->IsArray(vm)) {
        panda::Local<panda::ArrayRef> params = panda::Local<panda::ArrayRef>(blurOptionProperty);
        auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, params));
        if (length >= NUM2) {
            panda::Local<panda::JSValueRef> grey1Value = panda::ArrayRef::GetValueAt(vm, params, 0);
            panda::Local<panda::JSValueRef> grey2Value = panda::ArrayRef::GetValueAt(vm, params, 1);

            if (grey1Value->IsNumber() && grey2Value->IsNumber()) {
                auto grey1 = grey1Value->ToNumber(vm)->Uint32Value(vm);
                auto grey2 = grey2Value->ToNumber(vm)->Uint32Value(vm);
                std::vector<float> greyVec(2); // 2 number
                greyVec[0] = grey1;
                greyVec[1] = grey2;
                blurOption.grayscale = greyVec;
            }
        }
    }
}

void CalendarPickerDialogBridge::ParseInactiveColor(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, BlurStyleOption& styleOption)
{
    RefPtr<ResourceObject> inactiveColorResObj;
    panda::Local<panda::JSValueRef> inactiveColorValue =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "inactiveColor"));
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorValue, styleOption.inactiveColor, inactiveColorResObj)) {
        styleOption.isValidColor = true;
    }
    if (SystemProperties::ConfigChangePerform() && inactiveColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BlurStyleOption& styleOption) {
            Color inactiveColorValue;
            ResourceParseUtils::ParseResColor(resObj, inactiveColorValue);
            styleOption.inactiveColor = inactiveColorValue;
            styleOption.isValidColor = true;
        };
        styleOption.AddResource(
            "backgroundBlurStyle.backgroundBlurStyleOptions.inactiveColor", inactiveColorResObj, std::move(updateFunc));
    }
}

void CalendarPickerDialogBridge::ParseBlurStyleOption(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, BlurStyleOption& styleOption)
{
    if (jsOption->IsUndefined()) {
        return;
    }
    auto colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
    auto colorModeValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "colorMode"));
    ArkTSUtils::ParseJsInt32(vm, colorModeValue, colorMode);
    if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
        colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
        styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
    }
    auto adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColorValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "adaptiveColor"));
    ArkTSUtils::ParseJsInt32(vm, adaptiveColorValue, adaptiveColor);
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    auto policyValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "policy"));
    ArkTSUtils::ParseJsInt32(vm, policyValue, policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        styleOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    auto typeValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    ArkTSUtils::ParseJsInt32(vm, typeValue, blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        styleOption.blurType = static_cast<BlurType>(blurType);
    }

    // inactiveColor
    ParseInactiveColor(vm, jsOption, styleOption);

    // scale
    auto scaleValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "scale"));
    if (scaleValue->IsNumber()) {
        double scale = scaleValue->ToNumber(vm)->Value();
        styleOption.scale = std::clamp(scale, 0.0, 1.0);
    }

    auto blurOptionsValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "blurOptions"));
    if (blurOptionsValue->IsObject(vm)) {
        auto jsBlurOption = blurOptionsValue->ToObject(vm);
        BlurOption blurOption;
        ParseBlurOption(vm, jsBlurOption, blurOption);
        styleOption.blurOption = blurOption;
    }
}

void CalendarPickerDialogBridge::ParseCalendarPickerDialogBlurStyleOption(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties)
{
    auto blurStyleValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundBlurStyleOptions"));
    if (blurStyleValue->IsObject(vm)) {
        if (!properties.blurStyleOption.has_value()) {
            properties.blurStyleOption.emplace();
        }
        ParseBlurStyleOption(vm, blurStyleValue, properties.blurStyleOption.value());
    }
}

void CalendarPickerDialogBridge::GetEffectOptionColor(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption)
{
    auto colorValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    if (!SystemProperties::ConfigChangePerform()) {
        ArkTSUtils::ParseJsColorAlpha(vm, colorValue, effectOption.color);
    } else {
        RefPtr<ResourceObject> colorResObj;
        ArkTSUtils::ParseJsColor(vm, colorValue, effectOption.color, colorResObj);
        if (colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, EffectOption& effectOption) {
                Color effectOptionColor;
                ResourceParseUtils::ParseResColor(colorResObj, effectOptionColor);
                effectOption.color = effectOptionColor;
            };
            effectOption.AddResource("backgroundEffect.color", colorResObj, std::move(updateFunc));
        }
    }
}

void CalendarPickerDialogBridge::GetEffectOptionInactiveColorUpdate(
    const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption)
{
    if (inactiveColorObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption) {
            Color effectOptionInactiveColor;
            ResourceParseUtils::ParseResColor(inactiveColorObj, effectOptionInactiveColor);
            effectOption.inactiveColor = effectOptionInactiveColor;
        };
        effectOption.AddResource("backgroundEffect.inactiveColor", inactiveColorObj, std::move(updateFunc));
    }
}

void CalendarPickerDialogBridge::GetEffectOptionInactiveColor(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption)
{
    panda::Local<panda::JSValueRef> inactiveColorValue =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "inactiveColor"));
    if (!SystemProperties::ConfigChangePerform()) {
        if (ArkTSUtils::ParseJsColorAlpha(vm, inactiveColorValue, effectOption.inactiveColor)) {
            effectOption.isValidColor = true;
        }
    } else {
        RefPtr<ResourceObject> inactiveColorObj;
        if (ArkTSUtils::ParseJsColor(vm, inactiveColorValue, effectOption.inactiveColor, inactiveColorObj)) {
            GetEffectOptionInactiveColorUpdate(inactiveColorObj, effectOption);
            effectOption.isValidColor = true;
        }
    }
}

void CalendarPickerDialogBridge::ParseEffectBlurOption(EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption,
    EffectOption& effectOption)
{
    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    panda::Local<panda::JSValueRef> typeValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    ArkTSUtils::ParseJsInt32(vm, typeValue, blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        effectOption.blurType = static_cast<BlurType>(blurType);
    }

    BlurOption blurOption;
    panda::Local<panda::JSValueRef> blurOptionsValue =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "blurOptions"));
    if (blurOptionsValue->IsObject(vm)) {
        panda::Local<panda::ObjectRef> jsBlurOption = blurOptionsValue->ToObject(vm);
        ParseBlurOption(vm, jsBlurOption, blurOption);
        effectOption.blurOption = blurOption;
    }
}

void CalendarPickerDialogBridge::ParseEffectOption(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& jsOption, EffectOption& effectOption)
{
    CalcDimension radius;
    panda::Local<panda::JSValueRef> radiusValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusValue, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = radius;

    double saturation = 1.0f;
    panda::Local<panda::JSValueRef> saturationValue =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "saturation"));
    if (saturationValue->IsNumber()) {
        ArkTSUtils::ParseJsDouble(vm, saturationValue, saturation);
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    effectOption.saturation = saturation;

    double brightness = 1.0f;
    panda::Local<panda::JSValueRef> brightnessValue =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "brightness"));
    if (brightnessValue->IsNumber()) {
        ArkTSUtils::ParseJsDouble(vm, brightnessValue, brightness);
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    effectOption.brightness = brightness;

    GetEffectOptionColor(vm, jsOption, effectOption);

    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColor = AdaptiveColor::DEFAULT;

    panda::Local<panda::JSValueRef> adaptiveColorValueRef =
        jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "adaptiveColor"));
    ArkTSUtils::ParseJsInt32(vm, adaptiveColorValueRef, adaptiveColorValue);
    if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
    }
    effectOption.adaptiveColor = adaptiveColor;

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    panda::Local<panda::JSValueRef> policyValue = jsOption->Get(vm, panda::StringRef::NewFromUtf8(vm, "policy"));
    ArkTSUtils::ParseJsInt32(vm, policyValue, policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        effectOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // inactiveColor
    GetEffectOptionInactiveColor(vm, jsOption, effectOption);

    //blurOptions
    ParseEffectBlurOption(vm, jsOption, effectOption);
}

void CalendarPickerDialogBridge::ParseCalendarPickerDialogEffectOption(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& paramObj, DialogProperties& properties)
{
    auto effectOptionValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundEffect"));
    if (effectOptionValue->IsObject(vm)) {
        if (!properties.effectOption.has_value()) {
            properties.effectOption.emplace();
        }
        ParseEffectOption(vm, effectOptionValue, properties.effectOption.value());
    }
}

void CalendarPickerDialogBridge::RegisterCalendarPickerDialogAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
#ifndef ARKUI_WEARABLE
    const char* functionNames[] = { "show" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerDialogBridge::Show),
    };

    auto calendarPickerDialog =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "calendarPickerDialog"), calendarPickerDialog);

#endif
}
} // namespace OHOS::Ace::NG