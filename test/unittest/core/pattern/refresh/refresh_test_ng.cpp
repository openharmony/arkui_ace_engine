/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "refresh_test_ng.h"

namespace OHOS::Ace::NG {
void RefreshTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RefreshTheme>()));
}

void RefreshTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RefreshTestNg::SetUp() {}

void RefreshTestNg::TearDown()
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void RefreshTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RefreshPattern>();
    eventHub_ = frameNode_->GetEventHub<RefreshEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RefreshLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<RefreshAccessibilityProperty>();
}

void RefreshTestNg::Create(const std::function<void(RefreshModelNG)>& callback)
{
    RefreshModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(REFRESH_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

RefPtr<FrameNode> RefreshTestNg::CreateCustomNode()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(CUSTOM_NODE_WIDTH), CalcLength(CUSTOM_NODE_HEIGHT)));
    return frameNode;
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test drag low version, test whole refresh movement
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

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than TRIGGER_LOADING_DISTANCE
     * @tc.expected: scrollOffset_ is 1.f, onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate(1.f / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step5. HandleDragEnd
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    EXPECT_FALSE(isRefreshTrigger); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);

    /**
     * @tc.steps: step6. The front end set isRefreshing to false
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: Drag002
 * @tc.desc: Test drag low version, test cancel refresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: CustomDrag001
 * @tc.desc: Test drag with customBuilder_ low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, DISABLED_CustomDrag001, TestSize.Level1)
{
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
        model.SetOnStateChange(std::move(onStateChange));
        model.SetCustomBuilder(CreateCustomNode());
    });

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than TRIGGER_LOADING_DISTANCE
     * @tc.expected: scrollOffset_ is 1.f, onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate(1.f / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate(((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx()) / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step5. HandleDragEnd
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    EXPECT_FALSE(isRefreshTrigger); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);

    /**
     * @tc.steps: step6. The front end set isRefreshing to false
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: CustomDrag002
 * @tc.desc: Test drag with customBuilder_ low version, test cancel refresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, CustomDrag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    Create([](RefreshModelNG model) {
        model.SetCustomBuilder(CreateCustomNode());
    });
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
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
 * @tc.name: AddCustomBuilderNode002
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh
     * @tc.expected: init progress node.
     */
    Create([](RefreshModelNG model) { model.SetProgressColor(Color::BLUE); });
    EXPECT_EQ(layoutProperty_->GetProgressColor(), Color::BLUE);
    auto builder = CreateCustomNode();
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);
    EXPECT_NE(pattern_->progressChild_, nullptr);

    /**
     * @tc.steps: step2. init child node
     * @tc.expected: remove progress child.
     */
    int32_t childrenSize = frameNode_->GetChildren().size();
    pattern_->InitChildNode();
    EXPECT_EQ(pattern_->progressChild_, nullptr);
    EXPECT_EQ(frameNode_->GetChildren().size(), childrenSize - 1);

    /**
     * @tc.steps: step3. set null custom node
     * @tc.expected: isCustomBuilderExist_ is false, customBuilder_ is nullptr.
     */
    pattern_->AddCustomBuilderNode(nullptr);
    EXPECT_FALSE(pattern_->isCustomBuilderExist_);
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
}

/**
 * @tc.name: AddCustomBuilderNode003
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh with child node
     */
    auto builder = CreateCustomNode();
    RefreshModelNG model;
    model.Create();
    model.SetCustomBuilder(builder);
    {
        TextModelNG model;
        model.Create("text");
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->TotalChildCount(), 2);

    /**
     * @tc.steps: step2. set isCustomBuilderExist_ = false
     * @tc.expected: Check frameNode child node size.
     */
    pattern_->AddCustomBuilderNode(nullptr);
    EXPECT_FALSE(pattern_->isCustomBuilderExist_);
    pattern_->InitChildNode();
    EXPECT_EQ(frameNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing001, TestSize.Level1)
{
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: AttrRefreshing002
 * @tc.desc: Test attr refreshing low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing002, TestSize.Level1)
{
    Create();

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
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
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_UNKNOWN }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
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
    Create([onRefreshing](RefreshModelNG model) { model.SetOnRefreshing(std::move(onRefreshing)); });

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
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_R }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Frame Scene TEST
 * @tc.desc: Test frame ratio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshDragFrameRatio001, TestSize.Level1)
{
    Create();
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    frameNode_->renderContext_ = renderContext;
    // CalcExpectedFrameRate will be called
    pattern_->HandleDragStart();
    pattern_->HandleDragUpdate(0.0f);
    pattern_->HandleDragEnd(0.0f);
}

/**
 * @tc.name: GetTargetOffset001
 * @tc.desc: Test frame ratio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, GetTargetOffset001, TestSize.Level1)
{
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), 0.f);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() / RADIO);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    pattern_->HandleDragEnd(0.f);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE.ConvertToPx());
}
} // namespace OHOS::Ace::NG
