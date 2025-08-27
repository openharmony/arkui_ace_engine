/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/position_param.h"
#include "frameworks/core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "frameworks/core/pipeline/base/element.h"

#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VALUE_A = "A";
const std::string VALUE_C = "C";
const std::string VALUE_V = "V";
const std::string VALUE_Z = "Z";
const std::string VALUE_Y = "Y";
const std::string VALUE_X = "X";
const std::string VALUE_TAB = "TAB";
const std::string VALUE_DPAD_UP = "DPAD_UP";
const std::string VALUE_DPAD_DOWN = "DPAD_DOWN";
const std::string VALUE_DPAD_LEFT = "DPAD_LEFT";
const std::string VALUE_DPAD_RIGHT = "DPAD_RIGHT";
ViewAbstractModelNG viewAbstractModelNG;
std::string srcImages = "common/images/mmm.jpg";
auto callback = []() { srcImages = "test"; };
}; // namespace
class ShortCutsTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ShortCutsTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void ShortCutsTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ShortCutsTest001
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + tab.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + tab.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + tab.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest002
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with tab.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest003
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + tab.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + ctrl + tab.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest004
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + tab.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + tab.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest005
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Up key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with up arrow.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest006
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Up key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + up.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + up.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest007
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Up key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + up.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + up.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest008
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Up key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + up.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + up.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + up.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest009
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Down key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with down arrow.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest010
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Down key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + down.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + down.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest011
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Down key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + down.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + down.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest012
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Down key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + down.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + down.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + down.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_DOWN, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest013
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Left key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with left arrow.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest014
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Left key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + left.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + left.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest015
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Left key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + left.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + left.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest016
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Left key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + left.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + left.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + left.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_LEFT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest017
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Right key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with right arrow.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest018
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Right key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + right.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + right.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest019
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Right key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + right.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + right.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest020
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for arrow/Right key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + right.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + right.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + right.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_RIGHT, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest021
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for A key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with A.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest022
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for A key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + A.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + A.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest023
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for A key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + A.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + A.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest024
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for A key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + A.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + A.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + A.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest025
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for C key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with C.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest026
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for C key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + C.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + C.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest027
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for C key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + C.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + C.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest028
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for C key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + C.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + atl + C.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + atl + ctrl + C.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest029
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for V key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with V.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest030
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for V key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + V.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + V.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest031
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for V key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + V.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + V.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest032
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for V key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + V.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + atl + V.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + atl + ctrl + V.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest033
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with Z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest034
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + Z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + Z.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest035
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + Z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + Z.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest036
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + Z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + Z.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + Z.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest037
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with Y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest038
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + Y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + Y.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest039
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + Y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + Y.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest040
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for Y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + Y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + Y.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + Y.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsTest041
 * @tc.desc: Test the KeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsTestNg, ShortCutsTest041, TestSize.Level1)
{
    KeyEvent event;
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto keyEventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    event.code = KeyCode::KEY_TAB;
    event.action = KeyAction::DOWN;
    event.isPreIme = false;
    event.pressedCodes = {KeyCode::KEY_TAB};
    auto ret = keyEventManager->TriggerKeyEventDispatch(event);
    EXPECT_TRUE(ret);
    ret = keyEventManager->TriggerKeyEventDispatch(event);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG