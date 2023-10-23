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
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float CUSTOM_NODE_WIDTH = 100.f;
constexpr float CUSTOM_NODE_HEIGHT = 10.f;
const std::string TIME_TEXT = "TimeText";
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 42;
constexpr float PERCENT = 0.01; // Percent
constexpr Dimension TRIGGER_REFRESH_DISTANCE = 64.0_vp;
} // namespace
class RefreshTestNg : public testing::Test, public TestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(RefreshModelNG)>& callback = nullptr);
    static RefPtr<FrameNode> CreateCustomNode();
    void VersionElevenHandleDragEnd(float speed, float targetOffsetY);

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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RefreshTheme>()));
}

void RefreshTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void RefreshTestNg::SetUp() {}

void RefreshTestNg::TearDown()
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
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

void RefreshTestNg::Create(const std::function<void(RefreshModelNG)>& callback)
{
    RefreshModelNG model;
    model.Create();
    model.SetTextStyle(TextStyle());
    if (callback) {
        callback(model);
    }
    model.Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

RefPtr<FrameNode> RefreshTestNg::CreateCustomNode()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CUSTOM_NODE_WIDTH), CalcLength(CUSTOM_NODE_HEIGHT)));
    return frameNode;
}

void RefreshTestNg::VersionElevenHandleDragEnd(float speed, float targetOffsetY)
{
    pattern_->HandleDragEnd(speed);
    pattern_->scrollOffset_.SetY(targetOffsetY);
    pattern_->SpeedAnimationFinish();
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test Drag
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag001, TestSize.Level1)
{
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
        model.SetOnStateChange(std::move(onStateChange));
    });
    const float radio = DEFAULT_FRICTION_RATIO * PERCENT;
    const float lessThanOffset = DEFAULT_INDICATOR_OFFSET / radio;
    const float greaterThanOffset = 1 / radio;
    const float greaterThanRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx() / radio - lessThanOffset;

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd(0.0f);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);
    // The front end set isRefreshing to false
    paintProperty_->UpdateIsRefreshing(false);
    // isRefreshing changed by front end, will trigger OnModifyDone
    pattern_->OnModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
    pattern_->OnExitAnimationFinish(); // by OnModifyDone
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDrag distance < triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.0f);
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDrag to cancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance);
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
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });
    const float radio = DEFAULT_FRICTION_RATIO * PERCENT;
    const float lessThanOffset = DEFAULT_INDICATOR_OFFSET / radio;
    const float greaterThanOffset = 1 / radio;
    const float greaterThanRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx() / radio - lessThanOffset;

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance + CUSTOM_NODE_HEIGHT / radio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd(0.0f);
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
     * @tc.steps: step2. HandleDrag distance < triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.0f);
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragStart ->  HandleDragUpdate -> HandleDragCancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance + CUSTOM_NODE_HEIGHT / radio);
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
    Create();
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
    pattern_->HandleDragEnd(0.0f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step2. When isRefreshing_ == true, HandleDragStart and HandleDragUpdate
     * @tc.expected: return
     */
    pattern_->HandleDragStart();
    pattern_->HandleDragUpdate(10.f);
    pattern_->HandleDragEnd(0.0f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: AddCustomBuilderNode001
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode001, TestSize.Level1)
{
    auto builder = CreateCustomNode();
    Create([&builder](RefreshModelNG model) { model.SetCustomBuilder(builder); });

    /**
     * @tc.steps: step1. Add same custom node
     * @tc.expected: would not replace node
     */
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);

    /**
     * @tc.steps: step2. Add diff custom node
     * @tc.expected: would replace node
     */
    builder = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing001, TestSize.Level1)
{
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });

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
    Create();

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
 * @tc.name: RefreshModelNG001
 * @tc.desc: Test RefreshModelNG will pop according to different child node.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshModelNG001, TestSize.Level1)
{
   /**
     * @tc.steps: step1. refreshNode->TotalChildCount() < 2.
     * @tc.expected: would add Text child
     */
    Create([](RefreshModelNG model) {
        model.SetIsShowLastTime(true);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto paintProperty = frameNode->GetPaintProperty<RefreshRenderProperty>();
        paintProperty->UpdateTimeText(TIME_TEXT);
    });
    EXPECT_EQ(paintProperty_->GetLastTimeTextValue(), "");
    EXPECT_EQ(paintProperty_->GetTimeTextValue(), "");
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty->GetContentValue(), TIME_TEXT);

    /**
     * @tc.steps: step2. refreshNode->TotalChildCount() < 2 and SetIsShowLastTime(false).
     * @tc.expected: would add Text child, but child TimeText is std::nullopt
     */
    Create([](RefreshModelNG model) {
        model.SetIsShowLastTime(false);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto paintProperty = frameNode->GetPaintProperty<RefreshRenderProperty>();
        paintProperty->UpdateTimeText(TIME_TEXT);
    });
    EXPECT_EQ(paintProperty_->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(paintProperty_->GetTimeTextValue(), TIME_TEXT);
    textNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty->GetContent(), std::nullopt);

    /**
     * @tc.steps: step3. refreshNode->TotalChildCount() >= 2.
     * @tc.expected: Would not add text child.
     */
    Create([](RefreshModelNG model) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        auto loadingProgressChild =
            FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<LoadingProgressPattern>());
        frameNode->AddChild(textChild);
        frameNode->AddChild(loadingProgressChild);
    });
    EXPECT_GE(frameNode_->TotalChildCount(), 2);
    EXPECT_EQ(paintProperty_->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(paintProperty_->GetTimeText(), std::nullopt);

    /**
     * @tc.steps: step4. GetIsCustomBuilderExistValue() == true
     * @tc.expected: Would not add text child.
     */
    Create([](RefreshModelNG model) {
        model.SetIsShowLastTime(false);
        model.SetCustomBuilder(CreateCustomNode());
    });
    EXPECT_LT(frameNode_->TotalChildCount(), 2);
    EXPECT_EQ(paintProperty_->GetLastTimeText(), std::nullopt);
    EXPECT_EQ(paintProperty_->GetTimeText(), std::nullopt);
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test IsScrollable and SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AccessibilityProperty001, TestSize.Level1)
{
    Create();

    /**
     * @tc.steps: step1. When IsScrollable() == true
     * @tc.expected: Trigger AddSupportAction()
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. When IsScrollable() == false
     * @tc.expected: Nothing happend
     */
    pattern_->isRefreshing_ = true;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: RefreshAccessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, PerformActionTest001, TestSize.Level1)
{
    Create(); // trigger SetAccessibilityAction()

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

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: OnKeyEvent return false
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, OnKeyEvent001, TestSize.Level1)
{
    Create();

    /**
     * @tc.steps: step1. KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN)));

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN,
        KeyAction::UNKNOWN,
        { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_UNKNOWN },
        0, TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD
    )));
}

/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: OnKeyEvent return true
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, OnKeyEvent002, TestSize.Level1)
{
    bool isTrigger = false;
    auto onRefreshing = [&isTrigger]() { isTrigger = true; };
    Create([onRefreshing](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
    });

    /**
     * @tc.steps: step1. KeyCode::KEY_F5
     * @tc.expected: trigger onRefresh event
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_F5, KeyAction::UNKNOWN)));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_R
     * @tc.expected: no trigger onRefresh event
     */
    isTrigger = false;
    EXPECT_TRUE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN,
        KeyAction::UNKNOWN,
        { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_R },
        0, TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD
    )));
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: VersionElevenDrag001
 * @tc.desc: Test Drag
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, VersionElevenDrag001, TestSize.Level1)
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
        model.SetOnStateChange(std::move(onStateChange));
    });
    const float radio = DEFAULT_FRICTION_RATIO * PERCENT;
    const float lessThanOffset = DEFAULT_INDICATOR_OFFSET / radio;
    const float greaterThanOffset = 1 / radio;
    const float greaterThanRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx() / radio - lessThanOffset;

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    VersionElevenHandleDragEnd(1200.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);
    // The front end set isRefreshing to false
    paintProperty_->UpdateIsRefreshing(false);
    // isRefreshing changed by front end, will trigger OnModifyDone
    pattern_->OnModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
    pattern_->OnExitAnimationFinish(); // by OnModifyDone
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDrag distance < triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    VersionElevenHandleDragEnd(1200.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDrag to cancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragCancel();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: VersionElevenDrag002
 * @tc.desc: Test Drag with customBuilder_
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, VersionElevenDrag002, TestSize.Level1)
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });
    const float radio = DEFAULT_FRICTION_RATIO * PERCENT;
    const float lessThanOffset = DEFAULT_INDICATOR_OFFSET / radio;
    const float greaterThanOffset = 1 / radio;
    const float greaterThanRefreshDistance = TRIGGER_REFRESH_DISTANCE.ConvertToPx() / radio - lessThanOffset;

    /**
     * @tc.steps: step1. HandleDrag to refresh, and set IsRefreshing to false by front end
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance + CUSTOM_NODE_HEIGHT / radio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    VersionElevenHandleDragEnd(0.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
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
     * @tc.steps: step2. HandleDrag distance < triggerRefreshDistance
     * @tc.expected: would not trigger refresh
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    VersionElevenHandleDragEnd(0.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragStart ->  HandleDragUpdate -> HandleDragCancel
     * @tc.expected: RefreshStatus would change width action
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(lessThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanOffset);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(greaterThanRefreshDistance + CUSTOM_NODE_HEIGHT / radio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragCancel();
    pattern_->OnExitAnimationFinish();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: VersionElevenDrag003
 * @tc.desc: Test Drag in other conditions
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, VersionElevenDrag003, TestSize.Level1)
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    Create();
    pattern_->HandleDragStart();

    /**
     * @tc.steps: step1. delat is 0
     * @tc.expected: return
     */
    pattern_->HandleDragUpdate(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. drag to refresh
     * @tc.expected: refreshStatus_ is REFRESH
     */
    pattern_->HandleDragUpdate(155.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    VersionElevenHandleDragEnd(1200.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step2. When isRefreshing_ == true, HandleDragStart and HandleDragUpdate
     * @tc.expected: return
     */
    pattern_->HandleDragStart();
    pattern_->HandleDragUpdate(10.f);
    VersionElevenHandleDragEnd(1200.f, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: VersionElevenAttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, VersionElevenAttrRefreshing001, TestSize.Level1)
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });

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
 * @tc.name: VersionElevenAttrRefreshing002
 * @tc.desc: Test attr refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, VersionElevenAttrRefreshing002, TestSize.Level1)
{
    MockPipelineBase::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_ELEVEN);
    Create();

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
} // namespace OHOS::Ace::NG
