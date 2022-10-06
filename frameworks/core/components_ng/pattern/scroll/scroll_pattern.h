/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_position_controller.h"

namespace OHOS::Ace::NG {

class ScrollPattern : public Pattern {
    DECLARE_ACE_TYPE(ScrollPattern, Pattern);

public:
    ScrollPattern() = default;
    ~ScrollPattern() override
    {
        animator_ = nullptr;
        positionController_ = nullptr;
        scrollableEvent_ = nullptr;
        scrollEffect_ = nullptr;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ScrollLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<ScrollLayoutAlgorithm>(currentOffset_);
        return layoutAlgorithm;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ScrollEventHub>();
    }

    virtual bool ReachMaxCount() const
    {
        return true;
    }

    double GetCurrentPosition() const
    {
        return currentOffset_;
    }

    Offset GetCurrentOffset() const
    {
        if (axis_ == Axis::HORIZONTAL) {
            return Offset{currentOffset_, 0};
        }
        return Offset{0, currentOffset_};
    }

    const RefPtr<ScrollEdgeEffect>& GetScrollEdgeEffect() const
    {
        return scrollEffect_;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    float GetScrollableDistance() const
    {
        return scrollableDistance_;
    }

    bool IsRowReverse() const
    {
        // TODO: not consider rightToLeft
        return direction_ == FlexDirection::ROW_REVERSE;
    }

    bool IsColReverse() const
    {
        return  direction_ == FlexDirection::COLUMN_REVERSE;
    }

    void SetScrollPositionController(const RefPtr<ScrollPositionController>& positionController)
    {
        positionController_ = positionController;
    }

    void SetDirection(FlexDirection direction)
    {
        direction_ = direction;
    }

    bool IsAtTop() const;
    bool IsAtBottom() const;
    bool IsOutOfBoundary() const;

    void SetScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect);
    bool UpdateCurrentOffset(float offset, int32_t source);
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool limitDuration = true,
        const std::function<void()>& onFinish = nullptr);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);
    void ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish = nullptr);
    bool ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish = nullptr);
    void JumpToPosition(float position, int32_t source = SCROLL_FROM_JUMP);
    bool ScrollPageCheck(float delta, int32_t source);
    void AdjustOffset(float& delta, int32_t source);

protected:
    void DoJump(float position, int32_t source = SCROLL_FROM_JUMP);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool IsCrashTop() const;
    bool IsCrashBottom() const;
    void HandleCrashTop() const;
    void HandleCrashBottom() const;

    void RegisterScrollBeginTask();
    void RegisterOnScrollTask();
    void CreateOrStopAnimator();
    void HandleScrollEffect();
    void HandleScrollBarOutBoundary();
    void ValidateOffset(int32_t source);
    void HandleScrollPosition(float scroll, int32_t scrollState);
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect);
    void RemoveScrollEdgeEffect();

    RefPtr<Animator> animator_;
    RefPtr<ScrollPositionController> positionController_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    Axis axis_ = Axis::VERTICAL;
    float currentOffset_ = 0.0f;
    float lastOffset_ = 0.0f;
    float scrollableDistance_ = 0.0f;
    float viewPortLength_ = 0.0f;
    FlexDirection direction_ { FlexDirection::COLUMN };
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
