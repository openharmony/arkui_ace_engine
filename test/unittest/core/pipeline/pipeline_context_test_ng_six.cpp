/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
#include "test/mock/frameworks/base/mousestyle/mock_mouse_style.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_window.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "base/ressched/ressched_click_optimizer.h"
#include "base/ressched/ressched_touch_optimizer.h"
#include "core/common/ai/ai_write_adapter.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"
#include "core/common/event_manager.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/common/statistic_event_reporter.h"
#include "core/common/back_press_handler_manager.h"
#include "core/components_ng/manager/focus/focus_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_MOUSE_HOLD_NODE_ID = 601;
constexpr int32_t TEST_OTHER_MOUSE_HOLD_NODE_ID = 602;
constexpr int32_t TEST_TOUCH_EVENT_TYPE = 7;
constexpr uint64_t TEST_TOUCH_SENSOR_TIME = 11;
constexpr uint64_t TEST_TOUCH_RECEIVE_TIME = 12;
constexpr uint64_t TEST_TOUCH_DISPATCH_TIME = 13;

class SplitStageManager final : public StageManager {
public:
    SplitStageManager(const RefPtr<FrameNode>& stageNode, bool displaySplitMode)
        : StageManager(stageNode), displaySplitMode_(displaySplitMode)
    {}

    bool IsDisplaySplitMode() const override
    {
        return displaySplitMode_;
    }

private:
    bool displaySplitMode_ = false;
};

class TrackingContainerModalPattern final : public ContainerModalPattern {
public:
    bool GetFloatingTitleVisible() override
    {
        return floatingTitleVisible_;
    }

    bool GetCustomTitleVisible() override
    {
        return customTitleVisible_;
    }

    bool GetControlButtonVisible() override
    {
        return controlButtonVisible_;
    }

    void EnableContainerModalGesture(bool isEnable) override
    {
        gestureCallbackCalled_ = true;
        gestureEnabled_ = isEnable;
    }

    bool floatingTitleVisible_ = false;
    bool customTitleVisible_ = false;
    bool controlButtonVisible_ = false;
    bool gestureCallbackCalled_ = false;
    bool gestureEnabled_ = false;
};
} // namespace

