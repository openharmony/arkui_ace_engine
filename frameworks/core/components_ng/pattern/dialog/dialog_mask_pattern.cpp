/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dialog/dialog_mask_pattern.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void DialogMaskPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto maskLayoutProps = host->GetLayoutProperty();
    CHECK_NULL_VOID(maskLayoutProps);
    maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    maskLayoutProps->UpdateAlignment(Alignment::TOP_LEFT);

    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);

    auto maskRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    auto dialogProps = GetDialogProperties();
    maskRenderContext->UpdateBackgroundColor(dialogProps.maskColor.value_or(dialogTheme->GetMaskColorEnd()));

    InitClickEvent();
}

void DialogMaskPattern::InitClickEvent()
{
    if (onClick_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    GestureEventFunc task = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto dialog = pattern->GetDialogNode();
        if (!dialog) {
            TAG_LOGW(AceLogTag::ACE_DIALOG, "dialog node is null, close mask by click");
            pattern->CloseMask();
            return;
        }

        auto dialogProps = pattern->GetDialogProperties();
        if (dialogProps.autoCancel) {
            CHECK_NULL_VOID(dialog);
            auto dialogPattern = dialog->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->CloseDialogByEvent(DialogDismissReason::DIALOG_TOUCH_OUTSIDE);
        }
    };
    onClick_ = MakeRefPtr<ClickEvent>(std::move(task));
    gestureHub->AddClickEvent(onClick_);
}

void DialogMaskPattern::ShowMask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetOpacityAnimationDurIn());

    renderContext->OpacityAnimation(option, theme->GetOpacityStart(), theme->GetOpacityEnd());
}

void DialogMaskPattern::CloseMask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    auto dialog = GetDialogNode();
    auto dialogId = dialog ? dialog->GetId() : -1;

    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetAnimationDurationOut());
    option.SetOnFinishEvent([weakHost = WeakClaim(RawPtr(host)), dialogId]() {
        auto host = weakHost.Upgrade();
        CHECK_NULL_VOID(host);
        auto parent = host->GetParent();
        CHECK_NULL_VOID(parent);
        parent->RemoveChild(host);
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        SubwindowManager::GetInstance()->CloseMaskSubwindow(dialogId);
    });

    renderContext->OpacityAnimation(option, theme->GetOpacityEnd(), theme->GetOpacityStart());
}
} // namespace OHOS::Ace::NG
