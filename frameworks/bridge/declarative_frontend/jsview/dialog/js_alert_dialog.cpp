/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/components/dialog/dialog_component.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void ParseButtonObj(
    const JSCallbackInfo& args, DialogProperties& properties, JSRef<JSObject> obj, const std::string& property)
{
    auto jsVal = obj->GetProperty(property.c_str());
    if (jsVal->IsObject()) {
        JSRef<JSObject> objInner = JSRef<JSObject>::Cast(jsVal);
        JSRef<JSVal> value = objInner->GetProperty("value");
        std::string buttonValue;
        if (JSAlertDialog::ParseJsString(value, buttonValue)) {
            properties.buttons.emplace_back(buttonValue, "");
        }

        JSRef<JSVal> actionValue = objInner->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
            EventMarker actionId([execCtx = args.GetExecutionContext(), func = std::move(actionFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                func->Execute();
            });

            if (property == "confirm" || property == "primaryButton") {
                properties.primaryId = actionId;
            } else if (property == "secondaryButton") {
                properties.secondaryId = actionId;
            }
        }
    }
}

void JSAlertDialog::Show(const JSCallbackInfo& args)
{
    DialogProperties properties { .type = DialogType::ALERT_DIALOG };
    if (args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        // Parse title.
        JSRef<JSVal> titleValue = obj->GetProperty("title");
        std::string title;
        if (ParseJsString(titleValue, title)) {
            properties.title = title;
        }

        // Parses message.
        JSRef<JSVal> messageValue = obj->GetProperty("message");
        std::string message;
        if (ParseJsString(messageValue, message)) {
            properties.content = message;
        }

        // Parse auto autoCancel.
        JSRef<JSVal> autoCancelValue = obj->GetProperty("autoCancel");
        if (autoCancelValue->IsBoolean()) {
            properties.autoCancel = autoCancelValue->ToBoolean();
        }

        // Parse cancel.
        JSRef<JSVal> cancelValue = obj->GetProperty("cancel");
        if (cancelValue->IsFunction()) {
            auto cancelFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(cancelValue));
            EventMarker cancelId([execCtx = args.GetExecutionContext(), func = std::move(cancelFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                func->Execute();
            });
            properties.callbacks.try_emplace("cancel", cancelId);
        }

        if (obj->GetProperty("confirm")->IsObject()) {
            // Parse confirm.
            ParseButtonObj(args, properties, obj, "confirm");
        } else {
            // Parse primaryButton and secondaryButton.
            ParseButtonObj(args, properties, obj, "primaryButton");
            ParseButtonObj(args, properties, obj, "secondaryButton");
        }

        // Show dialog.
        auto container = Container::Current();
        if (container) {
            auto context = container->GetPipelineContext();
            auto executor = container->GetTaskExecutor();
            if (executor) {
                executor->PostTask(
                    [context, properties]() {
                        if (context) {
                            context->ShowDialog(properties, false);
                        }
                    },
                    TaskExecutor::TaskType::UI);
            }
        }
        args.SetReturnValue(args.This());
    }
}

void JSAlertDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSAlertDialog>::Declare("AlertDialog");
    JSClass<JSAlertDialog>::StaticMethod("show", &JSAlertDialog::Show);

    JSClass<JSAlertDialog>::Inherit<JSViewAbstract>();
    JSClass<JSAlertDialog>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