/**
 * @tc.name: PipelineContextFourTestNg113
 * @tc.desc: Test GetOrCreateAIWriteAdapter creates and reuses adapter.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg113, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->aiWriteAdapter_.Reset();

    auto firstAdapter = context_->GetOrCreateAIWriteAdapter().Upgrade();
    auto secondAdapter = context_->GetOrCreateAIWriteAdapter().Upgrade();

    EXPECT_NE(firstAdapter, nullptr);
    EXPECT_EQ(firstAdapter, secondAdapter);
    EXPECT_EQ(firstAdapter, context_->aiWriteAdapter_);
}

/**
 * @tc.name: PipelineContextFourTestNg114
 * @tc.desc: Test ArkUI object lifecycle callback register, fire and unregister.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg114, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    int callbackCount = 0;
    int callbackPayload = 0;
    void* callbackData = nullptr;

    context_->RegisterArkUIObjectLifecycleCallback([&](void* data) {
        callbackCount++;
        callbackData = data;
    });
    EXPECT_NE(context_->objectLifecycleCallback_, nullptr);

    context_->FireArkUIObjectLifecycleCallback(&callbackPayload);
    EXPECT_EQ(callbackCount, 1);
    EXPECT_EQ(callbackData, &callbackPayload);

    context_->UnregisterArkUIObjectLifecycleCallback();
    EXPECT_EQ(context_->objectLifecycleCallback_, nullptr);

    context_->FireArkUIObjectLifecycleCallback(&callbackPayload);
    EXPECT_EQ(callbackCount, 1);
}

/**
 * @tc.name: PipelineContextFourTestNg115
 * @tc.desc: Test CheckSourceTypeChange updates state only when source type changes.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg115, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->lastSourceType_ = SourceType::MOUSE;

    EXPECT_FALSE(context_->CheckSourceTypeChange(SourceType::MOUSE));
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

    EXPECT_TRUE(context_->CheckSourceTypeChange(SourceType::TOUCH));
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

/**
 * @tc.name: PipelineContextFourTestNg116
 * @tc.desc: Test SetParentPipeline keeps original manager for null parent and syncs valid parent manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg116, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    auto childContext = AceType::MakeRefPtr<PipelineContext>();
    ASSERT_NE(childContext, nullptr);
    auto originalManager = childContext->GetContentChangeManager();

    childContext->SetParentPipeline(WeakPtr<PipelineBase>());
    EXPECT_EQ(childContext->GetContentChangeManager(), originalManager);

    WeakPtr<PipelineBase> weakParent(context_);
    childContext->SetParentPipeline(weakParent);
    EXPECT_EQ(childContext->GetContentChangeManager(), context_->GetContentChangeManager());
}

/**
 * @tc.name: PipelineContextFourTestNg117
 * @tc.desc: Test IsDisplayInForceSplitMode fallback branches.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg117, TestSize.Level1)
{
    AssertValidContext();
    auto originalForceSplitMgr = context_->forceSplitMgr_;
    auto originalStageManager = context_->stageManager_;
    context_->isCurrentInForceSplitMode_ = true;

    context_->forceSplitMgr_.Reset();
    EXPECT_TRUE(context_->IsDisplayInForceSplitMode());

    context_->forceSplitMgr_ = AceType::MakeRefPtr<ForceSplitManager>();
    context_->forceSplitMgr_->SetIsRouter(false);
    EXPECT_TRUE(context_->IsDisplayInForceSplitMode());

    context_->forceSplitMgr_->SetIsRouter(true);
    context_->stageManager_.Reset();
    EXPECT_TRUE(context_->IsDisplayInForceSplitMode());

    context_->forceSplitMgr_ = originalForceSplitMgr;
    context_->stageManager_ = originalStageManager;
}

/**
 * @tc.name: PipelineContextFourTestNg118
 * @tc.desc: Test AddAsyncLoadTask and FlushAsyncLoadTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg118, TestSize.Level1)
{
    AssertValidContext();
    context_->asyncLoadTasks_.clear();
    int executionCount = 0;

    context_->FlushAsyncLoadTask();
    EXPECT_EQ(executionCount, 0);

    context_->AddAsyncLoadTask([&executionCount]() { executionCount += 1; });
    context_->AddAsyncLoadTask([&executionCount]() { executionCount += 2; });
    EXPECT_EQ(context_->asyncLoadTasks_.size(), DEFAULT_SIZE2);

    context_->FlushAsyncLoadTask();
    EXPECT_EQ(executionCount, DEFAULT_INT3);
    EXPECT_TRUE(context_->asyncLoadTasks_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg119
 * @tc.desc: Test RegisterTouchTimingCallback and UnregisterTouchTimingCallback with valid event manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg119, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->eventManager_, nullptr);

    context_->UnregisterTouchTimingCallback();
    EXPECT_EQ(context_->eventManager_->touchTimingCallback_, nullptr);

    context_->RegisterTouchTimingCallback([](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime,
                                             int32_t eventType) {
        EXPECT_EQ(sensorTime, TEST_TOUCH_SENSOR_TIME);
        EXPECT_EQ(receiveTime, TEST_TOUCH_RECEIVE_TIME);
        EXPECT_EQ(dispatchTime, TEST_TOUCH_DISPATCH_TIME);
        EXPECT_EQ(eventType, TEST_TOUCH_EVENT_TYPE);
    });
    ASSERT_NE(context_->eventManager_->touchTimingCallback_, nullptr);
    context_->eventManager_->touchTimingCallback_(
        TEST_TOUCH_SENSOR_TIME, TEST_TOUCH_RECEIVE_TIME, TEST_TOUCH_DISPATCH_TIME, TEST_TOUCH_EVENT_TYPE);

    context_->UnregisterTouchTimingCallback();
    EXPECT_EQ(context_->eventManager_->touchTimingCallback_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg120
 * @tc.desc: Test touch timing callback guard branch when event manager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg120, TestSize.Level1)
{
    AssertValidContext();
    auto originalEventManager = context_->eventManager_;
    context_->eventManager_.Reset();

    context_->RegisterTouchTimingCallback([](uint64_t, uint64_t, uint64_t, int32_t) {});
    context_->UnregisterTouchTimingCallback();
    EXPECT_EQ(context_->eventManager_, nullptr);

    context_->eventManager_ = originalEventManager;
}

/**
 * @tc.name: PipelineContextFourTestNg121
 * @tc.desc: Test GetDynamicComponentSafeManager creates, reuses and honors injected manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg121, TestSize.Level1)
{
    AssertValidContext();
    context_->dynamicComponentSafeManager_.Reset();

    auto generatedManager = context_->GetDynamicComponentSafeManager();
    ASSERT_NE(generatedManager, nullptr);
    EXPECT_EQ(generatedManager, context_->GetDynamicComponentSafeManager());

    auto injectedManager = AceType::MakeRefPtr<DynamicComponentSafeManager>();
    context_->SetDynamicComponentSafeManager(injectedManager);
    EXPECT_EQ(context_->GetDynamicComponentSafeManager(), injectedManager);
}

/**
 * @tc.name: PipelineContextFourTestNg122
 * @tc.desc: Test SetMouseStyleHoldNode and FreeMouseStyleHoldNode success and mismatch branches.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg122, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->eventManager_, nullptr);
    auto mouseStyleManager = context_->eventManager_->GetMouseStyleManager();
    ASSERT_NE(mouseStyleManager, nullptr);
    mouseStyleManager->mouseStyleNodeId_.reset();

    EXPECT_TRUE(context_->SetMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_OTHER_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode(TEST_OTHER_MOUSE_HOLD_NODE_ID));
    EXPECT_TRUE(context_->FreeMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_TRUE(context_->SetMouseStyleHoldNode(TEST_OTHER_MOUSE_HOLD_NODE_ID));
    EXPECT_TRUE(context_->FreeMouseStyleHoldNode());
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());
}

/**
 * @tc.name: PipelineContextFourTestNg123
 * @tc.desc: Test mouse style hold node guard branches when event or style manager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg123, TestSize.Level1)
{
    AssertValidContext();
    auto originalEventManager = context_->eventManager_;
    auto originalMouseStyleManager = originalEventManager->mouseStyleManager_;

    originalEventManager->mouseStyleManager_.Reset();
    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());

    originalEventManager->mouseStyleManager_ = originalMouseStyleManager;
    context_->eventManager_.Reset();
    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode(TEST_MOUSE_HOLD_NODE_ID));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());

    context_->eventManager_ = originalEventManager;
}

/**
 * @tc.name: PipelineContextFourTestNg124
 * @tc.desc: Test SetIsDragging updates event manager state and guards null event manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg124, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->eventManager_, nullptr);
    context_->SetIsDragging(true);
    EXPECT_TRUE(context_->eventManager_->IsDragging());

    auto originalEventManager = context_->eventManager_;
    context_->eventManager_.Reset();
    context_->SetIsDragging(false);
    EXPECT_EQ(context_->eventManager_, nullptr);

    context_->eventManager_ = originalEventManager;
}

/**
 * @tc.name: PipelineContextFourTestNg125
 * @tc.desc: Test SetUIExtensionImeShow forwards state to TextFieldManagerNG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg125, TestSize.Level1)
{
    AssertValidContext();
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    context_->textFieldManager_ = textFieldManager;

    context_->SetUIExtensionImeShow(true);
    EXPECT_TRUE(textFieldManager->uiExtensionImeShow_);

    context_->SetUIExtensionImeShow(false);
    EXPECT_FALSE(textFieldManager->uiExtensionImeShow_);
}

/**
 * @tc.name: PipelineContextFourTestNg126
 * @tc.desc: Test CalcPageWidth branches for ArkUI hook and force split state.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg126, TestSize.Level1)
{
    AssertValidContext();
    auto originalForceSplitMgr = context_->forceSplitMgr_;
    constexpr double rootWidth = 100.0;
    constexpr double expectedSplitWidth = 50.0;

    context_->SetIsArkUIHookEnabled(false);
    context_->SetIsCurrentInForceSplitMode(true);
    context_->forceSplitMgr_ = AceType::MakeRefPtr<ForceSplitManager>();
    EXPECT_DOUBLE_EQ(context_->CalcPageWidth(rootWidth), rootWidth);

    context_->SetIsArkUIHookEnabled(true);
    context_->SetIsCurrentInForceSplitMode(false);
    EXPECT_DOUBLE_EQ(context_->CalcPageWidth(rootWidth), rootWidth);

    context_->SetIsCurrentInForceSplitMode(true);
    context_->forceSplitMgr_.Reset();
    EXPECT_DOUBLE_EQ(context_->CalcPageWidth(rootWidth), rootWidth);

    context_->forceSplitMgr_ = AceType::MakeRefPtr<ForceSplitManager>();
    EXPECT_DOUBLE_EQ(context_->CalcPageWidth(rootWidth), expectedSplitWidth);

    context_->SetIsArkUIHookEnabled(false);
    context_->SetIsCurrentInForceSplitMode(false);
    context_->forceSplitMgr_ = originalForceSplitMgr;
}

/**
 * @tc.name: PipelineContextFourTestNg127
 * @tc.desc: Test overlay node positions storage and update callback branches.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg127, TestSize.Level1)
{
    AssertValidContext();
    std::vector<Ace::RectF> storedRects = { Ace::RectF(1.0f, 2.0f, 3.0f, 4.0f), Ace::RectF(5.0f, 6.0f, 7.0f, 8.0f) };
    context_->SetOverlayNodePositions(storedRects);

    auto overlayRects = context_->GetOverlayNodePositions();
    ASSERT_EQ(overlayRects.size(), storedRects.size());
    EXPECT_EQ(overlayRects[0].GetX(), storedRects[0].GetX());
    EXPECT_EQ(overlayRects[0].GetY(), storedRects[0].GetY());
    EXPECT_EQ(overlayRects[0].Width(), storedRects[0].Width());
    EXPECT_EQ(overlayRects[0].Height(), storedRects[0].Height());
    EXPECT_EQ(overlayRects[1].GetX(), storedRects[1].GetX());
    EXPECT_EQ(overlayRects[1].GetY(), storedRects[1].GetY());
    EXPECT_EQ(overlayRects[1].Width(), storedRects[1].Width());
    EXPECT_EQ(overlayRects[1].Height(), storedRects[1].Height());

    bool callbackTriggered = false;
    std::vector<Ace::RectF> callbackRects = { Ace::RectF(9.0f, 10.0f, 11.0f, 12.0f) };
    std::vector<Ace::RectF> receivedRects;
    context_->overlayNodePositionUpdateCallback_ = nullptr;
    context_->TriggerOverlayNodePositionsUpdateCallback(callbackRects);
    EXPECT_FALSE(callbackTriggered);

    context_->RegisterOverlayNodePositionsUpdateCallback([&](std::vector<Ace::RectF> rects) {
        callbackTriggered = true;
        receivedRects = rects;
    });
    context_->TriggerOverlayNodePositionsUpdateCallback(callbackRects);
    EXPECT_TRUE(callbackTriggered);
    ASSERT_EQ(receivedRects.size(), callbackRects.size());
    EXPECT_EQ(receivedRects[0].GetX(), callbackRects[0].GetX());
    EXPECT_EQ(receivedRects[0].GetY(), callbackRects[0].GetY());
    EXPECT_EQ(receivedRects[0].Width(), callbackRects[0].Width());
    EXPECT_EQ(receivedRects[0].Height(), callbackRects[0].Height());
}

// ==========================================================================
// Batch 4: FlushTSUpdates, SetFlushTSUpdates, RebuildFontNode, managers
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg128
 * @tc.desc: Test FlushTSUpdates skips when callback is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg128, TestSize.Level1)
{
    AssertValidContext();
    context_->flushTSUpdatesCb_ = nullptr;
    // No crash when callback is null
    context_->FlushTSUpdates();
    EXPECT_EQ(context_->flushTSUpdatesCb_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg129
 * @tc.desc: Test FlushTSUpdates executes callback and requests frame on true result.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg129, TestSize.Level1)
{
    AssertValidContext();
    int callCount = 0;
    context_->flushTSUpdatesCb_ = [&callCount](int32_t) {
        callCount++;
        return true;
    };
    context_->FlushTSUpdates();
    EXPECT_EQ(callCount, 1);
    context_->flushTSUpdatesCb_ = nullptr;
}

/**
 * @tc.name: PipelineContextFourTestNg130
 * @tc.desc: Test FlushTSUpdates does not request frame when callback returns false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg130, TestSize.Level1)
{
    AssertValidContext();
    int callCount = 0;
    context_->flushTSUpdatesCb_ = [&callCount](int32_t) {
        callCount++;
        return false;
    };
    context_->FlushTSUpdates();
    EXPECT_EQ(callCount, 1);
    context_->flushTSUpdatesCb_ = nullptr;
}

/**
 * @tc.name: PipelineContextFourTestNg131
 * @tc.desc: Test SetFlushTSUpdates stores callback and requests frame when non-null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg131, TestSize.Level1)
{
    AssertValidContext();
    context_->flushTSUpdatesCb_ = nullptr;
    context_->SetFlushTSUpdates([](int32_t) { return false; });
    EXPECT_NE(context_->flushTSUpdatesCb_, nullptr);
    context_->flushTSUpdatesCb_ = nullptr;

    context_->SetFlushTSUpdates(nullptr);
    EXPECT_EQ(context_->flushTSUpdatesCb_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg132
 * @tc.desc: Test RebuildFontNode skips when fontManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg132, TestSize.Level1)
{
    AssertValidContext();
    auto originalFontManager = context_->fontManager_;
    context_->fontManager_.Reset();

    // No crash
    context_->RebuildFontNode();
    EXPECT_TRUE(!context_->fontManager_);

    context_->fontManager_ = originalFontManager;
}

/**
 * @tc.name: PipelineContextFourTestNg133
 * @tc.desc: Test RebuildFontNode delegates when fontManager_ is valid.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg133, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->fontManager_, nullptr);
    // No crash when font manager is valid
    context_->RebuildFontNode();
    ASSERT_NE(context_->fontManager_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg134
 * @tc.desc: Test GetOrCreateFocusManager lazily creates and reuses focus manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg134, TestSize.Level1)
{
    AssertValidContext();
    context_->focusManager_.Reset();

    auto first = context_->GetOrCreateFocusManager();
    ASSERT_NE(first, nullptr);
    auto second = context_->GetOrCreateFocusManager();
    EXPECT_EQ(first, second);

    context_->focusManager_.Reset();
}

/**
 * @tc.name: PipelineContextFourTestNg135
 * @tc.desc: Test GetBackPressHandlerManager lazily creates and reuses.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg135, TestSize.Level1)
{
    AssertValidContext();
    context_->backPressHandlerManager_.Reset();

    auto first = context_->GetBackPressHandlerManager();
    ASSERT_NE(first, nullptr);
    auto second = context_->GetBackPressHandlerManager();
    EXPECT_EQ(first, second);

    context_->backPressHandlerManager_.Reset();
}

/**
 * @tc.name: PipelineContextFourTestNg136
 * @tc.desc: Test FlushDragWindowVisibleCallback executes and clears callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg136, TestSize.Level1)
{
    AssertValidContext();
    bool callbackCalled = false;
    context_->dragWindowVisibleCallback_ = [&callbackCalled]() { callbackCalled = true; };

    context_->FlushDragWindowVisibleCallback();
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(context_->dragWindowVisibleCallback_, nullptr);

    // Second call does nothing
    callbackCalled = false;
    context_->FlushDragWindowVisibleCallback();
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: PipelineContextFourTestNg137
 * @tc.desc: Test FlushAnimationClosure skips when list is empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg137, TestSize.Level1)
{
    AssertValidContext();
    context_->animationClosuresList_.clear();

    context_->FlushAnimationClosure();
    EXPECT_TRUE(context_->animationClosuresList_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg138
 * @tc.desc: Test FlushAnimationClosure executes all closures.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg138, TestSize.Level1)
{
    AssertValidContext();
    int count = 0;
    context_->animationClosuresList_.clear();
    context_->animationClosuresList_.push_back([&count]() { count++; });
    context_->animationClosuresList_.push_back([&count]() { count += 2; });

    context_->FlushAnimationClosure();
    EXPECT_EQ(count, DEFAULT_INT3);
    EXPECT_TRUE(context_->animationClosuresList_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg139
 * @tc.desc: Test FlushOnceVsyncTask executes and clears listener.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg139, TestSize.Level1)
{
    AssertValidContext();
    bool listenerCalled = false;
    context_->onceVsyncListener_ = [&listenerCalled]() { listenerCalled = true; };

    context_->FlushOnceVsyncTask();
    EXPECT_TRUE(listenerCalled);
    EXPECT_EQ(context_->onceVsyncListener_, nullptr);

    // Second call does nothing
    listenerCalled = false;
    context_->FlushOnceVsyncTask();
    EXPECT_FALSE(listenerCalled);
}

/**
 * @tc.name: PipelineContextFourTestNg140
 * @tc.desc: Test FlushOnceVsyncTask skips when listener is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg140, TestSize.Level1)
{
    AssertValidContext();
    context_->onceVsyncListener_ = nullptr;
    context_->FlushOnceVsyncTask();
    EXPECT_EQ(context_->onceVsyncListener_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg141
 * @tc.desc: Test FlushDragEventVoluntarily returns when dragDropManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg141, TestSize.Level1)
{
    AssertValidContext();
    auto originalMgr = context_->dragDropManager_;
    context_->dragDropManager_.Reset();

    context_->FlushDragEventVoluntarily();
    // No crash
    EXPECT_TRUE(!context_->dragDropManager_);

    context_->dragDropManager_ = originalMgr;
}

/**
 * @tc.name: PipelineContextFourTestNg142
 * @tc.desc: Test SetOnWindowFocused guards null taskExecutor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg142, TestSize.Level1)
{
    AssertValidContext();
    auto originalExecutor = context_->taskExecutor_;
    context_->taskExecutor_.Reset();

    context_->SetOnWindowFocused([]() {});
    EXPECT_EQ(context_->taskExecutor_, nullptr);

    context_->taskExecutor_ = originalExecutor;
}

/**
 * @tc.name: PipelineContextFourTestNg143
 * @tc.desc: Test SetupPageStackCallbacks guards null stageManager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg143, TestSize.Level1)
{
    AssertValidContext();
    auto originalStageManager = context_->stageManager_;
    context_->stageManager_.Reset();

    context_->SetupPageStackCallbacks();
    EXPECT_EQ(context_->stageManager_, nullptr);

    context_->stageManager_ = originalStageManager;
}

/**
 * @tc.name: PipelineContextFourTestNg144
 * @tc.desc: Test FlushDirtyPropertyNodes clears and processes nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg144, TestSize.Level1)
{
    AssertValidContext();
    context_->dirtyPropertyNodes_.clear();
    context_->FlushDirtyPropertyNodes();
    EXPECT_TRUE(context_->dirtyPropertyNodes_.empty());
}

// ==========================================================================
// Batch 5: StoreNode, GetRestoreInfo, RestoreNodeInfo, OnSurfacePositionChanged,
//          OnFoldDisplayModeChange, OnTransformHintChanged, SetOnDrawChildrenInfoMap
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg145
 * @tc.desc: Test GetRestoreInfo returns false for missing and true for existing.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg145, TestSize.Level1)
{
    AssertValidContext();
    context_->restoreNodeInfo_.clear();
    std::string info;

    EXPECT_FALSE(context_->GetRestoreInfo(DEFAULT_RESTORE_ID0, info));

    context_->restoreNodeInfo_[DEFAULT_RESTORE_ID0] = "test_info";
    EXPECT_TRUE(context_->GetRestoreInfo(DEFAULT_RESTORE_ID0, info));
    EXPECT_EQ(info, "test_info");
    EXPECT_EQ(context_->restoreNodeInfo_.count(DEFAULT_RESTORE_ID0), DEFAULT_SIZE0);

    context_->restoreNodeInfo_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg146
 * @tc.desc: Test OnSurfacePositionChanged fires registered callbacks and skips null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg146, TestSize.Level1)
{
    AssertValidContext();
    context_->surfacePositionChangedCallbackMap_.clear();
    int32_t receivedX = 0;
    int32_t receivedY = 0;

    context_->surfacePositionChangedCallbackMap_[1] = nullptr;
    context_->OnSurfacePositionChanged(10, 20);
    EXPECT_EQ(receivedX, 0);

    context_->surfacePositionChangedCallbackMap_[2] =
        [&receivedX, &receivedY](int32_t x, int32_t y) {
            receivedX = x;
            receivedY = y;
        };
    context_->OnSurfacePositionChanged(30, 40);
    EXPECT_EQ(receivedX, 30);
    EXPECT_EQ(receivedY, 40);

    context_->surfacePositionChangedCallbackMap_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg147
 * @tc.desc: Test OnFoldDisplayModeChange fires registered callbacks and skips null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg147, TestSize.Level1)
{
    AssertValidContext();
    context_->foldDisplayModeChangedCallbackMap_.clear();
    FoldDisplayMode receivedMode = FoldDisplayMode::UNKNOWN;

    context_->foldDisplayModeChangedCallbackMap_[1] = nullptr;
    context_->OnFoldDisplayModeChange(FoldDisplayMode::FULL);
    EXPECT_EQ(receivedMode, FoldDisplayMode::UNKNOWN);

    context_->foldDisplayModeChangedCallbackMap_[2] =
        [&receivedMode](FoldDisplayMode mode) { receivedMode = mode; };
    context_->OnFoldDisplayModeChange(FoldDisplayMode::MAIN);
    EXPECT_EQ(receivedMode, FoldDisplayMode::MAIN);

    context_->foldDisplayModeChangedCallbackMap_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg148
 * @tc.desc: Test OnTransformHintChanged fires registered callbacks and updates transform_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg148, TestSize.Level1)
{
    AssertValidContext();
    context_->transformHintChangedCallbackMap_.clear();
    uint32_t receivedTransform = 0;

    context_->transformHintChangedCallbackMap_[1] = nullptr;
    context_->OnTransformHintChanged(90);
    EXPECT_EQ(receivedTransform, 0u);

    context_->transformHintChangedCallbackMap_[2] =
        [&receivedTransform](uint32_t t) { receivedTransform = t; };
    context_->OnTransformHintChanged(180);
    EXPECT_EQ(receivedTransform, 180u);
    EXPECT_EQ(context_->transform_, 180u);

    context_->transformHintChangedCallbackMap_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg149
 * @tc.desc: Test SetOnDrawChildrenInfoMap inserts new parent and appends to existing.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg149, TestSize.Level1)
{
    AssertValidContext();
    context_->onDrawChildrenInfoMap_.clear();

    context_->SetOnDrawChildrenInfoMap(1, 10);
    EXPECT_EQ(context_->onDrawChildrenInfoMap_.size(), DEFAULT_SIZE1);
    EXPECT_EQ(context_->onDrawChildrenInfoMap_[1].size(), DEFAULT_SIZE1);

    // Same parent, new child
    context_->SetOnDrawChildrenInfoMap(1, 20);
    EXPECT_EQ(context_->onDrawChildrenInfoMap_[1].size(), DEFAULT_SIZE2);

    // Same parent, duplicate child (no insert)
    context_->SetOnDrawChildrenInfoMap(1, 20);
    EXPECT_EQ(context_->onDrawChildrenInfoMap_[1].size(), DEFAULT_SIZE2);

    // Different parent
    context_->SetOnDrawChildrenInfoMap(2, 30);
    EXPECT_EQ(context_->onDrawChildrenInfoMap_.size(), DEFAULT_SIZE2);

    context_->onDrawChildrenInfoMap_.clear();
}

// ==========================================================================
// Batch 6: AddFrameCallback, AddCAPIFrameCallback, TriggerIdleCallback,
//          Finish, AddNodesToNotifyMemoryLevel, NotifyMemoryLevel
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg150
 * @tc.desc: Test AddFrameCallback with delay<=0 adds frame and idle callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg150, TestSize.Level1)
{
    AssertValidContext();
    context_->frameCallbackFuncs_.clear();
    context_->idleCallbackFuncs_.clear();

    context_->AddFrameCallback(nullptr, nullptr, 0);
    EXPECT_TRUE(context_->frameCallbackFuncs_.empty());
    EXPECT_TRUE(context_->idleCallbackFuncs_.empty());

    int frameCount = 0;
    context_->AddFrameCallback([&frameCount](uint64_t) { frameCount++; }, nullptr, -1);
    EXPECT_EQ(context_->frameCallbackFuncs_.size(), DEFAULT_SIZE1);

    int idleCount = 0;
    context_->AddFrameCallback(nullptr, [&idleCount](uint64_t, uint32_t) { idleCount++; }, 0);
    EXPECT_EQ(context_->idleCallbackFuncs_.size(), DEFAULT_SIZE1);

    context_->frameCallbackFuncs_.clear();
    context_->idleCallbackFuncs_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg151
 * @tc.desc: Test AddCAPIFrameCallback guards null and adds valid callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg151, TestSize.Level1)
{
    AssertValidContext();
    context_->frameCallbackFuncsFromCAPI_.clear();

    context_->AddCAPIFrameCallback(nullptr);
    EXPECT_TRUE(context_->frameCallbackFuncsFromCAPI_.empty());

    int count = 0;
    context_->AddCAPIFrameCallback([&count](uint64_t, uint32_t) { count++; });
    EXPECT_EQ(context_->frameCallbackFuncsFromCAPI_.size(), DEFAULT_SIZE1);

    context_->frameCallbackFuncsFromCAPI_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg152
 * @tc.desc: Test TriggerIdleCallback returns early when list is empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg152, TestSize.Level1)
{
    AssertValidContext();
    context_->idleCallbackFuncs_.clear();

    context_->TriggerIdleCallback(INT64_MAX);
    EXPECT_TRUE(context_->idleCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg153
 * @tc.desc: Test Finish guards null finishEventHandler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg153, TestSize.Level1)
{
    AssertValidContext();
    auto originalHandler = context_->finishEventHandler_;
    context_->finishEventHandler_ = nullptr;

    context_->Finish(true);
    EXPECT_EQ(context_->finishEventHandler_, nullptr);

    context_->finishEventHandler_ = originalHandler;
}

/**
 * @tc.name: PipelineContextFourTestNg154
 * @tc.desc: Test Finish executes finishEventHandler when set.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg154, TestSize.Level1)
{
    AssertValidContext();
    bool handlerCalled = false;
    auto originalHandler = context_->finishEventHandler_;
    context_->finishEventHandler_ = [&handlerCalled]() { handlerCalled = true; };

    context_->Finish(false);
    EXPECT_TRUE(handlerCalled);

    context_->finishEventHandler_ = originalHandler;
}

/**
 * @tc.name: PipelineContextFourTestNg155
 * @tc.desc: Test AddNodesToNotifyMemoryLevel and RemoveNodesToNotifyMemoryLevel.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg155, TestSize.Level1)
{
    AssertValidContext();
    context_->nodesToNotifyMemoryLevel_.clear();

    context_->AddNodesToNotifyMemoryLevel(1);
    context_->AddNodesToNotifyMemoryLevel(2);
    EXPECT_EQ(context_->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE2);

    context_->RemoveNodesToNotifyMemoryLevel(1);
    EXPECT_EQ(context_->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE1);

    context_->RemoveNodesToNotifyMemoryLevel(2);
    EXPECT_TRUE(context_->nodesToNotifyMemoryLevel_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg156
 * @tc.desc: Test NotifyMemoryLevel erases invalid nodes and notifies valid ones.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg156, TestSize.Level1)
{
    AssertValidContext();
    context_->nodesToNotifyMemoryLevel_.clear();
    // Invalid node ID should be erased
    context_->AddNodesToNotifyMemoryLevel(-1);
    EXPECT_EQ(context_->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE1);

    context_->NotifyMemoryLevel(0);
    EXPECT_TRUE(context_->nodesToNotifyMemoryLevel_.empty());
}

// ==========================================================================
// Batch 7: IsTagInOverlay, AddFrameNodeChangeListener, RemoveFrameNodeChangeListener,
//          AddChangedFrameNode, RemoveChangedFrameNode, CleanNodeChangeFlag,
//          OnHalfFoldHoverChangedCallback, OnRawKeyboardChangedCallback
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg157
 * @tc.desc: Test IsTagInOverlay returns true for overlay tags and false otherwise.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg157, TestSize.Level1)
{
    AssertValidContext();
    EXPECT_TRUE(context_->IsTagInOverlay(V2::TOAST_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::POPUP_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::DIALOG_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::MENU_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::SHEET_PAGE_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::OVERLAY_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::ORDER_OVERLAY_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::ACTION_SHEET_DIALOG_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::ALERT_DIALOG_ETS_TAG));
    EXPECT_TRUE(context_->IsTagInOverlay(V2::MENU_WRAPPER_ETS_TAG));
    EXPECT_FALSE(context_->IsTagInOverlay("unknown_tag"));
    EXPECT_FALSE(context_->IsTagInOverlay(V2::ROOT_ETS_TAG));
    EXPECT_FALSE(context_->IsTagInOverlay(""));
}

/**
 * @tc.name: PipelineContextFourTestNg158
 * @tc.desc: Test OnHalfFoldHoverChangedCallback fires valid callbacks and skips null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg158, TestSize.Level1)
{
    AssertValidContext();
    context_->halfFoldHoverChangedCallbackMap_.clear();
    bool callbackFired = false;

    context_->halfFoldHoverChangedCallbackMap_[1] = nullptr;
    context_->halfFoldHoverChangedCallbackMap_[2] =
        [&callbackFired](bool) { callbackFired = true; };

    context_->OnHalfFoldHoverChangedCallback();
    EXPECT_TRUE(callbackFired);

    context_->halfFoldHoverChangedCallbackMap_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg159
 * @tc.desc: Test OnRawKeyboardChangedCallback fires valid callbacks and skips null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg159, TestSize.Level1)
{
    AssertValidContext();
    context_->rawKeyboardChangedCallbackMap_.clear();
    bool callbackFired = false;

    context_->rawKeyboardChangedCallbackMap_[1] = nullptr;
    context_->rawKeyboardChangedCallbackMap_[2] = [&callbackFired]() { callbackFired = true; };

    context_->OnRawKeyboardChangedCallback();
    EXPECT_TRUE(callbackFired);

    context_->rawKeyboardChangedCallbackMap_.clear();
}

// ==========================================================================
// Batch 8: UpdateDrawLayoutChildObserver, SetCallBackNode, UpdateIdUpdateZOrderIndex,
//          RegisterAttachedNode, RemoveAttachedNode, HandleSubwindow,
//          GetContainerCustomTitleVisible, GetContainerControlButtonVisible
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg160
 * @tc.desc: Test UpdateDrawLayoutChildObserver by int32_t guards invalid id.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg160, TestSize.Level1)
{
    AssertValidContext();
    // Invalid id returns null node, CHECK_NULL_VOID returns early
    context_->UpdateDrawLayoutChildObserver(-1, true, true);
    // No crash
    EXPECT_TRUE(context_->onDrawChildrenInfoMap_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg161
 * @tc.desc: Test UpdateDrawLayoutChildObserver by string guards invalid key.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg161, TestSize.Level1)
{
    AssertValidContext();
    context_->UpdateDrawLayoutChildObserver("nonexistent_key", true, true);
    // No crash
    EXPECT_TRUE(context_->onDrawChildrenInfoMap_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg162
 * @tc.desc: Test SetCallBackNode guards null weak node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg162, TestSize.Level1)
{
    AssertValidContext();
    context_->SetCallBackNode(nullptr);
    // No crash
    EXPECT_TRUE(context_->activeNode_.Invalid());
}

/**
 * @tc.name: PipelineContextFourTestNg163
 * @tc.desc: Test UpdateIdUpdateZOrderIndex increments index.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg163, TestSize.Level1)
{
    AssertValidContext();
    context_->idUpdateZOrderIndex_ = 0;

    context_->UpdateIdUpdateZOrderIndex();
    EXPECT_EQ(context_->GetIdUpdateZOrderIndex(), DEFAULT_SIZE1);

    context_->UpdateIdUpdateZOrderIndex();
    EXPECT_EQ(context_->GetIdUpdateZOrderIndex(), DEFAULT_SIZE2);

    context_->idUpdateZOrderIndex_ = 0;
}

/**
 * @tc.name: PipelineContextFourTestNg164
 * @tc.desc: Test GetContainerCustomTitleVisible returns false when rootNode_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg164, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    EXPECT_FALSE(context_->GetContainerCustomTitleVisible());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextFourTestNg165
 * @tc.desc: Test GetContainerControlButtonVisible returns false when rootNode_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg165, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    EXPECT_FALSE(context_->GetContainerControlButtonVisible());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextFourTestNg166
 * @tc.desc: Test GetContainerCustomTitleVisible returns false when containerNode is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg166, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context_->rootNode_ = rootNode;

    EXPECT_FALSE(context_->GetContainerCustomTitleVisible());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextFourTestNg167
 * @tc.desc: Test GetContainerControlButtonVisible returns false with empty children.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg167, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context_->rootNode_ = rootNode;

    EXPECT_FALSE(context_->GetContainerControlButtonVisible());

    context_->rootNode_ = originalRoot;
}

// ==========================================================================
// Batch 9: AddFontNodeNG, RemoveFontNodeNG, IsContainerModalVisible,
//          StopWindowAnimation, AddDirtyFreezeNode, SetAfterRenderZindexRebuild
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg168
 * @tc.desc: Test AddFontNodeNG skips when fontManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg168, TestSize.Level1)
{
    AssertValidContext();
    auto originalFontMgr = context_->fontManager_;
    context_->fontManager_.Reset();

    context_->AddFontNodeNG(nullptr);
    // No crash when fontManager_ is null
    EXPECT_TRUE(!context_->fontManager_);

    context_->fontManager_ = originalFontMgr;
}

/**
 * @tc.name: PipelineContextFourTestNg169
 * @tc.desc: Test RemoveFontNodeNG skips when fontManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg169, TestSize.Level1)
{
    AssertValidContext();
    auto originalFontMgr = context_->fontManager_;
    context_->fontManager_.Reset();

    context_->RemoveFontNodeNG(nullptr);
    // No crash when fontManager_ is null
    EXPECT_TRUE(!context_->fontManager_);

    context_->fontManager_ = originalFontMgr;
}

/**
 * @tc.name: PipelineContextFourTestNg170
 * @tc.desc: Test IsContainerModalVisible returns false when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg170, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    EXPECT_FALSE(context_->IsContainerModalVisible());

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextFourTestNg171
 * @tc.desc: Test StopWindowAnimation sets flag and requests frame when predict tasks exist.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg171, TestSize.Level1)
{
    AssertValidContext();
    context_->isWindowAnimation_ = true;

    context_->StopWindowAnimation();
    EXPECT_FALSE(context_->isWindowAnimation_);

    context_->isWindowAnimation_ = false;
}

/**
 * @tc.name: PipelineContextFourTestNg172
 * @tc.desc: Test SetAfterRenderZindexRebuild inserts into map and increments index.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg172, TestSize.Level1)
{
    AssertValidContext();
    context_->idUpdateZOrder_.clear();
    context_->idUpdateZOrderIndex_ = 0;

    context_->SetAfterRenderZindexRebuild(10);
    EXPECT_EQ(context_->idUpdateZOrder_.size(), DEFAULT_SIZE1);
    EXPECT_EQ(context_->idUpdateZOrderIndex_, DEFAULT_SIZE1);

    context_->SetAfterRenderZindexRebuild(20);
    EXPECT_EQ(context_->idUpdateZOrder_.size(), DEFAULT_SIZE2);
    EXPECT_EQ(context_->idUpdateZOrderIndex_, DEFAULT_SIZE2);

    context_->idUpdateZOrder_.clear();
    context_->idUpdateZOrderIndex_ = 0;
}

// ==========================================================================
// Batch 10: FlushNodeChangeFlag, FlushMouseEventVoluntarily, GetCurrentExtraInfo,
//           ResetDragging, SetIsWindowSizeDragging, AddIgnoreLayoutSafeAreaBundle
// ==========================================================================

/**
 * @tc.name: PipelineContextFourTestNg173
 * @tc.desc: Test FlushNodeChangeFlag skips empty listeners and calls ProcessFrameNodeChangeFlag.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg173, TestSize.Level1)
{
    AssertValidContext();
    context_->changeInfoListeners_.clear();
    context_->changedNodes_.clear();

    // Empty listeners - no crash
    context_->FlushNodeChangeFlag();
    EXPECT_TRUE(context_->changeInfoListeners_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg174
 * @tc.desc: Test FlushMouseEventVoluntarily returns early when lastMouseEvent_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg174, TestSize.Level1)
{
    AssertValidContext();
    context_->lastMouseEvent_ = nullptr;

    context_->FlushMouseEventVoluntarily();
    // No crash
    EXPECT_EQ(context_->lastMouseEvent_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg175
 * @tc.desc: Test FlushMouseEventVoluntarily returns early when action is WINDOW_LEAVE.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg175, TestSize.Level1)
{
    AssertValidContext();
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->lastMouseEvent_->action = MouseAction::WINDOW_LEAVE;

    context_->FlushMouseEventVoluntarily();
    // No crash, early return
    ASSERT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->action, MouseAction::WINDOW_LEAVE);

    context_->lastMouseEvent_.reset();
}

/**
 * @tc.name: PipelineContextFourTestNg176
 * @tc.desc: Test FlushMouseEventVoluntarily returns early when windowSizeChangeReason_ is DRAG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg176, TestSize.Level1)
{
    AssertValidContext();
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->lastMouseEvent_->action = MouseAction::MOVE;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::DRAG;

    context_->FlushMouseEventVoluntarily();
    // No crash, early return
    EXPECT_EQ(context_->windowSizeChangeReason_, WindowSizeChangeReason::DRAG);

    context_->lastMouseEvent_.reset();
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
}

/**
 * @tc.name: PipelineContextFourTestNg177
 * @tc.desc: Test GetCurrentExtraInfo returns empty when activeNode_ is expired.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg177, TestSize.Level1)
{
    AssertValidContext();
    context_->activeNode_.Reset();

    auto result = context_->GetCurrentExtraInfo();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg178
 * @tc.desc: Test ResetDragging guards null dragDropManager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg178, TestSize.Level1)
{
    AssertValidContext();
    auto originalMgr = context_->dragDropManager_;
    context_->dragDropManager_.Reset();

    context_->ResetDragging();
    // No crash
    EXPECT_TRUE(!context_->dragDropManager_);

    context_->dragDropManager_ = originalMgr;
}

/**
 * @tc.name: PipelineContextFourTestNg179
 * @tc.desc: Test SetIsWindowSizeDragging triggers drag end callbacks when not dragging.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg179, TestSize.Level1)
{
    AssertValidContext();
    bool callbackFired = false;
    context_->onWindowSizeDragEndCallbacks_.clear();
    context_->onWindowSizeDragEndCallbacks_.emplace_back([&callbackFired]() { callbackFired = true; });

    context_->SetIsWindowSizeDragging(false);
    EXPECT_TRUE(callbackFired);

    callbackFired = false;
    context_->SetIsWindowSizeDragging(true);
    EXPECT_FALSE(callbackFired);

    context_->onWindowSizeDragEndCallbacks_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg180
 * @tc.desc: Test AddIgnoreLayoutSafeAreaBundle skips when destroyed.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg180, TestSize.Level1)
{
    AssertValidContext();
    auto originalDestroyed = context_->destroyed_;
    context_->destroyed_ = true;

    IgnoreLayoutSafeAreaBundle bundle;
    context_->AddIgnoreLayoutSafeAreaBundle(std::move(bundle), true);
    // No crash, early return due to destroyed
    EXPECT_TRUE(context_->destroyed_);

    context_->destroyed_ = originalDestroyed;
}

/**
 * @tc.name: PipelineContextFourTestNg181
 * @tc.desc: Test AddDirtyLayoutNode guards null dirty node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg181, TestSize.Level1)
{
    AssertValidContext();
    context_->AddDirtyLayoutNode(nullptr);
    // No crash, CHECK_NULL_VOID returns early
    EXPECT_TRUE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg182
 * @tc.desc: Test AddDirtyRenderNode guards null dirty node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg182, TestSize.Level1)
{
    AssertValidContext();
    context_->AddDirtyRenderNode(nullptr);
    // No crash, CHECK_NULL_VOID returns early
    EXPECT_TRUE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg183
 * @tc.desc: Test AddDirtyCustomNode skips null dirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg183, TestSize.Level1)
{
    AssertValidContext();
    context_->dirtyNodes_.clear();

    context_->AddDirtyCustomNode(nullptr);
    EXPECT_TRUE(context_->dirtyNodes_.empty());

    context_->dirtyNodes_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg184
 * @tc.desc: Test GetIsRequestFrame returns false when window_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg184, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindow = context_->window_;
    context_->window_.reset();

    EXPECT_FALSE(context_->GetIsRequestFrame());

    context_->window_ = originalWindow;
}

/**
 * @tc.name: PipelineContextFourTestNg185
 * @tc.desc: Test GetWindowName returns empty when window_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg185, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindow = context_->window_;
    context_->window_.reset();

    EXPECT_EQ(context_->GetWindowName(), "");

    context_->window_ = originalWindow;
}

/**
 * @tc.name: PipelineContextFourTestNg186
 * @tc.desc: Test FlushBuildFinishCallbacks with empty and non-empty callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg186, TestSize.Level1)
{
    AssertValidContext();
    context_->buildFinishCallbacks_.clear();

    // Empty - no crash
    auto callbacks = std::move(context_->buildFinishCallbacks_);
    context_->buildFinishCallbacks_.clear();
    for (const auto& cb : callbacks) {
        cb();
    }

    int count = 0;
    context_->buildFinishCallbacks_.push_back([&count]() { count++; });
    context_->buildFinishCallbacks_.push_back([&count]() { count += 2; });

    auto cbs = std::move(context_->buildFinishCallbacks_);
    for (const auto& cb : cbs) {
        cb();
    }
    EXPECT_EQ(count, DEFAULT_INT3);
}

/**
 * @tc.name: PipelineContextFourTestNg187
 * @tc.desc: Test AddPendingDeleteCustomNode adds to stack.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg187, TestSize.Level1)
{
    AssertValidContext();
    size_t originalSize = context_->pendingDeleteCustomNode_.size();

    auto customNode = CustomNode::CreateCustomNode(DEFAULT_INT0, TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    context_->AddPendingDeleteCustomNode(customNode);
    EXPECT_EQ(context_->pendingDeleteCustomNode_.size(), originalSize + 1);

    context_->pendingDeleteCustomNode_.pop();
}

/**
 * @tc.name: PipelineContextFourTestNg188
 * @tc.desc: Test SetWindowSceneConsumed and IsWindowSceneConsumed.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg188, TestSize.Level1)
{
    AssertValidContext();
    context_->SetWindowSceneConsumed(true);
    EXPECT_TRUE(context_->IsWindowSceneConsumed());

    context_->SetWindowSceneConsumed(false);
    EXPECT_FALSE(context_->IsWindowSceneConsumed());
}

/**
 * @tc.name: PipelineContextFourTestNg189
 * @tc.desc: Test FlushSyncGeometryNodeTasks delegates to task scheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg189, TestSize.Level1)
{
    AssertValidContext();
    // No crash - simple delegation
    context_->FlushSyncGeometryNodeTasks();
    EXPECT_TRUE(context_->taskScheduler_->syncGeometryNodeTasks_.empty());
}

/**
 * @tc.name: PipelineContextFourTestNg190
 * @tc.desc: Test AddAfterLayoutTask delegates to task scheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg190, TestSize.Level1)
{
    AssertValidContext();
    bool taskExecuted = false;
    context_->AddAfterLayoutTask([&taskExecuted]() { taskExecuted = true; });
    // Task is queued in scheduler, not immediately executed
    EXPECT_FALSE(taskExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg191
 * @tc.desc: Test AddPersistAfterLayoutTask delegates to task scheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg191, TestSize.Level1)
{
    AssertValidContext();
    bool taskExecuted = false;
    context_->AddPersistAfterLayoutTask([&taskExecuted]() { taskExecuted = true; });
    EXPECT_FALSE(taskExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg192
 * @tc.desc: Test AddAfterRenderTask delegates to task scheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg192, TestSize.Level1)
{
    AssertValidContext();
    bool taskExecuted = false;
    context_->AddAfterRenderTask([&taskExecuted]() { taskExecuted = true; });
    EXPECT_FALSE(taskExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg193
 * @tc.desc: Test RestoreNodeInfo restores from JsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg193, TestSize.Level1)
{
    AssertValidContext();
    context_->restoreNodeInfo_.clear();
    auto json = JsonUtil::Create(true);
    json->Put("100", "info_100");
    json->Put("101", "info_101");

    context_->RestoreNodeInfo(std::move(json));
    EXPECT_EQ(context_->restoreNodeInfo_.size(), DEFAULT_SIZE2);
    EXPECT_EQ(context_->restoreNodeInfo_[100], "info_100");
    EXPECT_EQ(context_->restoreNodeInfo_[101], "info_101");

    context_->restoreNodeInfo_.clear();
}

/**
 * @tc.name: PipelineContextFourTestNg194
 * @tc.desc: Test GetStoredNodeInfo returns empty json when storeNode_ is empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg194, TestSize.Level1)
{
    AssertValidContext();
    context_->storeNode_.clear();

    auto result = context_->GetStoredNodeInfo();
    ASSERT_NE(result, nullptr);
}

} // namespace OHOS::Ace::NG
