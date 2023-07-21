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
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "core/components_ng/pattern/refresh/refresh_render_property.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
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

constexpr float CUSTOM_NODE_WIDTH = 100.f;
constexpr float CUSTOM_NODE_HEIGHT = 10.f;
} // namespace
class RefreshTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void RunMeasureAndLayout();
    void CreateRefreshNodeAndInitParam();
    RefPtr<FrameNode> GetChildFrameNode(int32_t index);
    RefPtr<FrameNode> CreateCustomNode();

    RefPtr<FrameNode> frameNode_;
    RefPtr<RefreshPattern> pattern_;
    RefPtr<RefreshEventHub> eventHub_;
    RefPtr<RefreshLayoutProperty> layoutProperty_;
    RefPtr<RefreshRenderProperty> paintProperty_;
    RefPtr<RefreshAccessibilityProperty> accessibilityProperty_;
};

void RefreshTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RefreshTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void RefreshTestNg::SetUp() {}

void RefreshTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void RefreshTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RefreshPattern>();
    eventHub_ = frameNode_->GetEventHub<RefreshEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RefreshLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<RefreshRenderProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<RefreshAccessibilityProperty>();
}

void RefreshTestNg::RunMeasureAndLayout()
{
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
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

void RefreshTestNg::CreateRefreshNodeAndInitParam()
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    const Dimension distance = Dimension(100);
    modelNG.SetRefreshDistance(distance);
    modelNG.SetLoadingDistance(distance);
    modelNG.SetProgressDistance(distance);
    modelNG.SetProgressDiameter(distance);
    modelNG.SetMaxDistance(distance);
    modelNG.SetShowTimeDistance(distance);
    modelNG.SetProgressColor(Color(0xf0000000));
    modelNG.SetProgressBackgroundColor(Color(0xf0000000));
    modelNG.SetTextStyle(TextStyle());
}

RefPtr<FrameNode> RefreshTestNg::GetChildFrameNode(int32_t index)
{
    auto child = frameNode_->GetChildAtIndex(index);
    return AceType::DynamicCast<FrameNode>(child);
}

RefPtr<FrameNode> RefreshTestNg::CreateCustomNode()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CUSTOM_NODE_WIDTH), CalcLength(CUSTOM_NODE_HEIGHT)));
    return frameNode;
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test Drag
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag001, TestSize.Level1)
{
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE; // default is INACTIVE
    auto onStateChangeEvent = [&refreshStatus](const int32_t param) {
        refreshStatus = static_cast<RefreshStatus>(param); };
    bool isRefreshingEventCalled = false;
    auto onRefreshingEvent = [&isRefreshingEventCalled]() { isRefreshingEventCalled = true; };

    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetTextStyle(TextStyle());
    modelNG.Pop();
    modelNG.SetOnStateChange(std::move(onStateChangeEvent));
    modelNG.SetOnRefreshing(std::move(onRefreshingEvent));
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    // handle action
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(15.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(135.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(20.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd();
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshingEventCalled);
    // The front end set isRefreshing to false
    paintProperty_->UpdateIsRefreshing(false);
    // isRefreshing changed by front end, will trigger OnModifyDone
    pattern_->OnModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
    pattern_->OnExitAnimationFinish(); // by OnModifyDone
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDrag distance > triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(150.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragEnd();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDrag to cancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(15.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(135.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(20.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragCancel();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: Drag002
 * @tc.desc: Test Drag with customBuilder_
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag002, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    auto builder = CreateCustomNode();
    modelNG.SetCustomBuilder(builder);
    modelNG.SetTextStyle(TextStyle());
    modelNG.Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    // handle action
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(15.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(135.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(20.f + CUSTOM_NODE_HEIGHT);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    // The front end set isRefreshing to false
    paintProperty_->UpdateIsRefreshing(false);
    // isRefreshing changed by front end, will trigger OnModifyDone
    pattern_->OnModifyDone();
    // the mock AnimationUtils::Animate will trigger finishCallback
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
    pattern_->OnExitAnimationFinish(); // by OnModifyDone
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDrag distance > triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(150.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragStart ->  HandleDragUpdate -> HandleDragCancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(15.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(135.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(20.f + CUSTOM_NODE_HEIGHT);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragCancel();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: Drag003
 * @tc.desc: Test Drag in other conditions
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag003, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetTextStyle(TextStyle());
    modelNG.Pop();
    GetInstance();
    RunMeasureAndLayout();
    
    pattern_->HandleDragStart();

    /**
     * @tc.steps: step1. delat is 0
     * @tc.expected: return
     */
    pattern_->HandleDragUpdate(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    
    /**
     * @tc.steps: step2. drag to refresh
     * @tc.expected: refreshStatus_ is REFRESH
     */
    pattern_->HandleDragUpdate(155.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step2. When isRefreshing_ == true, HandleDragStart and HandleDragUpdate
     * @tc.expected: return
     */
    pattern_->HandleDragStart();
    pattern_->HandleDragUpdate(10.f);
    pattern_->HandleDragEnd();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: Pattern001
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Pattern001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    auto builder_1 = CreateCustomNode();
    modelNG.SetCustomBuilder(builder_1);
    GetInstance();

    /**
     * @tc.steps: step1. Add same custom node
     * @tc.expected: would not replace node
     */
    pattern_->AddCustomBuilderNode(builder_1);
    EXPECT_EQ(GetChildFrameNode(0), builder_1);

    auto builder_2 = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern_->AddCustomBuilderNode(builder_2);
    EXPECT_EQ(GetChildFrameNode(0), builder_2);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    auto builder = CreateCustomNode();
    modelNG.SetCustomBuilder(builder);
    modelNG.SetTextStyle(TextStyle());
    modelNG.Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    paintProperty_->UpdateIsRefreshing(false);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    paintProperty_->UpdateIsRefreshing(true);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: AttrRefreshing002
 * @tc.desc: Test attr refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing002, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetTextStyle(TextStyle());
    modelNG.Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    paintProperty_->UpdateIsRefreshing(false);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    paintProperty_->UpdateIsRefreshing(true);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshTest005
 * @tc.desc: Test RefreshModelNG will pop according to different child node.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshTest005, TestSize.Level1)
{
   /**
     * @tc.steps: step1. refreshNode->TotalChildCount() < 2.
     * @tc.expected: would add Text child
     */
    RefreshModelNG modelNG;
    modelNG.Create();
    modelNG.SetIsShowLastTime(true);
    auto frameNode_1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto refreshRenderProperty_1 = frameNode_1->GetPaintProperty<RefreshRenderProperty>();
    const std::string timeText_1 = "TimeText";
    refreshRenderProperty_1->UpdateTimeText(timeText_1);
    modelNG.Pop();
    EXPECT_EQ(refreshRenderProperty_1->GetLastTimeTextValue(), "");
    EXPECT_EQ(refreshRenderProperty_1->GetTimeTextValue(), "");
    auto text_1 = frameNode_1->GetChildAtIndex(0);
    auto textFrameNode_1 = AceType::DynamicCast<FrameNode>(text_1);
    auto textLayoutProperty_1 = textFrameNode_1->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty_1->GetContentValue(), timeText_1);

    /**
     * @tc.steps: step2. refreshNode->TotalChildCount() < 2 and SetIsShowLastTime(false).
     * @tc.expected: would add Text child, but child TimeText is std::nullopt
     */
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode_2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto refreshRenderProperty_2 = frameNode_2->GetPaintProperty<RefreshRenderProperty>();
    const std::string timeText_2 = "TimeText";
    refreshRenderProperty_2->UpdateTimeText(timeText_2);
    modelNG.Pop();
    EXPECT_EQ(refreshRenderProperty_2->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(refreshRenderProperty_2->GetTimeTextValue(), timeText_2);
    auto text_2 = frameNode_2->GetChildAtIndex(0);
    auto textFrameNode_2 = AceType::DynamicCast<FrameNode>(text_2);
    auto textLayoutProperty_2 = textFrameNode_2->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty_2->GetContent(), std::nullopt);

    /**
     * @tc.steps: step3. refreshNode->TotalChildCount() >= 2.
     * @tc.expected: Would not add text child.
     */
    modelNG.Create();
    auto frameNode_3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto textChild_3 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    frameNode_3->AddChild(textChild_3);
    auto loadingProgressChild_3 =
        FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
    frameNode_3->AddChild(loadingProgressChild_3);
    modelNG.Pop();
    EXPECT_GE(frameNode_3->TotalChildCount(), 2);
    auto refreshRenderProperty_3 = frameNode_3->GetPaintProperty<RefreshRenderProperty>();
    EXPECT_EQ(refreshRenderProperty_3->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(refreshRenderProperty_3->GetTimeText(), std::nullopt);

    /**
     * @tc.steps: step4. GetIsCustomBuilderExistValue() == true
     * @tc.expected: Would not add text child.
     */
    modelNG.Create();
    modelNG.SetIsShowLastTime(false);
    auto frameNode_4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto builder_4 = CreateCustomNode();
    modelNG.SetCustomBuilder(builder_4);
    modelNG.Pop();
    EXPECT_LT(frameNode_4->TotalChildCount(), 2);
    auto refreshRenderProperty_4 = frameNode_4->GetPaintProperty<RefreshRenderProperty>();
    EXPECT_EQ(refreshRenderProperty_4->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(refreshRenderProperty_4->GetTimeText(), std::nullopt);
}

/**
 * @tc.name: RefreshAccessibility001
 * @tc.desc: Test IsScrollable and SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshAccessibility001, TestSize.Level1)
{
    RefreshModelNG modelNG;
    modelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When IsScrollable() == true
     * @tc.expected: Trigger AddSupportAction()
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    std::unordered_set<AceAction> supportAceActions_1 = accessibilityProperty_->GetSupportAction();
    uint64_t actions_1 = 0, expectActions_1 = 0;
    expectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    for (auto action : supportAceActions_1) {
        actions_1 |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions_1, expectActions_1);

    /**
     * @tc.steps: step2. When IsScrollable() == false
     * @tc.expected: Nothing happend
     */
    pattern_->isRefreshing_ = true;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    std::unordered_set<AceAction> supportAceActions_2 = accessibilityProperty_->GetSupportAction();
    uint64_t actions_2 = 0, expectActions_2 = 0;
    for (auto action : supportAceActions_2) {
        actions_2 |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions_2, expectActions_2);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: RefreshAccessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, PerformActionTest001, TestSize.Level1)
{
    RefreshModelNG refreshModelNG;
    refreshModelNG.Create();
    GetInstance();
    RunMeasureAndLayout(); // trigger SetAccessibilityAction()

    /**
     * @tc.steps: step1. pattern->IsRefreshing() == false
     * @tc.expected: return
     */
    pattern_->isRefreshing_ = false;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());

    /**
     * @tc.steps: step2. pattern->IsRefreshing() == true
     * @tc.expected: Trigger HandleDragStart() ...
     */
    pattern_->isRefreshing_ = true;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
}
} // namespace OHOS::Ace::NG
