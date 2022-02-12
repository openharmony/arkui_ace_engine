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
namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = {
    DialogAlignment::TOP, DialogAlignment::CENTER, DialogAlignment::BOTTOM, DialogAlignment::DEFAULT,
    DialogAlignment::TOP_START, DialogAlignment::TOP_END, DialogAlignment::CENTER_START,
    DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START, DialogAlignment::BOTTOM_END
};
} // namespace

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
            instance->dialogProperties_.autoCancel = autoCancelValue->ToBoolean();
        }

        // Parses customStyle.
        JSRef<JSVal> customStyleValue = constructorArg->GetProperty("customStyle");
        if (customStyleValue->IsBoolean()) {
            instance->dialogProperties_.customStyle = customStyleValue->ToBoolean();
        }

        // Parse alignment
        auto alignmentValue = constructorArg->GetProperty("alignment");
        if (alignmentValue->IsNumber()) {
            auto alignment = alignmentValue->ToNumber<int32_t>();
            if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
                instance->dialogProperties_.alignment = DIALOG_ALIGNMENT[alignment];
            }
        }

        // Parse offset
        auto offsetValue = constructorArg->GetProperty("offset");
        if (offsetValue->IsObject()) {
            auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
            Dimension dx;
            auto dxValue = offsetObj->GetProperty("dx");
            JSViewAbstract::ParseJsDimensionVp(dxValue, dx);
            Dimension dy;
            auto dyValue = offsetObj->GetProperty("dy");
            JSViewAbstract::ParseJsDimensionVp(dyValue, dy);
            instance->dialogProperties_.offset = DimensionOffset(dx, dy);
        }

        // Parses gridCount.
        auto gridCountValue = constructorArg->GetProperty("gridCount");
        if (gridCountValue->IsNumber()) {
            instance->dialogProperties_.gridCount = gridCountValue->ToNumber<int32_t>();
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
    dialogProperties_.customComponent = customDialog_;
    EventMarker cancelMarker([cancelCallback = jsCancelFunction_]() {
        if (cancelCallback) {
            ACE_SCORING_EVENT("CustomDialog.cancel");
            cancelCallback->Execute();
        }
    });
    dialogProperties_.callbacks.try_emplace("cancel", cancelMarker);
    dialogProperties_.onStatusChanged = [this](bool isShown) { this->isShown_ = isShown; };

    auto executor = context->GetTaskExecutor();
    if (!executor) {
        LOGE("JSCustomDialogController(JsOpenDialog) No Executor. Cannot post task.");
        return;
    }
    executor->PostTask(
        [context, dialogProperties = dialogProperties_, this]() mutable {
            if (context) {
                this->dialogComponent_ = context->ShowDialog(dialogProperties, false, "CustomDialog");
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
    {
        ACE_SCORING_EVENT("CustomDialog.builder");
        jsBuilderFunction_->Execute();
    }
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