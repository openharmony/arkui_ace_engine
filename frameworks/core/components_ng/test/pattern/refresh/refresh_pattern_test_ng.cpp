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

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#define private public
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);

constexpr float IDEAL_WIDTH = 300.0f;
constexpr float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);

constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
} // namespace
class RefreshPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void RunMeasureAndLayout();
    void CreateRefreshNodeAndInitParam();

    RefPtr<FrameNode> frameNode_;
    RefPtr<RefreshPattern> pattern_;
    RefPtr<RefreshEventHub> eventHub_;
    RefPtr<RefreshLayoutProperty> layoutProperty_;
    RefPtr<RefreshRenderProperty> paintProperty_;
    RefPtr<RefreshAccessibilityProperty> accessibilityProperty_;
};

void RefreshPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RefreshPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void RefreshPatternTestNg::SetUp() {}

void RefreshPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void RefreshPatternTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RefreshPattern>();
    eventHub_ = frameNode_->GetEventHub<RefreshEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RefreshLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<RefreshRenderProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<RefreshAccessibilityProperty>();
}

void RefreshPatternTestNg::RunMeasureAndLayout()
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { CONTAINER_WIDTH, CONTAINER_HEIGHT };
    LayoutConstraint.percentReference = { CONTAINER_WIDTH, CONTAINER_HEIGHT };
    LayoutConstraint.selfIdealSize = { CONTAINER_WIDTH, CONTAINER_HEIGHT };
    LayoutConstraint.maxSize = { CONTAINER_WIDTH, CONTAINER_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void RefreshPatternTestNg::CreateRefreshNodeAndInitParam()
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    modelNG.SetRefreshDistance(Dimension(100));
    modelNG.SetLoadingDistance(Dimension(100));
    modelNG.SetProgressDistance(Dimension(100));
    modelNG.SetProgressDiameter(Dimension(100));
    modelNG.SetMaxDistance(Dimension(100));
    modelNG.SetShowTimeDistance(Dimension(100));
    modelNG.SetProgressColor(Color(0xf0000000));
    modelNG.SetProgressBackgroundColor(Color(0xf0000000));
    modelNG.SetTextStyle(TextStyle());
}

/**
 * @tc.name: RefreshEventTest001
 * @tc.desc: Test event function of refresh pattern.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshEventTest001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();

    /**
     * @tc.steps: step1. set callback function by eventHub
     */
    std::string changeEventValue;
    auto onChangeEvent = [&changeEventValue](const std::string& param) { changeEventValue = param; };
    modelNG.SetChangeEvent(std::move(onChangeEvent));
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    modelNG.SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    modelNG.SetOnRefreshing(std::move(onRefreshingEvent));

    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. test pattern event function
     */
    pattern_->FireRefreshing();
    EXPECT_TRUE(refreshingValue);
    pattern_->FireChangeEvent("false");
    EXPECT_EQ(changeEventValue, "false");
    pattern_->FireChangeEvent("true");
    EXPECT_EQ(changeEventValue, "true");
    pattern_->FireStateChange(static_cast<int>(RefreshStatus::INACTIVE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::INACTIVE));
    pattern_->FireStateChange(static_cast<int>(RefreshStatus::REFRESH));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::REFRESH));
    pattern_->FireStateChange(static_cast<int>(RefreshStatus::DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    pattern_->FireStateChange(static_cast<int>(RefreshStatus::OVER_DRAG));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::OVER_DRAG));
    pattern_->FireStateChange(static_cast<int>(RefreshStatus::DONE));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DONE));

    /**
     * @tc.steps: step3. test pattern active function
     */
    pattern_->OnInActive();
    EXPECT_EQ(changeEventValue, "true");
    pattern_->OnModifyDone();
    EXPECT_EQ(layoutProperty_->GetLoadingProcessOffsetValue(OffsetF(0.0f, 0.0f)).GetY(), 0.0f);

    /**
     * @tc.steps: step4. test pattern drag function
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    pattern_->HandleDragUpdate(100.0f);
    pattern_->HandleDragEnd();
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    pattern_->HandleDragCancel();
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue().GetY(), 0.0f);
}

/**
 * @tc.name: RefreshPropertyTest001
 * @tc.desc: Test setting of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshPropertyTest001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    modelNG.SetRefreshDistance(Dimension(100));
    modelNG.SetLoadingDistance(Dimension(100));
    modelNG.SetProgressDistance(Dimension(100));
    modelNG.SetProgressDiameter(Dimension(100));
    modelNG.SetMaxDistance(Dimension(100));
    modelNG.SetShowTimeDistance(Dimension(100));
    modelNG.SetProgressColor(Color(0xf0000000));
    modelNG.SetProgressBackgroundColor(Color(0xf0000000));
    modelNG.SetTextStyle(TextStyle());
    modelNG.SetRefreshing(true);
    modelNG.SetUseOffset(true);
    modelNG.SetIndicatorOffset(Dimension(16.f));
    modelNG.SetFriction(42);
    modelNG.IsRefresh(true);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. test param model interface of refresh.
     */
    EXPECT_EQ(layoutProperty_->GetLoadingDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetRefreshDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetProgressDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetProgressDiameterValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetMaxDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetShowTimeDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetMaxDistanceValue(Dimension(0)), Dimension(100));
    EXPECT_EQ(layoutProperty_->GetProgressColorValue(Color::TRANSPARENT), Color(0xf0000000));
    EXPECT_EQ(layoutProperty_->GetProgressColorValue(Color::TRANSPARENT), Color(0xf0000000));
    EXPECT_TRUE(paintProperty_->GetIsRefreshingValue());
    EXPECT_TRUE(layoutProperty_->GetIsUseOffsetValue());
    EXPECT_EQ(layoutProperty_->GetIndicatorOffsetValue().ConvertToPx(), 16.f);
    EXPECT_EQ(layoutProperty_->GetFrictionValue(), 42);
    EXPECT_TRUE(layoutProperty_->GetIsRefreshValue());
}

/**
 * @tc.name: RefreshTest001
 * @tc.desc: test status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest001, TestSize.Level1)
{
    CreateRefreshNodeAndInitParam();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub_->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub_->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test refresh status
     */
    pattern_->OnModifyDone();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step5. test refresh status for DRAG
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(stateChangeValue, 1);
    pattern_->HandleDragStart();
    layoutProperty_->UpdateScrollableOffset(
        OffsetF(0.0f, layoutProperty_->GetTriggerRefreshDistanceValue().ConvertToPx() - 1));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
}

/**
 * @tc.name: RefreshTest002
 * @tc.desc: test status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest002, TestSize.Level1)
{
    CreateRefreshNodeAndInitParam();
    GetInstance();
    RunMeasureAndLayout();
    /**
     * @tc.steps: step2. set callback function by eventHub
     */
    int32_t stateChangeValue = -1;
    auto onStateChangeEvent = [&stateChangeValue](const int32_t param) { stateChangeValue = param; };
    eventHub_->SetOnStateChange(std::move(onStateChangeEvent));
    bool refreshingValue = false;
    auto onRefreshingEvent = [&refreshingValue]() { refreshingValue = true; };
    eventHub_->SetOnRefreshing(std::move(onRefreshingEvent));
    /**
     * @tc.steps: step3. test refresh status
     */
    pattern_->OnModifyDone();
    RunMeasureAndLayout();

    pattern_->HandleDragStart();
    layoutProperty_->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty_->GetTriggerRefreshDistanceValue().ConvertToPx())));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    /**
     * @tc.steps: step4. test refresh status for OVER_DRAG
     */
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    layoutProperty_->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty_->GetTriggerRefreshDistanceValue().ConvertToPx() - 1)));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    layoutProperty_->UpdateScrollableOffset(
        OffsetF(0.0f, static_cast<float>(layoutProperty_->GetTriggerRefreshDistanceValue().ConvertToPx())));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
    layoutProperty_->UpdateScrollableOffset(OffsetF(0.0f, 0.0f));
    EXPECT_EQ(stateChangeValue, static_cast<int>(RefreshStatus::DRAG));
}

