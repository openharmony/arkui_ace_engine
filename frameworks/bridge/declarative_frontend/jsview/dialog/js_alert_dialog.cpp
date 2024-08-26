/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/declarative_frontend/jsview/dialog/js_alert_dialog.h"

#include <sstream>
#include <string>
#include <vector>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/alert_dialog_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace {
std::unique_ptr<AlertDialogModel> AlertDialogModel::instance_ = nullptr;
std::mutex AlertDialogModel::mutex_;
AlertDialogModel* AlertDialogModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::AlertDialogModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::AlertDialogModelNG());
            } else {
                instance_.reset(new Framework::AlertDialogModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<DialogButtonDirection> DIALOG_BUTTONS_DIRECTION = { DialogButtonDirection::AUTO,
    DialogButtonDirection::HORIZONTAL, DialogButtonDirection::VERTICAL };
constexpr int32_t ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM = 1;
} // namespace

void SetParseStyle(ButtonInfo& buttonInfo, const int32_t styleValue)
{
    if (styleValue >= static_cast<int32_t>(DialogButtonStyle::DEFAULT) &&
        styleValue <= static_cast<int32_t>(DialogButtonStyle::HIGHTLIGHT)) {
        buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(styleValue);
    }
}

void ParseButtonObj(const JsiExecutionContext& execContext, DialogProperties& properties, JSRef<JSVal> jsVal,
    const std::string& property, bool isPrimaryButtonValid)
{
    if (!jsVal->IsObject()) {
        return;
    }
    auto objInner = JSRef<JSObject>::Cast(jsVal);
    std::string buttonValue;
    ButtonInfo buttonInfo;
    if (JSAlertDialog::ParseJsString(objInner->GetProperty("value"), buttonValue)) {
        buttonInfo.text = buttonValue;
    }

    // Parse enabled
    auto enabledValue = objInner->GetProperty("enabled");
    if (enabledValue->IsBoolean()) {
        buttonInfo.enabled = enabledValue->ToBoolean();
    }

    // Parse defaultFocus
    auto defaultFocusValue = objInner->GetProperty("defaultFocus");
    if (defaultFocusValue->IsBoolean()) {
        buttonInfo.defaultFocus = defaultFocusValue->ToBoolean();
    }

    // Parse style
    auto style = objInner->GetProperty("style");
    if (style->IsNumber()) {
        SetParseStyle(buttonInfo, style->ToNumber<int32_t>());
    }

    Color textColor;
    if (JSAlertDialog::ParseJsColor(objInner->GetProperty("fontColor"), textColor)) {
        buttonInfo.textColor = textColor.ColorToString();
    }

    Color backgroundColor;
    if (JSAlertDialog::ParseJsColor(objInner->GetProperty("backgroundColor"), backgroundColor)) {
        buttonInfo.isBgColorSetted = true;
        buttonInfo.bgColor = backgroundColor;
    }

    auto actionValue = objInner->GetProperty("action");
    if (actionValue->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
        auto eventFunc = [execCtx = execContext, func = std::move(actionFunc), property, node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("AlertDialog.[" + property + "].onAction");
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute();
        };
        AlertDialogModel::GetInstance()->SetParseButtonObj(eventFunc, buttonInfo, properties, property);
    }

    if (!buttonInfo.defaultFocus && isPrimaryButtonValid) {
        if (strcmp(property.c_str(), "confirm") == 0 ||
        strcmp(property.c_str(), "primaryButton") == 0) {
            buttonInfo.isPrimary = true;
        } else {
            auto primaryButton = objInner->GetProperty("primary");
            if (primaryButton->IsBoolean()) {
                buttonInfo.isPrimary = primaryButton->ToBoolean();
            }
        }
    }

    if (buttonInfo.IsValid()) {
        properties.buttons.emplace_back(buttonInfo);
    }
}

void ParseButtonArray(const JsiExecutionContext& execContext, DialogProperties& properties, JSRef<JSObject> obj,
    const std::string& property)
{
    auto jsVal = obj->GetProperty(property.c_str());
    if (!jsVal->IsArray()) {
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsVal);
    size_t length = array->Length();
    if (length <= 0) {
        return;
    }
    int32_t primaryButtonNum = 0;
    bool isPrimaryButtonValid = true;
    for (size_t i = 0; i < length; i++) {
        JSRef<JSVal> buttonItem = array->GetValueAt(i);
        if (!buttonItem->IsObject()) {
            break;
        }
        auto objInner = JSRef<JSObject>::Cast(buttonItem);
        auto primaryButton = objInner->GetProperty("primary");
        if (primaryButton->IsBoolean()) {
            primaryButtonNum += (primaryButton->ToBoolean() ? ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM : 0);
        }
        if (primaryButtonNum > ALERT_DIALOG_VALID_PRIMARY_BUTTON_NUM) {
            isPrimaryButtonValid = false;
            break;
        }
    }
    for (size_t i = 0; i < length; i++) {
        JSRef<JSVal> buttonItem = array->GetValueAt(i);
        if (!buttonItem->IsObject()) {
            break;
        }
        ParseButtonObj(execContext, properties, buttonItem, property + std::to_string(i), isPrimaryButtonValid);
    }
}

void ParseButtons(const JsiExecutionContext& execContext, DialogProperties& properties, JSRef<JSObject> obj)
{
    properties.buttons.clear();
    if (obj->GetProperty("confirm")->IsObject()) {
        // Parse confirm.
        auto objInner = obj->GetProperty("confirm");
        ParseButtonObj(execContext, properties, objInner, "confirm", true);
    } else if (obj->GetProperty("buttons")->IsArray()) {
        // Parse buttons array.
        ParseButtonArray(execContext, properties, obj, "buttons");
    } else {
        // Parse primaryButton and secondaryButton.
        auto objInner = obj->GetProperty("primaryButton");
        ParseButtonObj(execContext, properties, objInner, "primaryButton", true);
        objInner = obj->GetProperty("secondaryButton");
        ParseButtonObj(execContext, properties, objInner, "secondaryButton", true);
    }

    // Parse buttons direction.
    auto directionValue = obj->GetProperty("buttonDirection");
    if (directionValue->IsNumber()) {
        auto buttonDirection = directionValue->ToNumber<int32_t>();
        if (buttonDirection >= 0 && buttonDirection <= static_cast<int32_t>(DIALOG_BUTTONS_DIRECTION.size())) {
            properties.buttonDirection = DIALOG_BUTTONS_DIRECTION[buttonDirection];
        }
    }
}

void ParseDialogTitleAndMessage(DialogProperties& properties, JSRef<JSObject> obj)
{
    // Parse title.
    auto titleValue = obj->GetProperty("title");
    std::string title;
    if (JSAlertDialog::ParseJsString(titleValue, title)) {
        properties.title = title;
    }

    // Parse subtitle.
    auto subtitleValue = obj->GetProperty("subtitle");
    std::string subtitle;
    if (JSAlertDialog::ParseJsString(subtitleValue, subtitle)) {
        properties.subtitle = subtitle;
    }

    // Parses message.
    auto messageValue = obj->GetProperty("message");
    std::string message;
    if (JSAlertDialog::ParseJsString(messageValue, message)) {
        properties.content = message;
    }
}

void ParseAlertShadow(DialogProperties& properties, JSRef<JSObject> obj)
{
    // Parse shadow.
    auto shadowValue = obj->GetProperty("shadow");
    Shadow shadow;
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && JSAlertDialog::ParseShadowProps(shadowValue, shadow)) {
        properties.shadow = shadow;
    }
}

