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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "core/components/common/layout/constants.h"

#define private public
#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_algorithm.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_property.h"
#include "core/components_ng/pattern/panel/drag_bar_pattern.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool SLIDING_PANEL_SHOW = true;
constexpr float ZERO = 0.0f;
constexpr float OFFSET_X = 20.0f;
constexpr float OFFSET_Y = 50.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr Dimension HOT_REGION_WIDTH = 64.0_vp;
constexpr Dimension HOT_REGION_HEIGHT = 24.0_vp;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const OffsetF DRAG_OFFSET = OffsetF(OFFSET_X, OFFSET_Y);
const std::vector<PanelMode> PANEL_MODE = { PanelMode::FULL, PanelMode::HALF, PanelMode::MINI, PanelMode::AUTO };
const std::vector<bool> IS_FIRST_UPDATE = { true, false };
const std::vector<TouchType> TOUCH_TYPES = { TouchType::DOWN, TouchType::MOVE, TouchType::UP };
const std::vector<Offset> LOCAL_LOCATIONS = { Offset(20.0f, 60.0f), Offset(50.0f, 60.0f), Offset(100.0f, 200.0f) };
} // namespace

class DragBarPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
    void SetUp() override;
    void TearDown() override;

    PaddingProperty CreatePadding(float left, float top, float right, float bottom)
    {
        PaddingProperty padding;
        padding.left = CalcLength(left);
        padding.right = CalcLength(right);
        padding.top = CalcLength(top);
        padding.bottom = CalcLength(bottom);
        return padding;
    }
};

void DragBarPatternTestNg::SetUp() {}
void DragBarPatternTestNg::TearDown() {}

/**
 * @tc.name: DragBarPatternTest001
 * @tc.desc: Verify whether the layout property paint property, layoutAlgorithm  functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);

    auto hasDragBar = layoutProperty->GetHasDragBar().value_or(true);
    EXPECT_TRUE(hasDragBar == true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());

    auto dragBarFrameNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
    dragBarFrameNode->MountToParent(columnNode, 0);
    dragBarFrameNode->MarkModifyDone();

    CHECK_NULL_VOID(columnNode);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(dragBarNode);
    EXPECT_EQ(dragBarFrameNode, dragBarNode);

    /**
     * @tc.steps: step2. get pattern and create layout property, paint property, layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    EXPECT_FALSE(dragBarPattern == nullptr);
    auto layoutProPerty = dragBarPattern->CreateLayoutProperty();
    EXPECT_FALSE(layoutProPerty == nullptr);
    auto paintPropety = dragBarPattern->CreatePaintProperty();
    EXPECT_FALSE(paintPropety == nullptr);
    auto layoutAlgorithm = dragBarPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto paintMethod = dragBarPattern->CreateNodePaintMethod();
    EXPECT_FALSE(paintMethod == nullptr);
}

/**
 * @tc.name: DragBarPatternTest002
 * @tc.desc: Test dragBar onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto hasDragBar = layoutProperty->GetHasDragBar().value_or(true);
    EXPECT_TRUE(hasDragBar == true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);

    auto dragBarFrameNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
    dragBarFrameNode->MountToParent(columnNode, 0);
    dragBarFrameNode->MarkModifyDone();

    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(dragBarNode);
    dragBarNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and create layout property, paint property, layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    EXPECT_FALSE(dragBarPattern == nullptr);
    dragBarPattern->barStyleAnimator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    auto paintProperty = AceType::DynamicCast<DragBarPaintProperty>(dragBarPattern->CreatePaintProperty());
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateDragOffset(DRAG_OFFSET);
    // update different panelMode
    for (size_t i = 0; i < PANEL_MODE.size(); ++i) {
        paintProperty->UpdatePanelMode(PANEL_MODE[i]);
        dragBarPattern->isFirstUpdate_ = IS_FIRST_UPDATE[i % 2];
        dragBarPattern->OnModifyDone();

        /**
         * @tc.steps: step3. pattern OnModifyDone.
         * @tc.expected: step3. check whether the properties is correct.
         */
        bool isShowArrow = i % 2 == 0 ? true : false;
        dragBarPattern->ShowArrow(isShowArrow);
        EXPECT_EQ(paintProperty->GetPanelMode(), PANEL_MODE[i]);
    }
    EXPECT_EQ(paintProperty->GetDragOffset(), DRAG_OFFSET);
}

/**
 * @tc.name: DragBarPatternTest003
 * @tc.desc: Test dragBar touchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);

    auto dragBarFrameNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
    dragBarFrameNode->MountToParent(columnNode, 0);
    dragBarFrameNode->MarkModifyDone();

    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(dragBarNode);
    dragBarNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and create layout property, paint property, layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    EXPECT_FALSE(dragBarPattern == nullptr);
    auto paintProperty = dragBarNode->GetPaintProperty<DragBarPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateDragOffset(DRAG_OFFSET);

    auto hub = dragBarNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    dragBarPattern->InitTouchEvent(gestureHub);

    /**
     * @tc.steps: step3. update different touchEventInfo.
     * @tc.expected: step3. check whether touchEventInfo is correct.
     */

    for (size_t i = 0; i < TOUCH_TYPES.size(); ++i) {
        TouchEventInfo touchEventInfo = TouchEventInfo("touch");
        TouchLocationInfo touchLocationInfo = TouchLocationInfo(i);
        touchLocationInfo.SetTouchType(TOUCH_TYPES[i]);
        touchLocationInfo.SetLocalLocation(LOCAL_LOCATIONS[i]);
        touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
        dragBarPattern->HandleTouchEvent(touchEventInfo);
        EXPECT_EQ(touchEventInfo.GetTouches().front().GetTouchType(), TOUCH_TYPES[i]);
        EXPECT_EQ(touchEventInfo.GetTouches().front().GetLocalLocation(), LOCAL_LOCATIONS[i]);
    }
}

