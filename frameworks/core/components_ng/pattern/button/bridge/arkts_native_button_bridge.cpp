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
#include "core/components_ng/pattern/button/bridge/arkts_native_button_bridge.h"

#include <array>
#include <limits>
#include <string>

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_button_theme.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "core/interfaces/native/node/node_button_modifier.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END,
    TextAlign::JUSTIFY, TextAlign::LEFT, TextAlign::RIGHT };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::string DEFAULT_FONT_WEIGHT = "400";
const std::string DEFAULT_JS_FONT_WEIGHT = "normal";
const std::string NONE_FONT_FAMILY = "NoneFontFamily";
constexpr int32_t DEFAULT_BUTTON_TYPE = 1;
constexpr bool DEFAULT_STATE_EFFECT = true;
constexpr uint32_t DEFAULT_CONTROL_SIZE = 1;
constexpr uint32_t DEFAULT_STYLE = 1;
constexpr uint32_t DEFAULT_ROLE = 0;
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t CALL_ARG_2 = 2;
constexpr int32_t CALL_ARG_3 = 3;
constexpr int32_t CALL_ARG_4 = 4;
constexpr int32_t CALL_ARG_5 = 5;
constexpr int32_t MAX_LINES_ARG_2 = 2;
constexpr int32_t MIN_FONT_SIZE_ARG_3 = 3;
constexpr int32_t MAX_FONT_SIZE_ARG_4 = 4;
constexpr int32_t ADAPT_HEIGHT_ARG_5 = 5;
constexpr int32_t FONT_SIZE_ARG_6 = 6;
constexpr int32_t FONT_WEIGHT_ARG_7 = 7;
constexpr int32_t FONT_STYLE_ARG_8 = 8;
constexpr int32_t FONT_FAMILY_ARG_9 = 9;
constexpr int32_t TEXT_ALIGN_ARG_10 = 10;
const char* BUTTON_NODEPTR_OF_UINODE = "nodePtr_";
constexpr int32_t NUM_4 = 4;
constexpr size_t BUTTON_PADDING_TOP_INDEX = 0;
constexpr size_t BUTTON_PADDING_BOTTOM_INDEX = 1;
constexpr size_t BUTTON_PADDING_START_INDEX = 2;
constexpr size_t BUTTON_PADDING_END_INDEX = 3;

using ButtonPaddingCalcValueStorage = std::array<std::string, NUM_4>;

static bool g_isLabelButton = false;

bool HasProperty(EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, false);
    if (obj.IsEmpty()) {
        return false;
    }
    return obj->Has(vm, panda::StringRef::NewFromUtf8(vm, propertyName.c_str()));
}

Local<JSValueRef> GetProperty(
    const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto stringRef = panda::StringRef::NewFromUtf8(vm, propertyName.c_str());
    return obj->Get(vm, stringRef);
}

bool IsStringResource(const Local<JSValueRef>& value, EcmaVM* vm)
{
    return value->IsObject(vm) && HasProperty(vm, value->ToObject(vm), "id");
}

void ParseJsViewFont(EcmaVM* vm, const Local<JSValueRef>& fontValue, ButtonParameters& buttonParameters)
{
    if (fontValue->IsNull() || !fontValue->IsObject(vm)) {
        return;
    }

    auto fontObj = fontValue->ToObject(vm);
    auto sizeValue = GetProperty(vm, fontObj, "size");
    CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionFp(vm, sizeValue, fontSize, false)) {
        buttonParameters.fontSize = fontSize;
    }

    auto weightValue = GetProperty(vm, fontObj, "weight");
    if (weightValue->IsString(vm) || weightValue->IsNumber()) {
        buttonParameters.fontWeight = Framework::ConvertStrToFontWeight(weightValue->ToString(vm)->ToString(vm));
    }

    auto familyValue = GetProperty(vm, fontObj, "family");
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, familyValue, fontFamilies)) {
        buttonParameters.fontFamily = fontFamilies;
    }

    auto styleValue = GetProperty(vm, fontObj, "style");
    if (styleValue->IsNumber()) {
        auto fontStyle = styleValue->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            buttonParameters.fontStyle = FONT_STYLES[fontStyle];
        }
    }
}

void CompleteJsViewLabelStyle(ButtonParameters& buttonParameters)
{
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(node);
    auto buttonTheme = node->GetTheme<ButtonTheme>(true);
    CHECK_NULL_VOID(buttonTheme);

    auto textStyle = buttonTheme->GetTextStyle();
    if (!buttonParameters.maxLines.has_value()) {
        buttonParameters.maxLines = buttonTheme->GetTextMaxLines();
    }
    if (!buttonParameters.fontSize.has_value()) {
        buttonParameters.fontSize = textStyle.GetFontSize();
    }
    if (!buttonParameters.fontWeight.has_value()) {
        buttonParameters.fontWeight = textStyle.GetFontWeight();
    }
    if (!buttonParameters.fontStyle.has_value()) {
        buttonParameters.fontStyle = textStyle.GetFontStyle();
    }
    if (!buttonParameters.heightAdaptivePolicy.has_value()) {
        buttonParameters.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!buttonParameters.textOverflow.has_value()) {
        buttonParameters.textOverflow = TextOverflow::CLIP;
    }
}

bool ParseJsViewTextAlign(EcmaVM* vm, const Local<JSValueRef>& textAlignValue, ButtonParameters& buttonParameters)
{
    if (!textAlignValue->IsNull() && textAlignValue->IsNumber()) {
        auto textAlign = textAlignValue->Int32Value(vm);
        if (textAlign >= 0 && textAlign < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            buttonParameters.textAlign = TEXT_ALIGNS[textAlign];
            return true;
        }
    }
    return false;
}

void SetButtonPaddingValue(
    ArkUISizeType& value, const CalcDimension& dimension, std::string* calcValueStorage = nullptr)
{
    value.value = dimension.Value();
    value.unit = static_cast<int32_t>(dimension.Unit());
    value.string = nullptr;
    if (!dimension.CalcValue().empty() && calcValueStorage != nullptr) {
        *calcValueStorage = dimension.CalcValue();
        value.string = calcValueStorage->c_str();
    }
    value.isSet = true;
}

void SetDefaultButtonPadding(ArkUIPaddingType& padding, ButtonPaddingCalcValueStorage& calcValueStorage)
{
    CalcDimension top(0.0, DimensionUnit::VP);
    CalcDimension bottom(0.0, DimensionUnit::VP);
    CalcDimension start(0.0, DimensionUnit::VP);
    CalcDimension end(0.0, DimensionUnit::VP);
    if (g_isLabelButton) {
        auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(node);
        auto buttonTheme = node->GetTheme<ButtonTheme>(true);
        if (buttonTheme) {
            auto defaultPadding = buttonTheme->GetPadding();
            top = CalcDimension(defaultPadding.Top().Value(), defaultPadding.Top().Unit());
            bottom = CalcDimension(defaultPadding.Bottom().Value(), defaultPadding.Bottom().Unit());
            start = CalcDimension(defaultPadding.Left().Value(), defaultPadding.Left().Unit());
            end = CalcDimension(defaultPadding.Right().Value(), defaultPadding.Right().Unit());
        }
    }
    SetButtonPaddingValue(padding.top, top, &calcValueStorage[BUTTON_PADDING_TOP_INDEX]);
    SetButtonPaddingValue(padding.bottom, bottom, &calcValueStorage[BUTTON_PADDING_BOTTOM_INDEX]);
    SetButtonPaddingValue(padding.start, start, &calcValueStorage[BUTTON_PADDING_START_INDEX]);
    SetButtonPaddingValue(padding.end, end, &calcValueStorage[BUTTON_PADDING_END_INDEX]);
}

bool GetButtonOldPadding(EcmaVM* vm, const Local<JSValueRef>& jsValue, ArkUIPaddingType& padding,
    ButtonPaddingCalcValueStorage& calcValueStorage)
{
    if (jsValue->IsObject(vm)) {
        CalcDimension top(0.0, DimensionUnit::VP);
        CalcDimension bottom(0.0, DimensionUnit::VP);
        CalcDimension start(0.0, DimensionUnit::VP);
        CalcDimension end(0.0, DimensionUnit::VP);
        auto jsObj = jsValue->ToObject(vm);
        if (HasProperty(vm, jsObj, "top") || HasProperty(vm, jsObj, "bottom") || HasProperty(vm, jsObj, "left") ||
            HasProperty(vm, jsObj, "right")) {
            ArkTSUtils::ParseJsDimensionVp(vm, GetProperty(vm, jsObj, "top"), top, false);
            ArkTSUtils::ParseJsDimensionVp(vm, GetProperty(vm, jsObj, "bottom"), bottom, false);
            ArkTSUtils::ParseJsDimensionVp(vm, GetProperty(vm, jsObj, "left"), start, false);
            ArkTSUtils::ParseJsDimensionVp(vm, GetProperty(vm, jsObj, "right"), end, false);
        }
        SetButtonPaddingValue(padding.top, top, &calcValueStorage[BUTTON_PADDING_TOP_INDEX]);
        SetButtonPaddingValue(padding.bottom, bottom, &calcValueStorage[BUTTON_PADDING_BOTTOM_INDEX]);
        SetButtonPaddingValue(padding.start, start, &calcValueStorage[BUTTON_PADDING_START_INDEX]);
        SetButtonPaddingValue(padding.end, end, &calcValueStorage[BUTTON_PADDING_END_INDEX]);
        return true;
    }

    CalcDimension edgeValue;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, edgeValue, false)) {
        return false;
    }
    SetButtonPaddingValue(padding.top, edgeValue, &calcValueStorage[BUTTON_PADDING_TOP_INDEX]);
    SetButtonPaddingValue(padding.bottom, edgeValue, &calcValueStorage[BUTTON_PADDING_BOTTOM_INDEX]);
    SetButtonPaddingValue(padding.start, edgeValue, &calcValueStorage[BUTTON_PADDING_START_INDEX]);
    SetButtonPaddingValue(padding.end, edgeValue, &calcValueStorage[BUTTON_PADDING_END_INDEX]);
    return true;
}

void SetButtonPaddingOptionalValue(ArkUISizeType& value, const std::optional<CalcDimension>& dimension,
    std::string* calcValueStorage)
{
    if (!dimension.has_value()) {
        return;
    }
    auto paddingValue = dimension.value();
    if (!paddingValue.IsNonNegative()) {
        paddingValue = CalcDimension(0.0, DimensionUnit::VP);
    }
    SetButtonPaddingValue(value, paddingValue, calcValueStorage);
}

void GetButtonNewPadding(EcmaVM* vm, const Local<JSValueRef>& jsValue, ArkUIPaddingType& padding,
    ButtonPaddingCalcValueStorage& calcValueStorage)
{
    SetDefaultButtonPadding(padding, calcValueStorage);
    if (jsValue->IsObject(vm)) {
        CommonCalcDimension commonCalcDimension;
        auto paddingObj = jsValue->ToObject(vm);
        ArkTSUtils::ParseCommonMarginOrPaddingCorner(vm, paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = {};
            SetButtonPaddingOptionalValue(
                padding.top, commonCalcDimension.top, &calcValueStorage[BUTTON_PADDING_TOP_INDEX]);
            SetButtonPaddingOptionalValue(
                padding.bottom, commonCalcDimension.bottom, &calcValueStorage[BUTTON_PADDING_BOTTOM_INDEX]);
            SetButtonPaddingOptionalValue(
                padding.start, commonCalcDimension.left, &calcValueStorage[BUTTON_PADDING_START_INDEX]);
            SetButtonPaddingOptionalValue(
                padding.end, commonCalcDimension.right, &calcValueStorage[BUTTON_PADDING_END_INDEX]);
            return;
        }
    }

    CalcDimension edgeValue(-1.0, DimensionUnit::VP);
    ArkTSUtils::ParseJsDimensionVp(vm, jsValue, edgeValue, false);
    if (edgeValue.IsNonNegative()) {
        SetButtonPaddingValue(padding.top, edgeValue, &calcValueStorage[BUTTON_PADDING_TOP_INDEX]);
        SetButtonPaddingValue(padding.bottom, edgeValue, &calcValueStorage[BUTTON_PADDING_BOTTOM_INDEX]);
        SetButtonPaddingValue(padding.start, edgeValue, &calcValueStorage[BUTTON_PADDING_START_INDEX]);
        SetButtonPaddingValue(padding.end, edgeValue, &calcValueStorage[BUTTON_PADDING_END_INDEX]);
    }
}