void ParseAlertBorderWidthAndColor(DialogProperties& properties, JSRef<JSObject> obj)
{
    auto borderWidthValue = obj->GetProperty("borderWidth");
    NG::BorderWidthProperty borderWidth;
    if (JSAlertDialog::ParseBorderWidthProps(borderWidthValue, borderWidth)) {
        properties.borderWidth = borderWidth;
        auto colorValue = obj->GetProperty("borderColor");
        NG::BorderColorProperty borderColor;
        if (JSAlertDialog::ParseBorderColorProps(colorValue, borderColor)) {
            properties.borderColor = borderColor;
        } else {
            borderColor.SetColor(Color::BLACK);
            properties.borderColor = borderColor;
        }
    }
}

void ParseAlertRadius(DialogProperties& properties, JSRef<JSObject> obj)
{
    auto cornerRadiusValue = obj->GetProperty("cornerRadius");
    NG::BorderRadiusProperty radius;
    if (JSAlertDialog::ParseBorderRadius(cornerRadiusValue, radius)) {
        properties.borderRadius = radius;
    }
}

void UpdateAlertAlignment(DialogAlignment& alignment)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (alignment == DialogAlignment::TOP_START) {
        if (isRtl) {
            alignment = DialogAlignment::TOP_END;
        }
    } else if (alignment == DialogAlignment::TOP_END) {
        if (isRtl) {
            alignment = DialogAlignment::TOP_START;
        }
    } else if (alignment == DialogAlignment::CENTER_START) {
        if (isRtl) {
            alignment = DialogAlignment::CENTER_END;
        }
    } else if (alignment == DialogAlignment::CENTER_END) {
        if (isRtl) {
            alignment = DialogAlignment::CENTER_START;
        }
    } else if (alignment == DialogAlignment::BOTTOM_START) {
        if (isRtl) {
            alignment = DialogAlignment::BOTTOM_END;
        }
    } else if (alignment == DialogAlignment::BOTTOM_END) {
        if (isRtl) {
            alignment = DialogAlignment::BOTTOM_START;
        }
    }
}

