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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_RENDER_SCROLL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_RENDER_SCROLL_H

#include <utility>

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "core/animation/curve.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/refresh/render_refresh.h"
#include "core/components/scroll/scroll_bar_controller.h"
#include "core/components/scroll/scroll_component.h"
#include "core/components/scroll/scroll_edge_effect.h"
#include "core/components/scroll/scroll_position_controller.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

enum class ScrollType {
    SCROLL_INDEX = 0,
    SCROLL_PAGE_DOWN,
    SCROLL_PAGE_UP,
    SCROLL_BOTTOM,
    SCROLL_TOP,
};

class RenderScroll : public RenderNode {
    DECLARE_ACE_TYPE(RenderScroll, RenderNode)

public:
    ~RenderScroll() override = default;

    virtual void JumpToIndex(int32_t index, int32_t source = SCROLL_FROM_JUMP);
    virtual void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);
    virtual bool ScrollPage(bool reverse, bool smooth);
    virtual void JumpToPosition(double position, int32_t source = SCROLL_FROM_JUMP);
    // notify start position in global main axis
    virtual void NotifyDragStart(double startPosition) {};
    // notify drag offset in global main axis
    virtual void NotifyDragUpdate(double dragOffset, int32_t source) {};
    virtual void ProcessScrollOverCallback(double velocity) {};
    void AnimateTo(double position, float duration, const RefPtr<Curve>& curve);
    void ScrollBy(double pixelX, double pixelY, bool smooth);

    double GetCurrentPosition() const;
    bool UpdateOffset(Offset& delta, int32_t source);
    bool ScrollPageByChild(Offset& delta, int32_t source) override;
    double GetEstimatedHeight();
    void OnChildAdded(const RefPtr<RenderNode>& child) override;

    virtual double GetFixPositionOnWatch(double destination, double current)
    {
        return destination;
    }

    bool IsAtTop() const
    {
        return LessOrEqual(GetMainOffset(currentOffset_), 0.0);
    }

    bool IsAtBottom() const
    {
        auto outViewportSize = mainScrollExtent_ - GetMainSize(viewPort_);
        bool atBottom = GreatOrEqual(GetMainOffset(currentOffset_), outViewportSize);
        return LessOrEqual(outViewportSize, 0.0) || (atBottom && ReachMaxCount());
    }

    bool IsScrollStop() const
    {
        return (scrollable_ ? scrollable_->IsMotionStop() : true) &&
               (animator_ ? (!animator_->IsRunning()) : true);
    }

    bool CanScrollVertically(const Offset& delta);
    bool ScrollPageCheck(Offset& delta, int32_t source);

    double GetMainOffset(const Offset& offset) const
    {
        return axis_ == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    }

    double GetMainSize(const Size& size) const
    {
        return axis_ == Axis::HORIZONTAL ? size.Width() : size.Height();
    }

    Size GetViewPort() const
    {
        return viewPort_;
    }

    double GetCrossSize(const Size& size) const
    {
        return axis_ == Axis::HORIZONTAL ? size.Height() : size.Width();
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    bool IsRowReverse()
    {
        return axis_ == Axis::HORIZONTAL && rightToLeft_;
    }

    virtual bool ReachMaxCount() const
    {
        return true;
    }

    virtual double GetMainScrollExtent() const
    {
        return mainScrollExtent_;
    }

    void SetScrollPage(bool scrollPage)
    {
        scrollPage_ = scrollPage;
    }

    int32_t GetBarDisappearFlag() const
    {
        return scrollBarOpacity_;
    }

    Offset GetCurrentOffset() const
    {
        return currentOffset_;
    }

    const Offset& GetLastOffset() const
    {
        return lastOffset_;
    }

    void SetNeedMove(bool needMove)
    {
        moveStatus_.second = moveStatus_.first;
        moveStatus_.first = needMove;
    }

    virtual void HandleRotate(double rotateValue, bool isVertical);

    void HandleScrollOverByBar(double velocity);

    void SetMainScrollExtentForBar(double value)
    {
        scrollBarExtent_ = value;
    }

    RefPtr<ScrollBar> GetScrollBar() const
    {
        return scrollBar_;
    }

    double GetScrollBarOutBoundaryExtent() const
    {
        return scrollBarOutBoundaryExtent_;
    }

    bool IsSpringMotionRunning() const
    {
        return scrollable_ ? scrollable_->IsSpringMotionRunning() : false;
    }

    virtual bool IsOutOfBottomBoundary();

    virtual bool IsOutOfTopBoundary();

protected:
    explicit RenderScroll();

    void ResetEdgeEffect();
    void ResetScrollable();
    bool ValidateOffset(int32_t source);
    void DoJump(double position, int32_t source = SCROLL_FROM_JUMP);
    void Update(const RefPtr<Component>& component) override;
    void InitScrollBar(const RefPtr<ScrollBar>& scrollBar);

    virtual void AdjustTouchRestrict(TouchRestrict& touchRestrict) {};

    Edge padding_;
    Axis axis_ = Axis::FREE;
    std::pair<bool, bool> moveStatus_;
    Offset currentBottomOffset_;
    Offset currentOffset_;
    double currentDeltaInMain_ = 0.0;
    Offset correctedDelta_;
    Offset lastOffset_;
    double overScroll_ = 0.0;
    double mainScrollExtent_ = 0.0;
    double outBoundaryExtent_ = 0.0;
    double estimatedHeight_ = 0.0;
    bool scrollPage_ = false;
    RefPtr<ScrollPositionController> positionController_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<Scrollable> scrollable_;

    RefPtr<ScrollBar> scrollBar_;
    bool inLinkRefresh_ = false;
    WeakPtr<RenderRefresh> refreshParent_;
    bool rightToLeft_ = false;
    bool enable_ = true;
    bool isRoot_ = false;

    // used for scrollBar
    double scrollBarExtent_ = 0.0;
    double scrollBarOutBoundaryExtent_ = 0.0;
    bool scrollBarExtentFlag_ = false;
    int32_t scrollBarOpacity_ = 0;

    double friction_ = 0.0;
    RefPtr<SpringProperty> springProperty_;

private:
    static double CalculateFriction(double gamma);
    static double CalculateOffsetByFriction(double extentOffset, double delta, double friction);

    bool IsOutOfBoundary();
    bool IsCrashBottom();
    bool IsCrashTop();
    void Initialize();
    void AdjustOffset(Offset& delta, int32_t source);
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    void HandleScrollPosition(double scrollX, double scrollY, int32_t scrollState) const;
    void SetEdgeEffectAttribute();
    bool HandleCrashTop();
    bool HandleCrashBottom();
    bool HandleRefreshEffect(Offset& delta, int32_t source);
    void ResetScrollEventCallBack();
    void HandleScrollEffect();
    void SetBarCallBack(bool isVertical);
    void HandleScrollBarEnd();
    void HandleScrollBarOutBoundary();

    RefPtr<Animator> animator_;
    RefPtr<RawRecognizer> touchRecognizer_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_RENDER_SCROLL_H