void ParseButtonRole(EcmaVM* vm, const Local<panda::ObjectRef>& optionObj, CreateWithPara& para)
{
    if (HasProperty(vm, optionObj, "role")) {
        para.buttonRole = ButtonRole::NORMAL;
    }
    auto roleValue = GetProperty(vm, optionObj, "role");
    if (roleValue->IsNumber()) {
        auto buttonRoleIntValue = roleValue->Int32Value(vm);
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            para.buttonRole = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
}

void ParseCreatePara(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, bool hasLabel, CreateWithPara& para,
    RefPtr<ResourceObject>& labelResObj)
{
    para.parseSuccess = false;
    para.optionSetFirst = false;
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber < 1) {
        para.label = "";
        return;
    }

    uint32_t optionIndex = 0;
    if (hasLabel) {
        auto labelArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
        std::string label;
        para.parseSuccess = ArkTSUtils::ParseJsString(vm, labelArg, label, labelResObj);
        if (para.parseSuccess.value_or(false) && (labelArg->IsString(vm) || IsStringResource(labelArg, vm))) {
            optionIndex++;
        }
        para.label = label;
    }

    if (optionIndex >= argsNumber) {
        return;
    }

    auto optionArg = runtimeCallInfo->GetCallArgRef(optionIndex);
    if (!optionArg->IsObject(vm)) {
        return;
    }

    if (optionIndex == 0) {
        para.optionSetFirst = true;
    }

    auto optionObj = optionArg->ToObject(vm);
    auto typeValue = GetProperty(vm, optionObj, "type");
    if (typeValue->IsNumber()) {
        para.type = static_cast<ButtonType>(typeValue->Int32Value(vm));
    }

    auto stateEffectValue = GetProperty(vm, optionObj, "stateEffect");
    if (stateEffectValue->IsBoolean()) {
        para.stateEffect = stateEffectValue->ToBoolean(vm)->Value();
    }

    if (HasProperty(vm, optionObj, "buttonStyle")) {
        para.buttonStyleMode = ButtonStyleMode::EMPHASIZE;
    }
    auto buttonStyleValue = GetProperty(vm, optionObj, "buttonStyle");
    if (buttonStyleValue->IsNumber()) {
        auto styleModeIntValue = buttonStyleValue->Int32Value(vm);
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            para.buttonStyleMode = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }

    if (HasProperty(vm, optionObj, "controlSize")) {
        para.controlSize = ControlSize::NORMAL;
    }
    auto controlSizeValue = GetProperty(vm, optionObj, "controlSize");
    if (controlSizeValue->IsNumber()) {
        auto controlSizeIntValue = controlSizeValue->Int32Value(vm);
        if (controlSizeIntValue >= static_cast<int32_t>(ControlSize::SMALL) &&
            controlSizeIntValue <= static_cast<int32_t>(ControlSize::NORMAL)) {
            para.controlSize = static_cast<ControlSize>(controlSizeIntValue);
        }
    }

    ParseButtonRole(vm, optionObj, para);
}

const ArkUIButtonModifier* GetSafeButtonModifier()
{
    auto* nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, nullptr);
    CHECK_NULL_RETURN(nodeModifiers->getButtonModifier, nullptr);
    auto* buttonModifier = nodeModifiers->getButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, nullptr);
    return buttonModifier;
}

bool CreateButtonNode(CreateWithPara& para, const RefPtr<ResourceObject>& labelResObj, bool hasLabel)
{
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, false);

    if (hasLabel) {
        std::list<RefPtr<Component>> buttonChildren;
        buttonModifier->createButtonWithLabel(&para, &buttonChildren);
        buttonModifier->createButton(&para, &buttonChildren);
        if (SystemProperties::ConfigChangePerform()) {
            buttonModifier->createButtonStringResourceObj(nullptr,
                AceType::RawPtr(labelResObj), static_cast<int32_t>(ButtonStringType::LABEL));
        }
    } else {
        buttonModifier->createButtonWithChild(&para);
    }

    g_isLabelButton = hasLabel;
    auto buttonRole = para.buttonRole.value_or(ButtonRole::NORMAL);
    auto buttonStyleMode = para.buttonStyleMode.value_or(ButtonStyleMode::EMPHASIZE);
    Framework::JSButtonTheme::ApplyTheme(buttonRole, buttonStyleMode, g_isLabelButton);
    buttonModifier->setCreateWithLabel(nullptr, hasLabel);
    return true;
}

ArkUINativeModuleValue CreateButtonInternal(ArkUIRuntimeCallInfo* runtimeCallInfo, bool hasLabel)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    CreateWithPara para;
    RefPtr<ResourceObject> labelResObj;
    ParseCreatePara(vm, runtimeCallInfo, hasLabel, para, labelResObj);

    CreateButtonNode(para, labelResObj, hasLabel);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace

panda::Local<panda::JSValueRef> JsButtonClickCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != CALL_ARG_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!firstArg->IsNumber() || !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double xPos = firstArg->ToNumber(vm)->Value();
    double yPos = secondArg->ToNumber(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < CALL_ARG_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ButtonModelNG::TriggerClick(frameNode, xPos, yPos);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < 1) {
        return CreateButtonInternal(runtimeCallInfo, false);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    if (firstArg->IsString(vm) || IsStringResource(firstArg, vm)) {
        return CreateButtonInternal(runtimeCallInfo, true);
    }
    return CreateButtonInternal(runtimeCallInfo, false);
}

ArkUINativeModuleValue ButtonBridge::CreateWithLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return CreateButtonInternal(runtimeCallInfo, true);
}

ArkUINativeModuleValue ButtonBridge::CreateWithChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return CreateButtonInternal(runtimeCallInfo, false);
}

ArkUINativeModuleValue ButtonBridge::SetCreateWithLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    bool createWithLabel = false;
    if (secondArg->IsBoolean()) {
        createWithLabel = secondArg->ToBoolean(vm)->Value();
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setCreateWithLabel(nativeNode, createWithLabel);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    std::string value;
    ArkTSUtils::ParseJsString(vm, secondArg, value);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonLabelWithCheck(nativeNode, value.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonLabelWithCheck(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> stateEffectArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> buttonStyleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> controlSizeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);
    Local<JSValueRef> roleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    int32_t type = DEFAULT_BUTTON_TYPE;
    if (typeArg->IsNumber()) {
        type = typeArg->Int32Value(vm);
    }
    bool stateEffect = DEFAULT_STATE_EFFECT;
    if (stateEffectArg->IsBoolean()) {
        stateEffect = stateEffectArg->ToBoolean(vm)->Value();
    }
    uint32_t controlSize = DEFAULT_CONTROL_SIZE;
    if (controlSizeArg->IsNumber()) {
        controlSize = controlSizeArg->Uint32Value(vm);
    }
    uint32_t buttonStyle = DEFAULT_STYLE;
    if (buttonStyleArg->IsNumber()) {
        buttonStyle = buttonStyleArg->Uint32Value(vm);
    }
    uint32_t buttonRole = DEFAULT_ROLE;
    if (roleArg->IsNumber()) {
        buttonRole = roleArg->Uint32Value(vm);
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonType(nativeNode, type);
    buttonModifier->setButtonStateEffect(nativeNode, stateEffect);
    buttonModifier->setButtonControlSize(nativeNode, controlSize);
    buttonModifier->setButtonStyle(nativeNode, buttonStyle);
    buttonModifier->setButtonRole(nativeNode, buttonRole);
    buttonModifier->setButtonOptions(nativeNode, buttonStyle, buttonRole);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    int type = 0;
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        type = static_cast<int>(ButtonType::CAPSULE);
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            type = static_cast<int>(ButtonType::ROUNDED_RECTANGLE);
        }
        if (secondArg->IsNumber()) {
            type = secondArg->Int32Value(vm);
        }
    } else {
        type = secondArg->Int32Value(vm);
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonType(nativeNode, type);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        bool stateEffect = secondArg->ToBoolean(vm)->Value();
        buttonModifier->setButtonStateEffect(nativeNode, stateEffect);
    } else {
        buttonModifier->resetButtonStateEffect(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonStateEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsFontColor(runtimeCallInfo);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsColorAlphaForMaterial(vm, secondArg, color, colorResObj, nodeInfo)) {
        buttonModifier->resetButtonFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        buttonModifier->setButtonFontColorUseColorPtr(
            nativeNode, reinterpret_cast<ArkUI_InnerColor*>(&color), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Ace::CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize);
    } else {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, panda::NativePointerRef::New(vm, nullptr));
        fontSize = buttonTheme->GetTextStyle().GetFontSize();
    }
    int fontSizeUnit = static_cast<int>(fontSize.Unit());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        buttonModifier->setJsButtonFontSize(nativeNode, fontSize.Value(), fontSizeUnit);
    } else {
        buttonModifier->setButtonFontSize(nativeNode, fontSize.Value(), fontSizeUnit);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    if (ArkTSUtils::IsJsView(firstArg, vm) && (fontWeightArg->IsNull() || fontWeightArg->IsUndefined())) {
        fontWeight = DEFAULT_JS_FONT_WEIGHT;
    }
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString(vm)) {
            fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
        }
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonFontWeight(nativeNode, fontWeight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    int fontStyle = secondArg->Int32Value(vm);
    const std::vector<FontStyle> fontStyles = { FontStyle::NORMAL, FontStyle::ITALIC };
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (fontStyle < 0 || fontStyle >= static_cast<int32_t>(fontStyles.size())) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonFontStyle(nativeNode, fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    std::string fontFamily;
    RefPtr<ResourceObject> familiesResObj;
    auto result = ArkTSUtils::ParseJsFontFamiliesToString(vm, secondArg, fontFamily, familiesResObj);
    if (!ArkTSUtils::IsJsView(firstArg, vm) && !result) {
        buttonModifier->resetButtonFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (ArkTSUtils::IsJsView(firstArg, vm) && (!result || fontFamily.empty())) {
        auto textTheme = ArkTSUtils::GetTheme<TextTheme>();
        CHECK_NULL_RETURN(textTheme, panda::JSValueRef::Undefined(vm));
        std::vector<std::string> defaultFontFamilies = textTheme->GetTextStyle().GetFontFamilies();
        for (uint32_t i = 0; i < defaultFontFamilies.size(); i++) {
            fontFamily += defaultFontFamilies.at(i);
            if (i != defaultFontFamilies.size() - 1) {
                fontFamily += ",";
            }
        }
    }
    auto familiesRawPtr = AceType::RawPtr(familiesResObj);
    buttonModifier->setButtonFontFamilyPtr(nativeNode, fontFamily.c_str(), familiesRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsBackgroundColor(runtimeCallInfo);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        buttonModifier->resetButtonBackgroundColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        buttonModifier->setButtonBackgroundColorWithColorSpacePtr(
            nativeNode, color.GetValue(), color.GetColorSpace(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ButtonBridge::PushValuesVector(const std::optional<int32_t>& value, std::vector<int32_t>& valuesVector)
{
    valuesVector.push_back(static_cast<int32_t>(value.has_value()));
    if (value.has_value()) {
        valuesVector.push_back(static_cast<int32_t>(value.value()));
    } else {
        valuesVector.push_back(0);
    }
}

void ButtonBridge::PutButtonValuesParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<int32_t>& valuesVector)
{
    std::optional<int32_t> overflowOptional = std::nullopt;
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!overflowArg->IsNull() && overflowArg->IsNumber()) {
        auto overflow = overflowArg->Int32Value(vm);
        if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            overflowOptional = overflow;
        }
    }
    PushValuesVector(overflowOptional, valuesVector);

    std::optional<int32_t> maxLinesOptional = std::nullopt;
    Local<JSValueRef> maxLinesArg = runtimeCallInfo->GetCallArgRef(MAX_LINES_ARG_2);
    if (!maxLinesArg->IsNull() && maxLinesArg->IsNumber()) {
        auto maxLines = maxLinesArg->Int32Value(vm);
        maxLinesOptional = Positive(maxLines) ? maxLines : 1;
    }
    PushValuesVector(maxLinesOptional, valuesVector);

    std::optional<int32_t> adaptHeightOptional = std::nullopt;
    Local<JSValueRef> adaptHeightArg = runtimeCallInfo->GetCallArgRef(ADAPT_HEIGHT_ARG_5);
    if (!adaptHeightArg->IsNull() && adaptHeightArg->IsNumber()) {
        auto adaptHeight = adaptHeightArg->Int32Value(vm);
        if (adaptHeight >= 0 && adaptHeight < static_cast<double>(HEIGHT_ADAPTIVE_POLICY.size())) {
            adaptHeightOptional = adaptHeight;
        }
    }
    PushValuesVector(adaptHeightOptional, valuesVector);

    std::optional<int32_t> fontStyleOptional = std::nullopt;
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_8);
    if (!fontStyleArg->IsNull() && fontStyleArg->IsNumber()) {
        auto fontStyle = fontStyleArg->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            fontStyleOptional = fontStyle;
        }
    }
    PushValuesVector(fontStyleOptional, valuesVector);

    std::optional<int32_t> textAlignOptional = std::nullopt;
    Local<JSValueRef> textAlignArg = runtimeCallInfo->GetCallArgRef(TEXT_ALIGN_ARG_10);
    if (!textAlignArg->IsNull() && textAlignArg->IsNumber()) {
        auto textAlign = textAlignArg->Int32Value(vm);
        if (textAlign >= 0 && textAlign < static_cast<int32_t>(TEXT_ALIGNS.size())) {
            textAlignOptional = textAlign;
        }
    }
    PushValuesVector(textAlignOptional, valuesVector);
}

void ButtonBridge::PushDimensionVector(const std::optional<Dimension>& valueDim, std::vector<ArkUI_Float32>& dimensions)
{
    dimensions.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        dimensions.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        dimensions.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        dimensions.push_back(0);
        dimensions.push_back(0);
    }
}

