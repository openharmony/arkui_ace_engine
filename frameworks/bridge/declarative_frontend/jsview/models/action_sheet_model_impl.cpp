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
#include "bridge/declarative_frontend/jsview/models/action_sheet_model_impl.h"

#include "core/components/dialog/dialog_component.h"
#include "core/components/stack/stack_element.h"
#include "core/gestures/tap_gesture.h"

namespace OHOS::Ace::Framework {
void ActionSheetModelImpl::ShowActionSheet(const DialogProperties& arg)
{
#ifndef ARKUI_WEARABLE
    LOGE("ActionSheetModelImpl::ShowActionSheet");
    auto container = Container::Current();
    if (container) {
        auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        auto executor = container->GetTaskExecutor();
        if (executor) {
            executor->PostTask(
                [context, arg]() {
                    if (context) {
                        context->ShowDialog(arg, false, "ActionSheet");
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUIDialogShowActionSheet");
        }
    }
#endif
}

void ActionSheetModelImpl::SetAction(GestureEventFunc&& eventFunc, ActionSheetInfo& sheetInfo)
{
    LOGE("ActionSheetModelImpl::SetAction");
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>();
    tapGesture->SetOnActionId([func = std::move(eventFunc)](GestureEvent& info) {
        auto container = Container::Current();
        if (!container) {
            return;
        }
        auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        if (!context) {
            return;
        }
        auto stack = context->GetLastStack();
        if (!stack) {
            return;
        }
        stack->PopDialog();
        func(info);
    });
    sheetInfo.gesture = tapGesture;
}

void ActionSheetModelImpl::SetCancel(std::function<void()>&& eventFunc, DialogProperties& arg)
{
    LOGE("ActionSheetModelImpl::SetCancel");
    EventMarker cancelId(std::move(eventFunc));
    arg.callbacks.try_emplace("cancel", cancelId);
}

void ActionSheetModelImpl::SetConfirm(GestureEventFunc&& gestureEvent, std::function<void()>&& eventFunc,
    ButtonInfo& buttonInfo, DialogProperties& arg)
{
    EventMarker actionId(std::move(eventFunc));
    arg.primaryId = actionId;
}
} // namespace OHOS::Ace::Framework
