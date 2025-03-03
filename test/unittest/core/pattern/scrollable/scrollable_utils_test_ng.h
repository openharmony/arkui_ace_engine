
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_H
#define FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_H

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
constexpr float WIDTH = 240.0f;
constexpr float HEIGHT = 400.0f;
constexpr float ITEM_MAIN_SIZE = 100.0f;
constexpr float CONTENT_MAIN_SIZE = 1000.0f;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - HEIGHT;
constexpr float HORIZONTAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - WIDTH;
constexpr int32_t TICK = 2;

class ScrollableUtilsTestNG : public TestNG {
protected:
    // scrollable handle drag
    void DragStart(const RefPtr<FrameNode>& frameNode, Offset startOffset);
    void DragUpdate(float delta);
    void DragEnd(float velocityDelta);
    void DragAction(const RefPtr<FrameNode>& frameNode, Offset startOffset, float dragDelta, float velocityDelta);
    RefPtr<FrameNode> FindScrollableNode(const RefPtr<FrameNode>& frameNode);

    // scrollable controller
    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset = std::nullopt);
    bool AnimateTo(
        const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false);
    Offset GetCurrentOffset() const;
    Axis GetScrollDirection() const;
    virtual void ScrollBy(double pixelX, double pixelY, bool smooth = false);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, float velocity);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);
    void ScrollPage(bool reverse, bool smooth);
    void Fling(double flingVelocity);
    bool IsAtEnd() const;
    Rect GetItemRect(int32_t index) const;
    int32_t GetItemIndex(double x, double y) const;
    void StopAnimate();

    // utils
    void ScrollTo(float position);

    // AssertionResult
    virtual AssertionResult Position(const RefPtr<FrameNode>& frameNode, float expectOffset);
    AssertionResult TickPosition(const RefPtr<FrameNode>& frameNode, float expectOffset);
    AssertionResult TickPosition(const RefPtr<FrameNode>& frameNode, float velocity, float expectOffset);
    virtual AssertionResult Position(float expectOffset);
    AssertionResult TickPosition(float expectOffset);
    AssertionResult TickPosition(float velocity, float expectOffset);

private:
    RefPtr<FrameNode> frameNode_;
    RefPtr<FrameNode> dragNode_;
    GestureEvent dragInfo_;
    RefPtr<ScrollableController> positionController_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_H
