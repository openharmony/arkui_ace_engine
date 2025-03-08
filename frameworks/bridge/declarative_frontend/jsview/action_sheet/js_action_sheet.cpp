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

#include "frameworks/bridge/declarative_frontend/jsview/action_sheet/js_action_sheet.h"

#include <string>
#include <vector>

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/models/action_sheet_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/overlay/level_order.h"

namespace OHOS::Ace {
std::unique_ptr<ActionSheetModel> ActionSheetModel::instance_ = nullptr;
std::mutex ActionSheetModel::mutex_;

#ifndef ARKUI_WEARABLE
ActionSheetModel* ActionSheetModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ActionSheetModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ActionSheetModelNG());
            } else {
                instance_.reset(new Framework::ActionSheetModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT = DimensionOffset(0.0_vp, -40.0_vp);
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<LevelMode> DIALOG_LEVEL_MODE = { LevelMode::OVERLAY, LevelMode::EMBEDDED };
const std::vector<ImmersiveMode> DIALOG_IMMERSIVE_MODE = { ImmersiveMode::DEFAULT, ImmersiveMode::EXTEND};
} // namespace

#ifndef ARKUI_WEARABLE
static void SetParseStyle(ButtonInfo& buttonInfo, const int32_t styleValue)
{
    if (styleValue >= static_cast<int32_t>(DialogButtonStyle::DEFAULT) &&
        styleValue <= static_cast<int32_t>(DialogButtonStyle::HIGHTLIGHT)) {
        buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(styleValue);
    }
}
#endif

#ifndef ARKUI_WEARABLE
ActionSheetInfo ParseSheetInfo(const JsiExecutionContext& execContext, JSRef<JSVal> val)
{
    ActionSheetInfo sheetInfo;
    if (!val->IsObject()) {
        LOGW("param is not an object.");
        return sheetInfo;
    }

    auto obj = JSRef<JSObject>::Cast(val);
    auto titleVal = obj->GetProperty("title");
    std::string title;
    if (JSActionSheet::ParseJsString(titleVal, title)) {
        sheetInfo.title = title;
    }

    auto iconVal = obj->GetProperty("icon");
    std::string icon;
    if (JSActionSheet::ParseJsMedia(iconVal, icon)) {
        sheetInfo.icon = icon;
    }

    auto actionValue = obj->GetProperty("action");
    if (actionValue->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
        auto eventFunc = [execContext, func = std::move(actionFunc), node = frameNode](const GestureEvent&) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
            ACE_SCORING_EVENT("SheetInfo.action");
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->ExecuteJS();
        };
        ActionSheetModel::GetInstance()->SetAction(eventFunc, sheetInfo);
    }
    return sheetInfo;
}
#endif

void ParseTitleAndMessage(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    // Parse title.
    auto titleValue = obj->GetProperty("title");
    std::string title;
    if (JSActionSheet::ParseJsString(titleValue, title)) {
        properties.title = title;
    }

    // Parse subtitle.
    auto subtitleValue = obj->GetProperty("subtitle");
    std::string subtitle;
    if (JSActionSheet::ParseJsString(subtitleValue, subtitle)) {
        properties.subtitle = subtitle;
    }

    // Parses message.
    auto messageValue = obj->GetProperty("message");
    std::string message;
    if (JSActionSheet::ParseJsString(messageValue, message)) {
        properties.content = message;
    }
#endif
}

void ParseConfirmButton(const JsiExecutionContext& execContext, DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    auto confirmVal = obj->GetProperty("confirm");
    if (!confirmVal->IsObject()) {
        return;
    }
    JSRef<JSObject> confirmObj = JSRef<JSObject>::Cast(confirmVal);
    std::string buttonValue;
    if (JSActionSheet::ParseJsString(confirmObj->GetProperty("value"), buttonValue)) {
        ButtonInfo buttonInfo = { .text = buttonValue };
        JSRef<JSVal> actionValue = confirmObj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
            auto gestureEvent = [execContext, func = std::move(actionFunc), node = frameNode](GestureEvent&) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
                ACE_SCORING_EVENT("ActionSheet.confirm.action");
                auto pipelineContext = PipelineContext::GetCurrentContextSafely();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(node);
                func->ExecuteJS();
            };
            actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
            auto eventFunc = [execContext, func = std::move(actionFunc), node = frameNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
                ACE_SCORING_EVENT("ActionSheet.confirm.action");
                auto pipelineContext = PipelineContext::GetCurrentContextSafely();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(node);
                func->Execute();
            };
            ActionSheetModel::GetInstance()->SetConfirm(gestureEvent, eventFunc, buttonInfo, properties);
        }
        auto enabledValue = confirmObj->GetProperty("enabled");
        if (enabledValue->IsBoolean()) {
            buttonInfo.enabled = enabledValue->ToBoolean();
        }
        auto defaultFocusValue = confirmObj->GetProperty("defaultFocus");
        if (defaultFocusValue->IsBoolean()) {
            buttonInfo.defaultFocus = defaultFocusValue->ToBoolean();
        }
        auto style = confirmObj->GetProperty("style");
        if (style->IsNumber()) {
            SetParseStyle(buttonInfo, style->ToNumber<int32_t>());
        }
        if (!buttonInfo.defaultFocus) {
            buttonInfo.isPrimary = true;
        }
        if (buttonInfo.IsValid()) {
            properties.buttons.clear();
            properties.buttons.emplace_back(buttonInfo);
        }
    }
