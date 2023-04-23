/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <functional>
#include <optional>
#include <securec.h>

#include "gtest/gtest.h"

#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_ng/test/mock/pattern/picker/mock_picker_theme_manager.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HALF_INDEX_NUM = 5;
constexpr int32_t INDEX_NUM = 10;
constexpr int32_t CURRENT_INDEX = 8;
constexpr int32_t CURRENT_END_INDEX = 3;
constexpr size_t THREE_CHILDREN = 3;
constexpr size_t FIVE_CHILDREN = 5;
constexpr size_t THREE = 3;
constexpr size_t SECOND = 2;
constexpr size_t ZERO = 0;
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr uint32_t SELECTED_INDEX_2 = 2;
constexpr double HALF = 0.5;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_20 = 20.0;
constexpr double FONT_SIZE_INVALID = -1.0;
const std::string EMPTY_TEXT;
const std::string TEXT_PICKER_CONTENT = "text";
} // namespace

class TextPickerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void InitTextPickerTestNg();
    void DestroyTextPickerTestNgObject();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPickerPattern> textPickerPattern_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityProperty_;
    RefPtr<TextPickerRowAccessibilityProperty> textPickerRowAccessibilityProperty_;
    RefPtr<FrameNode> stackNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPattern_;
    RefPtr<FrameNode> stackNodeNext_;
    RefPtr<FrameNode> columnNodeNext_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPatternNext_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityPropertyNext_;
};

void TextPickerTestNg::DestroyTextPickerTestNgObject()
{
    frameNode_ = nullptr;
    textPickerPattern_ = nullptr;
    textPickerAccessibilityProperty_ = nullptr;
    textPickerRowAccessibilityProperty_ = nullptr;
    stackNode_ = nullptr;
    columnNode_ = nullptr;
    textPickerColumnPattern_ = nullptr;
    stackNodeNext_ = nullptr;
    columnNodeNext_ = nullptr;
    textPickerColumnPatternNext_ = nullptr;
    textPickerAccessibilityPropertyNext_ = nullptr;
}

void TextPickerTestNg::InitTextPickerTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    textPickerRowAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextPickerRowAccessibilityProperty>();
    ASSERT_NE(textPickerRowAccessibilityProperty_, nullptr);
    textPickerPattern_ = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern_, nullptr);
    stackNode_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode_, nullptr);
    columnNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode_, nullptr);
    textPickerAccessibilityProperty_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityProperty_, nullptr);
    textPickerColumnPattern_ = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->MountToParent(stackNode_);
    stackNode_->MountToParent(frameNode_);

    stackNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNodeNext_, nullptr);
    columnNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNodeNext_, nullptr);
    textPickerAccessibilityPropertyNext_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityPropertyNext_, nullptr);
    textPickerColumnPatternNext_ = columnNodeNext_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPatternNext_, nullptr);
    columnNodeNext_->MountToParent(stackNodeNext_);
    stackNodeNext_->MountToParent(frameNode_);
}

void TextPickerTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockPickerThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions001
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(kind:TEXT).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("1", content);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollUp001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_2);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = 0 - jump * HALF;
    double offset2 = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("1", content);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    double fontSize = textLayoutProperty->GetFontSize().value().Value();
    double expectFontSize = FONT_SIZE_5 * HALF + FONT_SIZE_5 * HALF * HALF;
    EXPECT_EQ(expectFontSize, fontSize);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollDown001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move down).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollDown001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_2);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = jump * HALF;
    double offset2 = jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("5", content);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    double fontSize = textLayoutProperty->GetFontSize().value().Value();
    double expectFontSize = FONT_SIZE_5 * HALF + FONT_SIZE_5 * HALF * HALF;
    EXPECT_EQ(expectFontSize, fontSize);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions002
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(kind:ICON).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions002, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_TRUE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp002
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:ICON, move up).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollUp002, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = 0 - jump * HALF;
    double offset2 = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto linearNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(linearNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollDown002
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:ICON, move down).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollDown002, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = jump * HALF;
    double offset2 = jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto linearNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(linearNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearNode->GetFirstChild());
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions003
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(kind:MIXTURE).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions003, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_TRUE(imageLayoutProperty->HasImageSourceInfo());

    auto textNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("test1", content);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions004
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions004, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(0);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions005
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is TEXT, option's size is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions005, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(textLayoutProperty->HasContent());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions006
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is ICON, option's size is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions006, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions007
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is MIXTURE, option's size is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions007, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions008
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is TEXT, showCount > optionCount).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions008, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("", content);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions009
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is ICON, showCount > optionCount).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions009, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions010
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is MIXTURE, showCount > optionCount).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions010, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions011
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is TEXT, showCount != column item count).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions011, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(TEXT);
    columnPattern->SetOptions(range);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    columnPattern->FlushCurrentOptions(false, false);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(textLayoutProperty->HasContent());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions012
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is ICON, showCount != column item count).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions012, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(ICON);
    columnPattern->SetOptions(range);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions013
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is MIXTURE, showCount != column item count).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions013, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(MIXTURE);
    columnPattern->SetOptions(range);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions014
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions
 *          (column kind is MIXTURE, linearNode's children size is not 2).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions014, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(MIXTURE);
    columnPattern->SetOptions(range);
    columnPattern->FlushCurrentOptions(false, false);
    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions015
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is TEXT, set text properties).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions015, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" }, { "/demo/demo4.jpg", "test2" }, { "/demo/demo5.jpg", "test2" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.textColor = Color::RED;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    disappearTextStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.textColor = Color::RED;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    selectedTextStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasFontWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, textLayoutProperty->GetFontWeight().value());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp003
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:MIXTURE, move up).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollUp003, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = 0 - jump * HALF;
    double offset2 = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("test1", content);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    double fontSize = textLayoutProperty->GetFontSize().value().Value();
    double expectFontSize = FONT_SIZE_5 * HALF + FONT_SIZE_5 * HALF * HALF;
    EXPECT_EQ(expectFontSize, fontSize);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp004
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up(jump then up)).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollUp004, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_2);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = 0 - jump * HALF;
    double offset2 = 0 - jump;
    double offset3 = 0 - jump / HALF;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);
    columnPattern->UpdateColumnChildPosition(offset3);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    double fontSize = textLayoutProperty->GetFontSize().value().Value();
    EXPECT_EQ(FONT_SIZE_5, fontSize);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollDown003
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:MIXTURE, move down).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScrollDown003, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    disappearTextStyle.textColor = Color::BLACK;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    textStyle.textColor = Color::BLUE;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    selectedTextStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset1 = jump * HALF;
    double offset2 = jump;
    columnPattern->UpdateColumnChildPosition(offset1);
    columnPattern->UpdateColumnChildPosition(offset2);

    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    std::string content = textLayoutProperty->GetContent().value_or("");
    EXPECT_EQ("test3", content);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    double fontSize = textLayoutProperty->GetFontSize().value().Value();
    double expectFontSize = FONT_SIZE_5 * HALF + FONT_SIZE_5 * HALF * HALF;
    EXPECT_EQ(expectFontSize, fontSize);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, OptionCount is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScroll001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, false);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(textLayoutProperty->HasContent());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll002
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, showCount != column item count).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScroll002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    columnPattern->SetOptions(range);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(textLayoutProperty->HasContent());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll003
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:MIXTURE, linearNode's children size is not 2)).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScroll003, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    columnPattern->SetOptions(range);
    columnPattern->SetColumnKind(MIXTURE);
    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset);

    auto linearLayoutNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(linearLayoutNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
    ASSERT_NE(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_FALSE(imageLayoutProperty->HasImageSourceInfo());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll004
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up, animationProperties_'s size is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScroll004, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    columnPattern->SetOptions(range);
    columnPattern->SetColumnKind(TEXT);
    columnPattern->FlushCurrentOptions(false, true);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset = 0 - jump * HALF;
    columnPattern->UpdateColumnChildPosition(offset);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    EXPECT_FALSE(textLayoutProperty->HasTextColor());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll005
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up, options'size is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternInnerHandleScroll005, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    columnPattern->SetOptions(range);
    columnPattern->SetColumnKind(TEXT);
    columnPattern->SetCurrentIndex(SELECTED_INDEX_2);
    columnPattern->FlushCurrentOptions(false, false);
    range.clear();
    columnPattern->SetOptions(range);

    double jump = theme->GetJumpInterval().ConvertToPx();
    double offset = 0 - jump;
    columnPattern->UpdateColumnChildPosition(offset);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    EXPECT_EQ("5", textLayoutProperty->GetContent().value());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions016
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(Clear Option).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerColumnPatternFlushCurrentOptions016, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    /**
     * @tc.step: step2. create textpicker cloumn pattern and call FlushCurrentOptions.
     * @tc.expected: clear options successfully.
     */
    auto count = columnPattern->GetOptionCount();
    EXPECT_EQ(THREE, count);
    columnPattern->ClearOptions();
    columnPattern->FlushCurrentOptions(false, false, true);
    auto textNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_TRUE(textLayoutProperty->HasContent());
    std::string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ("", content);
    count = columnPattern->GetOptionCount();
    EXPECT_EQ(ZERO, count);
}

/**
 * @tc.name: TextPickerPatternToJsonValue001
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is not empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternToJsonValue001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    PickerTextStyle disappearTextStyle;
    disappearTextStyle.fontSize = Dimension(FONT_SIZE_5);
    disappearTextStyle.textColor = Color::BLACK;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, disappearTextStyle);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    textStyle.textColor = Color::BLUE;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    PickerTextStyle selectedTextStyle;
    selectedTextStyle.fontSize = Dimension(FONT_SIZE_20);
    selectedTextStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, selectedTextStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    textPickerPattern->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerPatternToJsonValue002
 * @tc.desc: Test TextPickerPattern ToJsonValue(range is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternToJsonValue002, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    textPickerPattern->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerPatternProcessDepth001
 * @tc.desc: Test TextPickerPattern ProcessCascadeOptionDepth(child is empty).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternProcessDepth001, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    NG::TextCascadePickerOptions option;
    option.rangeResult = {"1", "2", "3"};
    /**
     * @tc.step: step2. create cascade option and call it.
     * @tc.expected: caculate the option depth, the depth is correct.
     */
    auto depth = textPickerPattern->ProcessCascadeOptionDepth(option);
    EXPECT_EQ(1, depth);
}