void ButtonBridge::PushButtonDimension(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizesVector, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    std::optional<CalcDimension> dimensionOptional = std::nullopt;
    CalcDimension parsedDimension;
    if (ArkTSUtils::ParseJsDimensionFp(vm, arg, parsedDimension, false)) {
        dimensionOptional = parsedDimension;
    }
    PushDimensionVector(dimensionOptional, fontSizesVector);
}

void ButtonBridge::PutButtonDimensionParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& fontSizesVector)
{
    std::vector<int32_t> indexVector = { MIN_FONT_SIZE_ARG_3, MAX_FONT_SIZE_ARG_4, FONT_SIZE_ARG_6 };
    for (size_t index = 0; index < indexVector.size(); index++) {
        PushButtonDimension(runtimeCallInfo, vm, fontSizesVector, indexVector[index]);
    }
}

ArkUINativeModuleValue ButtonBridge::SetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsLabelStyle(runtimeCallInfo);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::vector<ArkUI_Int32> valuesVector;
    PutButtonValuesParameters(runtimeCallInfo, vm, valuesVector);
    std::vector<ArkUI_Float32> fontSizesVector;
    PutButtonDimensionParameters(runtimeCallInfo, vm, fontSizesVector);
    std::vector<ArkUI_CharPtr> stringParameters;
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_7);
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString(vm)) {
            fontWeight = fontWeightArg->ToString(vm)->ToString(vm);
        }
    }
    stringParameters.push_back(fontWeight.c_str());

    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_9);
    std::string strFontFamilies;
    RefPtr<ResourceObject> fontFamiliesResObj;
    if (ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, strFontFamilies, fontFamiliesResObj)) {
        stringParameters.push_back(strFontFamilies.c_str());
    } else {
        strFontFamilies = NONE_FONT_FAMILY;
        stringParameters.push_back(strFontFamilies.c_str());
    }
    std::vector<ArkUI_Uint32> dataCountVector;
    dataCountVector.push_back(stringParameters.size());
    dataCountVector.push_back(valuesVector.size());
    dataCountVector.push_back(fontSizesVector.size());

    ArkUIButtonSizeStruct sizeResObj;
    auto maxFontSizeResObj = ParseFontSizeResObj(runtimeCallInfo, vm, MAX_FONT_SIZE_ARG_4);
    sizeResObj.maxFontSize = AceType::RawPtr(maxFontSizeResObj);
    auto minFontSizeResObj = ParseFontSizeResObj(runtimeCallInfo, vm, MIN_FONT_SIZE_ARG_3);
    sizeResObj.minFontSize = AceType::RawPtr(minFontSizeResObj);

    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonLabelStylePtr(nativeNode, stringParameters.data(), valuesVector.data(),
        fontSizesVector.data(), dataCountVector.data(), sizeResObj);
    return panda::JSValueRef::Undefined(vm);
}

