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

#include "core/components_ng/pattern/text_picker/bridge/arkts_native_textpickerdialog_bridge.h"

#include <securec.h>

#include "ark_native_engine.h"
#include "jsnapi_expo.h"
#include "native_engine.h"
#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_picker/bridge/textpicker_parser.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
const std::vector<DistortionMode> DIALOG_DISTORTION_MODE = { DistortionMode::DISTORTION_AUTO,
    DistortionMode::DISTORTION_ENABLED, DistortionMode::DISTORTION_DISABLED };
const std::vector<EdgeLightMode> DIALOG_EDGELIGHT_MODE = { EdgeLightMode::EDGELIGHT_AUTO,
    EdgeLightMode::EDGELIGHT_ENABLED, EdgeLightMode::EDGELIGHT_DISABLED };
const DimensionOffset TEXT_PICKER_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::string TEXTPICKER_OPTIONS_NUMERIC_VAL = "numeric";
const std::string TEXTPICKER_OPTIONS_TWO_DIGIT_VAL = "2-digit";
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };

void ParsePickerDialogMaterial(
    const EcmaVM* vm, TextPickerDialog& pickerDialog, const Local<panda::ObjectRef>& paramObject)
{
    auto systemMaterialValue = ArkTSUtils::GetProperty(vm, paramObject, "systemMaterial");
    if (systemMaterialValue->IsObject(vm)) {
        auto systemUiMaterial =
            static_cast<UiMaterial*>(ArkTSUtils::UnwrapNapiValue(vm, systemMaterialValue->ToObject(vm)));
        pickerDialog.systemMaterial = systemUiMaterial ? systemUiMaterial->Copy() : nullptr;
    }

    auto distortionModeValue = ArkTSUtils::GetProperty(vm, paramObject, "distortionMode");
    if (distortionModeValue->IsNumber()) {
        auto distortionModeVal = distortionModeValue->ToNumber(vm)->Int32Value(vm);
        if (distortionModeVal >= 0 && distortionModeVal < static_cast<int32_t>(DIALOG_DISTORTION_MODE.size())) {
            pickerDialog.distortionMode = DIALOG_DISTORTION_MODE[distortionModeVal];
        }
    }

    auto edgeLightModeValue = ArkTSUtils::GetProperty(vm, paramObject, "edgeLightMode");
    if (edgeLightModeValue->IsNumber()) {
        auto edgeLightModeVal = edgeLightModeValue->ToNumber(vm)->Int32Value(vm);
        if (edgeLightModeVal >= 0 && edgeLightModeVal < static_cast<int32_t>(DIALOG_EDGELIGHT_MODE.size())) {
            pickerDialog.edgeLightMode = DIALOG_EDGELIGHT_MODE[edgeLightModeVal];
        }
    }
}

void ParseFontOfButtonStyle(const EcmaVM* vm, const Local<JSValueRef>& pickerButtonParamObject, ButtonInfo& buttonInfo)
{
    CalcDimension fontSize;
    auto sizeProperty = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontSize");
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, sizeProperty, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        if (ArkTSUtils::ParseJsDimensionFp(vm, sizeProperty, fontSize)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    Color fontColor;
    RefPtr<ResourceObject> fontColorObject;
    if (ArkTSUtils::ParseJsColor(
            vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontColor"), fontColor, fontColorObject)) {
        buttonInfo.fontColor = fontColor;
    }
    auto fontWeight = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontWeight");
    if (fontWeight->IsString(vm) || fontWeight->IsNumber()) {
        buttonInfo.fontWeight =
            Framework::ConvertStrToFontWeight(fontWeight->ToString(vm)->ToString(vm), FontWeight::MEDIUM);
    }
    auto style = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontStyle");
    if (style->IsNumber()) {
        auto value = style->ToNumber(vm)->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(OHOS::Ace::FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<OHOS::Ace::FontStyle>(value);
        }
    }
    auto family = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "fontFamily");
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, family, fontFamilies)) {
        buttonInfo.fontFamily = fontFamilies;
    }
}

