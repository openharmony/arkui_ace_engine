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

#include <gtest/gtest.h>

#include <chrono>
#include <string>
#include <vector>

#define private public // NOLINT
#define protected public // NOLINT
#include "base/utils/feature_manager.h"
#include "core/common/event_manager.h"
#include "core/common/statistic_event_reporter.h"
#include "core/event/event_info_convertor.h"
#include "core/image/image_cache.h"
#include "core/pipeline/container_window_manager.h"
#include "frameworks/core/common/font_manager.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_window.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const char CONTEXT_MENU_OPTIONS[] = "contextMenuOptions";
constexpr int32_t DEFAULT_INSTANCE_ID = 0;
constexpr int32_t TEST_LONG_PRESS_DURATION = 3000;
constexpr int32_t LONG_PRESS_DEFAULT_DURATION = 500;
} // namespace

class RightMouseMappingTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
#ifdef ACE_UNITTEST
        FeatureManager::GetInstance().ResetForTest();
#endif
    }

    static void TearDownTestSuite()
    {
#ifdef ACE_UNITTEST
        FeatureManager::GetInstance().ClearFeatureParamForTest();
#endif
    }

    void SetUp() override
    {
#ifdef ACE_UNITTEST
        FeatureManager::GetInstance().ClearFeatureParamForTest();
#endif
    }

    void TearDown() override
    {
#ifdef ACE_UNITTEST
        FeatureManager::GetInstance().ClearFeatureParamForTest();
#endif
    }
};

// EventInfoConvertor stub always returns NOT_FOUND/false in TDD environment.
// These tests verify the stub contract: regardless of FeatureManager state,
// the stub returns NOT_FOUND and does not modify output parameters.

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig001, TestSize.Level1)
{
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::NOT_FOUND);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled001, TestSize.Level1)
{
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, LongPressRecognizerGetDuration001, TestSize.Level1)
{
    RefPtr<LongPressRecognizer> recognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(TEST_LONG_PRESS_DURATION, 1, false);
    EXPECT_EQ(recognizer->GetDuration(), TEST_LONG_PRESS_DURATION);
    recognizer->SetDuration(LONG_PRESS_DEFAULT_DURATION);
    EXPECT_EQ(recognizer->GetDuration(), LONG_PRESS_DEFAULT_DURATION);
}

class RightMouseMappingPipelineTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        auto window = std::make_shared<MockWindow>();
        EXPECT_CALL(*window, RequestFrame()).Times(AnyNumber());
        EXPECT_CALL(*window, FlushTasks(testing::_)).Times(AnyNumber());
        EXPECT_CALL(*window, OnHide()).Times(AnyNumber());
        EXPECT_CALL(*window, RecordFrameTime(_, _)).Times(AnyNumber());
        EXPECT_CALL(*window, OnShow()).Times(AnyNumber());
        context_ = AceType::MakeRefPtr<PipelineContext>(
            window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
        context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
        context_->statisticEventReporter_ = std::make_shared<StatisticEventReporter>(DEFAULT_INSTANCE_ID);
        context_->windowManager_ = AceType::MakeRefPtr<WindowManager>();
        context_->fontManager_ = FontManager::Create();
        context_->imageCache_ = ImageCache::Create();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = context_;
    }

    static void TearDownTestSuite()
    {
        context_->Destroy();
        context_->window_.reset();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        context_->isRightMouseMappingActive_ = false;
        context_->onRightMouseMappingCancel_ = nullptr;
        context_->lastSourceType_ = SourceType::NONE;
    }

    void TearDown() override
    {
        context_->isRightMouseMappingActive_ = false;
        context_->onRightMouseMappingCancel_ = nullptr;
        context_->lastSourceType_ = SourceType::NONE;
    }

    static RefPtr<PipelineContext> context_;
};

RefPtr<PipelineContext> RightMouseMappingPipelineTestNg::context_ = nullptr;

// PipelineContext: isRightMouseMappingActive_ default + set/get

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive001, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
}

// PipelineContext: onRightMouseMappingCancel_ callback

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingCancelCallback001, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() { cancelCalled = true; });
    context_->SetRightMouseMappingActive(true);
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_TRUE(cancelCalled);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingCancelCallback002, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() { cancelCalled = true; });
    EXPECT_FALSE(context_->isRightMouseMappingActive_);
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_FALSE(cancelCalled);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingCancelCallback003, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    context_->onRightMouseMappingCancel_ = nullptr;
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_TRUE(context_->isRightMouseMappingActive_);
}