/**
 * @tc.name: RefreshTest003
 * @tc.desc: test INACTIVE status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode_ of refresh.
     */
    CreateRefreshNodeAndInitParam();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Judge whether there is progressChild and textChild.
     */
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textChild, nullptr);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    auto loadingProgressChild =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    ASSERT_NE(loadingProgressChild, nullptr);
    pattern_->progressChild_ = loadingProgressChild;
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    /**
     * @tc.steps: step3. when there is both progressChild and textChild, and their valid property.
     */
    auto progressChildLayoutProperty = pattern_->progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    progressChildLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest004
 * @tc.desc: test REFRESH status change of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest004, TestSize.Level1)
{
    CreateRefreshNodeAndInitParam();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->refreshStatus_ = RefreshStatus::REFRESH;
    /**
     * @tc.steps: step2. when renderProperty has invalid IsRefreshing.
     */
    paintProperty_->UpdateIsRefreshing(true);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    /**
     * @tc.steps: step3. when renderProperty has valid IsRefreshing property, but has no IsShowLastTimeValue.
     */
    paintProperty_->UpdateIsRefreshing(false);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    /**
     * @tc.steps: step4. when renderProperty has valid IsRefreshing property and IsShowLastTimeValue.
     */
    pattern_->refreshStatus_ = RefreshStatus::REFRESH;
    paintProperty_->UpdateLastTimeText("LastTimeText");

    layoutProperty_->UpdateIsShowLastTime(true);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(paintProperty_->GetTimeText(), std::nullopt);
}

/**
 * @tc.name: RefreshTest005
 * @tc.desc: Test RefreshModelNG will pop according to different child node.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest005, TestSize.Level1)
{
    /**
     * @tc.cases: case1. refreshNode has less than two child node.
     */
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_FALSE(frameNode == nullptr);
    auto refreshRenderProperty = frameNode->GetPaintProperty<RefreshRenderProperty>();
    EXPECT_FALSE(refreshRenderProperty == nullptr);
    refreshRenderProperty->UpdateTimeText("TimeText");
    modelNG.Pop();
    EXPECT_EQ(refreshRenderProperty->GetLastTimeTextValue(), "");
    EXPECT_EQ(refreshRenderProperty->GetTimeTextValue(), "");
    /**
     * @tc.cases: case2. refreshNode has more than one child node.
     */
    modelNG.Create();
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_FALSE(frameNode2 == nullptr);
    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textChild == nullptr);
    frameNode2->AddChild(textChild);
    auto loadingProgressChild =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    EXPECT_FALSE(loadingProgressChild == nullptr);
    frameNode2->AddChild(loadingProgressChild);
    modelNG.Pop();
    EXPECT_TRUE(frameNode2->TotalChildCount() >= 2);
    auto refreshRenderProperty2 = frameNode2->GetPaintProperty<RefreshRenderProperty>();
    EXPECT_FALSE(refreshRenderProperty2 == nullptr);
    EXPECT_EQ(refreshRenderProperty2->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(refreshRenderProperty2->GetTimeText(), std::nullopt);
}

/**
 * @tc.name: RefreshTest006
 * @tc.desc: Test Refresh Pattern dragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest006, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    /**
     * @tc.steps: step2. initialize refreshStatus and create two child Node.
     */
    pattern_->refreshStatus_ = RefreshStatus::DRAG;
    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textChild, nullptr);
    frameNode_->AddChild(textChild);
    auto loadingProgressChild =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    ASSERT_NE(loadingProgressChild, nullptr);
    frameNode_->AddChild(loadingProgressChild);
    /**
     * @tc.steps: step3. test pattern dragUpdate function
     */
    pattern_->HandleDragStart();
    EXPECT_TRUE(pattern_->progressChild_ == nullptr);
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue(), OffsetF(0, 0));
    EXPECT_EQ(layoutProperty_->GetLoadingProcessOffsetValue(), OffsetF(0, 0));
    EXPECT_EQ(layoutProperty_->GetShowTimeOffsetValue(), OffsetF(0, 0));
    pattern_->HandleDragUpdate(.0f);
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue(), OffsetF(0, 0));
    EXPECT_EQ(layoutProperty_->GetLoadingProcessOffsetValue(), OffsetF(0, 0));
    EXPECT_EQ(layoutProperty_->GetShowTimeOffsetValue(), OffsetF(0, 0));
    /**
     * @tc.cases: case1. refresh's properties is isvalid and not to update textChild and progressChild LayoutProperty.
     */
    pattern_->HandleDragUpdate(100.0f);
    CHECK_NULL_VOID(pattern_->progressChild_);
    auto progressLayoutProperty = pattern_->progressChild_->GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    pattern_->HandleDragUpdate(100.0f);
    EXPECT_EQ(progressLayoutProperty->GetVisibilityValue(), VisibleType::INVISIBLE);
    /**
     * @tc.cases: case2. refresh's properties is valid to update textChild and progressChild LayoutProperty.
     */
    layoutProperty_->UpdateMaxDistance(Dimension(200.f));
    layoutProperty_->UpdateIsShowLastTime(true);

    CHECK_NULL_VOID(paintProperty_);
    paintProperty_->UpdateLastTimeText("lastTimeText");
    pattern_->HandleDragUpdate(100.0f);
    EXPECT_EQ(progressLayoutProperty->GetVisibilityValue(), VisibleType::VISIBLE);
    EXPECT_FALSE(paintProperty_->GetTimeText() == std::nullopt);
}

/**
 * @tc.name: RefreshTest007
 * @tc.desc: Test UpdateScrollableOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest007, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    /**
     * @tc.cases: case1. RefreshPattern need UpdateScrollableOffset when RefreshStatus is DONE and frameSize is invalid.
     */
    pattern_->refreshStatus_ = RefreshStatus::DONE;
    layoutProperty_->UpdateMaxDistance(Dimension(200.f));
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue(), OffsetF(0, 0.0f));
    /**
     * @tc.cases: case2. frameSize is valid.
     */
    frameNode_->geometryNode_->frame_.rect_ = RectF(0, 0, 100.0f, 100.0f);
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue(), OffsetF(0, 0.0f));
    /**
     * @tc.cases: case3. RefreshPattern need not UpdateScrollableOffset.
     */
    pattern_->refreshStatus_ = RefreshStatus::REFRESH;
    EXPECT_EQ(layoutProperty_->GetScrollableOffsetValue(), OffsetF(0, 0.0f));
}

/**
 * @tc.name: RefreshTest008
 * @tc.desc: Test GetFriction function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest008, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    layoutProperty_->UpdateFriction(100);
}

/**
 * @tc.name: RefreshTest009
 * @tc.desc: Test Refresh Pattern HandleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest009, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    /**
     * @tc.cases: case1. refreshStatus is invalid, HandleDragEnd func is also invalid.
     */
    pattern_->refreshStatus_ = RefreshStatus::INACTIVE;
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->refreshStatus_ = RefreshStatus::DONE;
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
    /**
     * @tc.steps: step2. initialize refreshStatus and create two child Node.
     */
    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textChild, nullptr);
    frameNode_->AddChild(textChild);
    auto loadingProgressChild =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    ASSERT_NE(loadingProgressChild, nullptr);
    frameNode_->AddChild(loadingProgressChild);
    /**
     * @tc.cases: case2. HandleDragEnd func is valid to run.
     */
    pattern_->refreshStatus_ = RefreshStatus::DRAG;
    layoutProperty_->UpdateScrollableOffset(OffsetF(0, 100.0f));
    layoutProperty_->UpdateIndicatorOffset(Dimension(50.0));
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(layoutProperty_->GetShowTimeOffsetValue(), OffsetF(0, 0));
}