RefPtr<ResourceObject> ButtonBridge::ParseFontSizeResObj(ArkUIRuntimeCallInfo* runtimeCallInfo,
    EcmaVM* vm, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    CalcDimension parsedDimension;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsDimensionFp(vm, arg, parsedDimension, resObj, false);
    return resObj;
}

ArkUINativeModuleValue ButtonBridge::ResetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonLabelStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseBorderRadius(EcmaVM* vm, const Local<JSValueRef>& args, std::optional<CalcDimension>& optionalDimension)
{
    CalcDimension valueDim;
    if (!args->IsUndefined() && ArkTSUtils::ParseJsDimensionVp(vm, args, valueDim, false)) {
        optionalDimension = valueDim;
    }
}

void PushBorderRadiusVector(const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32> &options)
{
    options.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        options.push_back(0);
        options.push_back(0);
    }
}

ArkUINativeModuleValue ButtonBridge::SetButtonBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsBorderRadius(runtimeCallInfo);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);

    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        buttonModifier->resetButtonBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;

    ParseBorderRadius(vm, topLeftArgs, radiusTopLeft);
    ParseBorderRadius(vm, topRightArgs, radiusTopRight);
    ParseBorderRadius(vm, bottomLeftArgs, radiusBottomLeft);
    ParseBorderRadius(vm, bottomRightArgs, radiusBottomRight);

    std::vector<ArkUI_Float32> options;
    PushBorderRadiusVector(radiusTopLeft, options);
    PushBorderRadiusVector(radiusTopRight, options);
    PushBorderRadiusVector(radiusBottomLeft, options);
    PushBorderRadiusVector(radiusBottomRight, options);

    buttonModifier->setButtonBorderRadius(nativeNode, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::SetBorder(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(9);      // 9:topLeft value
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(10);    // 10:topRight value
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(11);  // 11:bottomLeft value
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(12); // 12:bottomRight value
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getButtonModifier()->resetButtonBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;

    ParseBorderRadius(vm, topLeftArgs, radiusTopLeft);
    ParseBorderRadius(vm, topRightArgs, radiusTopRight);
    ParseBorderRadius(vm, bottomLeftArgs, radiusBottomLeft);
    ParseBorderRadius(vm, bottomRightArgs, radiusBottomRight);

    std::vector<ArkUI_Float32> options;
    PushBorderRadiusVector(radiusTopLeft, options);
    PushBorderRadiusVector(radiusTopRight, options);
    PushBorderRadiusVector(radiusBottomLeft, options);
    PushBorderRadiusVector(radiusBottomRight, options);

    GetArkUINodeModifiers()->getButtonModifier()->setButtonBorderRadius(nativeNode, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> widthArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> heightArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    CalcDimension width;
    std::string widthStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, widthArgs, width)) {
        widthStr = "undefined";
    } else {
        ArkTSUtils::ParseJsDimensionVp(vm, widthArgs, width);
        widthStr = std::to_string(width.Value());
    }
    CalcDimension height;
    std::string heightStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, heightArgs, height)) {
        heightStr = "undefined";
    } else {
        heightStr = std::to_string(height.Value());
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonSize(nativeNode, widthStr.c_str(), static_cast<int32_t>(width.Unit()),
        heightStr.c_str(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonRole(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsRole(runtimeCallInfo);
    }
    Local<JSValueRef> buttonRoleArgs = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (buttonRoleArgs->IsUndefined() || buttonRoleArgs->IsNull() || !buttonRoleArgs->IsNumber()) {
        buttonModifier->resetButtonRole(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t buttonRole = buttonRoleArgs->Uint32Value(vm);
    buttonModifier->setButtonRole(nativeNode, buttonRole);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonRole(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonRole(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return JsButtonStyle(runtimeCallInfo);
    }
    Local<JSValueRef> buttonStyleArgs = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (buttonStyleArgs->IsUndefined() || buttonStyleArgs->IsNull() || !buttonStyleArgs->IsNumber()) {
        buttonModifier->resetButtonStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t buttonStyle = buttonStyleArgs->Uint32Value(vm);
    buttonModifier->setButtonStyle(nativeNode, buttonStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> controlSizeArgs = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    if (controlSizeArgs->IsUndefined() || controlSizeArgs->IsNull()) {
        CHECK_NULL_RETURN(buttonModifier->resetButtonControlSize, panda::JSValueRef::Undefined(vm));
        buttonModifier->resetButtonControlSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t controlSize = controlSizeArgs->Uint32Value(vm);
    CHECK_NULL_RETURN(buttonModifier->setButtonControlSize, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonControlSize(nativeNode, controlSize);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonControlSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonControlSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        ButtonModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    ButtonModelNG::SetBuilderFunc(frameNode, [vm, frameNode, obj = std::move(obj), containerId](
            ButtonConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            auto context = ArkTSUtils::GetContext(vm);
            const char* keyOfButton[] = { "label", "pressed", "enabled", "triggerClick" };
            Local<JSValueRef> valuesOfButton[] = { panda::StringRef::NewFromUtf8(vm, config.label_.c_str()),
                panda::BooleanRef::New(vm, config.pressed_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsButtonClickCallback) };
            auto button = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keyOfButton),
                keyOfButton, valuesOfButton);
            button->SetNativePointerFieldCount(vm, 1);
            button->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[CALL_ARG_2] = { context, button };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, CALL_ARG_2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, BUTTON_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));

    RefPtr<ResourceObject> doubleResObj;
    double minFontScale = 0.0;
    bool hasValue = false;
    if (runtimeCallInfo->GetArgsNumber() >= CALL_ARG_2) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
        hasValue = ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale, doubleResObj);
    }
    if (!isJsView && !hasValue) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (hasValue) {
        if (LessOrEqual(minFontScale, 0.0f)) {
            minFontScale = 0.0f;
        } else if (GreatOrEqual(minFontScale, 1.0f)) {
            minFontScale = 1.0f;
        }
    }
    CHECK_NULL_RETURN(buttonModifier->setButtonMinFontScalePtr, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonMinFontScalePtr(
        nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(doubleResObj), hasValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));

    double maxFontScale = 0.0;
    RefPtr<ResourceObject> doubleResObj;
    bool hasValue = false;
    if (runtimeCallInfo->GetArgsNumber() >= CALL_ARG_2) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
        hasValue = ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, doubleResObj);
    }
    if (!isJsView && !hasValue) {
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, firstArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (hasValue && LessOrEqual(maxFontScale, 1.0f)) {
        maxFontScale = 1.0f;
    }
    CHECK_NULL_RETURN(buttonModifier->setButtonMaxFontScalePtr, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonMaxFontScalePtr(
        nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(doubleResObj), hasValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->resetButtonMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CalcDimension width;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, width, false) || LessNotEqual(width.Value(), 0.0)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(buttonModifier->setJsButtonWidth, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonWidth(nullptr, width.Value(), static_cast<int32_t>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CalcDimension height;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, height, false) || LessNotEqual(height.Value(), 0.0)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(buttonModifier->setJsButtonHeight, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonHeight(nullptr, height.Value(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsUndefined() && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NE_RETURN(secondArg->IsFunction(vm), true, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
    std::function<void(GestureEvent&)> onTap = [node = AceType::WeakClaim(frameNode),
                                                   func = panda::CopyableGlobal(vm, func)](GestureEvent& info) {
        auto vm = func.GetEcmaVM();
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("onClick");
        OHOS::Ace::PipelineContext::SetCallBackNode(node);
        auto infoPtr = new GestureEvent(info);
        auto eventObj = FrameNodeBridge::CreateGestureEventInfo(const_cast<EcmaVM*>(vm), infoPtr);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        CommonBridge::ReportClickEvent(node);
#endif
    };

    std::function<void(const ClickInfo*)> onClick = [node = AceType::WeakClaim(frameNode),
                                                        func = panda::CopyableGlobal(vm, func)](const ClickInfo* info) {
        auto vm = func.GetEcmaVM();
        CHECK_NULL_VOID(info);
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("onClick");
        OHOS::Ace::PipelineContext::SetCallBackNode(node);
        auto eventObj = FrameNodeBridge::CreateClickEventInfo(const_cast<EcmaVM*>(vm), info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        CommonBridge::ReportClickEvent(node);
#endif
    };
    double distanceThreshold = std::numeric_limits<double>::infinity();
    if (runtimeCallInfo->GetArgsNumber() > CALL_ARG_2) {
        auto thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
        if (thirdArg->IsNumber()) {
            distanceThreshold = thirdArg->ToNumber(vm)->Value();
        }
        distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
    }
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonOnClick(
        nullptr, reinterpret_cast<void*>(&onTap), reinterpret_cast<void*>(&onClick), distanceThreshold);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonRemoteMessage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    RemoteCallback remoteCallback;
    ArkTSUtils::JsRemoteMessage(vm, secondArg, remoteCallback);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(buttonModifier->setJsButtonRemoteMessage, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonRemoteMessage(nullptr, reinterpret_cast<void*>(&remoteCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonAspectRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    double aspectRatio = 0.0;
    CHECK_NE_RETURN(ArkTSUtils::ParseJsDouble(vm, secondArg, aspectRatio), true, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(buttonModifier->setJsButtonAspectRatio, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonAspectRatio(nullptr, aspectRatio);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonPadding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> paddingArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    ArkUIPaddingType oldPaddings = {};
    ButtonPaddingCalcValueStorage oldPaddingCalcValueStorage;
    bool hasOldPadding = GetButtonOldPadding(vm, paddingArg, oldPaddings, oldPaddingCalcValueStorage);
    ArkUIPaddingType newPaddings = {};
    ButtonPaddingCalcValueStorage newPaddingCalcValueStorage;
    GetButtonNewPadding(vm, paddingArg, newPaddings, newPaddingCalcValueStorage);
    CHECK_NULL_RETURN(buttonModifier->setJsButtonPadding, panda::JSValueRef::Undefined(vm));
    buttonModifier->setJsButtonPadding(nullptr, hasOldPadding ? &oldPaddings : nullptr, &newPaddings);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!styleArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    auto styleObj = styleArg->ToObject(vm);
    ButtonParameters buttonParameters;

    auto overflowValue = GetProperty(vm, styleObj, "overflow");
    buttonParameters.textOverflow = TextOverflow::ELLIPSIS;
    if (!overflowValue->IsNull() && overflowValue->IsNumber()) {
        auto overflow = overflowValue->Int32Value(vm);
        if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            buttonParameters.textOverflow = TEXT_OVERFLOWS[overflow];
        }
    }

    auto maxLinesValue = GetProperty(vm, styleObj, "maxLines");
    if (!maxLinesValue->IsNull() && maxLinesValue->IsNumber()) {
        auto maxLines = maxLinesValue->Int32Value(vm);
        buttonParameters.maxLines = Positive(maxLines) ? static_cast<uint32_t>(maxLines) : 1;
    }

    auto minFontSizeValue = GetProperty(vm, styleObj, "minFontSize");
    CalcDimension minFontSize;
    RefPtr<ResourceObject> minFontSizeResObj;
    if (ArkTSUtils::ParseJsDimensionFpNG(vm, minFontSizeValue, minFontSize, minFontSizeResObj, false)) {
        buttonParameters.minFontSize = minFontSize;
    }

    auto maxFontSizeValue = GetProperty(vm, styleObj, "maxFontSize");
    CalcDimension maxFontSize;
    RefPtr<ResourceObject> maxFontSizeResObj;
    if (ArkTSUtils::ParseJsDimensionFpNG(vm, maxFontSizeValue, maxFontSize, maxFontSizeResObj, false)) {
        buttonParameters.maxFontSize = maxFontSize;
    }

    auto adaptHeightValue = GetProperty(vm, styleObj, "heightAdaptivePolicy");
    if (!adaptHeightValue->IsNull() && adaptHeightValue->IsNumber()) {
        auto adaptHeight = adaptHeightValue->Int32Value(vm);
        if (adaptHeight >= 0 && adaptHeight < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
            buttonParameters.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICY[adaptHeight];
        }
    }

    ParseJsViewFont(vm, GetProperty(vm, styleObj, "font"), buttonParameters);
    if (!ParseJsViewTextAlign(vm, GetProperty(vm, styleObj, "textAlign"), buttonParameters)) {
        buttonModifier->resetButtonTextAlign(nullptr);
    }

    CompleteJsViewLabelStyle(buttonParameters);
    buttonModifier->setJsButtonLabelStylePtr(nullptr, &buttonParameters);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    bool colorFlag = ArkTSUtils::ParseJsColor(vm, secondArg, color, colorResObj);
    if (!colorFlag) {
        auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(node, panda::JSValueRef::Undefined(vm));
        auto buttonTheme = node->GetTheme<ButtonTheme>(true);
        if (buttonTheme) {
            color = buttonTheme->GetBgColor();
        }
    }
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    buttonModifier->setJsButtonBackgroundColorPtr(
        nullptr, reinterpret_cast<ArkUI_InnerColor*>(&color), colorRawPtr, colorFlag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    ArkTSUtils::SetButtonBorderRadiusByJs(vm, nativeNode, arg);
    ArkTSUtils::SetRenderStrategy(runtimeCallInfo, CALL_ARG_3);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!arg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto borderObj = arg->ToObject(vm);
    auto radius = GetProperty(vm, borderObj, "radius");
    ArkUINodeHandle nativeNode = nullptr;
    ArkTSUtils::SetButtonBorderRadiusByJs(vm, nativeNode, radius);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsButtonStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto buttonStyleMode = ButtonStyleMode::EMPHASIZE;
    if (secondArg->IsNumber()) {
        auto styleValue = secondArg->Int32Value(vm);
        if (styleValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonStyleMode = static_cast<ButtonStyleMode>(styleValue);
        }
    }
    if (Framework::JSButtonTheme::ApplyTheme(buttonStyleMode, g_isLabelButton)) {
        CHECK_NULL_RETURN(buttonModifier->setButtonStyleOnly, panda::JSValueRef::Undefined(vm));
        buttonModifier->setButtonStyleOnly(nullptr, static_cast<uint32_t>(buttonStyleMode));
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(buttonModifier->setButtonStyle, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonStyle(nullptr, static_cast<uint32_t>(buttonStyleMode));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsRole(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto buttonRole = ButtonRole::NORMAL;
    if (secondArg->IsNumber()) {
        auto roleValue = secondArg->Int32Value(vm);
        if (roleValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            roleValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonRole = static_cast<ButtonRole>(roleValue);
        }
    }
    if (Framework::JSButtonTheme::ApplyTheme(buttonRole, g_isLabelButton)) {
        CHECK_NULL_RETURN(buttonModifier->setButtonRoleOnly, panda::JSValueRef::Undefined(vm));
        buttonModifier->setButtonRoleOnly(nullptr, static_cast<uint32_t>(buttonRole));
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(buttonModifier->setButtonRole, panda::JSValueRef::Undefined(vm));
    buttonModifier->setButtonRole(nullptr, static_cast<uint32_t>(buttonRole));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::JsFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto* buttonModifier = GetSafeButtonModifier();
    CHECK_NULL_RETURN(buttonModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(frameNode);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlphaForMaterial(vm, secondArg, color, colorResObj, nodeInfo)) {
        auto buttonTheme = frameNode->GetTheme<ButtonTheme>(true);
        if (buttonTheme) {
            color = buttonTheme->GetTextStyle().GetTextColor();
        }
    }

    auto colorRawPtr = AceType::RawPtr(colorResObj);
    buttonModifier->setJsButtonFontColorUseColorPtr(
        nativeNode, reinterpret_cast<ArkUI_InnerColor*>(&color), colorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

void ButtonBridge::RegisterButtonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "createWithLabel",
        "createWithChild",
        "setCreateWithLabel",
        "setLabel",
        "resetLabel",
        "setOptions",
        "resetOptions",
        "setType",
        "resetType",
        "setStateEffect",
        "resetStateEffect",
        "setFontColor",
        "resetFontColor",
        "setFontSize",
        "resetFontSize",
        "setFontWeight",
        "resetFontWeight",
        "setFontStyle",
        "resetFontStyle",
        "setFontFamily",
        "resetFontFamily",
        "setLabelStyle",
        "resetLabelStyle",
        "setBackgroundColor",
        "resetBackgroundColor",
        "setButtonBorderRadius",
        "resetButtonBorderRadius",
        "setButtonBorder",
        "resetButtonBorder",
        "setButtonSize",
        "resetButtonSize",
        "setButtonRole",
        "resetButtonRole",
        "setButtonStyle",
        "resetButtonStyle",
        "setButtonControlSize",
        "setContentModifierBuilder",
        "resetButtonControlSize",
        "setMinFontScale",
        "resetMinFontScale",
        "setMaxFontScale",
        "resetMaxFontScale",
        "setWidth",
        "setHeight",
        "setOnClick",
        "setRemoteMessage",
        "setAspectRatio",
        "setPadding",
        "setJsButtonBorder",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::CreateWithLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::CreateWithChild),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetCreateWithLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetStateEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetStateEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetFontStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetFontFamily),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetLabelStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetLabelStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonBorder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonRole),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonRole),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonControlSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonControlSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetMinFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetMaxFontScale),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonOnClick),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonRemoteMessage),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonAspectRatio),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonPadding),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::JsBorder),
    };
    auto button = panda::ObjectRef::NewWithNamedProperties(
        vm, sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "button"), button);
}

} // namespace OHOS::Ace::NG