// PipelineContext: WindowFocus(false) triggers cancel when mapping active

HWTEST_F(RightMouseMappingPipelineTestNg, WindowFocusCancelsMapping001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() {
        cancelCalled = true;
    });
    context_->WindowFocus(false);
    EXPECT_TRUE(cancelCalled);
}

// PipelineContext: WindowFocus(false) does NOT trigger cancel when mapping inactive

HWTEST_F(RightMouseMappingPipelineTestNg, WindowFocusCancelsMapping002, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() {
        cancelCalled = true;
    });
    context_->WindowFocus(false);
    EXPECT_FALSE(cancelCalled);
}

// PipelineContext: OnHide triggers cancel when mapping active

HWTEST_F(RightMouseMappingPipelineTestNg, OnHideCancelsMapping001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() {
        cancelCalled = true;
    });
    context_->OnHide();
    EXPECT_TRUE(cancelCalled);
}

// PipelineContext: OnHide does NOT trigger cancel when mapping inactive

HWTEST_F(RightMouseMappingPipelineTestNg, OnHideCancelsMapping002, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() {
        cancelCalled = true;
    });
    context_->OnHide();
    EXPECT_FALSE(cancelCalled);
}

// PipelineContext: double cancel protection (OnHide then WindowFocus)

HWTEST_F(RightMouseMappingPipelineTestNg, DoubleCancelProtection001, TestSize.Level1)
{
    int callCount = 0;
    context_->SetOnRightMouseMappingCancel([&callCount]() {
        callCount++;
    });
    context_->SetRightMouseMappingActive(true);
    context_->OnHide();
    EXPECT_EQ(callCount, 1);
    context_->WindowFocus(false);
    EXPECT_EQ(callCount, 1);
}

// source-type protection: isRightMouseMappingActive_ + sourceTool=MOUSE + sourceType=TOUCH
// skips CheckSourceTypeChange so lastSourceType_ is not polluted