#endif
}

void ParseShadow(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    // Parse shadow.
    auto shadowValue = obj->GetProperty("shadow");
    Shadow shadow;
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && JSActionSheet::ParseShadowProps(shadowValue, shadow)) {
        properties.shadow = shadow;
    }
#endif
}

void ParseBorderWidthAndColor(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    auto borderWidthValue = obj->GetProperty("borderWidth");
    NG::BorderWidthProperty borderWidth;
    if (JSActionSheet::ParseBorderWidthProps(borderWidthValue, borderWidth)) {
        properties.borderWidth = borderWidth;
        auto colorValue = obj->GetProperty("borderColor");
        NG::BorderColorProperty borderColor;
        if (JSActionSheet::ParseBorderColorProps(colorValue, borderColor)) {
            properties.borderColor = borderColor;
        } else {
            borderColor.SetColor(Color::BLACK);
            properties.borderColor = borderColor;
        }
    }
#endif
}

void ParseRadius(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    auto cornerRadiusValue = obj->GetProperty("cornerRadius");
    NG::BorderRadiusProperty radius;
    if (JSActionSheet::ParseBorderRadius(cornerRadiusValue, radius)) {
        properties.borderRadius = radius;
    }
#endif
}

void UpdateDialogAlignment(DialogAlignment& alignment)
{
#ifndef ARKUI_WEARABLE
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
#endif
}

void ParseDialogAlignment(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    // Parse alignment
    auto alignmentValue = obj->GetProperty("alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber<int32_t>();
        if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            properties.alignment = DIALOG_ALIGNMENT[alignment];
            UpdateDialogAlignment(properties.alignment);
        }
        if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
            properties.offset = ACTION_SHEET_OFFSET_DEFAULT_TOP;
        }
    }
#endif
}

void ParseOffset(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    // Parse offset
    auto offsetValue = obj->GetProperty("offset");
    if (offsetValue->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
        CalcDimension dx;
        auto dxValue = offsetObj->GetProperty("dx");
        JSActionSheet::ParseJsDimensionVp(dxValue, dx);
        CalcDimension dy;
        auto dyValue = offsetObj->GetProperty("dy");
        JSActionSheet::ParseJsDimensionVp(dyValue, dy);
        properties.offset = DimensionOffset(dx, dy);
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        Dimension offsetX = isRtl ? properties.offset.GetX() * (-1) : properties.offset.GetX();
        properties.offset.SetX(offsetX);
    }
#endif
}

void ParseMaskRect(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
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
#endif
}

void ParseDialogLevelMode(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    auto levelMode = obj->GetProperty("levelMode");
    auto levelUniqueId = obj->GetProperty("levelUniqueId");
    auto immersiveMode = obj->GetProperty("immersiveMode");
    bool showInMainWindow = true;
    if (obj->GetProperty("showInSubWindow")->IsBoolean() && obj->GetProperty("showInSubWindow")->ToBoolean()) {
        showInMainWindow = false;
    }
    if (levelMode->IsNumber() && showInMainWindow) {
        auto mode = levelMode->ToNumber<int32_t>();
        if (mode >= 0 && mode < static_cast<int32_t>(DIALOG_LEVEL_MODE.size())) {
            properties.dialogLevelMode = DIALOG_LEVEL_MODE[mode];
        }
    }
    if (levelUniqueId->IsNumber()) {
        properties.dialogLevelUniqueId = levelUniqueId->ToNumber<int32_t>();
    }
    if (immersiveMode->IsNumber()) {
        auto immersiveVal = immersiveMode->ToNumber<int32_t>();
        if (immersiveVal >= 0 && immersiveVal < static_cast<int32_t>(DIALOG_IMMERSIVE_MODE.size())) {
            properties.dialogImmersiveMode = DIALOG_IMMERSIVE_MODE[immersiveVal];
        }
    }
#endif
}

void ParseLevelOrder(DialogProperties& properties, JSRef<JSObject> obj)
{
#ifndef ARKUI_WEARABLE
    if (properties.isShowInSubWindow) {
        return;
    }

    properties.levelOrder = std::make_optional(NG::LevelOrder::ORDER_DEFAULT);
    auto levelOrderValue = obj->GetProperty("levelOrder");
    if (!levelOrderValue->IsObject()) {
        return;
    }
    napi_value levelOrderApi = JsConverter::ConvertJsValToNapiValue(levelOrderValue);
    CHECK_NULL_VOID(levelOrderApi);

    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    NG::LevelOrder* levelOrder = nullptr;
    napi_status status = napi_unwrap(env, levelOrderApi, reinterpret_cast<void**>(&levelOrder));
    if (status != napi_ok || !levelOrder) {
        LOGE("Failed to unwrap LevelOrder.");
        return;
    }

    double order = levelOrder->GetOrder();
    properties.levelOrder = std::make_optional(order);
#endif
}