/**
 * @tc.name: DragBarPatternTest004
 * @tc.desc: Test dragBar layout.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);

    auto dragBarFrameNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
    dragBarFrameNode->MountToParent(columnNode, 0);
    dragBarFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);

    auto dragBarPattern = dragBarFrameNode->GetPattern<DragBarPattern>();
    EXPECT_FALSE(dragBarPattern == nullptr);
    auto layoutProPerty = dragBarPattern->GetLayoutProperty<DragBarLayoutProperty>();
    EXPECT_FALSE(layoutProPerty == nullptr);
    layoutProPerty->UpdateHotRegionHeight(HOT_REGION_HEIGHT.ConvertToPx());
    auto paintProperty = dragBarPattern->GetPaintProperty<DragBarPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);

    auto layoutAlgorithm = AceType::DynamicCast<DragBarLayoutAlgorithm>(dragBarPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dragBarFrameNode, geometryNode, dragBarFrameNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /* corresponding ets code:
       Panel(true){
       }
       .dragBar(true)
   */
    /**
     * @tc.steps: step3. use layoutAlgorithm to measureContent.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    auto idealSize =
        layoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
    EXPECT_EQ(idealSize, SizeF(HOT_REGION_WIDTH.ConvertToPx(), HOT_REGION_HEIGHT.ConvertToPx()));
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
    bool flag = dragBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(flag == true);
}

/**
 * @tc.name: DragBarPatternTest005
 * @tc.desc: Test dragBar HandleTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(dragBarNode);
    dragBarNode->MarkModifyDone();
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    EXPECT_FALSE(dragBarPattern == nullptr);
    auto paintProperty = dragBarNode->GetPaintProperty<DragBarPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateDragOffset(OffsetF(0.1f, 0.2f));
    dragBarPattern->HandleTouchUp();
    EXPECT_TRUE(paintProperty->GetDragOffset() == OffsetF(0.1f, 0.2f));
}

/**
 * @tc.name: DragBarPatternTest006
 * @tc.desc: Test dragBar DoStyleAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(columnNode, nullptr);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MarkModifyDone();
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto leftPoint = OffsetT<Dimension>(Dimension(1), Dimension(2));
    auto centerPoint = OffsetT<Dimension>(Dimension(1), Dimension(2));
    auto rightPoint = OffsetT<Dimension>(Dimension(1), Dimension(2));
    dragBarPattern->DoStyleAnimation(leftPoint, centerPoint, rightPoint);
    std::list<RefPtr<Interpolator>> test = dragBarPattern->barStyleAnimator_->interpolators_;
    for (std::list<RefPtr<Interpolator>>::iterator iter = test.begin(); iter != test.end(); iter++) {
        auto animation = static_cast<CurveAnimation<OffsetT<Dimension>>*>(AceType::RawPtr(*iter));
        animation->callbacks_.begin()->second(OffsetT<Dimension>(Dimension(1), Dimension(2)));
    }
}

/**
 * @tc.name: DragBarPatternTest007
 * @tc.desc: Test dragBar DoStyleAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(columnNode, nullptr);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MarkModifyDone();
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarNode->paintProperty_ = AceType::MakeRefPtr<DragBarPaintProperty>();
    auto paintProperty = dragBarPattern->GetPaintProperty<DragBarPaintProperty>();
    paintProperty->UpdateDragOffset(OffsetF(0.1f, 0.1f));
    dragBarPattern->HandleTouchUp();
    std::list<RefPtr<Interpolator>> test = dragBarPattern->barRangeAnimator_->interpolators_;
    auto dragAnimation = static_cast<CurveAnimation<OffsetF>*>(AceType::RawPtr(test.front()));
    dragAnimation->callbacks_.begin()->second(OffsetF(0.1f, 0.2f));
}

/**
 * @tc.name: DragBarPatternTest008
 * @tc.desc: Test dragBar InitProps.
 * @tc.type: FUNC
 */
HWTEST_F(DragBarPatternTestNg, DragBarPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get dragBar frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(columnNode, nullptr);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MarkModifyDone();
    auto dragBarPattern = dragBarNode->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->barTouchAnimator_ = nullptr;
    dragBarPattern->InitProps();
    std::list<RefPtr<Interpolator>> test = dragBarPattern->barTouchAnimator_->interpolators_;
    auto dragAnimation = static_cast<CurveAnimation<float>*>(AceType::RawPtr(test.front()));
    dragAnimation->callbacks_.begin()->second(0.1f);
}
} // namespace OHOS::Ace::NG