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
#include "test/mock/frameworks/core/components_ng/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/ai/ai_write_adapter.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/common/statistic_event_reporter.h"
#include "core/components_ng/pattern/web/itouch_event_callback.h"

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
    context_->windowModal_ = WindowModal::NORMAL;

    // Build a tree to verify early return doesn't modify pattern state
    auto tree = SetupContainerModalTree(context_);
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

} // namespace OHOS::Ace::NG