/**
 * @tc.name: RefreshTest010
 * @tc.desc: Test GetLoadingOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest010, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    layoutProperty_->UpdateIsUseOffset(false);
    layoutProperty_->UpdateScrollableOffset(OffsetF(100.0, 100.0));
    /**
     * @tc.cases: case1. scrollableOffset.Y >= triggerLoadingDistance and scrollableOffset.Y >= triggerRefreshDistance.
     */
    layoutProperty_->UpdateProgressDiameter(Dimension(1.0));
    /**
     * @tc.cases: case2. scrollableOffset.Y >= triggerLoadingDistance and scrollableOffset.Y < triggerRefreshDistance.
     */
    layoutProperty_->UpdateTriggerRefreshDistance(Dimension(200.0));
    /**
     * @tc.cases: case3. scrollableOffset.Y < triggerLoadingDistance.
     */
    layoutProperty_->UpdateLoadingDistance(Dimension(120.0));
}

/**
 * @tc.name: RefreshTest011
 * @tc.desc: Test GetOpacity function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest011, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();
    /**
     * @tc.cases: case1. scrollableOffset.Y < triggerRefreshDistance - timeDistance.
     */
    layoutProperty_->UpdateTriggerRefreshDistance(Dimension(200.0));
    layoutProperty_->UpdateShowTimeDistance(Dimension(50.0));
    layoutProperty_->UpdateScrollableOffset(OffsetF(100.0, 100.0));
    /**
     * @tc.cases: case2. scrollableOffset.Y >= triggerRefreshDistance - timeDistance, but scrollableOffset.Y <
     *                   triggerRefreshDistance.
     */
    layoutProperty_->UpdateTriggerRefreshDistance(Dimension(120.0));
    layoutProperty_->UpdateShowTimeDistance(Dimension(50.0));
    /**
     * @tc.cases: case3. scrollableOffset.Y >= triggerRefreshDistance - timeDistance, and scrollableOffset.Y >=
     *                   triggerRefreshDistance.
     */
    layoutProperty_->UpdateTriggerRefreshDistance(Dimension(90.0));
}

