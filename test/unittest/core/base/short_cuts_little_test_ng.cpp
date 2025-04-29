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
const std::string VALUE_LITTLE_A = "a";
const std::string VALUE_LITTLE_C = "c";
const std::string VALUE_LITTLE_V = "v";
const std::string VALUE_LITTLE_Z = "z";
const std::string VALUE_LITTLE_Y = "y";
const std::string VALUE_LITTLE_X = "x";
ViewAbstractModelNG viewAbstractModelNG;
std::string srcImages = "common/images/mmm.jpg";
auto callback = []() { srcImages = "test"; };
}; // namespace
class ShortCutsLittleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ShortCutsLittleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void ShortCutsLittleTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ShortCutsLittleTest001
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for a key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with a.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest002
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for a key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + a.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with alt + ctrl + a.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest003
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for a key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + a.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with ctrl + shift + a.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest004
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for a key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + a.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with shift + alt + a.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with shift + alt + ctrl + a.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_A, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest005
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for c key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with c.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest006
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for c key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + c.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest007
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for c key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + c.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest008
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for c key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + c.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_C, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest009
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for v key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with v.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest010
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for v key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + v.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest011
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for v key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + v.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest012
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for v key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + v.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_V, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest013
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest014
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest015
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest016
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for z key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + z.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Z, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest017
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest018
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest019
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest020
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for y key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + y.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_Y, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest021
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for x key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with x.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 0);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest022
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for x key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with alt + x.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest023
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for x key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + x.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}

/**
 * @tc.name: ShortCutsLittleTest024
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for x key.
 * @tc.type: FUNC
 */
HWTEST_F(ShortCutsLittleTestNg, ShortCutsLittleTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    eventManager->keyboardShortcutNode_.clear();

    /**
     * @tc.steps: step2. call SetKeyboardShortcut with shift + x.
     * @tc.expected: add success
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_LITTLE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
}
} // namespace OHOS::Ace::NG
