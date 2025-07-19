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

#include <gmock/gmock.h>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ScrollablePatternTestNg : public TestNG {
public:
};

class MockNestableScrollContainer : public NestableScrollContainer {
    DECLARE_ACE_TYPE(MockNestableScrollContainer, NestableScrollContainer);

public:
    MOCK_METHOD(OHOS::Ace::Axis, GetAxis, (), (const, override));
    MOCK_METHOD(ScrollResult, HandleScroll, (float, int32_t, NestedState, float), (override));
    MOCK_METHOD(bool, HandleScrollVelocity, (float, const RefPtr<NestableScrollContainer>&), (override));
    MOCK_METHOD(void, OnScrollStartRecursive, (WeakPtr<NestableScrollContainer>, float, float), (override));
    MOCK_METHOD(void, OnScrollEndRecursive, (const std::optional<float>&), (override));
    MOCK_METHOD(void, OnScrollDragEndRecursive, (), (override));
};

/**
 * @tc.name: HandleScrollParallel001
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, false }));
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    scrollablePattern->parent_ = nestableScrollContainer;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 2);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel002
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<NestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->parent_ = nestableScrollContainer;
    float offset = 2.0f;
    auto result = scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel003
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel003, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<NestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->parent_ = nestableScrollContainer;
    float offset = 2.0f;
    auto result = scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_FALSE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel004
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel004, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, true }));
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result = scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 2.0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel005
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel005, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(2)
        .WillOnce(testing::Return(ScrollResult { 2.0, true }));
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_CHECK_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel006
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel006, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 3.0, true }));
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_CHECK_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParallel007
 * @tc.desc: Test ScrollablePattern HandleScrollParallel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParallel007, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 4.0, false }));
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParallel(offset, SCROLL_FROM_JUMP, NestedState::CHILD_CHECK_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_FALSE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollableOverScroll001
 * @tc.desc: Test ScrollablePattern HandleScrollableOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollableOverScroll001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->parent_ = nullptr;
    auto result = scrollablePattern->HandleScrollableOverScroll(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanSpringOverScroll001
 * @tc.desc: Test ScrollablePattern CanSpringOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CanSpringOverScroll001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->effectEdge_ = EffectEdge::END;
    auto result = scrollablePattern->CanSpringOverScroll();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanSpringOverScroll002
 * @tc.desc: Test ScrollablePattern CanSpringOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CanSpringOverScroll002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    scrollablePattern->effectEdge_ = static_cast<EffectEdge>(number);
    auto result = scrollablePattern->CanSpringOverScroll();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateFadeInfo001
 * @tc.desc: Test ScrollablePattern UpdateFadeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, UpdateFadeInfo001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePaintMethod> paint = AceType::MakeRefPtr<ScrollablePaintMethod>(true, false);
    scrollablePattern->startPercent_ = 2.0f;
    scrollablePattern->endPercent_ = 4.0f;
    scrollablePattern->UpdateFadeInfo(true, true, 0.0f, paint);
    EXPECT_EQ(paint->startPercent_, 0.0f);
    EXPECT_EQ(paint->endPercent_, 1.0f);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ScrollablePattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ToJsonValue001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::FADE;
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    scrollablePattern->multiSelectable_ = true;
    auto json = JsonUtil::Create(true);
    scrollablePattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Fade");
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test ScrollablePattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ToJsonValue002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->effectEdge_ = EffectEdge::START;
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    scrollablePattern->multiSelectable_ = true;
    auto json = JsonUtil::Create(true);
    scrollablePattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("edgeEffectOptions")->GetString("effectEdge"), "EffectEdge.Start");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test ScrollablePattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ToJsonValue003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->effectEdge_ = EffectEdge::END;
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    scrollablePattern->multiSelectable_ = true;
    auto json = JsonUtil::Create(true);
    scrollablePattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("edgeEffectOptions")->GetString("effectEdge"), "EffectEdge.End");
}

/**
 * @tc.name: SetAxis001
 * @tc.desc: Test ScrollablePattern SetAxis
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, SetAxis001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->useDefaultBackToTop_ = false;
    scrollablePattern->scrollBar_ = nullptr;
    scrollablePattern->SetAxis(Axis::HORIZONTAL);
    EXPECT_FALSE(scrollablePattern->backToTop_);
}

/**
 * @tc.name: OnScrollPosition001
 * @tc.desc: Test ScrollablePattern OnScrollPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnScrollPosition001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isSearchRefresh_ = false;
    scrollablePattern->SetNeedLinked(false);
    EXPECT_FALSE(scrollablePattern->GetNeedLinked());
    scrollablePattern->isAnimationStop_ = false;
    double offset = 2.0;
    auto result = scrollablePattern->OnScrollPosition(offset, SCROLL_FROM_UPDATE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnScrollPosition002
 * @tc.desc: Test ScrollablePattern OnScrollPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnScrollPosition002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isSearchRefresh_ = false;
    scrollablePattern->SetNeedLinked(true);
    EXPECT_TRUE(scrollablePattern->GetNeedLinked());
    scrollablePattern->isAnimationStop_ = true;
    scrollablePattern->animator_ = nullptr;
    double offset = 2.0;
    auto result = scrollablePattern->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedSplitScroll001
 * @tc.desc: Test ScrollablePattern NeedSplitScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, NeedSplitScroll001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isRefreshInReactive_ = false;
    scrollablePattern->axis_ = Axis::VERTICAL;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RefreshCoordination> refreshCoordination = AceType::MakeRefPtr<RefreshCoordination>(frameNode);
    refreshCoordination->refreshNode_ = frameNode;
    scrollablePattern->refreshCoordination_ = refreshCoordination;
    OverScrollOffset overOffsets = { 2.0, 4.0 };
    auto result = scrollablePattern->NeedSplitScroll(overOffsets, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedSplitScroll002
 * @tc.desc: Test ScrollablePattern NeedSplitScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, NeedSplitScroll002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isRefreshInReactive_ = false;
    scrollablePattern->axis_ = Axis::VERTICAL;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RefreshCoordination> refreshCoordination = AceType::MakeRefPtr<RefreshCoordination>(frameNode);
    refreshCoordination->refreshNode_ = frameNode;
    scrollablePattern->refreshCoordination_ = refreshCoordination;
    OverScrollOffset overOffsets = { 2.0, 4.0 };
    auto result = scrollablePattern->NeedSplitScroll(overOffsets, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedSplitScroll003
 * @tc.desc: Test ScrollablePattern NeedSplitScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, NeedSplitScroll003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isRefreshInReactive_ = false;
    scrollablePattern->axis_ = Axis::VERTICAL;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RefreshCoordination> refreshCoordination = AceType::MakeRefPtr<RefreshCoordination>(frameNode);
    refreshCoordination->refreshNode_ = frameNode;
    scrollablePattern->refreshCoordination_ = refreshCoordination;
    OverScrollOffset overOffsets = { 2.0, 4.0 };
    auto result = scrollablePattern->NeedSplitScroll(overOffsets, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UninitMouseEvent001
 * @tc.desc: Test ScrollablePattern UninitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, UninitMouseEvent001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->boxSelectPanEvent_ = nullptr;
    scrollablePattern->isMouseEventInit_ = true;
    scrollablePattern->UninitMouseEvent();
    EXPECT_TRUE(scrollablePattern->isMouseEventInit_);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test ScrollablePattern HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragUpdate001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    GestureEvent info;
    Offset rawGlobalLocation(2.0, 4.0);
    info.rawGlobalLocation_ = rawGlobalLocation;
    info.inputEventType_ = InputEventType::TOUCH_PAD;
    scrollablePattern->mousePressed_ = true;
    scrollablePattern->canMultiSelect_ = true;
    scrollablePattern->HandleDragUpdate(info);
    EXPECT_FALSE(scrollablePattern->mousePressed_);
}

/**
 * @tc.name: SelectWithScroll001
 * @tc.desc: Test ScrollablePattern SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, SelectWithScroll001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    GestureEvent lastMouseMove;
    Offset localLocation(2.0, 4.0);
    lastMouseMove.localLocation_ = localLocation;
    scrollablePattern->lastMouseMove_ = lastMouseMove;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::PAUSED;
    scrollablePattern->animator_ = animator;
    scrollablePattern->endIndex_ = 6;
    scrollablePattern->maxListItemIndex_ = 8;
    scrollablePattern->isScrollable_ = true;
    scrollablePattern->isAnimationStop_ = true;
    scrollablePattern->SelectWithScroll();
    EXPECT_FALSE(scrollablePattern->mousePressed_);
    EXPECT_TRUE(scrollablePattern->scrollAbort_);
}

/**
 * @tc.name: SelectWithScroll002
 * @tc.desc: Test ScrollablePattern SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, SelectWithScroll002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    GestureEvent lastMouseMove;
    Offset localLocation(2.0, 4.0);
    lastMouseMove.localLocation_ = localLocation;
    scrollablePattern->lastMouseMove_ = lastMouseMove;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::STOPPED;
    scrollablePattern->animator_ = animator;
    scrollablePattern->endIndex_ = 6;
    scrollablePattern->maxListItemIndex_ = 8;
    scrollablePattern->isScrollable_ = true;
    scrollablePattern->isAnimationStop_ = true;
    scrollablePattern->SelectWithScroll();
    EXPECT_FALSE(scrollablePattern->mousePressed_);
    EXPECT_FALSE(scrollablePattern->scrollAbort_);
}

/**
 * @tc.name: GetOutOfScrollableOffset001
 * @tc.desc: Test ScrollablePattern GetOutOfScrollableOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetOutOfScrollableOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    GestureEvent lastMouseMove;
    Offset localLocation(2.0, 4.0);
    lastMouseMove.localLocation_ = localLocation;
    scrollablePattern->lastMouseMove_ = lastMouseMove;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    std::optional<float> width = 5.0f;
    std::optional<float> height = 8.0f;
    OptionalSizeF selfIdealSize(width, height);
    OptionalSizeF parentIdealSize(width, height);
    ViewPosReference viewPosRef = { 5.0f, 5.0f, 5.0f, ReferenceEdge::END, Axis::FREE };
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = selfIdealSize;
    layoutConstraint.parentIdealSize = parentIdealSize;
    layoutConstraint.viewPosRef = viewPosRef;
    listLayoutProperty->layoutConstraint_ = layoutConstraint;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(1.0f, 1.0f, 1.0f, 1.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->isScrollable_ = true;
    scrollablePattern->isAnimationStop_ = true;
    scrollablePattern->endIndex_ = 6;
    scrollablePattern->maxListItemIndex_ = 6;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->currentDelta_ = 2.0f;
    scrollablePattern->chainAnimation_ = nullptr;
    auto result = scrollablePattern->GetOutOfScrollableOffset();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetOutOfScrollableOffset002
 * @tc.desc: Test ScrollablePattern GetOutOfScrollableOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetOutOfScrollableOffset002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    GestureEvent lastMouseMove;
    Offset localLocation(-85.0, -70.0);
    lastMouseMove.localLocation_ = localLocation;
    scrollablePattern->lastMouseMove_ = lastMouseMove;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    std::optional<float> width = 5.0f;
    std::optional<float> height = 8.0f;
    OptionalSizeF selfIdealSize(width, height);
    OptionalSizeF parentIdealSize(width, height);
    ViewPosReference viewPosRef = { 5.0f, 5.0f, 5.0f, ReferenceEdge::END, Axis::FREE };
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = selfIdealSize;
    layoutConstraint.parentIdealSize = parentIdealSize;
    layoutConstraint.viewPosRef = viewPosRef;
    listLayoutProperty->layoutConstraint_ = layoutConstraint;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, -80.0f, -80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    frameNode->geometryNode_ = geometryNode;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->isScrollable_ = true;
    scrollablePattern->isAnimationStop_ = true;
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 6;
    scrollablePattern->endMainPos_ = 10.0f;
    scrollablePattern->startMainPos_ = 8.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->currentDelta_ = 2.0f;
    scrollablePattern->chainAnimation_ = nullptr;
    auto result = scrollablePattern->GetOutOfScrollableOffset();
    EXPECT_EQ(result, -10.0f);
}

/**
 * @tc.name: GetScrollState001
 * @tc.desc: Test ScrollablePattern GetScrollState
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetScrollState001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    auto result = scrollablePattern->GetScrollState(SCROLL_FROM_ANIMATION);
    EXPECT_EQ(result, ScrollState::FLING);
}

/**
 * @tc.name: HandleScrollParentFirst001
 * @tc.desc: Test ScrollablePattern HandleScrollParentFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParentFirst001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, true }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParentFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 2.0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParentFirst002
 * @tc.desc: Test ScrollablePattern HandleScrollParentFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParentFirst002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(0)
        .WillOnce(testing::Return(ScrollResult { 2.0, false }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollParentFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollParentFirst003
 * @tc.desc: Test ScrollablePattern HandleScrollParentFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollParentFirst003, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, false }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result = scrollablePattern->HandleScrollParentFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 2);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollSelfFirst001
 * @tc.desc: Test ScrollablePattern HandleScrollSelfFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollSelfFirst001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, true }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollSelfFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 2);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollSelfFirst002
 * @tc.desc: Test ScrollablePattern HandleScrollSelfFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollSelfFirst002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, false }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    float offset = 2.0f;
    auto result =
        scrollablePattern->HandleScrollSelfFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_OVER_SCROLL);
    EXPECT_EQ(result.remain, 0);
    EXPECT_TRUE(result.reachEdge);
}

/**
 * @tc.name: HandleScrollSelfFirst003
 * @tc.desc: Test ScrollablePattern HandleScrollSelfFirst
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleScrollSelfFirst003, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*nestableScrollContainer, HandleScroll(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(ScrollResult { 2.0, false }));
    scrollablePattern->parent_ = nestableScrollContainer;
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->currentVelocity_ = 2.0f;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent->scrollable_ = scrollable;
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->startMainPos_ = 2.0f;
    scrollablePattern->endMainPos_ = 4.0f;
    scrollablePattern->currentDelta_ = 0.0f;
    scrollablePattern->contentStartOffset_ = 0.0f;
    scrollablePattern->contentEndOffset_ = 6.0f;
    scrollablePattern->contentMainSize_ = 10.0f;
    scrollablePattern->maxListItemIndex_ = 2;
    scrollablePattern->repeatDifference_ = 2;
    float offset = 2.0f;
    auto result = scrollablePattern->HandleScrollSelfFirst(offset, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 2);
    EXPECT_FALSE(result.reachEdge);
}

/**
 * @tc.name: HandleOverScroll001
 * @tc.desc: Test ScrollablePattern HandleOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOverScroll001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<MockNestableScrollContainer> nestableScrollContainer = AceType::MakeRefPtr<MockNestableScrollContainer>();
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->nestedScroll_.forward = NestedScrollMode::SELF_ONLY;
    scrollablePattern->nestedScroll_.backward = NestedScrollMode::SELF_ONLY;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    frameNode->accessibilityId_ = 2;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::END;
    auto result = scrollablePattern->HandleOverScroll(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleOverScroll002
 * @tc.desc: Test ScrollablePattern HandleOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOverScroll002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePattern> nestableScrollContainer = AceType::MakeRefPtr<ListPattern>();
    nestableScrollContainer->parent_ = nullptr;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->nestedScroll_.forward = NestedScrollMode::SELF_FIRST;
    scrollablePattern->nestedScroll_.backward = NestedScrollMode::SELF_FIRST;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    frameNode->accessibilityId_ = 2;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    auto result = scrollablePattern->HandleOverScroll(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleOverScroll003
 * @tc.desc: Test ScrollablePattern HandleOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOverScroll003, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePattern> nestableScrollContainer = AceType::MakeRefPtr<ListPattern>();
    nestableScrollContainer->parent_ = nullptr;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->nestedScroll_.forward = NestedScrollMode::PARENT_FIRST;
    scrollablePattern->nestedScroll_.backward = NestedScrollMode::PARENT_FIRST;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    frameNode->accessibilityId_ = 2;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->effectEdge_ = EffectEdge::ALL;
    auto result = scrollablePattern->HandleOverScroll(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleOverScroll004
 * @tc.desc: Test ScrollablePattern HandleOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOverScroll004, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePattern> nestableScrollContainer = AceType::MakeRefPtr<ListPattern>();
    nestableScrollContainer->parent_ = nullptr;
    scrollablePattern->parent_ = nestableScrollContainer;
    scrollablePattern->nestedScroll_.forward = NestedScrollMode::PARENT_FIRST;
    scrollablePattern->nestedScroll_.backward = NestedScrollMode::PARENT_FIRST;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    frameNode->accessibilityId_ = 2;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->edgeEffect_ = EdgeEffect::FADE;
    scrollablePattern->effectEdge_ = EffectEdge::END;
    auto result = scrollablePattern->HandleOverScroll(2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HotZoneScroll001
 * @tc.desc: Test ScrollablePattern HotZoneScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HotZoneScroll001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isScrollable_ = true;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->lastHonezoneOffsetPct_ = 0.5f;
    scrollablePattern->isAnimationStop_ = false;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::RUNNING;
    scrollablePattern->animator_ = animator;
    RefPtr<BezierVariableVelocityMotion> velocityMotion =
        AceType::MakeRefPtr<BezierVariableVelocityMotion>(0.8f, [](float value) { return value > 0.3f; });
    velocityMotion->offsetPct_ = 1.0f;
    velocityMotion->velocity_ = 3.0f;
    scrollablePattern->velocityMotion_ = velocityMotion;
    scrollablePattern->HotZoneScroll(2.0f);
    EXPECT_EQ(scrollablePattern->velocityMotion_->offsetPct_, 2.0f);
    EXPECT_EQ(scrollablePattern->velocityMotion_->velocity_, MAX_SPEED);
}

/**
 * @tc.name: HotZoneScroll002
 * @tc.desc: Test ScrollablePattern HotZoneScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HotZoneScroll002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->isScrollable_ = true;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->lastHonezoneOffsetPct_ = 0.5f;
    scrollablePattern->isAnimationStop_ = false;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::RUNNING;
    scrollablePattern->animator_ = animator;
    scrollablePattern->velocityMotion_ = nullptr;
    scrollablePattern->HotZoneScroll(2.0f);
    EXPECT_EQ(scrollablePattern->lastHonezoneOffsetPct_, 0.5f);
}

/**
 * @tc.name: GetPaintPropertyDumpInfo_Parameter001
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetPaintPropertyDumpInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    paintProperty->UpdateScrollBarMode(DisplayMode::AUTO);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPaintPropertyDumpInfo(json);
    EXPECT_EQ(json->GetString("innerScrollBarState"), "AUTO");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo_Parameter002
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetPaintPropertyDumpInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    paintProperty->UpdateScrollBarMode(DisplayMode::ON);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPaintPropertyDumpInfo(json);
    EXPECT_EQ(json->GetString("innerScrollBarState"), "ON");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo_Parameter003
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetPaintPropertyDumpInfo_Parameter003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    int32_t number = 6;
    paintProperty->UpdateScrollBarMode(static_cast<DisplayMode>(number));
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    json->Put("innerScrollBarState", "default");
    scrollablePattern->GetPaintPropertyDumpInfo(json);
    EXPECT_EQ(json->GetString("innerScrollBarState"), "default");
}

/**
 * @tc.name: GetNestedScrollVelocity001
 * @tc.desc: Test ScrollablePattern GetNestedScrollVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetNestedScrollVelocity001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->nestedScrollVelocity_ = 0.0f;
    auto result = scrollablePattern->GetNestedScrollVelocity();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetNestedScrollVelocity002
 * @tc.desc: Test ScrollablePattern GetNestedScrollVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetNestedScrollVelocity002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->nestedScrollVelocity_ = 2.0f;
    auto result = scrollablePattern->GetNestedScrollVelocity();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: UpdateMouseStartOffset001
 * @tc.desc: Test ScrollablePattern UpdateMouseStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, UpdateMouseStartOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    frameNode->context_ = AceType::RawPtr(context);
    scrollablePattern->frameNode_ = frameNode;
    OffsetF offset(2.0f, 4.0f);
    scrollablePattern->mouseStartOffset_ = offset;
    scrollablePattern->selectScrollOffset_ = 2.0f;
    scrollablePattern->lastVsyncTime_ = 3;
    scrollablePattern->UpdateMouseStartOffset();
    frameNode->context_ = nullptr;
    EXPECT_EQ(scrollablePattern->lastVsyncTime_, 4);
    EXPECT_EQ(scrollablePattern->selectScrollOffset_, 0.0f);
    EXPECT_EQ(scrollablePattern->mouseStartOffset_.GetY(), 6.0f);
}

/**
 * @tc.name: UpdateMouseStartOffset002
 * @tc.desc: Test ScrollablePattern UpdateMouseStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, UpdateMouseStartOffset002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::FREE;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    frameNode->context_ = AceType::RawPtr(context);
    scrollablePattern->frameNode_ = frameNode;
    OffsetF offset(2.0f, 4.0f);
    scrollablePattern->mouseStartOffset_ = offset;
    scrollablePattern->selectScrollOffset_ = 2.0f;
    scrollablePattern->lastVsyncTime_ = 3;
    scrollablePattern->UpdateMouseStartOffset();
    frameNode->context_ = nullptr;
    EXPECT_EQ(scrollablePattern->lastVsyncTime_, 4);
    EXPECT_EQ(scrollablePattern->selectScrollOffset_, 0.0f);
    EXPECT_EQ(scrollablePattern->mouseStartOffset_.GetX(), 4.0f);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test ScrollablePattern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    Color color(0xffff0000, 1);
    paintProperty->UpdateScrollBarColor(color);
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->scrollBar_ = scrollBar;
    scrollablePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(scrollablePattern->scrollBar_->foregroundColor_.colorValue_.value, 0xffff0000);
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test ScrollablePattern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    Color color(0xff00ff00, 2);
    scrollBar->SetForegroundColor(color);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->scrollBar_ = scrollBar;
    scrollablePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(scrollablePattern->scrollBar_->foregroundColor_.colorValue_.value, 0xff00ff00);
}

/**
 * @tc.name: OnColorConfigurationUpdate003
 * @tc.desc: Test ScrollablePattern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnColorConfigurationUpdate003, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    Color color(0xff0000ff, 3);
    scrollBar->SetForegroundColor(color);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = nullptr;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->scrollBar_ = scrollBar;
    scrollablePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(scrollablePattern->scrollBar_->foregroundColor_.colorValue_.value, 0xff0000ff);
}

/**
 * @tc.name: OnColorConfigurationUpdate004
 * @tc.desc: Test ScrollablePattern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, OnColorConfigurationUpdate004, TestSize.Level1)
{
    RefPtr<ArcListPattern> scrollablePattern = AceType::MakeRefPtr<ArcListPattern>();
    RefPtr<ArcScrollBar> arcScrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    arcScrollBar->SetDisplayMode(DisplayMode::AUTO);
    arcScrollBar->SetShapeMode(ShapeMode::ROUND);
    Color color(Color::RED);
    bool isRoundScroll = true;
    arcScrollBar->SetForegroundColor(color, isRoundScroll);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = nullptr;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->scrollBar_ = arcScrollBar;
    scrollablePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(scrollablePattern->scrollBar_->arcForegroundColor_, Color::RED);
}

/**
 * @tc.name: AddEventsFiredInfo001
 * @tc.desc: Test ScrollablePattern AddEventsFiredInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, AddEventsFiredInfo001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->eventsFiredInfos_.clear();
    ScrollableEventsFiredInfo scrollableEventsFiredInfo = { 1, ScrollableEventType::ON_SCROLL_START, 1 };
    ScrollableEventsFiredInfo info = { 2, ScrollableEventType::ON_SCROLL_STOP, 2 };
    scrollablePattern->eventsFiredInfos_.push_front(scrollableEventsFiredInfo);
    for (int i = 1; i <= 59; ++i) {
        scrollablePattern->eventsFiredInfos_.push_back(info);
    }
    scrollablePattern->AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_EDGE);
    EXPECT_EQ(scrollablePattern->eventsFiredInfos_.front().eventType_, ScrollableEventType::ON_SCROLL_STOP);
    EXPECT_EQ(scrollablePattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_SCROLL_EDGE);
}

/**
 * @tc.name: AddScrollableFrameInfo001
 * @tc.desc: Test ScrollablePattern AddScrollableFrameInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, AddScrollableFrameInfo001, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->scrollableFrameInfos_.clear();
    ScrollableFrameInfo scrollableFrameInfo = { 1, 1, true, 1 };
    ScrollableFrameInfo info = { 2, 2, false, 2 };
    scrollablePattern->scrollableFrameInfos_.push_front(scrollableFrameInfo);
    for (int i = 1; i <= 59; ++i) {
        scrollablePattern->scrollableFrameInfos_.push_back(info);
    }
    scrollablePattern->AddScrollableFrameInfo(3);
    EXPECT_EQ(scrollablePattern->scrollableFrameInfos_.front().scrollState_, 2);
    EXPECT_EQ(scrollablePattern->scrollableFrameInfos_.back().scrollState_, 3);
}

/**
 * @tc.name: ProcessAxisUpdateEvent001
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent001, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->snapDirection_ = SnapDirection::NONE;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(-2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::BACKWARD);
}

/**
 * @tc.name: ProcessAxisUpdateEvent002
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent002, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->snapDirection_ = SnapDirection::BACKWARD;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(-2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::BACKWARD);
}

/**
 * @tc.name: ProcessAxisUpdateEvent003
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent003, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->snapDirection_ = SnapDirection::FORWARD;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::FORWARD);
}

/**
 * @tc.name: ProcessAxisUpdateEvent004
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent004, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->snapDirection_ = SnapDirection::BACKWARD;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::FORWARD);
}

/**
 * @tc.name: ProcessAxisUpdateEvent005
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent005, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->snapDirection_ = SnapDirection::FORWARD;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(-2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::BACKWARD);
}

/**
 * @tc.name: ProcessAxisUpdateEvent006
 * @tc.desc: Test Scrollable ProcessAxisUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ProcessAxisUpdateEvent006, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->vsyncTime_ = 4;
    scrollable->context_ = context;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) { return options.fromScrollBar; };
    scrollable->lastVsyncTime_ = 3;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->snapDirection_ = SnapDirection::NONE;
    scrollable->currentPos_ = 2.0f;
    scrollable->endPos_ = 6.0f;
    scrollable->ProcessAxisUpdateEvent(2.0f, true);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::FORWARD);
}

/**
 * @tc.name: IsSnapStopped001
 * @tc.desc: Test Scrollable IsSnapStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, IsSnapStopped001, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    auto result = scrollable->IsSnapStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: Test Scrollable HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragStart001, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    GestureEvent info;
    info.sourceTool_ = SourceTool::TOUCHPAD;
    scrollable->isTouching_ = false;
    scrollable->HandleDragStart(info);
    EXPECT_TRUE(scrollable->isTouching_);
}

/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: Test Scrollable HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragEnd001, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    GestureEvent info;
    info.mainVelocity_ = 2.0f;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::TOUCHPAD;
    scrollable->dragStartPosition_ = 2.0f;
    scrollable->dragEndPosition_ = 4.0f;
    scrollable->isTouching_ = true;
    scrollable->currentPos_ = 2.0f;
    scrollable->currentVelocity_ = 2.0f;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) {
        return options.animationVelocity == 0.0f;
    };
    scrollable->HandleDragEnd(info, true);
    EXPECT_EQ(scrollable->currentPos_, 0.0f);
    EXPECT_FALSE(scrollable->isTouching_);
}

/**
 * @tc.name: HandleDragEnd002
 * @tc.desc: Test Scrollable HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragEnd002, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    GestureEvent info;
    info.mainVelocity_ = 2.0f;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::TOUCHPAD;
    scrollable->dragStartPosition_ = 2.0f;
    scrollable->dragEndPosition_ = 4.0f;
    scrollable->isTouching_ = true;
    scrollable->currentPos_ = 2.0f;
    scrollable->currentVelocity_ = 2.0f;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions options) {
        return options.animationVelocity > 0.0f;
    };
    scrollable->HandleDragEnd(info, true);
    EXPECT_EQ(scrollable->currentPos_, 0.0f);
    EXPECT_EQ(scrollable->currentVelocity_, 0.0f);
}

/**
 * @tc.name: HandleDragEnd003
 * @tc.desc: Test Scrollable HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragEnd003, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    GestureEvent info;
    info.mainVelocity_ = 2.0f;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::TOUCHPAD;
    scrollable->dragStartPosition_ = 2.0f;
    scrollable->dragEndPosition_ = 4.0f;
    scrollable->isTouching_ = true;
    scrollable->currentPos_ = 2.0f;
    scrollable->currentVelocity_ = 2.0f;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = nullptr;
    scrollable->HandleDragEnd(info, true);
    EXPECT_EQ(scrollable->currentPos_, 0.0f);
    EXPECT_EQ(scrollable->currentVelocity_, 0.0f);
}

/**
 * @tc.name: HandleDragEnd004
 * @tc.desc: Test Scrollable HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleDragEnd004, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    GestureEvent info;
    info.mainVelocity_ = 2.0f;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::TOUCHPAD;
    info.deviceType_ = SourceType::CROWN;
    scrollable->dragStartPosition_ = 2.0f;
    scrollable->dragEndPosition_ = 4.0f;
    scrollable->isTouching_ = true;
    scrollable->currentPos_ = 2.0f;
    scrollable->currentVelocity_ = 2.0f;
    scrollable->getSnapTypeCallback_ = []() { return SnapType::SCROLL_SNAP; };
    scrollable->startSnapAnimationCallback_ = nullptr;
    scrollable->HandleDragEnd(info, true);
    EXPECT_EQ(scrollable->dragStartPosition_, 0.0f);
    EXPECT_EQ(scrollable->dragEndPosition_, 0.0f);
}

/**
 * @tc.name: CalcNextStep001
 * @tc.desc: Test Scrollable CalcNextStep
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CalcNextStep001, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->currentPos_ = 2.0f;
    scrollable->finalPosition_ = 30.0f;
    auto result = scrollable->CalcNextStep(4.0, 2.0);
    EXPECT_EQ(result, 2.0);
}

/**
 * @tc.name: CalcNextStep002
 * @tc.desc: Test Scrollable CalcNextStep
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CalcNextStep002, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->currentPos_ = 2.0f;
    scrollable->finalPosition_ = 2.5f;
    auto result = scrollable->CalcNextStep(4.0, 2.0);
    EXPECT_EQ(result, 0.5);
}

/**
 * @tc.name: CalcNextStep003
 * @tc.desc: Test Scrollable CalcNextStep
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CalcNextStep003, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->currentPos_ = 2.0f;
    scrollable->finalPosition_ = 8.0f;
    scrollable->nextStep_ = 6.0f;
    auto result = scrollable->CalcNextStep(5.0, 4.0);
    EXPECT_EQ(result, 6.0);
}

/**
 * @tc.name: CalcNextStep004
 * @tc.desc: Test Scrollable CalcNextStep
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CalcNextStep004, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->currentPos_ = 2.0f;
    scrollable->finalPosition_ = 8.0f;
    scrollable->nextStep_ = std::nullopt;
    auto result = scrollable->CalcNextStep(5.0, 0.8);
    EXPECT_EQ(scrollable->nextStep_.value(), 1.0);
    EXPECT_EQ(result, 1.0);
}

/**
 * @tc.name: CalcNextStep005
 * @tc.desc: Test Scrollable CalcNextStep
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, CalcNextStep005, TestSize.Level1)
{
    RefPtr<Scrollable> scrollable =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollable->currentPos_ = 2.0f;
    scrollable->finalPosition_ = 8.0f;
    scrollable->nextStep_ = std::nullopt;
    auto result = scrollable->CalcNextStep(5.0, 2.0);
    EXPECT_EQ(result, 2.0);
}

/**
 * @tc.name: ContentClipToStr001
 * @tc.desc: Test ScrollablePaintProperty ContentClipToStr
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ContentClipToStr001, TestSize.Level1)
{
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollablePaintProperty->propContentClip_ = std::nullopt;
    RefPtr<ShapeRect> shapeRect = AceType::MakeRefPtr<ShapeRect>();
    auto contentClip = std::make_pair(ContentClipMode::BOUNDARY, shapeRect);
    scrollablePaintProperty->UpdateContentClip(contentClip);
    auto result = scrollablePaintProperty->ContentClipToStr();
    EXPECT_EQ(result, "ContentClipMode.BOUNDARY");
}

/**
 * @tc.name: ContentClipToStr002
 * @tc.desc: Test ScrollablePaintProperty ContentClipToStr
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ContentClipToStr002, TestSize.Level1)
{
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollablePaintProperty->propContentClip_ = std::nullopt;
    RefPtr<ShapeRect> shapeRect = AceType::MakeRefPtr<ShapeRect>();
    auto contentClip = std::make_pair(ContentClipMode::CUSTOM, shapeRect);
    scrollablePaintProperty->UpdateContentClip(contentClip);
    auto result = scrollablePaintProperty->ContentClipToStr();
    EXPECT_EQ(result, "RectShape");
}

/**
 * @tc.name: ContentClipToStr003
 * @tc.desc: Test ScrollablePaintProperty ContentClipToStr
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ContentClipToStr003, TestSize.Level1)
{
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollablePaintProperty->propContentClip_ = std::nullopt;
    RefPtr<ShapeRect> shapeRect = AceType::MakeRefPtr<ShapeRect>();
    auto contentClip = std::make_pair(ContentClipMode::SAFE_AREA, shapeRect);
    scrollablePaintProperty->UpdateContentClip(contentClip);
    auto result = scrollablePaintProperty->ContentClipToStr();
    EXPECT_EQ(result, "ContentClipMode.SAFE_AREA");
}

/**
 * @tc.name: ContentClipToStr004
 * @tc.desc: Test ScrollablePaintProperty ContentClipToStr
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, ContentClipToStr004, TestSize.Level1)
{
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollablePaintProperty->propContentClip_ = std::nullopt;
    int32_t number = 6;
    RefPtr<ShapeRect> shapeRect = AceType::MakeRefPtr<ShapeRect>();
    auto contentClip = std::make_pair(static_cast<ContentClipMode>(number), shapeRect);
    scrollablePaintProperty->UpdateContentClip(contentClip);
    auto result = scrollablePaintProperty->ContentClipToStr();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: GetBarStateString001
 * @tc.desc: Test ScrollablePaintProperty GetBarStateString
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetBarStateString001, TestSize.Level1)
{
    RefPtr<ScrollablePaintProperty> scrollablePaintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollablePaintProperty->propScrollBarProperty_ = std::make_unique<ScrollBarProperty>();
    int32_t number = 5;
    scrollablePaintProperty->propScrollBarProperty_->propScrollBarMode = static_cast<DisplayMode>(number);
    auto result = scrollablePaintProperty->GetBarStateString();
    EXPECT_EQ(result, "BarState.Off");
}

/**
 * @tc.name: AddObserver
 * @tc.desc: Test ScrollerObserverManager AddObserver
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, AddObserver, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    manager->AddObserver(observer, 2);
    EXPECT_EQ(manager->observers_.count(2), 1);
}

/**
 * @tc.name: RemoveObserver001
 * @tc.desc: Test ScrollerObserverManager RemoveObserver
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, RemoveObserver001, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onReachStartEvent = []() {};
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->RemoveObserver(2);
    EXPECT_EQ(manager->observers_.find(2), manager->observers_.end());
}

/**
 * @tc.name: RemoveObserver002
 * @tc.desc: Test ScrollerObserverManager RemoveObserver
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, RemoveObserver002, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onReachStartEvent = []() {};
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->RemoveObserver(3);
    EXPECT_EQ(manager->observers_.find(3), manager->observers_.end());
}

/**
 * @tc.name: HandleOnTouchEvent001
 * @tc.desc: Test ScrollerObserverManager HandleOnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnTouchEvent001, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    RefPtr<NG::TouchEventImpl> onTouchEvent =
        AceType::MakeRefPtr<NG::TouchEventImpl>([](TouchEventInfo& info) { info.isTouchEventsEnd_ = true; });
    observer.onTouchEvent = onTouchEvent;
    TouchEventInfo info = TouchEventInfo("touch");
    info.isTouchEventsEnd_ = false;
    manager->AddObserver(observer, 1);
    manager->HandleOnTouchEvent(info);
    EXPECT_TRUE(info.isTouchEventsEnd_);
}

/**
 * @tc.name: HandleOnTouchEvent002
 * @tc.desc: Test ScrollerObserverManager HandleOnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnTouchEvent002, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onTouchEvent = nullptr;
    TouchEventInfo info = TouchEventInfo("touch");
    manager->AddObserver(observer, 1);
    manager->HandleOnTouchEvent(info);
    EXPECT_FALSE(info.isTouchEventsEnd_);
}

/**
 * @tc.name: HandleOnReachEvent001
 * @tc.desc: Test ScrollerObserverManager HandleOnReachEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnReachEvent001, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = true;
    ScrollerObserver observer;
    observer.onReachStartEvent = nullptr;
    observer.onReachEndEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = false;
        manager->AddObserver(observer, 2);
    };
    manager->AddObserver(observer, 1);
    manager->HandleOnReachEvent(true);
    EXPECT_FALSE(callbackTriggered);
    EXPECT_EQ(manager->observers_.count(2), 1);
}

/**
 * @tc.name: HandleOnReachEvent002
 * @tc.desc: Test ScrollerObserverManager HandleOnReachEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnReachEvent002, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = false;
    ScrollerObserver observer;
    observer.onReachStartEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = true;
        manager->RemoveObserver(2);
    };
    observer.onReachEndEvent = nullptr;
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnReachEvent(true);
    EXPECT_NE(manager->observers_.find(2), manager->observers_.end());
}

/**
 * @tc.name: HandleOnReachEvent003
 * @tc.desc: Test ScrollerObserverManager HandleOnReachEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnReachEvent003, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = false;
    ScrollerObserver observer;
    observer.onReachStartEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = true;
        manager->AddObserver(observer, 3);
    };
    observer.onReachEndEvent = nullptr;
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnReachEvent(false);
    EXPECT_TRUE(callbackTriggered);
    EXPECT_EQ(manager->observers_.count(3), 1);
}

/**
 * @tc.name: HandleOnReachEvent004
 * @tc.desc: Test ScrollerObserverManager HandleOnReachEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnReachEvent004, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = false;
    ScrollerObserver observer;
    observer.onReachStartEvent = nullptr;
    observer.onReachEndEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = true;
        manager->AddObserver(observer, 3);
    };
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnReachEvent(false);
    EXPECT_EQ(manager->observers_.count(3), 0);
}

/**
 * @tc.name: HandleOnScrollStartEvent001
 * @tc.desc: Test ScrollerObserverManager HandleOnScrollStartEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnScrollStartEvent001, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = false;
    ScrollerObserver observer;
    observer.onScrollStartEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = true;
        manager->AddObserver(observer, 2);
    };
    manager->AddObserver(observer, 1);
    manager->HandleOnScrollStartEvent();
    EXPECT_TRUE(callbackTriggered);
    EXPECT_EQ(manager->observers_.count(2), 1);
}

/**
 * @tc.name: HandleOnScrollStartEvent002
 * @tc.desc: Test ScrollerObserverManager HandleOnScrollStartEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnScrollStartEvent002, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onScrollStartEvent = nullptr;
    manager->AddObserver(observer, 1);
    manager->HandleOnScrollStartEvent();
    EXPECT_EQ(manager->observers_.count(2), 0);
}

/**
 * @tc.name: HandleOnScrollStopEvent001
 * @tc.desc: Test ScrollerObserverManager HandleOnScrollStopEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnScrollStopEvent001, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    bool callbackTriggered = true;
    ScrollerObserver observer;
    observer.onScrollStopEvent = [manager, observer, &callbackTriggered]() {
        callbackTriggered = false;
        manager->AddObserver(observer, 3);
    };
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnScrollStopEvent();
    EXPECT_FALSE(callbackTriggered);
    EXPECT_EQ(manager->observers_.count(3), 1);
}

/**
 * @tc.name: HandleOnScrollStopEvent002
 * @tc.desc: Test ScrollerObserverManager HandleOnScrollStopEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnScrollStopEvent002, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onScrollStopEvent = nullptr;
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnScrollStopEvent();
    EXPECT_NE(manager->observers_.find(2), manager->observers_.end());
}

/**
 * @tc.name: HandleOnDidScrollEvent
 * @tc.desc: Test ScrollerObserverManager HandleOnDidScrollEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnDidScrollEvent, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    int32_t scrollCount = 0;
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onDidScrollEvent = nullptr;
    manager->AddObserver(observer, 1);
    manager->HandleOnDidScrollEvent(Dimension(1.0), ScrollSource::SCROLLER, false, true);
    EXPECT_NE(scrollCount, 1);
    manager->observers_.clear();
    observer.onDidScrollEvent = [&scrollCount](Dimension dimension, ScrollSource source, bool isAtTop,
                                    bool isAtBottom) { scrollCount++; };
    manager->AddObserver(observer, 1);
    manager->AddObserver(observer, 2);
    manager->HandleOnDidScrollEvent(Dimension(2.0), ScrollSource::SCROLLER_ANIMATION, true, false);
    EXPECT_EQ(scrollCount, 2);
}

/**
 * @tc.name: HandleOnWillScrollEventEx
 * @tc.desc: Test ScrollerObserverManager HandleOnWillScrollEventEx
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, HandleOnWillScrollEventEx, TestSize.Level1)
{
    RefPtr<ScrollerObserverManager> manager = AceType::MakeRefPtr<ScrollerObserverManager>();
    ScrollFrameResult result = { .offset = Dimension(0.0) };
    manager->observers_.clear();
    ScrollerObserver observer;
    observer.onWillScrollEventEx = nullptr;
    manager->AddObserver(observer, 1);
    manager->HandleOnWillScrollEventEx(result, ScrollState::SCROLL, ScrollSource::DRAG);
    EXPECT_NE(result.offset.Value(), 1.0);
    manager->observers_.clear();
    observer.onWillScrollEventEx = [](ScrollFrameResult& result, ScrollState state, ScrollSource source) {
        result.offset = Dimension(1.0);
    };
    manager->AddObserver(observer, 1);
    manager->HandleOnWillScrollEventEx(result, ScrollState::SCROLL, ScrollSource::DRAG);
    EXPECT_EQ(result.offset.Value(), 1.0);
}

/**
 * @tc.name: GetDVSyncOffset
 * @tc.desc: Test GetDVSyncOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollablePatternTestNg, GetDVSyncOffset, TestSize.Level1)
{
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    float dvsyncOffset = scrollablePattern->GetDVSyncOffset();
    EXPECT_EQ(dvsyncOffset, 0);
}
} // namespace OHOS::Ace::NG