std::optional<NG::BorderRadiusProperty> HandleDifferentRadius(const EcmaVM* vm, const Local<JSValueRef>& args)
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
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "topLeft"), topLeft)) {
        radiusTopLeft = topLeft;
    }
    CalcDimension topRight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "topRight"), topRight)) {
        radiusTopRight = topRight;
    }
    CalcDimension bottomLeft;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "bottomLeft"), bottomLeft)) {
        radiusBottomLeft = bottomLeft;
    }
    CalcDimension bottomRight;
    if (ArkTSUtils::ParseJsDimensionVp(vm, ArkTSUtils::GetProperty(vm, object, "bottomRight"), bottomRight)) {
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

std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(const EcmaVM* vm, const Local<JSValueRef>& args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    CalcDimension radiusDim;
    if (!args->IsObject(vm) && !args->IsNumber() && !args->IsString(vm)) {
        return prop;
    }
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, args, radiusDim)) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
    } else if (args->IsObject(vm)) {
        prop = HandleDifferentRadius(vm, args);
    }
    return prop;
}

ButtonInfo ParseButtonStyle(const EcmaVM* vm, const Local<JSValueRef>& pickerButtonParamObject)
{
    ButtonInfo buttonInfo;
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "type")->IsNumber()) {
        auto buttonTypeIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "type")->ToNumber(vm)->Int32Value(vm);
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "style")->IsNumber()) {
        auto styleModeIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "style")->ToNumber(vm)->Int32Value(vm);
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "role")->IsNumber()) {
        auto buttonRoleIntValue =
            ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "role")->ToNumber(vm)->Int32Value(vm);
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
    ParseFontOfButtonStyle(vm, pickerButtonParamObject, buttonInfo);
    Color backgroundColor;
    RefPtr<ResourceObject> backgroundColorObject;
    if (ArkTSUtils::ParseJsColor(vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "backgroundColor"),
            backgroundColor, backgroundColorObject)) {
        buttonInfo.backgroundColor = backgroundColor;
    }
    auto radius = ParseBorderRadiusAttr(vm, ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "borderRadius"));
    if (radius.has_value()) {
        buttonInfo.borderRadius = radius.value();
    }

    auto primaryValue = ArkTSUtils::GetProperty(vm, pickerButtonParamObject, "primary");
    if (primaryValue->IsBoolean()) {
        buttonInfo.isPrimary = primaryValue->ToBoolean(vm)->Value();
    }

    return buttonInfo;
}

std::vector<ButtonInfo> ParseButtonStyles(const EcmaVM* vm, const Local<JSValueRef>& paramObject)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonStyle = ArkTSUtils::GetProperty(vm, paramObject, "acceptButtonStyle");
    if (acceptButtonStyle->IsObject(vm)) {
        auto acceptButtonStyleParamObject = acceptButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, acceptButtonStyleParamObject));
        buttonInfos[0].isAcceptButton = true;
    } else {
        ButtonInfo buttonInfo;
        buttonInfos.emplace_back(buttonInfo);
    }
    auto cancelButtonStyle = ArkTSUtils::GetProperty(vm, paramObject, "cancelButtonStyle");
    if (cancelButtonStyle->IsObject(vm)) {
        auto cancelButtonStyleParamObject = cancelButtonStyle->ToObject(vm);
        buttonInfos.emplace_back(ParseButtonStyle(vm, cancelButtonStyleParamObject));
    }

    return buttonInfos;
}

void TextPickerDialogAppearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, TextPickerDialogEvent& textPickerDialogEvent)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    std::function<void()> didAppearEvent;
    std::function<void()> willAppearEvent;
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return;
    }
    auto paramObject = firstArg->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = ArkTSUtils::GetProperty(vm, paramObject, "onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onDidAppear->ToObject(vm);
        didAppearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onWillAppear = ArkTSUtils::GetProperty(vm, paramObject, "onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onWillAppear->ToObject(vm);
        willAppearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    textPickerDialogEvent.onDidAppear = std::move(didAppearEvent);
    textPickerDialogEvent.onWillAppear = std::move(willAppearEvent);
}

void TextPickerDialogDisappearEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, TextPickerDialogEvent& textPickerDialogEvent)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    std::function<void()> didDisappearEvent;
    std::function<void()> willDisappearEvent;
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return;
    }
    auto paramObject = firstArg->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onDidDisappear->ToObject(vm);
        didDisappearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onWillDisappear = ArkTSUtils::GetProperty(vm, paramObject, "onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = onWillDisappear->ToObject(vm);
        willDisappearEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), node = targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    textPickerDialogEvent.onDidDisappear = std::move(didDisappearEvent);
    textPickerDialogEvent.onWillDisappear = std::move(willDisappearEvent);
}

void ExecuteInternal(const EcmaVM* vm, const std::unique_ptr<JsonValue>& value, const std::string& key,
    const Local<panda::ObjectRef>& eventInfo)
{
    auto pandaKey = panda::StringRef::NewFromUtf8(vm, key.c_str());
    if (value->IsString()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetString()));
    } else if (value->IsNumber()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetDouble()));
    } else if (value->IsBool()) {
        eventInfo->Set(vm, pandaKey, ArkTSUtils::ToJSValueWithVM(vm, value->GetBool()));
    } else if (value->IsObject()) {
        auto valueRef = ArkTSUtils::ToJSValueWithVM<std::string>(vm, value->ToString().c_str());
        if (valueRef->IsString(vm)) {
            eventInfo->Set(vm, pandaKey, panda::JSON::Parse(vm, valueRef));
        }
    } else if (value->IsArray()) {
        auto valueArray = panda::ArrayRef::New(vm);
        uint32_t length = value->GetArraySize();
        for (uint32_t index = 0; index < length; index++) {
            auto item = value->GetArrayItem(index);
            if (item && item->IsString()) {
                panda::ArrayRef::SetValueAt(vm, valueArray, index, ArkTSUtils::ToJSValueWithVM(vm, item->GetString()));
            }
            if (item && item->IsNumber()) {
                panda::ArrayRef::SetValueAt(vm, valueArray, index, ArkTSUtils::ToJSValueWithVM(vm, item->GetInt()));
            }
        }
        eventInfo->Set(vm, pandaKey, valueArray);
    }
}

bool ParseShowDataOptions(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, ParseTextArrayParam& param,
    NG::TextCascadePickerOptionsAttr& attr)
{
    bool optionsMultiContentCheckErr = false;
    bool optionsCascadeContentCheckErr = false;
    if (!TextPickerParser::ParseMultiTextArray(vm, paramObj, param)) {
        param.options.clear();
        optionsMultiContentCheckErr = true;
    }

    if (optionsMultiContentCheckErr) {
        if (!TextPickerParser::ParseCascadeTextArray(vm, paramObj, param, attr)) {
            param.options.clear();
            optionsCascadeContentCheckErr = true;
        } else {
            auto getRange = ArkTSUtils::GetProperty(vm, paramObj, "range");
            TextPickerParser::GenerateCascadeOptions(vm, getRange, param.options);
            attr.isCascade = true;

            TextPickerParser::ParseColumnWidths(vm, paramObj, param);
        }
    }

    if (optionsMultiContentCheckErr && optionsCascadeContentCheckErr) {
        param.options.clear();
        return false;
    }

    return true;
}

void ParseShowDataMultiContent(const std::vector<TextCascadePickerOptions>& options,
    const std::vector<uint32_t>& selectedValues, const std::vector<std::string>& values,
    TextCascadePickerOptionsAttr& attr, TextPickerSettingData& settingData)
{
    settingData.columnKind = NG::TEXT;
    for (auto& item : selectedValues) {
        settingData.selectedValues.emplace_back(item);
    }
    for (auto& item : values) {
        settingData.values.emplace_back(item);
    }
    for (auto& item : options) {
        settingData.options.emplace_back(item);
    }
    settingData.attr.isCascade = attr.isCascade;
    settingData.attr.isHasSelectAttr = attr.isHasSelectAttr;
}

