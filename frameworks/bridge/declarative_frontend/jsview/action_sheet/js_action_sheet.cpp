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
#include "bridge/declarative_frontend/jsview/models/action_sheet_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<ActionSheetModel> ActionSheetModel::instance_ = nullptr;
std::mutex ActionSheetModel::mutex_;

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
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT = DimensionOffset(0.0_vp, -40.0_vp);
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
} // namespace

static void SetParseStyle(ButtonInfo& buttonInfo, const int32_t styleValue)
{
    if (styleValue >= static_cast<int32_t>(DialogButtonStyle::DEFAULT) &&
        styleValue <= static_cast<int32_t>(DialogButtonStyle::HIGHTLIGHT)) {
        buttonInfo.dlgButtonStyle = static_cast<DialogButtonStyle>(styleValue);
    }
}

ActionSheetInfo ParseSheetInfo(const JSCallbackInfo& args, JSRef<JSVal> val)
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
        auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
        auto eventFunc = [execCtx = args.GetExecutionContext(), func = std::move(actionFunc)](const GestureEvent&) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("SheetInfo.action");
            func->ExecuteJS();
        };
        ActionSheetModel::GetInstance()->SetAction(eventFunc, sheetInfo);
    }
    return sheetInfo;
}

void JSActionSheet::Show(const JSCallbackInfo& args)
{
    LOGD("show ActionSheet");
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
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
    // Parse title.
    auto titleValue = obj->GetProperty("title");
    std::string title;
    if (ParseJsString(titleValue, title)) {
        properties.title = title;
    }

    // Parse subtitle.
    auto subtitleValue = obj->GetProperty("subtitle");
    std::string subtitle;
    if (ParseJsString(subtitleValue, subtitle)) {
        properties.subtitle = subtitle;
    }

    // Parses message.
    auto messageValue = obj->GetProperty("message");
    std::string message;
    if (ParseJsString(messageValue, message)) {
        properties.content = message;
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
        auto eventFunc = [execCtx = args.GetExecutionContext(), func = std::move(cancelFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ActionSheet.cancel");
            func->Execute();
        };
        ActionSheetModel::GetInstance()->SetCancel(eventFunc, properties);
    }

    // Parse confirm.
    auto confirmVal = obj->GetProperty("confirm");
    if (confirmVal->IsObject()) {
        JSRef<JSObject> confirmObj = JSRef<JSObject>::Cast(confirmVal);
        JSRef<JSVal> value = confirmObj->GetProperty("value");
        std::string buttonValue;
        if (ParseJsString(value, buttonValue)) {
            ButtonInfo buttonInfo = { .text = buttonValue };
            JSRef<JSVal> actionValue = confirmObj->GetProperty("action");
            // parse confirm action
            if (actionValue->IsFunction()) {
                auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
                auto gestureEvent = [execCtx = args.GetExecutionContext(),
                    func = std::move(actionFunc)](GestureEvent&) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("ActionSheet.confirm.action");
                    LOGD("actionSheet confirm triggered");
                    func->ExecuteJS();
                };
                actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
                auto eventFunc = [execCtx = args.GetExecutionContext(), func = std::move(actionFunc)]() {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("ActionSheet.confirm.action");
                    func->Execute();
                };
                ActionSheetModel::GetInstance()->SetConfirm(gestureEvent, eventFunc, buttonInfo, properties);
            }

            // Parse enabled
            auto enabledValue = confirmObj->GetProperty("enabled");
            if (enabledValue->IsBoolean()) {
                buttonInfo.enabled = enabledValue->ToBoolean();
            }

            // Parse defaultFocus
            auto defaultFocusValue = confirmObj->GetProperty("defaultFocus");
            if (defaultFocusValue->IsBoolean()) {
                buttonInfo.defaultFocus = defaultFocusValue->ToBoolean();
            }

            // Parse style
            auto style = confirmObj->GetProperty("style");
            if (style->IsNumber()) {
                auto styleValue = style->ToNumber<int32_t>();
                SetParseStyle(buttonInfo, styleValue);
            }

            if (buttonInfo.IsValid()) {
                properties.buttons.emplace_back(buttonInfo);
            }
        }
    }

    // Parse sheets
    auto sheetsVal = obj->GetProperty("sheets");
    if (sheetsVal->IsArray()) {
        std::vector<ActionSheetInfo> sheetsInfo;
        auto sheetsArr = JSRef<JSArray>::Cast(sheetsVal);
        for (size_t index = 0; index < sheetsArr->Length(); ++index) {
            sheetsInfo.emplace_back(ParseSheetInfo(args, sheetsArr->GetValueAt(index)));
        }
        properties.sheetsInfo = std::move(sheetsInfo);
    }

    // Parse alignment
    auto alignmentValue = obj->GetProperty("alignment");
    if (alignmentValue->IsNumber()) {
        auto alignment = alignmentValue->ToNumber<int32_t>();
        if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            properties.alignment = DIALOG_ALIGNMENT[alignment];
        }
        if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
            properties.offset = ACTION_SHEET_OFFSET_DEFAULT_TOP;
        }
    }

    // Parse offset
    auto offsetValue = obj->GetProperty("offset");
    if (offsetValue->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
        CalcDimension dx;
        auto dxValue = offsetObj->GetProperty("dx");
        ParseJsDimensionVp(dxValue, dx);
        CalcDimension dy;
        auto dyValue = offsetObj->GetProperty("dy");
        ParseJsDimensionVp(dyValue, dy);
        properties.offset = DimensionOffset(dx, dy);
    }

    // Parse maskRect.
    auto maskRectValue = obj->GetProperty("maskRect");
    DimensionRect maskRect;
    if (JSViewAbstract::ParseJsDimensionRect(maskRectValue, maskRect)) {
        properties.maskRect = maskRect;
    }

    // Parses gridCount.
    auto gridCountValue = obj->GetProperty("gridCount");
    if (gridCountValue->IsNumber()) {
        properties.gridCount = gridCountValue->ToNumber<int32_t>();
    }

    ActionSheetModel::GetInstance()->ShowActionSheet(properties);
    args.SetReturnValue(args.This());
}

void JSActionSheet::JSBind(BindingTarget globalObj)
{
    JSClass<JSActionSheet>::Declare("ActionSheet");
    JSClass<JSActionSheet>::StaticMethod("show", &JSActionSheet::Show);
    JSClass<JSActionSheet>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