void ParseAlertAlignment(DialogProperties& properties, JSRef<JSObject> obj)
{
    // Parse alignment
    auto alignmentValue = obj->GetProperty("alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber<int32_t>();
        if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            properties.alignment = DIALOG_ALIGNMENT[alignment];
            UpdateAlertAlignment(properties.alignment);
        }
    }
}

void ParseAlertOffset(DialogProperties& properties, JSRef<JSObject> obj)
{
    // Parse offset
    auto offsetValue = obj->GetProperty("offset");
    if (offsetValue->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
        CalcDimension dx;
        auto dxValue = offsetObj->GetProperty("dx");
        JSAlertDialog::ParseJsDimensionVp(dxValue, dx);
        CalcDimension dy;
        auto dyValue = offsetObj->GetProperty("dy");
        JSAlertDialog::ParseJsDimensionVp(dyValue, dy);
        properties.offset = DimensionOffset(dx, dy);
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        Dimension offsetX = isRtl ? properties.offset.GetX() * (-1) : properties.offset.GetX();
        properties.offset.SetX(offsetX);
    }
}

void ParseTextStyle(DialogProperties& properties, JSRef<JSObject> obj)
{
    auto textStyleObj = obj->GetProperty("textStyle");
    if (textStyleObj->IsNull() || !textStyleObj->IsObject()) {
        return;
    }
    auto textStyle = JSRef<JSObject>::Cast(textStyleObj);
    auto args = textStyle->GetProperty("wordBreak");
    int32_t index = 1;
    if (args->IsNumber()) {
        index = args->ToNumber<int32_t>();
    }
    if (index < 0 || index >= static_cast<int32_t>(WORD_BREAK_TYPES.size())) {
        index = 1;
    }
    properties.wordBreak = WORD_BREAK_TYPES[index];
}

void ParseAlertMaskRect(DialogProperties& properties, JSRef<JSObject> obj)
{
    // Parse maskRect.
    auto maskRectValue = obj->GetProperty("maskRect");
    DimensionRect maskRect;
    if (JSViewAbstract::ParseJsDimensionRect(maskRectValue, maskRect)) {
        properties.maskRect = maskRect;
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        auto offset = maskRect.GetOffset();
        Dimension offsetX = isRtl ? offset.GetX() * (-1) : offset.GetX();
        offset.SetX(offsetX);
        properties.maskRect->SetOffset(offset);
    }
}