/**
 * @tc.name: TextPickerPatternProcessDepth002
 * @tc.desc: Test TextPickerPattern ProcessCascadeOptionDepth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternProcessDepth002, TestSize.Level1)
{
    auto pipeline = MockPipelineBase::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    EXPECT_CALL(*pipeline, GetIsDeclarative()).WillRepeatedly(Return(false));
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    /**
     * @tc.step: step2. create cascade option and call it.
     * @tc.expected: caculate the option depth, the depth is correct.
     */
    NG::TextCascadePickerOptions option;
    option.rangeResult = {"1", "2", "3"};
    NG::TextCascadePickerOptions childoption;
    childoption.rangeResult = {"11", "12", "13"};
    option.children.emplace_back(childoption);
    auto depth = textPickerPattern->ProcessCascadeOptionDepth(option);
    EXPECT_EQ(SECOND, depth);
}

/**
 * @tc.name: TextPickerDialogViewShow001
 * @tc.desc: Test TextPickerDialogView Show(column kind is MIXTURE).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow001, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto func = [](const std::string& info) { (void)info; };
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    dialogEvent["changeId"] = func;
    dialogEvent["acceptId"] = func;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    memcpy_s(&settingData.properties, sizeof(PickerTextProperties), &properties, sizeof(PickerTextProperties));
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow002
 * @tc.desc: Test TextPickerDialogView Show(do not set callback).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow002, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    memcpy_s(&settingData.properties, sizeof(PickerTextProperties), &properties, sizeof(PickerTextProperties));
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow003
 * @tc.desc: Test TextPickerDialogView Show(do not set properties).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow003, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow004
 * @tc.desc: Test TextPickerDialogView Show(column kind is TEXT).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow004, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow005
 * @tc.desc: Test TextPickerDialogView Show(column kind is ICON).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow005, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = ICON;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow006
 * @tc.desc: Test TextPickerDialogView Show(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow006, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = 0;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow007
 * @tc.desc: Test TextPickerDialogView Show(Invailid font size).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow007, TestSize.Level1)
{
    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.normalTextStyle_.textColor = Color::RED;
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_INVALID);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    settingData.columnKind = MIXTURE;
    settingData.height = Dimension(FONT_SIZE_10);
    memcpy_s(&settingData.properties, sizeof(PickerTextProperties), &properties, sizeof(PickerTextProperties));
    settingData.rangeVector = { { "", "1" }, { "", "2" }, { "", "3" } };
    settingData.selected = 0;

    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow008
 * @tc.desc: Test TextPickerDialogView Show(Multi Column).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow008, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = {0, 0, 0};
    settingData.isCascade = false;
    /**
     * @tc.step: step1. create multi TextCascadePickerOptions of settingData
     */
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = {"11", "12", "13"};
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = {"21", "22", "23"};
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = {"31", "32", "33"};
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow009
 * @tc.desc: Test TextPickerDialogView Show(Cascade Column).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow009, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = {0, 0};
    settingData.isCascade = true;
    /**
     * @tc.step: step1. create cascade TextCascadePickerOptions of settingData
     */
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = {"11", "12"};
    options1.rangeResult = {"1"};
    options1.children.emplace_back(options1Child);
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    options2Child.rangeResult = {"21", "22"};
    options2.rangeResult = {"2"};
    options2.children.emplace_back(options2Child);
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = {"31", "32"};
    options3.rangeResult = {"3"};
    options3.children.emplace_back(options3Child);
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerDialogViewShow010
 * @tc.desc: Test TextPickerDialogView Show(Cascade Column Supply Zero Child).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewShow010, TestSize.Level1)
{
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    TextPickerSettingData settingData;
    memset_s(&settingData, sizeof(TextPickerSettingData), 0x00, sizeof(TextPickerSettingData));
    settingData.columnKind = TEXT;
    settingData.height = Dimension(FONT_SIZE_10);
    settingData.selectedValues = {0, 0, 0};
    settingData.isCascade = true;
    /**
     * @tc.step: step1. create cascade TextCascadePickerOptions of settingData(Zero Child)
     */
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = {"11", "12"};
    options1.rangeResult = {"1"};
    options1.children.emplace_back(options1Child);
    settingData.options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = {"221", "222"};
    options2Child.rangeResult = {"21"};
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = {"2"};
    options2.children.emplace_back(options2Child);
    settingData.options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = {"31", "32"};
    options3.rangeResult = {"3"};
    options3.children.emplace_back(options3Child);
    settingData.options.emplace_back(options3);
    DialogProperties dialogProperties;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    /**
     * @tc.step: step2. call Show of TextPickerDialogView
     * @tc.expected: the function of show can generate framenode.
     */
    auto frameNode = TextPickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TextPickerPatternOnAttachToFrameNode001
 * @tc.desc: Test TextPickerPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreateTextPicker001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, ICON);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = AceType::MakeRefPtr<TextPickerPattern>();
    textPickerPattern->AttachToFrameNode(frameNode);
    textPickerPattern->OnAttachToFrameNode();
    auto host = textPickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetDisappearFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetDisappearTextStyle004
 * @tc.desc: Test TextPickerModelNG SetDisappearTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDisappearTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasDisappearWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle001
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle002
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle003
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetNormalTextStyle004
 * @tc.desc: Test TextPickerModelNG SetNormalTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetNormalTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set Color).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontSize).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(FONT_SIZE_10);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_EQ(Dimension(FONT_SIZE_10), pickerProperty->GetSelectedFontSize().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontSize 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(0);
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: TextPickerModelNGSetSelectedTextStyle004
 * @tc.desc: Test TextPickerModelNG SetSelectedTextStyle(set FontWeight).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelectedTextStyle004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    PickerTextStyle textStyle;
    textStyle.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedWeight());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: TextPickerModelNGSetSelected001
 * @tc.desc: Test TextPickerModelNG SetSelected.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelected001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelected());
    EXPECT_EQ(1, pickerProperty->GetSelected().value());
}

