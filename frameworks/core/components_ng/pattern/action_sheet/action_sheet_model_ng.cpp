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
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif
#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ActionSheetModelNG::ShowActionSheet(const DialogProperties& arg)
{
#ifndef ARKUI_WEARABLE
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (arg.dialogLevelMode == LevelMode::EMBEDDED) {
        auto embeddedOverlay = NG::DialogManager::GetEmbeddedOverlay(arg.dialogLevelUniqueId, context);
        if (embeddedOverlay) {
            overlayManager = embeddedOverlay;
        }
    }
    RefPtr<NG::FrameNode> dialog;
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
            CHECK_NULL_VOID(mask);
            overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
        }
    } else {
        dialog = overlayManager->ShowDialog(arg, nullptr, false);
        CHECK_NULL_VOID(dialog);
    }
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    UiSessionManager::GetInstance().ReportComponentChangeEvent("onVisibleChange", "show");
#endif
#endif
}

void ActionSheetModelNG::SetAction(GestureEventFunc&& eventFunc, ActionSheetInfo& sheetInfo)
{
    sheetInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(eventFunc));
}

void ActionSheetModelNG::SetCancel(std::function<void()>&& eventFunc, DialogProperties& arg)
{
    arg.onCancel = eventFunc;
}

void ActionSheetModelNG::SetOnWillDismiss(std::function<void(const int32_t& info,
    const int32_t& instanceId)>&& onWillDismissFunc, DialogProperties& arg)
{
    arg.onWillDismiss = std::move(onWillDismissFunc);
}

void ActionSheetModelNG::SetConfirm(
    GestureEventFunc&& gestureEvent, std::function<void()>&& eventFunc, ButtonInfo& buttonInfo, DialogProperties& arg)
{
    buttonInfo.action = AceType::MakeRefPtr<NG::ClickEvent>(std::move(gestureEvent));
}
} // namespace OHOS::Ace::NG
