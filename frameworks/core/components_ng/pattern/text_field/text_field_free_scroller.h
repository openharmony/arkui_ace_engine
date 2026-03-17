/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTFIELD_SCROLL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTFIELD_SCROLL_CONTROLLER_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_free_scroll_controller.h"
#include "core/components_ng/pattern/text/text_scroll_bar_2d.h"
#include "core/components_ng/pattern/text_field/text_field_overlay_modifier.h"

namespace OHOS::Ace::NG {
class TextFieldFreeScroller final : public AceType {
    DECLARE_ACE_TYPE(TextFieldFreeScroller, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldFreeScroller);

public:
    explicit TextFieldFreeScroller(const WeakPtr<Pattern>& pattern);
    ~TextFieldFreeScroller() = default;

    void SetScrollBar(DisplayMode displayMode);
    void SetMinHeight(const Dimension& height);
    void UpdateScrollBar();
    void AttachModifier(const RefPtr<TextFieldOverlayModifier>& modifier);
    bool IsAttachedModifier() const
    {
        return isScrollBarModiferPropertyttached_;
    }
    bool HandleMouseEventByScrollBar(MouseInfo& info);
    bool CheckMousePressedOverScrollBar(GestureEvent& info);
    void HandleScrollCallback(float offset, int32_t source, bool isVertical);
    void UpdateScrollBarOffsetWithAxis(Axis axis);
    void UpdateSecondHandleInfoByMouse(MouseInfo& info);
    void PlayScrollBarAppearAnimation(Axis axis);
    void ScheduleDisappearDelayTaskWitAxis(Axis axis);
    void ScheduleDisappearDelayTask();
    void ScheduleScrollingDisappearDelayTask();
    void StopScrolling();
    void OnDrawScrollBar(DrawingContext& context)
    {
        if (scrollBar_) {
            scrollBar_->OnDraw(context);
        }
    }

    RefPtr<NGGestureRecognizer> GetScrollGestureRecognizer() const
    {
        return freeScrollController_ ? freeScrollController_->GetGestureRecognizer() : nullptr;
    }

    struct AutoScrollStepParam {
        Offset offset;
        bool hasHotArea = true;
        bool enableScrollOutside = true;
    };
    void UpdateAutoScrollStepOffset(const AutoScrollStepParam& param, Axis& axis, std::optional<float>& step);

private:
    void Initialize();
    void HandleStartScroll(bool isVertical);
    void HandleEndScrollCallback(bool isVertical);
    void SyncOffset();
    bool IsPointInScrollBarRect(const BaseEventInfo* info, bool isVertical);

    // Helper methods for auto-scroll
    bool HandleInHorizontalBand(const AutoScrollStepParam& param, const RectF& workRect,
        Axis& axis, std::optional<float>& step) const;
    bool HandleInVerticalBand(const AutoScrollStepParam& param, const RectF& workRect,
        Axis& axis, std::optional<float>& step) const;
    bool HandleCornerScrolling(const AutoScrollStepParam& param, const RectF& workRect,
        Axis& axis, std::optional<float>& step) const;

    RefPtr<TextFreeScrollController> freeScrollController_;
    RefPtr<TextScrollBar2D> scrollBar_;
    WeakPtr<Pattern> pattern_;
    Axis scrollingAxis_ = Axis::NONE;
    bool isScrollBarModiferPropertyttached_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXTFIELD_SCROLL_CONTROLLER_H