/**
 * @tc.name: RefreshTest012
 * @tc.desc: Test Refresh Pattern OnExitAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest012, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RefreshPattern> pattern = frameNode->GetPattern<RefreshPattern>();
    ASSERT_NE(pattern, nullptr);
    auto refreshLayoutProperty = frameNode->GetLayoutProperty<RefreshLayoutProperty>();
    ASSERT_NE(refreshLayoutProperty, nullptr);
    pattern->progressChild_ = frameNode;
    pattern->OnExitAnimationFinish();

    refreshLayoutProperty->UpdateCustomBuilderIndex(1);
    refreshLayoutProperty->UpdateIsCustomBuilderExist(true);
    pattern->customBuilder_ = frameNode;
    pattern->OnModifyDone();
    pattern->scrollOffset_.SetY(0.2f);
    pattern->OnExitAnimationFinish();
    EXPECT_EQ(pattern->scrollOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: RefreshTest013
 * @tc.desc: Test Refresh Pattern GetScrollOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest013, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetCustomBuilder(nullptr);
    GetInstance();
    RunMeasureAndLayout();

    pattern_->scrollOffset_.SetY(10.0f);
    float delta = 20.0f;
    auto result = pattern_->GetScrollOffset(delta);
    EXPECT_EQ(result, 18.4f);
}

/**
 * @tc.name: RefreshTest014
 * @tc.desc: Test Refresh Pattern OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest014, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->scrollOffset_.SetY(0.2f);
    layoutProperty_->UpdateCustomBuilderIndex(1);
    layoutProperty_->UpdateIsCustomBuilderExist(true);
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(20.0f, 20.0f));
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->scrollOffset_.GetY(), 0.0f);

    pattern_->customBuilder_ = frameNode_;
    paintProperty_->UpdateIsRefreshing(true);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->triggerLoadingDistance_, 16.0);
}

/**
 * @tc.name: RefreshTest015
 * @tc.desc: Test Refresh Pattern HandleDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest015, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    paintProperty_->UpdateIsRefreshing(true);
    pattern_->HandleDragStart();
    EXPECT_NE(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest016
 * @tc.desc: Test Refresh Pattern HandleDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest016, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->customBuilder_ = frameNode_;
    ASSERT_NE(pattern_->customBuilder_, nullptr);

    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
}

/**
 * @tc.name: RefreshTest017
 * @tc.desc: Test Refresh Pattern HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest017, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    float delta = 100.0;
    layoutProperty_->UpdateIsRefresh(true);
    pattern_->HandleDragUpdate(delta);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    delta = 0.0;
    pattern_->HandleDragUpdate(delta);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest018
 * @tc.desc: Test Refresh Pattern HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest018, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    layoutProperty_->UpdateCustomBuilderIndex(1);
    layoutProperty_->UpdateIsCustomBuilderExist(true);
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(20.0f, 20.0f));
    pattern_->customBuilder_ = frameNode_;
    float delta = 100.0f;
    EXPECT_EQ(pattern_->scrollOffset_.GetY(), 0.0f);
    pattern_->HandleDragUpdate(delta);
    EXPECT_EQ(pattern_->scrollOffset_.GetY(), 42.0f);

    delta = 0.0;
    pattern_->HandleDragUpdate(delta);
    EXPECT_EQ(pattern_->scrollOffset_.GetY(), 42.0f);
}

/**
 * @tc.name: RefreshTest019
 * @tc.desc: Test Refresh Pattern HandleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest019, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->isRefreshing_ = true;
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest020
 * @tc.desc: Test Refresh Pattern HandleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest020, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->scrollOffset_.SetY(70.0f);
    layoutProperty_->UpdateCustomBuilderIndex(1);
    layoutProperty_->UpdateIsCustomBuilderExist(true);
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(20.0f, 20.0f));
    pattern_->customBuilder_ = frameNode_;

    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest021
 * @tc.desc: Test Refresh Pattern HandleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest021, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->scrollOffset_.SetY(50.0f);
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    pattern_->scrollOffset_.SetY(70.0f);
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshTest022
 * @tc.desc: Test Refresh Pattern HandleDragCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest022, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->scrollOffset_.SetY(70.0f);
    layoutProperty_->UpdateCustomBuilderIndex(1);
    layoutProperty_->UpdateIsCustomBuilderExist(true);
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(20.0f, 20.0f));
    pattern_->customBuilder_ = frameNode_;
    pattern_->HandleDragCancel();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest023
 * @tc.desc: Test Refresh Pattern CheckCustomBuilderDragUpdateStage function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest023, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->customBuilder_ = frameNode_;
    pattern_->triggerLoadingDistance_ = 180.0f;
    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 20.0f));
    pattern_->CheckCustomBuilderDragUpdateStage();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    pattern_->triggerLoadingDistance_ = 16.0f;
    pattern_->scrollOffset_.SetY(20.0f);
    pattern_->CheckCustomBuilderDragUpdateStage();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    pattern_->scrollOffset_.SetY(65.0f);
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(200.0f, 200.0f));
    pattern_->CheckCustomBuilderDragUpdateStage();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest024
 * @tc.desc: Test Refresh Pattern TriggerFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest024, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->refreshStatus_ = RefreshStatus::REFRESH;
    pattern_->TriggerFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: RefreshTest025
 * @tc.desc: Test Refresh Pattern CheckCustomBuilderDragEndStage function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest025, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->customBuilder_ = frameNode_;
    pattern_->triggerLoadingDistance_ = 180.0f;
    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 20.0f));

    pattern_->CheckCustomBuilderDragEndStage();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest026
 * @tc.desc: Test Refresh Pattern CheckCustomBuilderDragEndStage function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest026, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    pattern_->customBuilder_ = frameNode_;
    pattern_->triggerLoadingDistance_ = 180.0f;
    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 20.0f));

    pattern_->CheckCustomBuilderDragEndStage();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest027
 * @tc.desc: Test Refresh Pattern CustomBuilderRefreshingAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest027, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textChild, nullptr);
    frameNode_->AddChild(textChild);
    auto loadingProgressChild =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    ASSERT_NE(loadingProgressChild, nullptr);
    frameNode_->AddChild(loadingProgressChild);

    pattern_->customBuilder_ = frameNode_;
    pattern_->triggerLoadingDistance_ = 16.0f;
    pattern_->scrollOffset_.SetY(60.0f);
    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 20.0f));
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(200.0f, 200.0f));

    pattern_->CustomBuilderRefreshingAnimation();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest028
 * @tc.desc: Test Refresh Pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest028, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    DirtySwapConfig swapConfig;
    pattern_->customBuilder_ = frameNode_;
    pattern_->triggerLoadingDistance_ = 16.0f;
    pattern_->scrollOffset_.SetY(60.0f);
    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(20.0f, 20.0f));
    layoutProperty_->UpdateCustomBuilderOffset(OffsetF(200.0f, 200.0f));
    pattern_->OnDirtyLayoutWrapperSwap(nullptr, swapConfig);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    layoutProperty_->UpdateIsCustomBuilderExist(true);
    paintProperty_->UpdateIsRefreshing(true);
    pattern_->OnDirtyLayoutWrapperSwap(nullptr, swapConfig);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    pattern_->customBuilder_->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    pattern_->OnDirtyLayoutWrapperSwap(nullptr, swapConfig);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshTest029
 * @tc.desc: Test CustomBuilder function.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshTest029, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();

    /**
     * @tc.steps: step1. SetRefreshing, SetCustomBuilder.
     * @tc.expected: Verify GetIsCustomBuilderExistValue.
     */
    auto test = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto builder = AceType::DynamicCast<UINode>(test);
    modelNG.SetRefreshing(true);
    modelNG.SetCustomBuilder(builder);

    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step3. RunMeasureAndLayout.
     * @tc.expected: Verify isRefresh.
     */
    EXPECT_TRUE(pattern_->isRefreshing_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshAccessibility001
 * @tc.desc: Test IsScrollable and supportAction of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, RefreshAccessibility001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    pattern_->isRefreshing_ = true;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Refresh Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh and initialize related properties.
     */
    RefreshModelNG refreshModelNG;
    refreshModelNG.Create();

    /**
     * @tc.steps: step2. Get refresh frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto refreshPattern = frameNode->GetPattern<RefreshPattern>();
    ASSERT_NE(refreshPattern, nullptr);
    refreshPattern->isRefreshing_ = false;
    refreshPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get refresh accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto refreshAccessibilityProperty = frameNode->GetAccessibilityProperty<RefreshAccessibilityProperty>();
    ASSERT_NE(refreshAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When refresh is not Refreshing, call the callback function in refreshAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(refreshAccessibilityProperty->ActActionScrollForward());

    /**
     * @tc.steps: step5. When refresh is Refreshing, call the callback function in refreshAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    refreshPattern->isRefreshing_ = true;
    EXPECT_TRUE(refreshAccessibilityProperty->ActActionScrollForward());
}
} // namespace OHOS::Ace::NG
