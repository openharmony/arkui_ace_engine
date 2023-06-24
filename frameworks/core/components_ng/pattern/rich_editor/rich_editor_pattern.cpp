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

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t RICH_EDITOR_TWINKLING_INTERVAL_MS = 500;
}

void RichEditorPattern::OnModifyDone()
{
    TextPattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();

    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    InitClickEvent(gestureEventHub);

    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
}

void RichEditorPattern::BeforeCreateLayoutWrapper()
{
    TextPattern::BeforeCreateLayoutWrapper();
}

bool RichEditorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    bool ret = TextPattern::OnDirtyLayoutWrapperSwap(dirty, config);
    if (!isRichEditorInit_) {
        auto eventHub = GetEventHub<RichEditorEventHub>();
        CHECK_NULL_RETURN(eventHub, ret);
        eventHub->FireOnReady();
        isRichEditorInit_ = true;
    }
    return ret;
}
int32_t RichEditorPattern::GetInstanceId() const
{
    return instanceId_;
}

int32_t RichEditorPattern::GetTextContentLength()
{
    if (!spanItemChildren_.empty()) {
        auto it = spanItemChildren_.rbegin();
        return (*it)->position;
    }
    return 0;
}

int32_t RichEditorPattern::GetCaretPosition()
{
    return caretPosition_;
}

OffsetF RichEditorPattern::CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight)
{
    return TextPattern::CalcCursorOffsetByPosition(position, selectLineHeight);
}

void RichEditorPattern::SetCaretPosition(int32_t pos)
{
    caretPosition_ = std::clamp(pos, 0, GetTextContentLength());
}

bool RichEditorPattern::GetCaretVisible() const
{
    return caretVisible_;
}

void RichEditorPattern::ScheduleCaretTwinkling()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        LOGW("context has no task executor.");
        return;
    }

    auto weak = WeakClaim(this);
    caretTwinklingTask_.Reset([weak] {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnCaretTwinkling();
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(caretTwinklingTask_, TaskExecutor::TaskType::UI, RICH_EDITOR_TWINKLING_INTERVAL_MS);
}

void RichEditorPattern::StartTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = true;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
}

void RichEditorPattern::OnCaretTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = !caretVisible_;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
}

void RichEditorPattern::StopTwinkling()
{
    caretTwinklingTask_.Cancel();
    if (caretVisible_) {
        caretVisible_ = false;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RichEditorPattern::HandleClickEvent(GestureEvent& info)
{
    auto contentRect = GetTextRect();
    contentRect.SetTop(contentRect.GetY() - std::min(baselineOffset_, 0.0f));
    contentRect.SetHeight(contentRect.Height() - std::max(baselineOffset_, 0.0f));
    if (contentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY()))) {
        CHECK_NULL_VOID_NOLOG(!spanItemChildren_.empty());
        Offset textOffset = { info.GetLocalLocation().GetX() - contentRect.GetX(),
            info.GetLocalLocation().GetY() - contentRect.GetY() };
        CHECK_NULL_VOID(paragraph_);
        auto position = paragraph_->GetHandlePositionForClick(textOffset);
        auto focusHub = GetHost()->GetOrCreateFocusHub();
        if (focusHub) {
            if (focusHub->RequestFocusImmediately()) {
                float caretHeight = 0.0f;
                SetCaretPosition(position);
                OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
                CHECK_NULL_VOID(richEditorOverlayModifier_);
                richEditorOverlayModifier_->SetCaretOffsetAndHeight(caretOffset, caretHeight);
                StartTwinkling();
            } else {
                LOGE("request focus fail");
            }
        } else {
            LOGE("focusHub is NULL");
        }
    }
}

void RichEditorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!clickEventInitialized_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickListener);
    clickEventInitialized_ = true;
}

void RichEditorPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID_NOLOG(!focusEventInitialized_);
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    focusEventInitialized_ = true;
}

void RichEditorPattern::HandleBlurEvent()
{
    StopTwinkling();
}

void RichEditorPattern::HandleFocusEvent() {}
} // namespace OHOS::Ace::NG
