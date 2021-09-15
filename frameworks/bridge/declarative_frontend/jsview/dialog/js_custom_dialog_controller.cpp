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

#include "bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"

#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSCustomDialogController::ConstructorCallback(const JSCallbackInfo& info)
{
    int argc = info.Length();
    if (argc > 1 && !info[0]->IsUndefined() && info[0]->IsObject() && !info[1]->IsUndefined() && info[1]->IsObject()) {
        JSRef<JSObject> constructorArg = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSObject> ownerObj = JSRef<JSObject>::Cast(info[1]);

        // check if owner object is set
        JSView* ownerView = ownerObj->Unwrap<JSView>();
        if (ownerView == nullptr) {
            LOGE("JSCustomDialogController creation with invalid arguments. Missing \'ownerView\'");
            return;
        }

        auto instance = new JSCustomDialogController(ownerView);
        instance->ownerView_ = ownerView;

        // Process builder function.
        JSRef<JSVal> builderCallback = constructorArg->GetProperty("builder");
        if (!builderCallback->IsUndefined() && builderCallback->IsFunction()) {
            instance->jsBuilderFunction_ =
                AceType::MakeRefPtr<JsFunction>(ownerObj, JSRef<JSFunc>::Cast(builderCallback));
        } else {
            LOGE("JSCustomDialogController invalid builder function argument");
            return;
        }

        // Process cancel function.
        JSRef<JSVal> cancelCallback = constructorArg->GetProperty("cancel");
        if (!cancelCallback->IsUndefined() && cancelCallback->IsFunction()) {
            instance->jsCancelFunction_ =
                AceType::MakeRefPtr<JsFunction>(ownerObj, JSRef<JSFunc>::Cast(cancelCallback));
        }

        // Parses autoCancel.
        JSRef<JSVal> autoCancelValue = constructorArg->GetProperty("autoCancel");
        if (autoCancelValue->IsBoolean()) {
            instance->autoCancel_ = autoCancelValue->ToBoolean();
        }

        info.SetReturnValue(instance);
    } else {
        LOGE("JSView creation with invalid arguments.");
    }
}

void JSCustomDialogController::DestructorCallback(JSCustomDialogController* controller)
{
    if (controller != nullptr) {
        controller->ownerView_ = nullptr;
        delete controller;
    }
}

void JSCustomDialogController::ShowDialog(const JSCallbackInfo& info)
{
    LOGD("JSCustomDialogController(ShowDialog)");
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        LOGE("JSCustomDialogController No Context");
        return;
    }
    DialogProperties dialogProperties;
    dialogProperties.autoCancel = autoCancel_;
    dialogProperties.customComponent = customDialog_;
    EventMarker cancelMarker([cancelCallback = jsCancelFunction_]() {
        if (cancelCallback) {
            cancelCallback->Execute();
        }
    });
    dialogProperties.callbacks.try_emplace("cancel", cancelMarker);
    dialogProperties.onStatusChanged = [this](bool isShown) { this->isShown_ = isShown; };

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(JsOpenDialog) No Executor. Cannot post task.");
        return;
    }
    executor->PostTask(
        [context, dialogProperties, this]() mutable {
            if (context) {
                this->dialogComponent_ = context->ShowDialog(dialogProperties, false);
            }
        },
        TaskExecutor::TaskType::UI);
}

void JSCustomDialogController::CloseDialog()
{
    LOGD("JSCustomDialogController(CloseDialog)");
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        LOGE("JSCustomDialogController No Context");
        return;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        LOGE("JSCustomDialogController No Stack!");
        return;
    }
    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(JsOpenDialog) No Executor. Cannot post task.");
        return;
    }
    executor->PostTask(
        [lastStack, dialogComponent = dialogComponent_]() {
            if (!lastStack || !dialogComponent) {
                return;
            }
            auto animator = dialogComponent->GetAnimator();
            auto dialogId = dialogComponent->GetDialogId();
            if (animator) {
                animator->AddStopListener([lastStack, dialogId] {
                    if (lastStack) {
                        lastStack->PopDialog(dialogId);
                    }
                });
                animator->Play();
            } else {
                lastStack->PopDialog(dialogId);
            }
        },
        TaskExecutor::TaskType::UI);
}

void JSCustomDialogController::JsOpenDialog(const JSCallbackInfo& info)
{
    LOGD("JSCustomDialogController(JsOpenDialog)");
    if (isShown_) {
        LOGD("CustomDialog has already shown.");
        return;
    }

    // Cannot reuse component because might depend on state
    if (customDialog_) {
        customDialog_ = nullptr;
    }

    if (!jsBuilderFunction_) {
        LOGE("Builder of CustomDialog is null.");
        return;
    }
    jsBuilderFunction_->Execute();
    customDialog_ = ViewStackProcessor::GetInstance()->Finish();

    if (!customDialog_) {
        LOGE("Builder does not generate view.");
        return;
    }

    ShowDialog(info);
}

void JSCustomDialogController::JsCloseDialog(const JSCallbackInfo& info)
{
    LOGD("JSCustomDialogController(JsCloseDialog)");
    CloseDialog();
}

void JSCustomDialogController::JSBind(BindingTarget object)
{
    JSClass<JSCustomDialogController>::Declare("CustomDialogController");
    JSClass<JSCustomDialogController>::CustomMethod("open", &JSCustomDialogController::JsOpenDialog);
    JSClass<JSCustomDialogController>::CustomMethod("close", &JSCustomDialogController::JsCloseDialog);
    JSClass<JSCustomDialogController>::Bind(
        object, &JSCustomDialogController::ConstructorCallback, &JSCustomDialogController::DestructorCallback);
}

} // namespace OHOS::Ace::Framework