void ParseTextProperties(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, NG::PickerTextProperties& result)
{
    auto disappearProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disappearTextStyle"));
    auto normalProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"));
    auto selectedProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selectedTextStyle"));
    auto defaultProperty = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "defaultTextStyle"));

    if (!disappearProperty->IsNull() && disappearProperty->IsObject(vm)) {
        auto disappearObj = disappearProperty->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, disappearObj, result.disappearTextStyle_, "disappearTextStyle");
    }

    if (!normalProperty->IsNull() && normalProperty->IsObject(vm)) {
        auto noramlObj = normalProperty->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, noramlObj, result.normalTextStyle_, "textStyle");
    }

    if (!selectedProperty->IsNull() && selectedProperty->IsObject(vm)) {
        auto selectedObj = selectedProperty->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, selectedObj, result.selectedTextStyle_, "selectedTextStyle");
    }

    if (!defaultProperty->IsNull() && defaultProperty->IsObject(vm)) {
        auto defaultObj = defaultProperty->ToObject(vm);
        TextPickerParser::ParseTextStyle(vm, defaultObj, result.defaultTextStyle_, "defaultTextStyle");
    }
}

bool ParseShowDataAttribute(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, NG::TextPickerSettingData& settingData)
{
    CalcDimension height;
    auto defaultHeight = ArkTSUtils::GetProperty(vm, paramObj, "defaultPickerItemHeight");
    if (defaultHeight->IsNumber() || defaultHeight->IsString(vm)) {
        if (!ArkTSUtils::ParseJsDimensionFp(vm, defaultHeight, height)) {
            return false;
        }
    }
    settingData.height = height;

    ParseTextProperties(vm, paramObj, settingData.properties);

    auto selectedBackgroundStyle = ArkTSUtils::GetProperty(vm, paramObj, "selectedBackgroundStyle");
    if (selectedBackgroundStyle->IsObject(vm)) {
        TextPickerParser::ParsePickerBackgroundStyle(vm, selectedBackgroundStyle, settingData.pickerBgStyle);
    } else {
        settingData.pickerBgStyle.color = Color::TRANSPARENT;
        settingData.pickerBgStyle.borderRadius = NG::BorderRadiusProperty(8.0_vp);
    }

    return true;
}

bool ParseCanLoop(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, bool& canLoop)
{
    bool result = false;
    auto prop = ArkTSUtils::GetProperty(vm, paramObj, "canLoop");
    bool value = false;
    if (prop->IsBoolean() && ArkTSUtils::ParseJsBool(vm, prop, value)) {
        canLoop = value;
        result = true;
    } else {
        canLoop = true;
        result = false;
    }
    return result;
}

void ParseDisableTextStyleAnimation(
    const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, bool& isDisableTextStyleAnimation)
{
    auto prop = ArkTSUtils::GetProperty(vm, paramObj, "disableTextStyleAnimation");
    bool value = false;
    if (prop->IsBoolean() && ArkTSUtils::ParseJsBool(vm, prop, value)) {
        isDisableTextStyleAnimation = value;
    } else {
        isDisableTextStyleAnimation = false;
    }
}