/**
 * @tc.name: TextPickerModelNGSetRange001
 * @tc.desc: Test TextPickerModelNG SetRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetRange001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetRange().size());
}

/**
 * @tc.name: TextPickerModelNGSetRange002
 * @tc.desc: Test TextPickerModelNG SetRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetRange002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range;
    TextPickerModelNG::GetInstance()->SetRange(range);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_TRUE(pickerPattern->GetRange().empty());
}

/**
 * @tc.name: TextPickerModelNGCreate001
 * @tc.desc: Test TextPickerModelNG Create(DeviceType::PHONE, DeviceOrientation::LANDSCAPE).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreate001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnChildren = columnNode->GetChildren();
    EXPECT_EQ(THREE_CHILDREN, columnChildren.size());
}

/**
 * @tc.name: TextPickerModelNGCreate002
 * @tc.desc: Test TextPickerModelNG Create(DeviceType::PHONE, DeviceOrientation::0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGCreate002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnChildren = columnNode->GetChildren();
    EXPECT_EQ(FIVE_CHILDREN, columnChildren.size());
}

/**
 * @tc.name: TextPickerModelNGSetDefaultAttributes001
 * @tc.desc: Test TextPickerModelNG SetDefaultAttributes.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetDefaultAttributes001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
}

/**
 * @tc.name: TextPickerModelNGMultiInit001
 * @tc.desc: Test TextPickerModelNG MultiInit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGMultiInit001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = AceType::MakeRefPtr<TextPickerPattern>();
    textPickerPattern->AttachToFrameNode(frameNode);
    textPickerPattern->OnAttachToFrameNode();
    auto host = textPickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: TextPickerModelNGSetIsCascade001
 * @tc.desc: Test TextPickerModelNG SetIsCascade.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetIsCascade001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.step: step2. Get textpicker pattern and Call the interface.
     * @tc.expected: the result of isCascade is correct.
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_TRUE(pickerPattern->GetIsCascade());
}

/**
 * @tc.name: TextPickerModelNGSetSelecteds001
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<uint32_t> selecteds = {0, 1, 2};
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(0, pickerProperty->GetSelecteds().value().at(0));
    EXPECT_EQ(1, pickerProperty->GetSelecteds().value().at(1));
    EXPECT_EQ(2, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetValues001
 * @tc.desc: Test TextPickerModelNG SetValues.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetValues001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<std::string> values = {"0", "1", "2"};
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetValues is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasValues());
    EXPECT_EQ("0", pickerProperty->GetValues().value().at(0));
    EXPECT_EQ("1", pickerProperty->GetValues().value().at(1));
    EXPECT_EQ("2", pickerProperty->GetValues().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetColumns001
 * @tc.desc: Test TextPickerModelNG SetColumns(Multi).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = {"11", "12", "13"};
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = {"21", "22", "23"};
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = {"31", "32", "33"};
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Multi Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetColumns002
 * @tc.desc: Test TextPickerModelNG SetColumns(Cascade).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = {"11", "12"};
    options1.rangeResult = {"1"};
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    options2Child.rangeResult = {"21", "22"};
    options2.rangeResult = {"2"};
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = {"31", "32"};
    options3.rangeResult = {"3"};
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetColumns003
 * @tc.desc: Test TextPickerModelNG SetColumns(Cascade Supply Zero Child).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = {"11", "12"};
    options1.rangeResult = {"1"};
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = {"221", "222"};
    options2Child.rangeResult = {"21"};
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = {"2"};
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = {"31", "32"};
    options3.rangeResult = {"3"};
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue001
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerLayoutPropertyToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    /**
     * @tc.step: step2. Get json result and compare the result.
     * @tc.expected: the result of ToJsonValue is correct.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pickerProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TextPickerLayoutPropertyClone001
 * @tc.desc: Test TextPickerLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerLayoutPropertyClone001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutProperty = pickerProperty->Clone();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: TextPickerLayoutPropertyReset001
 * @tc.desc: Test TextPickerLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerLayoutPropertyReset001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
     * @tc.step: step1. Set Selecteds Values and Set Values.
     */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->Reset();
    EXPECT_FALSE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetText001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerRowAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of textPickerRowAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerRowAccessibilityPropertyGetText001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Init TextPickerTestNg.
     */
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    /**
     * @tc.step: step2. Set Options of Multi Columns.
     */
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPatternNext_->SetOptions(contents);
    /**
     * @tc.step: step3. Get Text result and compare the result.
     * @tc.expected: the result of GetText is correct.
     */
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT + TEXT_PICKER_CONTENT);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerRowAccessibilityPropertyGetText002
 * @tc.desc: Test GetText of textPickerRowAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerRowAccessibilityPropertyGetText002, TestSize.Level1)
{
    /**
     * @tc.step: step1. Init TextPickerTestNg.
     */
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), EMPTY_TEXT);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    /**
     * @tc.step: step2. Set Options of Single Column.
     */
    textPickerColumnPattern_->SetOptions(contents);
    /**
     * @tc.step: step3. Get Text result and compare the result.
     * @tc.expected: the result of GetText is correct.
     */
    EXPECT_EQ(textPickerRowAccessibilityProperty_->GetText(), TEXT_PICKER_CONTENT);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCurrentIndex(), 0);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(0);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), 0);

    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetBeginIndex(), CURRENT_INDEX);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    contents.emplace_back(content);
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(1);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetEndIndex(), CURRENT_END_INDEX);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    InitTextPickerTestNg();
    AccessibilityValue result;
    EXPECT_TRUE(textPickerAccessibilityProperty_->HasRange());
    result = textPickerAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, 0);

    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(INDEX_NUM);
    result = textPickerAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, INDEX_NUM);
    EXPECT_EQ(result.current, INDEX_NUM);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCollectionItemCounts(), 0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_EQ(textPickerAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitTextPickerTestNg();
    EXPECT_FALSE(textPickerAccessibilityProperty_->IsScrollable());
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index < INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    EXPECT_TRUE(textPickerAccessibilityProperty_->IsScrollable());
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerAccessibilityPropertySetSpecificSupportAction001
 * @tc.desc: Test SetSpecificSupportAction of textPickerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAccessibilityPropertySetSpecificSupportAction001, TestSize.Level1)
{
    InitTextPickerTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->showOptionCount_ = INDEX_NUM;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    NG::RangeContent content;
    content.icon_ = EMPTY_TEXT;
    content.text_ = TEXT_PICKER_CONTENT;
    std::vector<NG::RangeContent> contents;
    for (int index = 0; index <= HALF_INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerColumnPattern_->SetCurrentIndex(1);
    textPickerAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = textPickerAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    for (int index = 0; index <= INDEX_NUM; index++) {
        contents.emplace_back(content);
    }
    textPickerColumnPattern_->SetOptions(contents);
    textPickerAccessibilityProperty_->ResetSupportAction();
    supportAceActions = textPickerAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: TextPickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    LayoutWrapper layoutWrapper =
        LayoutWrapper(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapper> subTwoLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest002
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);

    LayoutWrapper layoutWrapper =
        LayoutWrapper(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest003
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapper layoutWrapper =
        LayoutWrapper(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapper> subTwoLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest004
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);

    LayoutWrapper layoutWrapper =
        LayoutWrapper(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
}

/**
 * @tc.name: TextPickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPaintTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPaintMethod = AceType::MakeRefPtr<TextPickerPaintMethod>();
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawLine(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TextPickerPaintTest002
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPaintTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPaintMethod = AceType::MakeRefPtr<TextPickerPaintMethod>();
    textPickerPaintMethod->SetEnabled(false);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawLine(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: TextPickerPatternTest001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    
    /**
     * @tc.cases: case1. up KeyEvent.
     */
    KeyEvent keyEventUp(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    focusHub->onKeyEventInternal_(keyEventUp);
    auto propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case1. down KeyEvent.
     */
    KeyEvent keyEventDown(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    focusHub->onKeyEventInternal_(keyEventDown);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
}

/**
 * @tc.name: TextPickerPatternTest002
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerPatternTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetEventHub<NG::TextPickerEventHub>()->GetOrCreateFocusHub();
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    
    /**
     * @tc.cases: case1. left KeyEvent.
     */
    KeyEvent keyEventLeft(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    focusHub->onKeyEventInternal_(keyEventLeft);
    auto propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case1. right KeyEvent.
     */
    KeyEvent keyEventRight(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    focusHub->onKeyEventInternal_(keyEventRight);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
}
} // namespace OHOS::Ace::NG
