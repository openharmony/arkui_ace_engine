/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/bubble//bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_paint_method.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"

namespace OHOS::Ace::NG {

enum class TransitionStatus {
    INVISIABLE,
    ENTERING,
    NORMAL,
    EXITING,
};
class BubblePattern : public PopupBasePattern {
    DECLARE_ACE_TYPE(BubblePattern, PopupBasePattern);

public:
    BubblePattern() = default;
    BubblePattern(int32_t id, const std::string& tag) : targetNodeId_(id), targetTag_(tag) {}
    ~BubblePattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto bubbleMethod = AceType::MakeRefPtr<BubblePaintMethod>();
        bubbleMethod->SetArrowPosition(arrowPosition_);
        bubbleMethod->SetChildOffset(childOffset_);
        bubbleMethod->SetChildSize(childSize_);
        bubbleMethod->SetShowArrow(showArrow_);
        return bubbleMethod;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        auto bubbleProp = AceType::MakeRefPtr<BubbleLayoutProperty>();
        bubbleProp->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return bubbleProp;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<BubbleLayoutAlgorithm>(targetNodeId_, targetTag_, targetOffset_, targetSize_);
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<BubbleRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<BubbleEventHub>();
    }

    OffsetF GetChildOffset()
    {
        return childOffset_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void OnWindowHide() override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void StartEnteringAnimation(std::function<void()> finish);
    void StartExitingAnimation(std::function<void()> finish);
    bool IsOnShow();
    bool IsExiting();
    void OnColorConfigurationUpdate() override;

    void SetMessageNode(RefPtr<FrameNode> messageNode)
    {
        messageNode_ = messageNode;
    }

    void SetCustomPopupTag(bool isCustomPopup)
    {
        isCustomPopup_ = isCustomPopup;
    }

    void SetTransitionStatus(TransitionStatus transitionStatus)
    {
        transitionStatus_ = transitionStatus;
    }

protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    RefPtr<FrameNode> GetButtonRowNode();
    RefPtr<PopupTheme> GetPopupTheme();
    void InitTouchEvent();
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const Offset& clickPosition);
    void RegisterButtonOnHover();
    void RegisterButtonOnTouch();
    void ButtonOnHover(bool isHover, const RefPtr<NG::FrameNode>& buttonNode);
    void ButtonOnPress(const TouchEventInfo& info, const RefPtr<NG::FrameNode>& buttonNode);
    void PopBubble();
    void Animation(
        RefPtr<RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve);

    OffsetT<Dimension> GetInvisibleOffset();
    RefPtr<RenderContext> GetRenderContext();
    void ResetToInvisible();
    bool PostTask(const TaskExecutor::Task& task);
    void StartOffsetEnteringAnimation();
    void StartAlphaEnteringAnimation(std::function<void()> finish);
    void StartOffsetExitingAnimation();
    void StartAlphaExitingAnimation(std::function<void()> finish);

    int32_t targetNodeId_ = -1;
    std::string targetTag_;

    RefPtr<TouchEventImpl> touchEvent_;
    bool mouseEventInitFlag_ = false;
    bool touchEventInitFlag_ = false;
    bool isHover_ = false;

    OffsetF childOffset_;
    OffsetF arrowPosition_;
    SizeF childSize_;
    RectF touchRegion_;
    std::optional<Placement> arrowPlacement_;

    bool showArrow_ = false;

    TransitionStatus transitionStatus_ = TransitionStatus::INVISIABLE;

    bool delayShow_ = false;

    std::optional<OffsetF> targetOffset_;
    std::optional<SizeF> targetSize_;

    bool isCustomPopup_ = false;
    RefPtr<FrameNode> messageNode_;
    ACE_DISALLOW_COPY_AND_MOVE(BubblePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_PATTERN_H