void JSActionSheet::Show(const JSCallbackInfo& args)
{
#ifndef ARKUI_WEARABLE
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }
    if (!args[0]->IsObject()) {
        LOGE("args is not an object, can't show ActionSheet.");
        return;
    }

    DialogProperties properties {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = ACTION_SHEET_OFFSET_DEFAULT
    };
    auto obj = JSRef<JSObject>::Cast(args[0]);
    auto execContext = args.GetExecutionContext();
    auto dialogNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

    ParseTitleAndMessage(properties, obj);
    ParseConfirmButton(execContext, properties, obj);
    ParseShadow(properties, obj);
    ParseBorderWidthAndColor(properties, obj);
    ParseRadius(properties, obj);
    ParseDialogAlignment(properties, obj);
    ParseOffset(properties, obj);
    ParseMaskRect(properties, obj);
    ParseDialogLevelMode(properties, obj);

    auto onLanguageChange = [execContext, obj, parseContent = ParseTitleAndMessage, parseButton = ParseConfirmButton,
                                parseShadow = ParseShadow, parseBorderProps = ParseBorderWidthAndColor,
                                parseRadius = ParseRadius, parseAlignment = ParseDialogAlignment,
                                parseOffset = ParseOffset,  parseMaskRect = ParseMaskRect,
                                parseDialogLevelMode = ParseDialogLevelMode,
                                node = dialogNode](DialogProperties& dialogProps) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execContext);
        ACE_SCORING_EVENT("ActionSheet.property.onLanguageChange");
        auto pipelineContext = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        parseContent(dialogProps, obj);
        parseButton(execContext, dialogProps, obj);
        parseShadow(dialogProps, obj);
        parseBorderProps(dialogProps, obj);
        parseRadius(dialogProps, obj);
        ParseDialogAlignment(dialogProps, obj);
        parseOffset(dialogProps, obj);
        parseMaskRect(dialogProps, obj);
        parseDialogLevelMode(dialogProps, obj);
        // Parse sheets
        auto sheetsVal = obj->GetProperty("sheets");
        if (sheetsVal->IsArray()) {
            std::vector<ActionSheetInfo> sheetsInfo;
            auto sheetsArr = JSRef<JSArray>::Cast(sheetsVal);
            for (size_t index = 0; index < sheetsArr->Length(); ++index) {
                sheetsInfo.emplace_back(ParseSheetInfo(execContext, sheetsArr->GetValueAt(index)));
            }
            dialogProps.sheetsInfo = std::move(sheetsInfo);
        }
    };
    properties.onLanguageChange = std::move(onLanguageChange);

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
            ACE_SCORING_EVENT("ActionSheet.cancel");
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute();
        };
        ActionSheetModel::GetInstance()->SetCancel(eventFunc, properties);
    }

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismissFunc = nullptr;
    ParseDialogCallback(obj, onWillDismissFunc);
    ActionSheetModel::GetInstance()->SetOnWillDismiss(std::move(onWillDismissFunc), properties);

    JSViewAbstract::ParseAppearDialogCallback(args, properties);

    // Parse sheets
    auto sheetsVal = obj->GetProperty("sheets");
    if (sheetsVal->IsArray()) {
        std::vector<ActionSheetInfo> sheetsInfo;
        auto sheetsArr = JSRef<JSArray>::Cast(sheetsVal);
        for (size_t index = 0; index < sheetsArr->Length(); ++index) {
            sheetsInfo.emplace_back(ParseSheetInfo(execContext, sheetsArr->GetValueAt(index)));
        }
        properties.sheetsInfo = std::move(sheetsInfo);
    }

    // Parses gridCount.
    auto gridCountValue = obj->GetProperty("gridCount");
    if (gridCountValue->IsNumber()) {
        properties.gridCount = gridCountValue->ToNumber<int32_t>();
    }

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

    // Parse isModalValue.
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
    ParseLevelOrder(properties, obj);
    JSViewAbstract::SetDialogProperties(obj, properties);
    JSViewAbstract::SetDialogHoverModeProperties(obj, properties);
    JSViewAbstract::SetDialogBlurStyleOption(obj, properties);
    JSViewAbstract::SetDialogEffectOption(obj, properties);
    ActionSheetModel::GetInstance()->ShowActionSheet(properties);
    args.SetReturnValue(args.This());
#endif
}

void JSActionSheet::JSBind(BindingTarget globalObj)
{
#ifndef ARKUI_WEARABLE
    JSClass<JSActionSheet>::Declare("ActionSheet");
    JSClass<JSActionSheet>::StaticMethod("show", &JSActionSheet::Show);
    JSClass<JSActionSheet>::InheritAndBind<JSViewAbstract>(globalObj);
#endif
}
} // namespace OHOS::Ace::Framework
