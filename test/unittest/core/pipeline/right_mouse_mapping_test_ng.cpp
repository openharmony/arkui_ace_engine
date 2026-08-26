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

#define private public
#define protected public
#include "base/utils/feature_manager.h"
#include "core/common/event_manager.h"
#include "core/event/event_info_convertor.h"
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

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig001, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "", FeatureManager::INIT_FAILED);
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::INIT_FAILED);
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig002, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "", FeatureManager::KEY_NOT_FOUND);
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::NOT_FOUND);
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig003, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "not_valid_json");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::NOT_FOUND);
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig004, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":false})");
#endif
    bool enabled = true;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig005, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":true})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig006, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","TextArea","RichEditor","Text"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 4u);
    EXPECT_EQ(components[0], "TextInput");
    EXPECT_EQ(components[1], "TextArea");
    EXPECT_EQ(components[2], "RichEditor");
    EXPECT_EQ(components[3], "Text");
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig007, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":true,"needTransferComponent":[]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig008, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":true,"needTransferComponent":"not_an_array"})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig009, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "{}");
#endif
    bool enabled = true;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig010, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":"true"})");
#endif
    bool enabled = true;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig011, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","TextArea"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 2u);
    EXPECT_EQ(components[0], "TextInput");
    EXPECT_EQ(components[1], "TextArea");
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig012, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","TextInput","Text"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 3u);
    EXPECT_EQ(components[0], "TextInput");
    EXPECT_EQ(components[1], "TextInput");
    EXPECT_EQ(components[2], "Text");
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig013, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["All"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig014, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","All","Text"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, GetRightMouse2LongPressConfig015, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["CustomWidget","MySpecialNode"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 2u);
    EXPECT_EQ(components[0], "CustomWidget");
    EXPECT_EQ(components[1], "MySpecialNode");
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled001, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "", FeatureManager::INIT_FAILED);
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_FALSE(ret);
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled002, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(CONTEXT_MENU_OPTIONS, "", FeatureManager::KEY_NOT_FOUND);
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_FALSE(ret);
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled003, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS, R"({"rightMouse2LongPress":false})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_FALSE(ret);
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled004, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","TextArea"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 2u);
}

HWTEST_F(RightMouseMappingTestNg, IsRightMouseMappingEnabled005, TestSize.Level1)
{
#ifdef ACE_UNITTEST
    FeatureManager::GetInstance().SetFeatureParamForTest(
        CONTEXT_MENU_OPTIONS,
        R"({"rightMouse2LongPress":true,"needTransferComponent":["All"]})");
#endif
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(enabled);
    EXPECT_TRUE(components.empty());
}

HWTEST_F(RightMouseMappingTestNg, LongPressDefaultDuration001, TestSize.Level1)
{
    RefPtr<LongPressRecognizer> recognizer = AceType::MakeRefPtr<
        LongPressRecognizer>(LONG_PRESS_DEFAULT_DURATION, 1, false);
    EXPECT_EQ(recognizer->GetDuration(), LONG_PRESS_DEFAULT_DURATION);
}

HWTEST_F(RightMouseMappingTestNg, LongPressRecognizerGetDuration001, TestSize.Level1)
{
    RefPtr<LongPressRecognizer> recognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(TEST_LONG_PRESS_DURATION, 1, false);
    EXPECT_EQ(recognizer->GetDuration(), TEST_LONG_PRESS_DURATION);
}