void JSAlertDialog::Show(const JSCallbackInfo& args)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }

    DialogProperties properties { .type = DialogType::ALERT_DIALOG };
    if (args[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(args[0]);
        auto dialogNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto execContext = args.GetExecutionContext();

        ParseDialogTitleAndMessage(properties, obj);
        ParseButtons(execContext, properties, obj);
        ParseAlertShadow(properties, obj);
        ParseAlertBorderWidthAndColor(properties, obj);
        ParseAlertRadius(properties, obj);
        ParseAlertAlignment(properties, obj);
        ParseAlertOffset(properties, obj);
        ParseTextStyle(properties, obj);
        ParseAlertMaskRect(properties, obj);

        auto onLanguageChange = [execContext, obj, parseContent = ParseDialogTitleAndMessage,
                                    parseButton = ParseButtons, parseShadow = ParseAlertShadow,
                                    parseBorderProps = ParseAlertBorderWidthAndColor,
                                    parseRadius = ParseAlertRadius, parseAlignment = ParseAlertAlignment,
                                    parseOffset = ParseAlertOffset, parseMaskRect = ParseAlertMaskRect,
                                    node = dialogNode](DialogProperties& dialogProps) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
            ACE_SCORING_EVENT("AlertDialog.property.onLanguageChange");
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            parseContent(dialogProps, obj);
            parseButton(execContext, dialogProps, obj);
            parseShadow(dialogProps, obj);
            parseBorderProps(dialogProps, obj);
            parseRadius(dialogProps, obj);
            parseAlignment(dialogProps, obj);
            parseOffset(dialogProps, obj);
            parseMaskRect(dialogProps, obj);
        };
        properties.onLanguageChange = std::move(onLanguageChange);

        // Parses gridCount.
        auto gridCountValue = obj->GetProperty("gridCount");
        if (gridCountValue->IsNumber()) {
            properties.gridCount = gridCountValue->ToNumber<int32_t>();
        }

        // Parse auto autoCancel.
        auto autoCancelValue = obj->GetProperty("autoCancel");
        if (autoCancelValue->IsBoolean()) {
            properties.autoCancel = autoCancelValue->ToBoolean();
        }

        // Parse cancel.
        auto cancelValue = obj->GetProperty("cancel");
        if (cancelValue->IsFunction()) {
            auto cancelFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(cancelValue));
            auto eventFunc = [execContext, func = std::move(cancelFunc), node = dialogNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
                ACE_SCORING_EVENT("AlertDialog.property.cancel");
                auto pipelineContext = PipelineContext::GetCurrentContextSafely();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(node);
                func->Execute();
            };
            AlertDialogModel::GetInstance()->SetOnCancel(eventFunc, properties);
        }

        std::function<void(const int32_t& info)> onWillDismissFunc = nullptr;
        ParseDialogCallback(obj, onWillDismissFunc);
        AlertDialogModel::GetInstance()->SetOnWillDismiss(std::move(onWillDismissFunc), properties);

        // Parse showInSubWindowValue.
        auto showInSubWindowValue = obj->GetProperty("showInSubWindow");
        if (showInSubWindowValue->IsBoolean()) {
#if defined(PREVIEW)
            LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
                 "emulator or a real device instead.");
#else
            properties.isShowInSubWindow = showInSubWindowValue->ToBoolean();
#endif
        }

        // Parse isModal.
        auto isModalValue = obj->GetProperty("isModal");
        if (isModalValue->IsBoolean()) {
            LOGI("Parse isModalValue");
            properties.isModal = isModalValue->ToBoolean();
        }

        auto backgroundColorValue = obj->GetProperty("backgroundColor");
        Color backgroundColor;
        if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
            properties.backgroundColor = backgroundColor;
        }

        auto backgroundBlurStyle = obj->GetProperty("backgroundBlurStyle");
        if (backgroundBlurStyle->IsNumber()) {
            auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
            if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
                blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
                properties.backgroundBlurStyle = blurStyle;
            }
        }
        // Parse transition.
        properties.transitionEffect = ParseJsTransitionEffect(args);
        JSViewAbstract::SetDialogProperties(obj, properties);
        JSViewAbstract::SetDialogHoverModeProperties(obj, properties);
        AlertDialogModel::GetInstance()->SetShowDialog(properties);
    }
}

void JSAlertDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSAlertDialog>::Declare("AlertDialog");
    JSClass<JSAlertDialog>::StaticMethod("show", &JSAlertDialog::Show);

    JSClass<JSAlertDialog>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
