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
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/common/event_manager.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/mousestyle/mock_mouse_style.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_window.h"
#include "test/mock/frameworks/core/common/mock_resource_register.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/ai/ai_write_adapter.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/common/statistic_event_reporter.h"
#include "core/components_ng/pattern/web/itouch_event_callback.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MockTouchEventCallback : public ITouchEventCallback {
public:
    MockTouchEventCallback() = default;
    ~MockTouchEventCallback() override = default;
    void OnTouchEvent() override {}
    WeakPtr<NG::Pattern> GetPatternFromListener() override { return nullptr; }
};
} // namespace

namespace {
constexpr uint32_t TEST_CALLBACK_ID1 = 100;
constexpr uint32_t TEST_CALLBACK_ID2 = 200;
constexpr uint64_t TEST_NANO_TIMESTAMP = 12345;
constexpr uint64_t TEST_FRAME_COUNT = 5;
constexpr int32_t TEST_WINDOW_ID_POSITIVE = 10;
constexpr int32_t TEST_WINDOW_ID_ZERO = 0;
constexpr int32_t TEST_CURSOR_VALID = 0;
constexpr int32_t TEST_CURSOR_OUT_OF_RANGE = 99999;
constexpr int32_t TEST_CURSOR_NEGATIVE = -1;
constexpr uint8_t TEST_RENDERING_MODE_FORM = 1;
constexpr uint8_t TEST_RENDERING_MODE_FULL = 0;
constexpr uint64_t LARGE_TIME_THRESHOLD = static_cast<uint64_t>(INT64_MAX >> 2);
constexpr uint64_t TEST_SMALL_TIMESTAMP = 1000;
} // namespace

// ==========================================================================
// Batch 1: Simple state and callback methods
// ==========================================================================