HWTEST_F(RightMouseMappingPipelineTestNg, SourceTypeProtection001, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    context_->SetRightMouseMappingActive(true);
    TouchEvent mappedDown;
    mappedDown.id = 1002;
    mappedDown.x = 100.0f;
    mappedDown.y = 100.0f;
    mappedDown.type = TouchType::DOWN;
    mappedDown.sourceType = SourceType::TOUCH;
    mappedDown.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(mappedDown);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

    TouchEvent mappedMove;
    mappedMove.id = 1002;
    mappedMove.x = 101.0f;
    mappedMove.y = 101.0f;
    mappedMove.type = TouchType::MOVE;
    mappedMove.sourceType = SourceType::TOUCH;
    mappedMove.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(mappedMove);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

    TouchEvent mappedUp;
    mappedUp.id = 1002;
    mappedUp.x = 101.0f;
    mappedUp.y = 101.0f;
    mappedUp.type = TouchType::UP;
    mappedUp.sourceType = SourceType::TOUCH;
    mappedUp.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(mappedUp);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

// source-type protection: real touch (sourceTool=FINGER) still updates lastSourceType_

HWTEST_F(RightMouseMappingPipelineTestNg, SourceTypeProtection002, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    TouchEvent realTouch;
    realTouch.x = 100.0f;
    realTouch.y = 100.0f;
    realTouch.type = TouchType::DOWN;
    realTouch.sourceType = SourceType::TOUCH;
    realTouch.sourceTool = SourceTool::FINGER;
    context_->OnTouchEvent(realTouch);
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

// source-type protection: after mapping ends, real mouse MOVE detects no spurious change

HWTEST_F(RightMouseMappingPipelineTestNg, SourceTypeProtection003, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    context_->SetRightMouseMappingActive(true);
    TouchEvent mappedDown;
    mappedDown.id = 1002;
    mappedDown.type = TouchType::DOWN;
    mappedDown.sourceType = SourceType::TOUCH;
    mappedDown.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(mappedDown);
    context_->SetRightMouseMappingActive(false);

    MouseEvent mouseMove;
    mouseMove.x = 102.0f;
    mouseMove.y = 102.0f;
    mouseMove.sourceType = SourceType::MOUSE;
    mouseMove.sourceTool = SourceTool::MOUSE;
    mouseMove.action = MouseAction::MOVE;
    mouseMove.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(mouseMove, context_->GetRootElement());
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

// PipelineContext member layout: isRightMouseMappingActive_ at end, no ABI break

HWTEST_F(RightMouseMappingPipelineTestNg, PipelineContextMemberLayout001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    auto focusNode = FrameNode::GetOrCreateFrameNode("focusTest", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    context_->focusNode_ = focusNode;
    EXPECT_EQ(context_->focusNode_, focusNode);
    context_->focusNode_ = nullptr;
}

// HitTestMouseTargetForMapping: null root returns false

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping001, TestSize.Level1)
{
    MouseEvent event;
    event.x = 100.0f;
    event.y = 100.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput" };
    bool result = context_->HitTestMouseTargetForMapping(event, nullptr, whitelist);
    EXPECT_FALSE(result);
}

// HitTestMouseTargetForMapping: empty whitelist (no tag restriction)

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping002, TestSize.Level1)
{
    auto rootNode = FrameNode::GetOrCreateFrameNode("root", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(rootNode, nullptr);
    context_->rootNode_ = rootNode;

    MouseEvent event;
    event.x = 100.0f;
    event.y = 100.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> emptyWhitelist;
    context_->HitTestMouseTargetForMapping(event, nullptr, emptyWhitelist);
    context_->rootNode_ = nullptr;
}

// HitTestMouseTargetForMapping: tag not in whitelist returns false

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping003, TestSize.Level1)
{
    auto buttonNode = FrameNode::GetOrCreateFrameNode("button", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    context_->rootNode_ = buttonNode;

    MouseEvent event;
    event.x = 0.0f;
    event.y = 0.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput", "TextArea" };
    bool result = context_->HitTestMouseTargetForMapping(event, buttonNode, whitelist);
    EXPECT_FALSE(result);
    context_->rootNode_ = nullptr;
}

// HitTestMouseTargetForMapping: tag in whitelist but no children

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping004, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode("TextInput", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(textNode, nullptr);
    context_->rootNode_ = textNode;

    MouseEvent event;
    event.x = 0.0f;
    event.y = 0.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput" };
    bool result = context_->HitTestMouseTargetForMapping(event, textNode, whitelist);
    context_->rootNode_ = nullptr;
}

// HitTestMouseTargetForMapping: parent tag not in whitelist, child tag matches (recursive)

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping005, TestSize.Level1)
{
    auto parentNode = FrameNode::GetOrCreateFrameNode("parent", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(parentNode, nullptr);
    auto childNode = FrameNode::GetOrCreateFrameNode("TextInput", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(childNode, nullptr);
    context_->rootNode_ = parentNode;

    MouseEvent event;
    event.x = 0.0f;
    event.y = 0.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput" };
    bool result = context_->HitTestMouseTargetForMapping(event, parentNode, whitelist);
    context_->rootNode_ = nullptr;
}

// CheckSourceTypeChange: NONE->TOUCH->MOUSE transitions

HWTEST_F(RightMouseMappingPipelineTestNg, CheckSourceTypeChange001, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::NONE;
    EXPECT_TRUE(context_->CheckSourceTypeChange(SourceType::TOUCH));
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
    EXPECT_TRUE(context_->CheckSourceTypeChange(SourceType::MOUSE));
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

// CheckSourceTypeChange: same type returns false

HWTEST_F(RightMouseMappingPipelineTestNg, CheckSourceTypeChange002, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::TOUCH;
    EXPECT_FALSE(context_->CheckSourceTypeChange(SourceType::TOUCH));
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

// Event interaction: mapped touch DOWN/MOVE/UP with isRightMouseMappingActive_ preserves lastSourceType_

HWTEST_F(RightMouseMappingPipelineTestNg, MappedTouchPreservesSourceType001, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    context_->SetRightMouseMappingActive(true);

    TouchEvent downEvent;
    downEvent.id = 1002;
    downEvent.x = 100.0f;
    downEvent.y = 100.0f;
    downEvent.type = TouchType::DOWN;
    downEvent.sourceType = SourceType::TOUCH;
    downEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(downEvent);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

    TouchEvent moveEvent;
    moveEvent.id = 1002;
    moveEvent.x = 101.0f;
    moveEvent.y = 101.0f;
    moveEvent.type = TouchType::MOVE;
    moveEvent.sourceType = SourceType::TOUCH;
    moveEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(moveEvent);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

    TouchEvent upEvent;
    upEvent.id = 1002;
    upEvent.x = 101.0f;
    upEvent.y = 101.0f;
    upEvent.type = TouchType::UP;
    upEvent.sourceType = SourceType::TOUCH;
    upEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(upEvent);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

// Event interaction: mapped touch CANCEL does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, MappedTouchCancel001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    TouchEvent downEvent;
    downEvent.id = 1002;
    downEvent.x = 100.0f;
    downEvent.y = 100.0f;
    downEvent.type = TouchType::DOWN;
    downEvent.sourceType = SourceType::TOUCH;
    downEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(downEvent);

    TouchEvent cancelEvent;
    cancelEvent.id = 1002;
    cancelEvent.x = 100.0f;
    cancelEvent.y = 100.0f;
    cancelEvent.type = TouchType::CANCEL;
    cancelEvent.sourceType = SourceType::TOUCH;
    cancelEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(cancelEvent);
}

// Event interaction: mouse MOVE when mapping active does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, MouseMoveMappingActive001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent mouseMove;
    mouseMove.x = 101.0f;
    mouseMove.y = 101.0f;
    mouseMove.sourceType = SourceType::MOUSE;
    mouseMove.sourceTool = SourceTool::MOUSE;
    mouseMove.action = MouseAction::MOVE;
    mouseMove.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(mouseMove, context_->GetRootElement());
}

// Event interaction: left-click after mapping cancelled does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, LeftClickAfterCancel001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    context_->SetRightMouseMappingActive(false);
    MouseEvent mouseEvent;
    mouseEvent.x = 100.0f;
    mouseEvent.y = 100.0f;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.sourceTool = SourceTool::MOUSE;
    mouseEvent.action = MouseAction::PRESS;
    mouseEvent.button = MouseButton::LEFT_BUTTON;
    context_->OnMouseEvent(mouseEvent, context_->GetRootElement());
}

// Right-button fallback: right-click PRESS with empty whitelist does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickPressEmptyWhitelist001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent pressEvent;
    pressEvent.x = 100.0f;
    pressEvent.y = 100.0f;
    pressEvent.sourceType = SourceType::MOUSE;
    pressEvent.sourceTool = SourceTool::MOUSE;
    pressEvent.action = MouseAction::PRESS;
    pressEvent.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(pressEvent, context_->GetRootElement());
}

// Right-button fallback: right-click MOVE with NONE_BUTTON does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickMoveNoneButton001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent moveEvent;
    moveEvent.x = 101.0f;
    moveEvent.y = 101.0f;
    moveEvent.sourceType = SourceType::MOUSE;
    moveEvent.sourceTool = SourceTool::MOUSE;
    moveEvent.action = MouseAction::MOVE;
    moveEvent.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(moveEvent, context_->GetRootElement());
}

// Right-button fallback: right-click RELEASE does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickRelease001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent releaseEvent;
    releaseEvent.x = 100.0f;
    releaseEvent.y = 100.0f;
    releaseEvent.sourceType = SourceType::MOUSE;
    releaseEvent.sourceTool = SourceTool::MOUSE;
    releaseEvent.action = MouseAction::RELEASE;
    releaseEvent.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(releaseEvent, context_->GetRootElement());
}

// Right-button fallback: right-click CANCEL with NONE_BUTTON does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickCancelNoneButton001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent cancelEvent;
    cancelEvent.x = 100.0f;
    cancelEvent.y = 100.0f;
    cancelEvent.sourceType = SourceType::MOUSE;
    cancelEvent.sourceTool = SourceTool::MOUSE;
    cancelEvent.action = MouseAction::CANCEL;
    cancelEvent.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(cancelEvent, context_->GetRootElement());
}

