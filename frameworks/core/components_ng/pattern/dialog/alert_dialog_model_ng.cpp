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

#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"

namespace OHOS::Ace::NG {
void AlertDialogModelNG::SetParseButtonObj(
    std::function<void()>&& eventFunc, ButtonInfo& buttonInfo, DialogProperties& arg, const std::string& property)
{
    auto func = eventFunc;
    auto eventFuncNg = [func](GestureEvent& /* info */) { func(); };
    buttonInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(eventFuncNg));
}

void AlertDialogModelNG::SetOnCancel(std::function<void()>&& eventFunc, DialogProperties& arg)
{
    arg.onCancel = eventFunc;
}

void AlertDialogModelNG::SetOnWillDismiss(std::function<void(const int32_t& info)>&& onWillDismissFunc,
    DialogProperties& arg)
{
    arg.onWillDismiss = std::move(onWillDismissFunc);
}

void AlertDialogModelNG::SetShowDialog(const DialogProperties& arg)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);

    auto executor = container->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    executor->PostTask(
        [currentId = Container::CurrentId(), arg]() mutable {
            auto container = AceEngine::Get().GetContainer(currentId);
            CHECK_NULL_VOID(container);
            if (container->IsSubContainer()) {
                currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
                container = AceEngine::Get().GetContainer(currentId);
                CHECK_NULL_VOID(container);
            }
            ContainerScope scope(currentId);
            RefPtr<NG::FrameNode> dialog;
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(context);
            auto overlayManager = context->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            if (arg.isShowInSubWindow) {
                dialog = SubwindowManager::GetInstance()->ShowDialogNG(arg, nullptr);
                CHECK_NULL_VOID(dialog);
                if (arg.isModal && !container->IsUIExtensionWindow()) {
                    DialogProperties Maskarg;
                    Maskarg.isMask = true;
                    Maskarg.autoCancel = arg.autoCancel;
                    Maskarg.onWillDismiss = arg.onWillDismiss;
                    Maskarg.shadow = arg.shadow;
                    auto mask = overlayManager->ShowDialog(Maskarg, nullptr, false);
                    overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
                    CHECK_NULL_VOID(mask);
                }
            } else {
                dialog = overlayManager->ShowDialog(arg, nullptr, false);
                CHECK_NULL_VOID(dialog);
            }
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
            UiSessionManager::GetInstance().ReportComponentChangeEvent("onVisibleChange", "show");
#endif
            auto hub = dialog->GetEventHub<NG::DialogEventHub>();
            hub->SetOnCancel(arg.onCancel);
            auto pattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetOnWillDismiss(arg.onWillDismiss);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowAlertDialog");
}
} // namespace OHOS::Ace::NG