bool ParseShowData(const EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, NG::TextPickerSettingData& settingData)
{
    ParseTextArrayParam param;
    bool rangeContentCheckErr = false;
    bool optionsCascadeContentCheckErr = false;
    TextCascadePickerOptionsAttr attr;

    auto getRange = ArkTSUtils::GetProperty(vm, paramObj, "range");
    if (getRange->IsNull() || getRange->IsUndefined()) {
        return false;
    }

    if (!TextPickerParser::ParseTextArray(vm, paramObj, param)) {
        if (!TextPickerParser::ParseIconTextArray(vm, paramObj, param)) {
            rangeContentCheckErr = true;
            param.result.clear();
        }
    }

    if (rangeContentCheckErr) {
        optionsCascadeContentCheckErr = !ParseShowDataOptions(vm, paramObj, param, attr);
    }

    if (rangeContentCheckErr && optionsCascadeContentCheckErr) {
        return false;
    }

    if (memset_s(&settingData, sizeof(TextPickerSettingData), 0, sizeof(TextPickerSettingData)) != EOK) {
        return false;
    }

    if (!ParseShowDataAttribute(vm, paramObj, settingData)) {
        return false;
    }

    ParseCanLoop(vm, paramObj, settingData.canLoop);
    ParseDisableTextStyleAnimation(vm, paramObj, settingData.isDisableTextStyleAnimation);

    if (param.result.size() > 0) {
        settingData.selected = param.selected;
        settingData.columnKind = param.kind;
        for (const auto& item : param.result) {
            settingData.rangeVector.emplace_back(item);
        }
    } else {
        ParseShowDataMultiContent(param.options, param.selecteds, param.values, attr, settingData);
    }

    bool isEnableHapticFeedback = DEFAULT_ENABLE_HAPTIC_FEEDBACK;
    auto enableHapticFeedbackValue = ArkTSUtils::GetProperty(vm, paramObj, "enableHapticFeedback");
    if (enableHapticFeedbackValue->IsBoolean()) {
        isEnableHapticFeedback = enableHapticFeedbackValue->ToBoolean(vm)->Value();
    }
    settingData.isEnableHapticFeedback = isEnableHapticFeedback;

    for (auto& item : param.columnWidths) {
        settingData.columnWidths.emplace_back(item);
    }

    return true;
}
} // namespace

void TextPickerDialogBridge::RegisterTextPickerDialogAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "show" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerDialogBridge::JsShow),
    };

    auto textPickerDialog =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textPickerDialog"), textPickerDialog);
}

