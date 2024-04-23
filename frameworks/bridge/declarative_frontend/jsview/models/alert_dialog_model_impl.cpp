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

#include "bridge/declarative_frontend/jsview/models/alert_dialog_model_impl.h"

#include "core/components/dialog/alert_dialog_component.h"

namespace OHOS::Ace::Framework {
void AlertDialogModelImpl::SetParseButtonObj(
    std::function<void()>&& eventFuncImpl, ButtonInfo& buttonInfo, DialogProperties& arg, const std::string& property)
{
    EventMarker actionId(std::move(eventFuncImpl));
    if (property == "confirm" || property == "primaryButton") {
        arg.primaryId = actionId;
    } else if (property == "secondaryButton") {
        arg.secondaryId = actionId;
    }
}

void AlertDialogModelImpl::SetOnCancel(std::function<void()>&& eventFunc, DialogProperties& arg)
{
    EventMarker cancelId(std::move(eventFunc));
    arg.callbacks.try_emplace("cancel", cancelId);
}

void AlertDialogModelImpl::SetShowDialog(const DialogProperties& arg)
{
    auto container = Container::Current();
    if (container) {
        auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        auto executor = container->GetTaskExecutor();
        if (executor) {
            executor->PostTask(
                [context, arg]() {
                    if (context) {
                        context->ShowDialog(arg, false, "AlertDialog");
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUIDialogShowAlertDialog");
        }
    }
}
} // namespace OHOS::Ace::Framework