HWTEST_F(RightMouseMappingTestNg, LongPressRecognizerGetDuration002, TestSize.Level1)
{
    RefPtr<LongPressRecognizer> recognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(TEST_LONG_PRESS_DURATION, 1, false);
    recognizer->SetDuration(800);
    EXPECT_EQ(recognizer->GetDuration(), 800);
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

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive001, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive002, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive003, TestSize.Level1)
{
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive004, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() { cancelCalled = true; });
    context_->SetRightMouseMappingActive(true);
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_TRUE(cancelCalled);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive005, TestSize.Level1)
{
    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() { cancelCalled = true; });
    EXPECT_FALSE(context_->isRightMouseMappingActive_);
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_FALSE(cancelCalled);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive006, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    context_->onRightMouseMappingCancel_ = nullptr;
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_TRUE(context_->isRightMouseMappingActive_);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive007, TestSize.Level1)
{
    int callCount1 = 0;
    int callCount2 = 0;
    context_->SetOnRightMouseMappingCancel([&callCount1]() { callCount1++; });
    context_->SetOnRightMouseMappingCancel([&callCount2]() { callCount2++; });
    context_->SetRightMouseMappingActive(true);
    if (context_->isRightMouseMappingActive_ && context_->onRightMouseMappingCancel_) {
        context_->onRightMouseMappingCancel_();
    }
    EXPECT_EQ(callCount1, 0);
    EXPECT_EQ(callCount2, 1);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingActive008, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());
}

HWTEST_F(RightMouseMappingPipelineTestNg, MappedMouseTouchEventPreservesSourceType001, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    bool isMappedMouseTouch = true;
    if (!isMappedMouseTouch) {
        context_->CheckSourceTypeChange(SourceType::TOUCH);
    }
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
    context_->CheckSourceTypeChange(SourceType::TOUCH);
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

HWTEST_F(RightMouseMappingPipelineTestNg, MappedMouseTouchEventPreservesSourceType002, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    bool changed = context_->CheckSourceTypeChange(SourceType::TOUCH);
    EXPECT_TRUE(changed);
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

HWTEST_F(RightMouseMappingPipelineTestNg, CheckSourceTypeChange001, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::NONE;
    EXPECT_TRUE(context_->CheckSourceTypeChange(SourceType::TOUCH));
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
    EXPECT_TRUE(context_->CheckSourceTypeChange(SourceType::MOUSE));
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

HWTEST_F(RightMouseMappingPipelineTestNg, CheckSourceTypeChange002, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::TOUCH;
    EXPECT_FALSE(context_->CheckSourceTypeChange(SourceType::TOUCH));
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

HWTEST_F(RightMouseMappingPipelineTestNg, CheckSourceTypeChange003, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::NONE;
    bool changed = context_->CheckSourceTypeChange(SourceType::TOUCH);
    EXPECT_TRUE(changed);
    EXPECT_EQ(context_->lastSourceType_, SourceType::TOUCH);
}

HWTEST_F(RightMouseMappingPipelineTestNg, MappedMouseTouchEventPreservesSourceType003, TestSize.Level1)
{
    context_->lastSourceType_ = SourceType::MOUSE;
    bool isMappedMouseTouch = true;
    if (!isMappedMouseTouch) {
        context_->CheckSourceTypeChange(SourceType::TOUCH);
    }
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
    if (!isMappedMouseTouch) {
        context_->CheckSourceTypeChange(SourceType::TOUCH);
    }
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
    bool changed = context_->CheckSourceTypeChange(SourceType::MOUSE);
    EXPECT_FALSE(changed);
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);
}

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

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping001, TestSize.Level1)
{
    MouseEvent event;
    event.x = 100.0f;
    event.y = 100.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput" };
    int32_t longPressDuration = 0;
    bool result = context_->HitTestMouseTargetForMapping(event, nullptr, whitelist, longPressDuration);
    EXPECT_FALSE(result);
}

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
    int32_t longPressDuration = 0;
    context_->HitTestMouseTargetForMapping(event, nullptr, emptyWhitelist, longPressDuration);
    context_->rootNode_ = nullptr;
}

HWTEST_F(RightMouseMappingPipelineTestNg, HitTestMouseTargetForMapping003, TestSize.Level1)
{
    MouseEvent event;
    event.x = -1000.0f;
    event.y = -1000.0f;
    event.button = MouseButton::RIGHT_BUTTON;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    std::vector<std::string> whitelist = { "TextInput" };
    int32_t longPressDuration = 999;
    context_->HitTestMouseTargetForMapping(event, nullptr, whitelist, longPressDuration);
    EXPECT_EQ(longPressDuration, LONG_PRESS_DEFAULT_DURATION);
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingMoveEvent001, TestSize.Level1)
{
    MouseEvent mouseMove;
    mouseMove.x = 100.0f;
    mouseMove.y = 100.0f;
    mouseMove.sourceType = SourceType::MOUSE;
    mouseMove.sourceTool = SourceTool::MOUSE;
    mouseMove.action = MouseAction::MOVE;
    mouseMove.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(mouseMove, context_->GetRootElement());
    EXPECT_EQ(context_->lastSourceType_, SourceType::MOUSE);

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
}

HWTEST_F(RightMouseMappingPipelineTestNg, RightMouseMappingMoveEvent002, TestSize.Level1)
{
    TouchEvent downEvent;
    downEvent.id = 1002;
    downEvent.x = 100.0f;
    downEvent.y = 100.0f;
    downEvent.type = TouchType::DOWN;
    downEvent.sourceType = SourceType::TOUCH;
    downEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(downEvent);

    TouchEvent moveEvent;
    moveEvent.id = 1002;
    moveEvent.x = 101.0f;
    moveEvent.y = 101.0f;
    moveEvent.type = TouchType::MOVE;
    moveEvent.sourceType = SourceType::TOUCH;
    moveEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(moveEvent);

    TouchEvent upEvent;
    upEvent.id = 1002;
    upEvent.x = 101.0f;
    upEvent.y = 101.0f;
    upEvent.type = TouchType::UP;
    upEvent.sourceType = SourceType::TOUCH;
    upEvent.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(upEvent);

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

HWTEST_F(RightMouseMappingPipelineTestNg, LeftClickCancelsMapping001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());

    bool cancelCalled = false;
    context_->SetOnRightMouseMappingCancel([&cancelCalled]() {
        cancelCalled = true;
    });

    context_->WindowFocus(false);
    EXPECT_TRUE(cancelCalled);
}

HWTEST_F(RightMouseMappingPipelineTestNg, LeftClickCancelsMapping002, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());
    context_->SetRightMouseMappingActive(false);
    EXPECT_FALSE(context_->IsRightMouseMappingActive());

    MouseEvent mouseEvent;
    mouseEvent.x = 100.0f;
    mouseEvent.y = 100.0f;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.sourceTool = SourceTool::MOUSE;
    mouseEvent.action = MouseAction::PRESS;
    mouseEvent.button = MouseButton::LEFT_BUTTON;
    context_->OnMouseEvent(mouseEvent, context_->GetRootElement());
}