ArkUINativeModuleValue TextPickerDialogBridge::JsShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_RETURN(scopedDelegate, panda::NativePointerRef::New(vm, nullptr));
    auto param = runtimeCallInfo->GetCallArgRef(0);
    if (!param->IsObject(vm)) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    auto paramObject = param->ToObject(vm);
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    auto onCancel = ArkTSUtils::GetProperty(vm, paramObject, "onCancel");
    WeakPtr<FrameNode> targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!onCancel->IsUndefined() && onCancel->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onCancel;
        cancelEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode]() {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onCancel");
            PipelineContext::SetCallBackNode(targetNode);
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onAccept = ArkTSUtils::GetProperty(vm, paramObject, "onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onAccept->ToObject(vm);
        acceptEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onAccept");
            PipelineContext::SetCallBackNode(targetNode);
            std::vector<std::string> keys = { "value", "index" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    auto onChange = ArkTSUtils::GetProperty(vm, paramObject, "onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onChange->ToObject(vm);
        changeEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onChange");
            PipelineContext::SetCallBackNode(targetNode);
            std::vector<std::string> keys = { "value", "index" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    std::function<void(const std::string&)> scrollStopEvent;
    auto onScrollStop = ArkTSUtils::GetProperty(vm, paramObject, "onScrollStop");
    if (!onScrollStop->IsUndefined() && onScrollStop->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onScrollStop->ToObject(vm);
        scrollStopEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onScrollStop");
            PipelineContext::SetCallBackNode(targetNode);
            std::vector<std::string> keys = { "value", "index" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    std::function<void(const std::string&)> enterSelectedAreaEvent;
    auto onEnterSelectedArea = ArkTSUtils::GetProperty(vm, paramObject, "onEnterSelectedArea");
    if (!onEnterSelectedArea->IsUndefined() && onEnterSelectedArea->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsFunc = onEnterSelectedArea->ToObject(vm);
        enterSelectedAreaEvent = [vm, func = panda::CopyableGlobal(vm, jsFunc), targetNode](const std::string& info) {
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ACE_SCORING_EVENT("TextPickerDialog.onEnterSelectedArea");
            PipelineContext::SetCallBackNode(targetNode);
            std::vector<std::string> keys = { "value", "index" };
            auto argsPtr = JsonUtil::ParseJsonString(info);
            if (!argsPtr) {
                return;
            }
            Local<panda::ObjectRef> eventInfo = panda::ObjectRef::New(vm);
            for (auto key : keys) {
                const auto value = argsPtr->GetValue(key);
                if (!value) {
                    LOGD("key[%{public}s] not exist.", key.c_str());
                    continue;
                }
                ExecuteInternal(vm, value, key, eventInfo);
            }
            panda::Local<panda::JSValueRef> params[] = { eventInfo };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    TextPickerSettingData settingData;
    TextPickerDialog textPickerDialog;
    auto pickerText = GetArkUINodeModifiers()->getTextPickerModifier()->createObject();
    if (pickerText == nullptr) {
        // parse Multi column text
        if (!ParseShowData(vm, paramObject, settingData)) {
            return panda::NativePointerRef::New(vm, nullptr);
        }
    } else {
        auto getSelected = ArkTSUtils::GetProperty(vm, paramObject, "selected");
        auto defaultHeight = ArkTSUtils::GetProperty(vm, paramObject, "defaultPickerItemHeight");
        auto getRange = ArkTSUtils::GetProperty(vm, paramObject, "range");
        std::vector<std::string> getRangeVector;
        if (!TextPickerParser::ParseJsStrArray(vm, getRange, getRangeVector)) {
            return panda::NativePointerRef::New(vm, nullptr);
        }
        std::string value = "";
        uint32_t selectedValue = 0;
        auto getValue = ArkTSUtils::GetProperty(vm, paramObject, "value");
        if (!ArkTSUtils::ParseJsInteger(vm, getSelected, selectedValue) &&
            ArkTSUtils::ParseJsString(vm, getValue, value)) {
            auto valueIterator = std::find(getRangeVector.begin(), getRangeVector.end(), value);
            if (valueIterator != getRangeVector.end()) {
                selectedValue = static_cast<uint32_t>(std::distance(getRangeVector.begin(), valueIterator));
            }
        }
        if (selectedValue >= getRangeVector.size()) {
            selectedValue = 0;
        }
        CalcDimension height;
        if (defaultHeight->IsNumber() || defaultHeight->IsString(vm)) {
            if (!ArkTSUtils::ParseJsDimension(vm, defaultHeight, height, DimensionUnit::FP)) {
                return panda::NativePointerRef::New(vm, nullptr);
            }
        }
        if (!defaultHeight->IsNull() && !defaultHeight->IsUndefined()) {
            textPickerDialog.isDefaultHeight = true;
        }
        textPickerDialog.height = height;
        textPickerDialog.selectedValue = selectedValue;
        textPickerDialog.getRangeVector = getRangeVector;
    }
    // Parse alignment
    auto alignmentValue = ArkTSUtils::GetProperty(vm, paramObject, "alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->Int32Value(vm);
        if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            textPickerDialog.alignment = DIALOG_ALIGNMENT[alignment];
        }
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
                alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
                textPickerDialog.offset = TEXT_PICKER_OFFSET_DEFAULT_TOP;
            }
        }
    }
    // Parse offset
    auto offsetValue = ArkTSUtils::GetProperty(vm, paramObject, "offset");
    if (offsetValue->IsObject(vm)) {
        auto offsetObj = offsetValue->ToObject(vm);
        CalcDimension dx;
        auto dxValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dx"));
        ArkTSUtils::ParseJsDimension(vm, dxValue, dx, DimensionUnit::VP);
        CalcDimension dy;
        auto dyValue = offsetObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "dy"));
        ArkTSUtils::ParseJsDimension(vm, dyValue, dy, DimensionUnit::VP);
        textPickerDialog.offset = DimensionOffset(dx, dy);
    }
    // Parse maskRect.
    auto maskRectValue = ArkTSUtils::GetProperty(vm, paramObject, "maskRect");
    DimensionRect maskRect;
    if (ArkTSUtils::ParseJsDimensionRect(vm, maskRectValue, maskRect)) {
        textPickerDialog.maskRect = maskRect;
    }
    auto backgroundColorValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundColor");
    Color backgroundColor;
    RefPtr<ResourceObject> colorResObj;
    if (ArkTSUtils::ParseJsColor(vm, backgroundColorValue, backgroundColor, colorResObj)) {
        textPickerDialog.backgroundColor = backgroundColor;
    }
    auto backgroundBlurStyle = ArkTSUtils::GetProperty(vm, paramObject, "backgroundBlurStyle");
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->Int32Value(vm);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            textPickerDialog.backgroundBlurStyle = blurStyle;
        }
    }
    auto shadowValue = ArkTSUtils::GetProperty(vm, paramObject, "shadow");
    Shadow shadow;
    RefPtr<ResourceObject> shadowResObj;
    if ((shadowValue->IsObject(vm) || shadowValue->IsNumber()) &&
        ArkTSUtils::ParseShadowProps(vm, shadowValue, shadow, shadowResObj)) {
        textPickerDialog.shadow = shadow;
    }
    auto enableHoverModeValue = ArkTSUtils::GetProperty(vm, paramObject, "enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        textPickerDialog.enableHoverMode = enableHoverModeValue->ToBoolean(vm)->Value();
    }
    auto hoverModeAreaValue = ArkTSUtils::GetProperty(vm, paramObject, "hoverModeArea");
    textPickerDialog.hoverModeArea = HoverModeAreaType::BOTTOM_SCREEN;
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->Int32Value(vm);
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            textPickerDialog.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }
    auto blurStyleValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundBlurStyleOptions");
    if (blurStyleValue->IsObject(vm)) {
        if (!textPickerDialog.blurStyleOption.has_value()) {
            textPickerDialog.blurStyleOption.emplace();
        }
        ArkTSUtils::ParseBlurStyleOption(vm, blurStyleValue, textPickerDialog.blurStyleOption.value());
    }
    auto effectOptionValue = ArkTSUtils::GetProperty(vm, paramObject, "backgroundEffect");
    if (effectOptionValue->IsObject(vm)) {
        if (!textPickerDialog.effectOption.has_value()) {
            textPickerDialog.effectOption.emplace();
        }
        ArkTSUtils::ParseEffectOption(vm, effectOptionValue, textPickerDialog.effectOption.value());
    }
    auto buttonInfos = ParseButtonStyles(vm, paramObject);
    ParsePickerDialogMaterial(vm, textPickerDialog, paramObject);
    OHOS::Ace::TextPickerDialogEvent textPickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    TextPickerDialogAppearEvent(runtimeCallInfo, textPickerDialogEvent);
    TextPickerDialogDisappearEvent(runtimeCallInfo, textPickerDialogEvent);
    GetArkUINodeModifiers()->getTextPickerModifier()->show(reinterpret_cast<void*>(&pickerText),
        reinterpret_cast<void*>(&settingData), reinterpret_cast<void*>(&cancelEvent),
        reinterpret_cast<void*>(&acceptEvent), reinterpret_cast<void*>(&changeEvent),
        reinterpret_cast<void*>(&scrollStopEvent), reinterpret_cast<void*>(&enterSelectedAreaEvent),
        reinterpret_cast<void*>(&textPickerDialog), reinterpret_cast<void*>(&textPickerDialogEvent),
        reinterpret_cast<void*>(&buttonInfos));
    return panda::NativePointerRef::New(vm, nullptr);
}
} // namespace OHOS::Ace::NG