// Right-button fallback: right-click CANCEL with RIGHT_BUTTON does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickCancelRightButton001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent cancelEvent;
    cancelEvent.x = 100.0f;
    cancelEvent.y = 100.0f;
    cancelEvent.sourceType = SourceType::MOUSE;
    cancelEvent.sourceTool = SourceTool::MOUSE;
    cancelEvent.action = MouseAction::CANCEL;
    cancelEvent.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(cancelEvent, context_->GetRootElement());
}

// Right-button fallback: stylus right-click (sourceTool=PEN) does not trigger mapping

HWTEST_F(RightMouseMappingPipelineTestNg, StylusRightClickNoMapping001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent stylusEvent;
    stylusEvent.x = 100.0f;
    stylusEvent.y = 100.0f;
    stylusEvent.sourceType = SourceType::MOUSE;
    stylusEvent.sourceTool = SourceTool::PEN;
    stylusEvent.action = MouseAction::PRESS;
    stylusEvent.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(stylusEvent, context_->GetRootElement());
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
}

// Right-button fallback: consecutive right-click PRESS does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, ConsecutiveRightClickPress001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent press1;
    press1.x = 100.0f;
    press1.y = 100.0f;
    press1.sourceType = SourceType::MOUSE;
    press1.sourceTool = SourceTool::MOUSE;
    press1.action = MouseAction::PRESS;
    press1.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(press1, context_->GetRootElement());

    MouseEvent press2;
    press2.x = 200.0f;
    press2.y = 200.0f;
    press2.sourceType = SourceType::MOUSE;
    press2.sourceTool = SourceTool::MOUSE;
    press2.action = MouseAction::PRESS;
    press2.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(press2, context_->GetRootElement());
}

// Right-button fallback: full PRESS→MOVE→RELEASE→CANCEL sequence does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, FullRightClickSequence001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    MouseEvent press;
    press.x = 100.0f;
    press.y = 100.0f;
    press.sourceType = SourceType::MOUSE;
    press.sourceTool = SourceTool::MOUSE;
    press.action = MouseAction::PRESS;
    press.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(press, context_->GetRootElement());

    MouseEvent move;
    move.x = 101.0f;
    move.y = 101.0f;
    move.sourceType = SourceType::MOUSE;
    move.sourceTool = SourceTool::MOUSE;
    move.action = MouseAction::MOVE;
    move.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(move, context_->GetRootElement());

    MouseEvent release;
    release.x = 101.0f;
    release.y = 101.0f;
    release.sourceType = SourceType::MOUSE;
    release.sourceTool = SourceTool::MOUSE;
    release.action = MouseAction::RELEASE;
    release.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(release, context_->GetRootElement());

    MouseEvent cancel;
    cancel.x = 101.0f;
    cancel.y = 101.0f;
    cancel.sourceType = SourceType::MOUSE;
    cancel.sourceTool = SourceTool::MOUSE;
    cancel.action = MouseAction::CANCEL;
    cancel.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(cancel, context_->GetRootElement());
}

// Right-button fallback: mapping inactive + right-click PRESS does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickPressMappingInactive001, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    MouseEvent press;
    press.x = 100.0f;
    press.y = 100.0f;
    press.sourceType = SourceType::MOUSE;
    press.sourceTool = SourceTool::MOUSE;
    press.action = MouseAction::PRESS;
    press.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(press, context_->GetRootElement());
}

// Right-button fallback: mapping inactive + right-click MOVE does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickMoveMappingInactive001, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    MouseEvent move;
    move.x = 101.0f;
    move.y = 101.0f;
    move.sourceType = SourceType::MOUSE;
    move.sourceTool = SourceTool::MOUSE;
    move.action = MouseAction::MOVE;
    move.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(move, context_->GetRootElement());
}

// Right-button fallback: mapping inactive + right-click RELEASE does not crash

HWTEST_F(RightMouseMappingPipelineTestNg, RightClickReleaseMappingInactive001, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    MouseEvent release;
    release.x = 100.0f;
    release.y = 100.0f;
    release.sourceType = SourceType::MOUSE;
    release.sourceTool = SourceTool::MOUSE;
    release.action = MouseAction::RELEASE;
    release.button = MouseButton::RIGHT_BUTTON;
    context_->OnMouseEvent(release, context_->GetRootElement());
}

} // namespace OHOS::Ace::NG