/**
 * @tc.name: PipelineContextSevenTest001
 * @tc.desc: Test FlushFrameCallback skips when frameCount is UINT64_MAX.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest001, TestSize.Level1)
{
    AssertValidContext();
    int executeCount = 0;
    context_->frameCallbackFuncs_.push_back([&executeCount](uint64_t) { executeCount++; });

    context_->FlushFrameCallback(TEST_NANO_TIMESTAMP, UINT64_MAX);
    EXPECT_EQ(executeCount, 0);
    EXPECT_FALSE(context_->frameCallbackFuncs_.empty());

    context_->frameCallbackFuncs_.clear();
}

/**
 * @tc.name: PipelineContextSevenTest002
 * @tc.desc: Test FlushFrameCallback executes callbacks when list is non-empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest002, TestSize.Level1)
{
    AssertValidContext();
    int executeCount = 0;
    context_->frameCallbackFuncs_.clear();
    context_->FlushFrameCallback(TEST_NANO_TIMESTAMP, TEST_FRAME_COUNT);
    EXPECT_EQ(executeCount, 0);

    uint64_t receivedTimestamp = 0;
    context_->frameCallbackFuncs_.push_back([&executeCount, &receivedTimestamp](uint64_t ts) {
        executeCount++;
        receivedTimestamp = ts;
    });
    context_->FlushFrameCallback(TEST_NANO_TIMESTAMP, TEST_FRAME_COUNT);
    EXPECT_EQ(executeCount, 1);
    EXPECT_EQ(receivedTimestamp, TEST_NANO_TIMESTAMP);
    EXPECT_TRUE(context_->frameCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextSevenTest003
 * @tc.desc: Test FlushFrameCallbackFromCAPI skips when frameCount is UINT64_MAX.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest003, TestSize.Level1)
{
    AssertValidContext();
    int executeCount = 0;
    context_->frameCallbackFuncsFromCAPI_.push_back([&executeCount](uint64_t, uint32_t) { executeCount++; });

    context_->FlushFrameCallbackFromCAPI(TEST_NANO_TIMESTAMP, UINT64_MAX);
    EXPECT_EQ(executeCount, 0);
    EXPECT_FALSE(context_->frameCallbackFuncsFromCAPI_.empty());

    context_->frameCallbackFuncsFromCAPI_.clear();
}

/**
 * @tc.name: PipelineContextSevenTest004
 * @tc.desc: Test FlushFrameCallbackFromCAPI executes callbacks when list is non-empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest004, TestSize.Level1)
{
    AssertValidContext();
    int executeCount = 0;
    context_->frameCallbackFuncsFromCAPI_.clear();
    context_->FlushFrameCallbackFromCAPI(TEST_NANO_TIMESTAMP, TEST_FRAME_COUNT);
    EXPECT_EQ(executeCount, 0);

    uint64_t receivedTs = 0;
    uint32_t receivedCount = 0;
    context_->frameCallbackFuncsFromCAPI_.push_back(
        [&executeCount, &receivedTs, &receivedCount](uint64_t ts, uint32_t fc) {
            executeCount++;
            receivedTs = ts;
            receivedCount = fc;
        });
    context_->FlushFrameCallbackFromCAPI(TEST_NANO_TIMESTAMP, TEST_FRAME_COUNT);
    EXPECT_EQ(executeCount, 1);
    EXPECT_EQ(receivedTs, TEST_NANO_TIMESTAMP);
    EXPECT_EQ(receivedCount, static_cast<uint32_t>(TEST_FRAME_COUNT));
    EXPECT_TRUE(context_->frameCallbackFuncsFromCAPI_.empty());
}

/**
 * @tc.name: PipelineContextSevenTest005
 * @tc.desc: Test RegisterTouchEventListener guards null listener.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest005, TestSize.Level1)
{
    AssertValidContext();
    size_t originalSize = context_->listenerVector_.size();

    context_->RegisterTouchEventListener(nullptr);
    EXPECT_EQ(context_->listenerVector_.size(), originalSize);
}

/**
 * @tc.name: PipelineContextSevenTest006
 * @tc.desc: Test RegisterTouchEventListener adds valid listener.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest006, TestSize.Level1)
{
    AssertValidContext();
    size_t originalSize = context_->listenerVector_.size();
    auto listener = std::make_shared<MockTouchEventCallback>();
    ASSERT_NE(listener, nullptr);

    context_->RegisterTouchEventListener(listener);
    EXPECT_EQ(context_->listenerVector_.size(), originalSize + 1);

    context_->listenerVector_.pop_back();
}

/**
 * @tc.name: PipelineContextSevenTest007
 * @tc.desc: Test CatchInteractiveAnimations returns false when navigationMgr_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest007, TestSize.Level1)
{
    AssertValidContext();
    auto originalMgr = context_->navigationMgr_;
    context_->navigationMgr_.Reset();

    EXPECT_FALSE(context_->CatchInteractiveAnimations([]() {}));

    context_->navigationMgr_ = originalMgr;
}

/**
 * @tc.name: PipelineContextSevenTest008
 * @tc.desc: Test CatchInteractiveAnimations returns false when not interactive.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest008, TestSize.Level1)
{
    AssertValidContext();
    context_->navigationMgr_ = AceType::MakeRefPtr<NavigationManager>();

    EXPECT_FALSE(context_->CatchInteractiveAnimations([]() {}));
}

/**
 * @tc.name: PipelineContextSevenTest009
 * @tc.desc: Test SetDisplayWindowRectInfo updates offset and adjusts lastMouseEvent_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest009, TestSize.Level1)
{
    AssertValidContext();
    context_->displayWindowRectInfo_ = Rect(0, 0, 100, 100);
    context_->lastMouseEvent_ = nullptr;

    context_->SetDisplayWindowRectInfo(Rect(0, 0, 200, 200));
    EXPECT_EQ(context_->displayWindowRectInfo_.Width(), 200);

    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->lastMouseEvent_->x = 50;
    context_->lastMouseEvent_->y = 50;

    context_->SetDisplayWindowRectInfo(Rect(10, 20, 200, 200));
    EXPECT_EQ(context_->lastMouseEvent_->x, 40);
    EXPECT_EQ(context_->lastMouseEvent_->y, 30);

    context_->lastMouseEvent_.reset();
}

/**
 * @tc.name: PipelineContextSevenTest010
 * @tc.desc: Test SetIsTransFlag updates value only when different.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest010, TestSize.Level1)
{
    AssertValidContext();
    context_->isTransFlag_ = false;

    context_->SetIsTransFlag(false);
    EXPECT_FALSE(context_->isTransFlag_);

    context_->SetIsTransFlag(true);
    EXPECT_TRUE(context_->isTransFlag_);

    context_->isTransFlag_ = false;
}

/**
 * @tc.name: PipelineContextSevenTest011
 * @tc.desc: Test GetNodeRenderStatusMonitor lazily creates and reuses monitor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest011, TestSize.Level1)
{
    AssertValidContext();
    context_->nodeRenderStatusMonitor_.Reset();

    auto first = context_->GetNodeRenderStatusMonitor();
    ASSERT_NE(first, nullptr);
    auto second = context_->GetNodeRenderStatusMonitor();
    EXPECT_EQ(first, second);
}

/**
 * @tc.name: PipelineContextSevenTest012
 * @tc.desc: Test GetOrCreateAIWriteAdapter creates and reuses adapter.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest012, TestSize.Level1)
{
    AssertValidContext();
    context_->aiWriteAdapter_.Reset();

    auto first = context_->GetOrCreateAIWriteAdapter();
    EXPECT_FALSE(first.Invalid());

    auto second = context_->GetOrCreateAIWriteAdapter();
    EXPECT_FALSE(second.Invalid());

    context_->aiWriteAdapter_.Reset();
}

/**
 * @tc.name: PipelineContextSevenTest013
 * @tc.desc: Test OnRotationAnimationEnd fires registered callbacks and skips null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest013, TestSize.Level1)
{
    AssertValidContext();
    context_->rotationEndCallbackMap_.clear();
    int count = 0;

    context_->rotationEndCallbackMap_[TEST_CALLBACK_ID1] = [&count]() { count++; };
    context_->rotationEndCallbackMap_[TEST_CALLBACK_ID2] = nullptr;

    context_->OnRotationAnimationEnd();
    EXPECT_EQ(count, 1);

    context_->rotationEndCallbackMap_.clear();
}

/**
 * @tc.name: PipelineContextSevenTest014
 * @tc.desc: Test SetCursor with int32_t variant - valid and out-of-range.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest014, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->eventManager_, nullptr);
    auto mouseStyleManager = context_->eventManager_->GetMouseStyleManager();
    ASSERT_NE(mouseStyleManager, nullptr);

    context_->SetCursor(std::variant<int32_t, CustomCursorInfo>(TEST_CURSOR_VALID));
    EXPECT_TRUE(mouseStyleManager->userSetCursor_);

    mouseStyleManager->userSetCursor_ = false;
    context_->SetCursor(std::variant<int32_t, CustomCursorInfo>(TEST_CURSOR_OUT_OF_RANGE));
    EXPECT_FALSE(mouseStyleManager->userSetCursor_);

    context_->SetCursor(std::variant<int32_t, CustomCursorInfo>(TEST_CURSOR_NEGATIVE));
    EXPECT_FALSE(mouseStyleManager->userSetCursor_);
}

/**
 * @tc.name: PipelineContextSevenTest015
 * @tc.desc: Test SetCursor with CustomCursorInfo variant - null pixelMap guard.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest015, TestSize.Level1)
{
    AssertValidContext();
    auto mouseStyleManager = context_->eventManager_->GetMouseStyleManager();
    ASSERT_NE(mouseStyleManager, nullptr);
    mouseStyleManager->userSetCursor_ = false;

    CustomCursorInfo nullPixelMapInfo;
    nullPixelMapInfo.pixelMap = nullptr;
    context_->SetCursor(std::variant<int32_t, CustomCursorInfo>(nullPixelMapInfo));
    EXPECT_FALSE(mouseStyleManager->userSetCursor_);
}

// ==========================================================================
// Batch 2: Node and configuration methods
// ==========================================================================

/**
 * @tc.name: PipelineContextSevenTest016
 * @tc.desc: Test SetEnableSwipeBack guards null rootNode_ and null rootPattern.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest016, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    context_->SetEnableSwipeBack(true);
    EXPECT_TRUE(!context_->rootNode_);

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest017
 * @tc.desc: Test SetEnableSwipeBack with valid rootNode_ with RootPattern.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest017, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    context_->rootNode_ = rootNode;

    context_->SetEnableSwipeBack(true);
    EXPECT_EQ(context_->rootNode_, rootNode);

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest018
 * @tc.desc: Test SetHostParentOffsetToWindow with null rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest018, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    Offset offset(DEFAULT_DOUBLE1, DEFAULT_DOUBLE2);
    context_->SetHostParentOffsetToWindow(offset);
    EXPECT_EQ(context_->lastHostParentOffsetToWindow_.GetX(), DEFAULT_DOUBLE1);
    EXPECT_EQ(context_->lastHostParentOffsetToWindow_.GetY(), DEFAULT_DOUBLE2);

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest019
 * @tc.desc: Test CheckNeedUpdateBackgroundColor skips when not form render.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest019, TestSize.Level1)
{
    AssertValidContext();
    context_->isFormRender_ = false;
    context_->renderingMode_ = TEST_RENDERING_MODE_FORM;

    Color color(0xFF000000);
    Color originalColor = color;
    context_->CheckNeedUpdateBackgroundColor(color);
    EXPECT_EQ(color.GetValue(), originalColor.GetValue());

    context_->isFormRender_ = true;
    context_->renderingMode_ = TEST_RENDERING_MODE_FULL;
    context_->CheckNeedUpdateBackgroundColor(color);
    EXPECT_EQ(color.GetValue(), originalColor.GetValue());

    context_->isFormRender_ = true;
    context_->renderingMode_ = TEST_RENDERING_MODE_FORM;
    context_->CheckNeedUpdateBackgroundColor(color);
    EXPECT_NE(color.GetValue(), originalColor.GetValue());

    context_->isFormRender_ = false;
    context_->renderingMode_ = TEST_RENDERING_MODE_FULL;
}

/**
 * @tc.name: PipelineContextSevenTest020
 * @tc.desc: Test CheckNeedDisableUpdateBackgroundImage returns correct results.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest020, TestSize.Level1)
{
    AssertValidContext();

    context_->isFormRender_ = false;
    context_->renderingMode_ = TEST_RENDERING_MODE_FORM;
    context_->enableBlurBackground_ = false;
    EXPECT_FALSE(context_->CheckNeedDisableUpdateBackgroundImage());

    context_->isFormRender_ = true;
    context_->renderingMode_ = TEST_RENDERING_MODE_FORM;
    EXPECT_TRUE(context_->CheckNeedDisableUpdateBackgroundImage());

    context_->isFormRender_ = true;
    context_->renderingMode_ = TEST_RENDERING_MODE_FULL;
    context_->enableBlurBackground_ = false;
    EXPECT_FALSE(context_->CheckNeedDisableUpdateBackgroundImage());

    context_->isFormRender_ = true;
    context_->renderingMode_ = TEST_RENDERING_MODE_FULL;
    context_->enableBlurBackground_ = true;
    EXPECT_TRUE(context_->CheckNeedDisableUpdateBackgroundImage());

    context_->isFormRender_ = false;
    context_->renderingMode_ = TEST_RENDERING_MODE_FULL;
    context_->enableBlurBackground_ = false;
}

/**
 * @tc.name: PipelineContextSevenTest021
 * @tc.desc: Test DisableNotifyResponseRegionChanged with null taskExecutor_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest021, TestSize.Level1)
{
    AssertValidContext();
    auto originalExecutor = context_->taskExecutor_;
    context_->taskExecutor_.Reset();

    context_->DisableNotifyResponseRegionChanged();
    EXPECT_TRUE(!context_->taskExecutor_);

    context_->taskExecutor_ = originalExecutor;
}

/**
 * @tc.name: PipelineContextSevenTest022
 * @tc.desc: Test CheckThreadSafe with null taskExecutor_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest022, TestSize.Level1)
{
    AssertValidContext();
    auto originalExecutor = context_->taskExecutor_;
    context_->taskExecutor_.Reset();

    EXPECT_TRUE(context_->CheckThreadSafe());

    context_->taskExecutor_ = originalExecutor;
}

/**
 * @tc.name: PipelineContextSevenTest023
 * @tc.desc: Test CheckThreadSafe with form render returns true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest023, TestSize.Level1)
{
    AssertValidContext();
    context_->isFormRender_ = true;

    EXPECT_TRUE(context_->CheckThreadSafe());

    context_->isFormRender_ = false;
}

/**
 * @tc.name: PipelineContextSevenTest024
 * @tc.desc: Test RestoreDefault with positive and zero windowId.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest024, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_NE(context_->eventManager_, nullptr);
    auto mouseStyleManager = context_->eventManager_->GetMouseStyleManager();
    ASSERT_NE(mouseStyleManager, nullptr);
    mouseStyleManager->userSetCursor_ = true;

    context_->RestoreDefault(TEST_WINDOW_ID_POSITIVE, MouseStyleChangeReason::INNER_SET_MOUSESTYLE);
    EXPECT_FALSE(mouseStyleManager->userSetCursor_);
}

/**
 * @tc.name: PipelineContextSevenTest025
 * @tc.desc: Test RestoreDefault with null mouseStyleManager guard.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest025, TestSize.Level1)
{
    AssertValidContext();
    auto originalEventManager = context_->eventManager_;
    auto originalMouseStyleManager = originalEventManager->mouseStyleManager_;
    originalEventManager->mouseStyleManager_.Reset();

    context_->RestoreDefault(TEST_WINDOW_ID_ZERO, MouseStyleChangeReason::INNER_SET_MOUSESTYLE);
    EXPECT_TRUE(!originalEventManager->mouseStyleManager_);

    originalEventManager->mouseStyleManager_ = originalMouseStyleManager;
}

/**
 * @tc.name: PipelineContextSevenTest026
 * @tc.desc: Test HandleTouchHoverOut returns early for non-finger source.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest026, TestSize.Level1)
{
    AssertValidContext();

    TouchEvent penEvent;
    penEvent.sourceTool = SourceTool::PEN;
    penEvent.force = 1.0f;
    context_->HandleTouchHoverOut(penEvent);
    EXPECT_EQ(penEvent.sourceTool, SourceTool::PEN);

    TouchEvent zeroForceEvent;
    zeroForceEvent.sourceTool = SourceTool::FINGER;
    zeroForceEvent.force = 0.0f;
    context_->HandleTouchHoverOut(zeroForceEvent);
    EXPECT_EQ(zeroForceEvent.sourceTool, SourceTool::FINGER);
    EXPECT_NEAR(zeroForceEvent.force, 0.0f, 0.001f);
}

/**
 * @tc.name: PipelineContextSevenTest027
 * @tc.desc: Test GetPageRootNode returns nullptr when stageManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest027, TestSize.Level1)
{
    AssertValidContext();
    auto originalStageManager = context_->stageManager_;
    context_->stageManager_.Reset();

    EXPECT_EQ(context_->GetPageRootNode(), nullptr);

    context_->stageManager_ = originalStageManager;
}

/**
 * @tc.name: PipelineContextSevenTest028
 * @tc.desc: Test GetPageRootNode returns nullptr when stageManager_ has no last page.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest028, TestSize.Level1)
{
    AssertValidContext();
    auto originalStageManager = context_->stageManager_;
    auto stageNode = FrameNode::GetOrCreateFrameNode(V2::STAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StagePattern>(); });
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);

    EXPECT_EQ(context_->GetPageRootNode(), nullptr);

    context_->stageManager_ = originalStageManager;
}

// ==========================================================================
// Batch 3: ContainerModal series (~100 branches)
// ==========================================================================

namespace {
// Helper: build a standard ContainerModal node tree and set windowModal_.
// Returns the rootNode, containerNode, and containerPattern as output params.
struct ContainerModalTree {
    RefPtr<FrameNode> rootNode;
    RefPtr<FrameNode> containerNode;
    RefPtr<ContainerModalPattern> containerPattern;
};

ContainerModalTree SetupContainerModalTree(const RefPtr<PipelineContext>& ctx)
{
    ContainerModalTree tree;
    ctx->SetWindowModal(WindowModal::CONTAINER_MODAL);
    tree.rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    tree.containerNode = FrameNode::CreateFrameNode(
        "ContainerModal", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ContainerModalPattern>());
    tree.rootNode->AddChild(tree.containerNode);
    ctx->rootNode_ = tree.rootNode;
    tree.containerPattern = tree.containerNode->GetPattern<ContainerModalPattern>();
    return tree;
}

// TrackingContainerModalPattern overrides virtual getters for testing return values.
class TrackingContainerModalPattern final : public ContainerModalPattern {
public:
    bool floatingTitleVisible_ = false;
    bool customTitleVisible_ = false;
    bool controlButtonVisible_ = false;

    bool GetFloatingTitleVisible() override { return floatingTitleVisible_; }
    bool GetCustomTitleVisible() override { return customTitleVisible_; }
    bool GetControlButtonVisible() override { return controlButtonVisible_; }
};
} // namespace

/**
 * @tc.name: PipelineContextSevenTest029
 * @tc.desc: Test SetContainerButtonHide early return when windowModal_ != CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest029, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;

    // Build a tree to verify early return doesn't modify pattern state
    auto tree = SetupContainerModalTree(context_);
    context_->windowModal_ = WindowModal::NORMAL;
    bool originalHideSplit = tree.containerPattern->hideSplitButton_;
    context_->SetContainerButtonHide(true, true, true, true);
    EXPECT_EQ(tree.containerPattern->hideSplitButton_, originalHideSplit);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest030
 * @tc.desc: Test SetContainerButtonHide CHECK_NULL_VOID rootNode_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest030, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->rootNode_.Reset();

    context_->SetContainerButtonHide(true, true, true, true);
    EXPECT_TRUE(!context_->rootNode_);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest031
 * @tc.desc: Test SetContainerButtonHide with empty children on rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest031, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context_->rootNode_ = rootNode;

    context_->SetContainerButtonHide(true, true, true, true);
    EXPECT_TRUE(rootNode->GetChildren().empty());

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest032
 * @tc.desc: Test EnableContainerModalGesture with null rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest032, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    context_->EnableContainerModalGesture(true);
    EXPECT_TRUE(!context_->rootNode_);

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest033
 * @tc.desc: Test EnableContainerModalGesture with empty children.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest033, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context_->rootNode_ = rootNode;

    context_->EnableContainerModalGesture(true);
    // children.empty() -> early return
    EXPECT_TRUE(rootNode->GetChildren().empty());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest034
 * @tc.desc: Test EnableContainerModalGesture normal path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest034, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto tree = SetupContainerModalTree(context_);

    context_->EnableContainerModalGesture(true);
    // All checks pass, virtual method called on pattern - no crash
    ASSERT_NE(tree.containerPattern, nullptr);

    context_->EnableContainerModalGesture(false);
    ASSERT_NE(tree.containerPattern, nullptr);

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest035
 * @tc.desc: Test GetContainerFloatingTitleVisible with null rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest035, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    context_->rootNode_.Reset();

    EXPECT_FALSE(context_->GetContainerFloatingTitleVisible());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest036
 * @tc.desc: Test GetContainerFloatingTitleVisible with null containerNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest036, TestSize.Level1)
{
    AssertValidContext();
    auto originalRoot = context_->rootNode_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context_->rootNode_ = rootNode;

    EXPECT_FALSE(context_->GetContainerFloatingTitleVisible());

    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest037
 * @tc.desc: Test SetWindowContainerColor early return when windowModal_ != CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest037, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    auto tree = SetupContainerModalTree(context_);
    Color originalActive = tree.containerPattern->activeColor_;

    context_->windowModal_ = WindowModal::NORMAL;
    context_->SetWindowContainerColor(Color::RED, Color::GREEN);
    EXPECT_EQ(tree.containerPattern->activeColor_, originalActive);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest038
 * @tc.desc: Test SetWindowContainerColor with null rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest038, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->rootNode_.Reset();

    context_->SetWindowContainerColor(Color::RED, Color::GREEN);
    EXPECT_TRUE(!context_->rootNode_);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest039
 * @tc.desc: Test SetCloseButtonStatus early return when windowModal_ != CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest039, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    context_->SetCloseButtonStatus(true);
    EXPECT_EQ(context_->windowModal_, WindowModal::NORMAL);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest040
 * @tc.desc: Test SetCloseButtonStatus normal path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest040, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    auto tree = SetupContainerModalTree(context_);

    context_->SetCloseButtonStatus(true);
    // Mock implementation calls GetHost() which returns the containerNode
    ASSERT_NE(tree.containerPattern, nullptr);

    context_->SetCloseButtonStatus(false);
    ASSERT_NE(tree.containerPattern, nullptr);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest041
 * @tc.desc: Test SetContainerModalTitleVisible early return when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest041, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    context_->SetContainerModalTitleVisible(true, true);
    EXPECT_EQ(context_->windowModal_, WindowModal::NORMAL);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest042
 * @tc.desc: Test SetContainerModalTitleHeight early return when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest042, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    context_->SetContainerModalTitleHeight(50);
    EXPECT_EQ(context_->windowModal_, WindowModal::NORMAL);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest043
 * @tc.desc: Test GetContainerModalTitleHeight early return when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest043, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    EXPECT_EQ(context_->GetContainerModalTitleHeight(), -1);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest044
 * @tc.desc: Test GetContainerModalNode when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest044, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    EXPECT_EQ(context_->GetContainerModalNode(), nullptr);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest045
 * @tc.desc: Test GetContainerModalNode null rootNode_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest045, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->rootNode_.Reset();

    EXPECT_EQ(context_->GetContainerModalNode(), nullptr);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest046
 * @tc.desc: Test GetContainerModalButtonsRect when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest046, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;
    RectF containerModal, buttons;

    EXPECT_FALSE(context_->GetContainerModalButtonsRect(containerModal, buttons));

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest047
 * @tc.desc: Test GetContainerModalButtonsRect normal path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest047, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    auto tree = SetupContainerModalTree(context_);
    RectF containerModal, buttons;

    auto result = context_->GetContainerModalButtonsRect(containerModal, buttons);
    // Mock returns false
    EXPECT_FALSE(result);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest048
 * @tc.desc: Test SubscribeContainerModalButtonsRectChange when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest048, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;

    context_->SubscribeContainerModalButtonsRectChange([](RectF&, RectF&) {});
    EXPECT_EQ(context_->windowModal_, WindowModal::NORMAL);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest049
 * @tc.desc: Test GetWindowPaintRectWithoutMeasureAndLayout when not CONTAINER_MODAL.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest049, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    context_->windowModal_ = WindowModal::NORMAL;
    RectInt rect(1, 2, 3, 4);

    context_->GetWindowPaintRectWithoutMeasureAndLayout(rect);
    // early return, rect unchanged
    EXPECT_EQ(rect.Left(), 1);

    context_->windowModal_ = originalWindowModal;
}

/**
 * @tc.name: PipelineContextSevenTest050
 * @tc.desc: Test GetCustomTitleHeight with null containerModal node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest050, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    context_->windowModal_ = WindowModal::NORMAL;

    auto result = context_->GetCustomTitleHeight();
    EXPECT_EQ(result.Value(), 0.0);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest051
 * @tc.desc: Test GetCustomTitleHeight normal path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest051, TestSize.Level1)
{
    AssertValidContext();
    auto originalWindowModal = context_->windowModal_;
    auto originalRoot = context_->rootNode_;
    auto tree = SetupContainerModalTree(context_);

    auto result = context_->GetCustomTitleHeight();
    // Mock returns Dimension(0.0)
    EXPECT_EQ(result.Value(), 0.0);

    context_->windowModal_ = originalWindowModal;
    context_->rootNode_ = originalRoot;
}

/**
 * @tc.name: PipelineContextSevenTest052
 * @tc.desc: Test DumpVisibleInspectorTree with normal rootNode (no ContainerModal, no AtomicService)
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest052, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest053
 * @tc.desc: Test DumpVisibleInspectorTree with interaction
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest053, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    config.interactionInfo = true;
    config.accessibilityInfo = true;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest054
 * @tc.desc: Test DumpVisibleInspectorTree when rootNode has no ContainerModal child
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest054, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest055
 * @tc.desc: Test DumpVisibleInspectorTree under CONTAINER_MODAL window modal with ContainerModalPattern child
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest055, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto windowModalBackup = context_->windowModal_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto containerModalNode = FrameNode::CreateFrameNode(
        "ContainerModal", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ContainerModalPattern>());
    rootNode->AddChild(containerModalNode);
    context_->rootNode_ = rootNode;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(containerModalNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->windowModal_ = windowModalBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest056
 * @tc.desc: Test DumpVisibleInspectorTree under CONTAINER_MODAL but child has no ContainerModalPattern
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest056, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto windowModalBackup = context_->windowModal_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto nonContainerModalChild = FrameNode::CreateFrameNode(
        "NonContainerModal", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(nonContainerModalChild);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->windowModal_ = windowModalBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest057
 * @tc.desc: Test DumpVisibleInspectorTree when rootNode has ATOMIC_SERVICE child
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest057, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto atomicNode = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(atomicNode);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest058
 * @tc.desc: Test DumpVisibleInspectorTree when rootNode has no ATOMIC_SERVICE child
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest058, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto otherChild = FrameNode::CreateFrameNode(
        "OtherTag", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(otherChild);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest059
 * @tc.desc: Test DumpVisibleInspectorTree when rootNode has no children besides stage
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest059, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    auto overlayBackup = context_->overlayManager_;
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    rootNode->AddChild(stageNode);
    context_->rootNode_ = rootNode;
    context_->overlayManager_ = AceType::MakeRefPtr<OverlayManager>(rootNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpVisibleInspectorTree(root, config);
    EXPECT_FALSE(root->ToString().empty());
    context_->rootNode_ = rootBackup;
    context_->overlayManager_ = overlayBackup;
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest060
 * @tc.desc: Test PipelineContext 6-param constructor initializes managers and sets pipeline context.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest060, TestSize.Level1)
{
    auto window = std::make_shared<MockWindow>();
    EXPECT_CALL(*window, RequestFrame()).Times(AnyNumber());
    EXPECT_CALL(*window, FlushTasks(testing::_)).Times(AnyNumber());
    EXPECT_CALL(*window, OnHide()).Times(AnyNumber());
    EXPECT_CALL(*window, RecordFrameTime(_, _)).Times(AnyNumber());
    auto context = AceType::MakeRefPtr<PipelineContext>(
        window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr,
        AceType::MakeRefPtr<MockResourceRegister>(), nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->navigationMgr_, nullptr);
    ASSERT_NE(context->forceSplitMgr_, nullptr);
    ASSERT_NE(context->avoidInfoMgr_, nullptr);
    ASSERT_NE(context->safeAreaManager_, nullptr);
    ASSERT_NE(context->touchOptimizer_, nullptr);
    ASSERT_NE(context->clickOptimizer_, nullptr);
    ASSERT_NE(context->dynamicComponentSafeManager_, nullptr);
    EXPECT_EQ(context->avoidInfoMgr_->instanceId_, DEFAULT_INSTANCE_ID);
}

/**
 * @tc.name: PipelineContextSevenTest061
 * @tc.desc: Test DumpInspector skips when accessibilityManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest061, TestSize.Level1)
{
    AssertValidContext();
    auto mockFrontend = AceType::MakeRefPtr<MockFrontend>();
    testing::Mock::AllowLeak(AceType::RawPtr(mockFrontend));
    auto weakFrontendBackup = context_->weakFrontend_;
    context_->weakFrontend_ = mockFrontend;
    EXPECT_CALL(*mockFrontend, GetAccessibilityManager())
        .WillRepeatedly(testing::Return(nullptr));
    std::vector<std::string> params = { "-inspector" };
    context_->DumpInspector(params, true);
    context_->weakFrontend_ = weakFrontendBackup;
}

/**
 * @tc.name: PipelineContextSevenTest062
 * @tc.desc: Test FlushReload when fontManager is not null and languageUpdate is true,
 *           covering branch (fontManager && (languageUpdate || fullUpdate)) as true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest062, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto fontManagerBackup = context_->fontManager_;
    context_->fontManager_ = FontManager::Create();
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    config.languageUpdate = true;
    config.colorModeUpdate = true;
    context_->FlushReload(config, true);
    EXPECT_FALSE(context_->isReloading_);
    context_->fontManager_ = fontManagerBackup;
    context_->stageManager_ = stageManagerBackup;
    context_->onShow_ = false;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest063
 * @tc.desc: Test FlushReload when fontManager is null and no updates,
 *           covering branch (fontManager && (languageUpdate || fullUpdate)) as false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest063, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto fontManagerBackup = context_->fontManager_;
    context_->fontManager_ = nullptr;
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    context_->FlushReload(config, false);
    EXPECT_FALSE(context_->isReloading_);
    context_->fontManager_ = fontManagerBackup;
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest064
 * @tc.desc: Test FlushReload when iconUpdate is true,
 *           covering branch (IsNeedUpdate() || iconUpdate) as true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest064, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    config.iconUpdate = true;
    context_->FlushReload(config, false);
    EXPECT_FALSE(context_->isReloading_);
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest065
 * @tc.desc: Test FlushReload when all config flags are false,
 *           covering branch (IsNeedUpdate() || iconUpdate) as false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest065, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto fontManagerBackup = context_->fontManager_;
    context_->fontManager_ = nullptr;
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    context_->FlushReload(config, false);
    EXPECT_FALSE(context_->isReloading_);
    context_->fontManager_ = fontManagerBackup;
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest066
 * @tc.desc: Test FlushReload when fullUpdate is true and IsNeedUpdate is true,
 *           covering branch (fullUpdate && IsNeedUpdate()) as true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest066, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto fontManagerBackup = context_->fontManager_;
    context_->fontManager_ = FontManager::Create();
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    config.languageUpdate = true;
    config.colorModeUpdate = true;
    context_->FlushReload(config, true);
    EXPECT_FALSE(context_->isReloading_);
    context_->fontManager_ = fontManagerBackup;
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest067
 * @tc.desc: Test FlushReload when fullUpdate is true but IsNeedUpdate is false,
 *           covering branch (fullUpdate && IsNeedUpdate()) as false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest067, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto fontManagerBackup = context_->fontManager_;
    context_->fontManager_ = nullptr;
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    context_->FlushReload(config, true);
    EXPECT_FALSE(context_->isReloading_);
    context_->fontManager_ = fontManagerBackup;
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest068
 * @tc.desc: Test FlushReload when onShow is false,
 *           covering branch (!onShow_) as true, changeTask executed directly.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest068, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = false;
    ConfigurationChange config;
    context_->FlushReload(config, false);
    EXPECT_FALSE(context_->isReloading_);
    context_->stageManager_ = stageManagerBackup;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest069
 * @tc.desc: Test FlushReload when onShow is true,
 *           covering branch (!onShow_) as false, AnimationUtils::Animate path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest069, TestSize.Level1)
{
    AssertValidContext();
    auto rootBackup = context_->rootNode_;
    context_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto stageManagerBackup = context_->stageManager_;
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(context_->rootNode_);
    context_->onShow_ = true;
    ConfigurationChange config;
    context_->FlushReload(config, false);
    EXPECT_FALSE(context_->isReloading_);
    context_->stageManager_ = stageManagerBackup;
    context_->onShow_ = false;
    context_->rootNode_ = rootBackup;
}

/**
 * @tc.name: PipelineContextSevenTest070
 * @tc.desc: Test TriggerIdleCallback when idleCallbackFuncs is empty,
 *           covering branch (idleCallbackFuncs_.empty()) as true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest070, TestSize.Level1)
{
    AssertValidContext();
    ASSERT_TRUE(context_->idleCallbackFuncs_.empty());
    context_->TriggerIdleCallback(0);
    EXPECT_TRUE(context_->idleCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextSevenTest071
 * @tc.desc: Test TriggerIdleCallback when deadline - currentTime < MIN_IDLE_TIME,
 *           covering branch (deadline - currentTime < MIN_IDLE_TIME) as true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest071, TestSize.Level1)
{
    AssertValidContext();
    auto idleBackup = std::move(context_->idleCallbackFuncs_);
    context_->idleCallbackFuncs_.push_back([](uint64_t, uint32_t) {});
    context_->TriggerIdleCallback(0);
    EXPECT_FALSE(context_->idleCallbackFuncs_.empty());
    context_->idleCallbackFuncs_ = std::move(idleBackup);
}

/**
 * @tc.name: PipelineContextSevenTest072
 * @tc.desc: Test ProcessOverlayChildrenDumpInfo when child has overlay tag and isInSubWindow is true
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest072, TestSize.Level1)
{
    AssertValidContext();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayChild = FrameNode::CreateFrameNode(
        V2::TOAST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlayChild, nullptr);
    overlayChild->SetActive(true);
    rootNode->AddChild(overlayChild);
    auto overlayChildrenArray = JsonUtil::CreateArray();
    auto subWindowOverlayArray = JsonUtil::CreateArray();
    ParamConfig config;
    bool result = context_->ProcessOverlayChildrenDumpInfo(rootNode, overlayChildrenArray, subWindowOverlayArray,
        true, config, DEFAULT_NODE_OPACITY);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PipelineContextSevenTest073
 * @tc.desc: Test ProcessOverlayChildrenDumpInfo when child has overlay tag and isInSubWindow is false
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest073, TestSize.Level1)
{
    AssertValidContext();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayChild = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlayChild, nullptr);
    overlayChild->SetActive(true);
    rootNode->AddChild(overlayChild);
    auto overlayChildrenArray = JsonUtil::CreateArray();
    auto subWindowOverlayArray = JsonUtil::CreateArray();
    ParamConfig config;
    bool result = context_->ProcessOverlayChildrenDumpInfo(rootNode, overlayChildrenArray, subWindowOverlayArray,
        false, config, DEFAULT_NODE_OPACITY);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PipelineContextSevenTest074
 * @tc.desc: Test ProcessOverlayChildrenDumpInfo when child does not have overlay tag
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest074, TestSize.Level1)
{
    AssertValidContext();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto nonOverlayChild = FrameNode::CreateFrameNode(
        "Column", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nonOverlayChild, nullptr);
    rootNode->AddChild(nonOverlayChild);
    auto overlayChildrenArray = JsonUtil::CreateArray();
    auto subWindowOverlayArray = JsonUtil::CreateArray();
    ParamConfig config;
    bool result = context_->ProcessOverlayChildrenDumpInfo(rootNode, overlayChildrenArray, subWindowOverlayArray,
        false, config, DEFAULT_NODE_OPACITY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PipelineContextSevenTest075
 * @tc.desc: Test ProcessOverlayChildrenDumpInfo when rootNode has no children
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest075, TestSize.Level1)
{
    AssertValidContext();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayChildrenArray = JsonUtil::CreateArray();
    auto subWindowOverlayArray = JsonUtil::CreateArray();
    ParamConfig config;
    bool result = context_->ProcessOverlayChildrenDumpInfo(rootNode, overlayChildrenArray, subWindowOverlayArray,
        false, config, DEFAULT_NODE_OPACITY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PipelineContextSevenTest076
 * @tc.desc: Test GetComponentOverlayInspector with isInSubWindow false
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest076, TestSize.Level1)
{
    AssertValidContext();
    auto startNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(startNode, nullptr);
    auto overlayChild = FrameNode::CreateFrameNode(
        V2::TOAST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlayChild, nullptr);
    startNode->AddChild(overlayChild);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->GetComponentOverlayInspector(root, startNode, config, false);
    EXPECT_TRUE(root->Contains("$type"));
}

/**
 * @tc.name: PipelineContextSevenTest077
 * @tc.desc: Test GetComponentOverlayInspector with isInSubWindow true and root has no "$children"
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest077, TestSize.Level1)
{
    AssertValidContext();
    auto startNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(startNode, nullptr);
    auto overlayChild = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlayChild, nullptr);
    overlayChild->SetActive(true);
    startNode->AddChild(overlayChild);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->GetComponentOverlayInspector(root, startNode, config, true);
    EXPECT_TRUE(root->Contains("$children"));
}

/**
 * @tc.name: PipelineContextSevenTest078
 * @tc.desc: Test GetComponentOverlayInspector with isInSubWindow true and root contains "$children"
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest078, TestSize.Level1)
{
    AssertValidContext();
    auto startNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(startNode, nullptr);
    auto overlayChild = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlayChild, nullptr);
    startNode->AddChild(overlayChild);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    auto childrenArray = JsonUtil::CreateArray();
    auto childItem = JsonUtil::CreateSharedPtrJson();
    auto subChildren = JsonUtil::CreateArray();
    childItem->PutRef("$children", std::move(subChildren));
    childrenArray->Put(childItem);
    root->PutRef("$children", std::move(childrenArray));
    ParamConfig config;
    context_->GetComponentOverlayInspector(root, startNode, config, true);
    auto rootChildren = root->GetValue("$children");
    ASSERT_TRUE(rootChildren != nullptr && rootChildren->IsArray() && rootChildren->GetArraySize() > 0);
    auto firstChild = rootChildren->GetArrayItem(0);
    ASSERT_TRUE(firstChild != nullptr && firstChild->Contains("$children"));
    EXPECT_GT(firstChild->GetValue("$children")->GetArraySize(), 0);
}

/**
 * @tc.name: PipelineContextSevenTest079
 * @tc.desc: Test DumpSimplifyTreeJsonEntrance when lastPageNode is null
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest079, TestSize.Level1)
{
    AssertValidContext();
    auto startNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(startNode, nullptr);
    auto stageManagerBackup = context_->stageManager_;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(rootNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    context_->DumpSimplifyTreeJsonEntrance(root, startNode, config);
    EXPECT_FALSE(root->Contains("$children"));
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest080
 * @tc.desc: Test DumpSimplifyTreeJsonEntrance when lastPageNode exists but has no navigation child
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest080, TestSize.Level1)
{
    AssertValidContext();
    auto startNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(startNode, nullptr);
    auto stageManagerBackup = context_->stageManager_;
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    stageNode->AddChild(pageNode);
    context_->stageManager_ = AceType::MakeRefPtr<StageManager>(stageNode);
    auto root = JsonUtil::CreateSharedPtrJson(true);
    ParamConfig config;
    EXPECT_NO_FATAL_FAILURE(context_->DumpSimplifyTreeJsonEntrance(root, startNode, config));
    context_->stageManager_ = stageManagerBackup;
}

/**
 * @tc.name: PipelineContextSevenTest081
 * @tc.desc: Test AdjustVsyncTimeStamp when period is 0 (default mock window)
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest081, TestSize.Level1)
{
    AssertValidContext();
    auto backupRecvTime = context_->recvTime_;
    context_->recvTime_ = 0;
    auto result = context_->AdjustVsyncTimeStamp(TEST_SMALL_TIMESTAMP);
    EXPECT_EQ(result, TEST_SMALL_TIMESTAMP);
    context_->recvTime_ = backupRecvTime;
}

/**
 * @tc.name: PipelineContextSevenTest082
 * @tc.desc: Test AdjustVsyncTimeStamp when nanoTimestamp exceeds LARGE_TIME
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest082, TestSize.Level1)
{
    AssertValidContext();
    auto backupRecvTime = context_->recvTime_;
    context_->recvTime_ = 0;
    uint64_t hugeTimestamp = LARGE_TIME_THRESHOLD + 1;
    auto result = context_->AdjustVsyncTimeStamp(hugeTimestamp);
    EXPECT_EQ(result, hugeTimestamp);
    context_->recvTime_ = backupRecvTime;
}

/**
 * @tc.name: PipelineContextSevenTest083
 * @tc.desc: Test DumpForceColor when params size <= PARAM_NUM
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest083, TestSize.Level1)
{
    AssertValidContext();
    std::vector<std::string> params = {"-forcecolor"};
    EXPECT_NO_FATAL_FAILURE(context_->DumpForceColor(params));
}

/**
 * @tc.name: PipelineContextSevenTest084
 * @tc.desc: Test DumpForceColor when nodeId < 0 (invalid node id string)
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest084, TestSize.Level1)
{
    AssertValidContext();
    std::vector<std::string> params = {"-forcecolor", "abc", "#FF000000"};
    EXPECT_NO_FATAL_FAILURE(context_->DumpForceColor(params));
}

/**
 * @tc.name: PipelineContextSevenTest085
 * @tc.desc: Test DumpForceColor with valid params, nodeId >= 0
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextSevenTest085, TestSize.Level1)
{
    AssertValidContext();
    std::vector<std::string> params = {"-forcecolor", "100", "#FF000000"};
    EXPECT_NO_FATAL_FAILURE(context_->DumpForceColor(params));
}

} // namespace OHOS::Ace::NG