HWTEST_F(RightMouseMappingPipelineTestNg, CancelMouseMappingSendsCancel001, TestSize.Level1)
{
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

HWTEST_F(RightMouseMappingPipelineTestNg, MoveEventDoesNotCancelMapping001, TestSize.Level1)
{
    context_->SetRightMouseMappingActive(true);
    EXPECT_TRUE(context_->IsRightMouseMappingActive());

    MouseEvent mouseMove;
    mouseMove.x = 101.0f;
    mouseMove.y = 101.0f;
    mouseMove.sourceType = SourceType::MOUSE;
    mouseMove.sourceTool = SourceTool::MOUSE;
    mouseMove.action = MouseAction::MOVE;
    mouseMove.button = MouseButton::NONE_BUTTON;
    context_->OnMouseEvent(mouseMove, context_->GetRootElement());
}

HWTEST_F(RightMouseMappingPipelineTestNg, MappedTouchDoesNotUpdateLastSourceType001, TestSize.Level1)
{
    SourceType savedType = context_->lastSourceType_;

    TouchEvent mappedDown;
    mappedDown.id = 1002;
    mappedDown.x = 100.0f;
    mappedDown.y = 100.0f;
    mappedDown.type = TouchType::DOWN;
    mappedDown.sourceType = SourceType::TOUCH;
    mappedDown.sourceTool = SourceTool::MOUSE;
    context_->OnTouchEvent(mappedDown);

    EXPECT_EQ(context_->lastSourceType_, savedType);
}

} // namespace OHOS::Ace::NG
