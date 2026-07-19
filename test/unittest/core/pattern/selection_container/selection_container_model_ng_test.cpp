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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"
#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG("SelectionContainer");
const Color TEST_CARET_COLOR = Color(0xFF0000FF);
const Color TEST_SELECTED_BG_COLOR = Color(0xFFFF0000);
const std::u16string TEST_SELECTION_TEXT = u"SelectedText";
} // namespace

class SelectionContainerModelNGTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectionContainerPattern> pattern_;
};

void SelectionContainerModelNGTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SelectionContainerModelNGTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectionContainerModelNGTest::SetUp()
{
    pattern_ = AceType::MakeRefPtr<SelectionContainerPattern>();
    frameNode_ = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern_, true);
    frameNode_->AttachToMainTree();
    auto layoutProperty = AceType::MakeRefPtr<SelectionContainerLayoutProperty>();
    frameNode_->layoutProperty_ = layoutProperty;
}

void SelectionContainerModelNGTest::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
}

/**
 * @tc.name: SetCopyOptionTest001
 * @tc.desc: Test SetCopyOption with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetCopyOptionTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(AceType::RawPtr(frameNode_), CopyOptions::Distributed);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto copyOption = layoutProperty->GetCopyOptionValue(CopyOptions::InApp);
    
    EXPECT_EQ(copyOption, CopyOptions::Distributed);
}

/**
 * @tc.name: SetCopyOptionTest002
 * @tc.desc: Test SetCopyOption with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetCopyOptionTest002, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(AceType::RawPtr(frameNode_), CopyOptions::None);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto copyOption = layoutProperty->GetCopyOptionValue(CopyOptions::InApp);
    
    EXPECT_EQ(copyOption, CopyOptions::None);
}

/**
 * @tc.name: ResetCopyOptionTest001
 * @tc.desc: Test ResetCopyOption001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, ResetCopyOptionTest001, TestSize.Level1)
{
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateCopyOption(CopyOptions::Distributed);
    
    SelectionContainerModelNG::ResetCopyOption(AceType::RawPtr(frameNode_));
    
    auto copyOption = layoutProperty->GetCopyOptionValue(CopyOptions::InApp);
    EXPECT_EQ(copyOption, CopyOptions::InApp);
}

/**
 * @tc.name: SetEnableHapticFeedbackTest001
 * @tc.desc: Test SetEnableHapticFeedback with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetEnableHapticFeedbackTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetEnableHapticFeedback(AceType::RawPtr(frameNode_), true);
    
    EXPECT_TRUE(pattern_->GetEnableHapticFeedback());
}

/**
 * @tc.name: SetEnableHapticFeedbackTest002
 * @tc.desc: Test SetEnableHapticFeedback with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetEnableHapticFeedbackTest002, TestSize.Level1)
{
    SelectionContainerModelNG::SetEnableHapticFeedback(AceType::RawPtr(frameNode_), false);
    
    EXPECT_FALSE(pattern_->GetEnableHapticFeedback());
}

/**
 * @tc.name: ResetEnableHapticFeedbackTest001
 * @tc.desc: Test ResetEnableHapticFeedback001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, ResetEnableHapticFeedbackTest001, TestSize.Level1)
{
    pattern_->SetEnableHapticFeedback(false);
    
    SelectionContainerModelNG::ResetEnableHapticFeedback(AceType::RawPtr(frameNode_));
    
    EXPECT_TRUE(pattern_->GetEnableHapticFeedback());
}

/**
 * @tc.name: SetTextJoinStyleTest001
 * @tc.desc: Test SetTextJoinStyle with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetTextJoinStyleTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetTextJoinStyle(AceType::RawPtr(frameNode_), SelectionContainerTextJoinStyle::DIRECT);
    
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_TRUE(separator.empty());
}

/**
 * @tc.name: SetTextJoinStyleTest002
 * @tc.desc: Test SetTextJoinStyle with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetTextJoinStyleTest002, TestSize.Level1)
{
    SelectionContainerModelNG::SetTextJoinStyle(AceType::RawPtr(frameNode_), SelectionContainerTextJoinStyle::NEWLINE);
    
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_EQ(separator, u"\n");
}

/**
 * @tc.name: ResetTextJoinStyleTest001
 * @tc.desc: Test ResetTextJoinStyle001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, ResetTextJoinStyleTest001, TestSize.Level1)
{
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::DIRECT);
    
    SelectionContainerModelNG::ResetTextJoinStyle(AceType::RawPtr(frameNode_));
    
    auto separator = pattern_->GetTextJoinSeparator();
    EXPECT_EQ(separator, u"\n");
}

/**
 * @tc.name: SetCaretColorTest001
 * @tc.desc: Test SetCaretColor with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetCaretColorTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCaretColor(AceType::RawPtr(frameNode_), TEST_CARET_COLOR);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto caretColor = layoutProperty->GetCaretColorValue(Color::TRANSPARENT);
    
    EXPECT_EQ(caretColor, TEST_CARET_COLOR);
}

/**
 * @tc.name: ResetCaretColorTest001
 * @tc.desc: Test ResetCaretColor001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, ResetCaretColorTest001, TestSize.Level1)
{
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateCaretColor(TEST_CARET_COLOR);
    
    SelectionContainerModelNG::ResetCaretColor(AceType::RawPtr(frameNode_));
    
    auto caretColor = layoutProperty->GetCaretColorValue(Color::TRANSPARENT);
    EXPECT_EQ(caretColor, Color::TRANSPARENT);
}

/**
 * @tc.name: SetSelectedBackgroundColorTest001
 * @tc.desc: Test SetSelectedBackgroundColor with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetSelectedBackgroundColorTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), TEST_SELECTED_BG_COLOR);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto bgColor = layoutProperty->GetSelectedBackgroundColorValue(Color::TRANSPARENT);
    
    EXPECT_EQ(bgColor, TEST_SELECTED_BG_COLOR);
}

/**
 * @tc.name: ResetSelectedBackgroundColorTest001
 * @tc.desc: Test ResetSelectedBackgroundColor001 resets state correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, ResetSelectedBackgroundColorTest001, TestSize.Level1)
{
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    layoutProperty->UpdateSelectedBackgroundColor(TEST_SELECTED_BG_COLOR);
    
    SelectionContainerModelNG::ResetSelectedBackgroundColor(AceType::RawPtr(frameNode_));
    
    auto bgColor = layoutProperty->GetSelectedBackgroundColor();
    EXPECT_FALSE(bgColor.has_value());
}

/**
 * @tc.name: SetOnWillCopyTest001
 * @tc.desc: Test SetOnWillCopy with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetOnWillCopyTest001, TestSize.Level1)
{
    bool callbackCalled = false;
    auto callback = [&callbackCalled](const std::u16string& text) {
        callbackCalled = true;
        return true;
    };
    
    SelectionContainerModelNG::SetOnWillCopy(AceType::RawPtr(frameNode_), std::move(callback));
    
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto result = eventHub->FireOnWillCopy(TEST_SELECTION_TEXT);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SetOnCopyTest001
 * @tc.desc: Test SetOnCopy with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetOnCopyTest001, TestSize.Level1)
{
    bool callbackCalled = false;
    std::u16string receivedText;
    auto callback = [&callbackCalled, &receivedText](const std::u16string& text) {
        callbackCalled = true;
        receivedText = text;
    };
    
    SelectionContainerModelNG::SetOnCopy(AceType::RawPtr(frameNode_), std::move(callback));
    
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnCopy(TEST_SELECTION_TEXT);
    
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(receivedText, TEST_SELECTION_TEXT);
}

/**
 * @tc.name: SetOnTextSelectionChangeTest001
 * @tc.desc: Test SetOnTextSelectionChange with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetOnTextSelectionChangeTest001, TestSize.Level1)
{
    bool callbackCalled = false;
    std::vector<std::u16string> receivedTexts;
    auto callback = [&callbackCalled, &receivedTexts](const std::vector<std::u16string>& texts) {
        callbackCalled = true;
        receivedTexts = texts;
    };
    
    SelectionContainerModelNG::SetOnTextSelectionChange(AceType::RawPtr(frameNode_), std::move(callback));
    
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::vector<std::u16string> testTexts = { TEST_SELECTION_TEXT };
    eventHub->FireOnTextSelectionChange(testTexts);
    
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(receivedTexts.size(), 1);
    EXPECT_EQ(receivedTexts[0], TEST_SELECTION_TEXT);
}

/**
 * @tc.name: BindSelectionMenuTest001
 * @tc.desc: Test BindSelectionMenu001 binds correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, BindSelectionMenuTest001, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    
    SelectionContainerModelNG::BindSelectionMenu(
        AceType::RawPtr(frameNode_), TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
    EXPECT_TRUE(menuParams->isValid);
}

/**
 * @tc.name: BindSelectionMenuTest002
 * @tc.desc: Test BindSelectionMenu002 binds correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, BindSelectionMenuTest002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = false;
    
    SelectionContainerModelNG::BindSelectionMenu(
        AceType::RawPtr(frameNode_), TextSpanType::IMAGE, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    
    auto menuParams = pattern_->GetMenuParams(TextSpanType::IMAGE, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
    EXPECT_FALSE(menuParams->isValid);
}

/**
 * @tc.name: SetSelectionMenuItemClickWithTextCallbackTest001
 * @tc.desc: Test SetSelectionMenuItemClickWithTextCallback with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetSelectionMenuItemClickWithTextCallbackTest001, TestSize.Level1)
{
    bool callbackCalled = false;
    auto callback = [&callbackCalled](const MenuItemParam& param, const std::u16string& text) {
        callbackCalled = true;
        return true;
    };
    
    SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(
        AceType::RawPtr(frameNode_), std::move(callback));
    
    ASSERT_NE(pattern_->onMenuItemClickWithText_, nullptr);
    MenuItemParam param;
    auto result = pattern_->onMenuItemClickWithText_(param, TEST_SELECTION_TEXT);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: SetSelectionMenuItemClickWithTextCallbackTest002
 * @tc.desc: Test SetSelectionMenuItemClickWithTextCallback with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, SetSelectionMenuItemClickWithTextCallbackTest002, TestSize.Level1)
{
    auto callback = [](const MenuItemParam& param, const std::u16string& text) {
        return false;
    };
    
    SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(
        AceType::RawPtr(frameNode_), std::move(callback));
    
    ASSERT_NE(pattern_->onMenuItemClickWithText_, nullptr);
    MenuItemParam param;
    auto result = pattern_->onMenuItemClickWithText_(param, TEST_SELECTION_TEXT);
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PropertyUpdateFlagsTest001
 * @tc.desc: Test PropertyUpdateFlags001 updates flags correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, PropertyUpdateFlagsTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(AceType::RawPtr(frameNode_), CopyOptions::Distributed);
    
    uint32_t expectedFlag = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, expectedFlag);
}

/**
 * @tc.name: PropertyUpdateFlagsTest002
 * @tc.desc: Test PropertyUpdateFlags002 updates flags correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, PropertyUpdateFlagsTest002, TestSize.Level1)
{
    SelectionContainerModelNG::SetEnableHapticFeedback(AceType::RawPtr(frameNode_), false);
    
    uint32_t expectedFlag = static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, expectedFlag);
}

/**
 * @tc.name: PropertyUpdateFlagsTest003
 * @tc.desc: Test PropertyUpdateFlags003 updates flags correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, PropertyUpdateFlagsTest003, TestSize.Level1)
{
    SelectionContainerModelNG::SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), TEST_SELECTED_BG_COLOR);
    
    uint32_t expectedFlag = static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, expectedFlag);
}

/**
 * @tc.name: MultiplePropertyUpdatesTest001
 * @tc.desc: Test MultiplePropertyUpdates001 updates flags correctly
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, MultiplePropertyUpdatesTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(AceType::RawPtr(frameNode_), CopyOptions::Distributed);
    SelectionContainerModelNG::SetEnableHapticFeedback(AceType::RawPtr(frameNode_), true);
    SelectionContainerModelNG::SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), TEST_SELECTED_BG_COLOR);
    
    uint32_t expectedFlags = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION) |
        static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK) |
        static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR);
    
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, expectedFlags);
}

/**
 * @tc.name: NullFrameNodeTest001
 * @tc.desc: Test NullFrameNode001
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, NullFrameNodeTest001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(nullptr, CopyOptions::Distributed);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto copyOption = layoutProperty->GetCopyOptionValue(CopyOptions::InApp);
    
    EXPECT_EQ(copyOption, CopyOptions::InApp);
}

/**
 * @tc.name: NullFrameNodeTest002
 * @tc.desc: Test NullFrameNode002
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, NullFrameNodeTest002, TestSize.Level1)
{
    SelectionContainerModelNG::SetCaretColor(nullptr, TEST_CARET_COLOR);
    
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    auto caretColor = layoutProperty->GetCaretColorValue(Color::TRANSPARENT);
    
    EXPECT_EQ(caretColor, Color::TRANSPARENT);
}

/**
 * @tc.name: NullFrameNodeTest003
 * @tc.desc: Test NullFrameNode003
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerModelNGTest, NullFrameNodeTest003, TestSize.Level1)
{
    auto originalValue = pattern_->GetEnableHapticFeedback();
    
    SelectionContainerModelNG::SetEnableHapticFeedback(nullptr, false);
    
    EXPECT_EQ(pattern_->GetEnableHapticFeedback(), originalValue);
}

} // namespace OHOS::Ace::NG