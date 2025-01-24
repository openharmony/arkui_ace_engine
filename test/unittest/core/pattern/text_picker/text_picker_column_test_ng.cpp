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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t COLUMN_INDEX_0 = 0;
constexpr int32_t COLUMN_INDEX_2 = 2;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr size_t THREE = 3;
constexpr size_t ZERO = 0;
constexpr uint32_t SELECTED_INDEX_1 = 1;
constexpr uint32_t SELECTED_INDEX_2 = 2;
constexpr double HALF = 0.5;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_20 = 20.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
constexpr double TOSS_DELTA = 20.0;
constexpr double DISTANCE = 20.0;
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
const std::vector<std::string> DEFAULT_VALUE = { "1", "2", "3" };
const std::vector<std::string> CUSTOM_VALUE = { "appCustomFont" };
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class TextPickerColumnTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerColumnTestNg();
    void DestroyTextPickerColumnTestNgObject();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPickerPattern> textPickerPattern_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityProperty_;
    RefPtr<TextPickerRowAccessibilityProperty> textPickerRowAccessibilityProperty_;
    RefPtr<FrameNode> stackNode_;
    RefPtr<FrameNode> blendNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPattern_;
    RefPtr<FrameNode> stackNodeNext_;
    RefPtr<FrameNode> blendNodeNext_;
    RefPtr<FrameNode> columnNodeNext_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPatternNext_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityPropertyNext_;
};

void TextPickerColumnTestNg::DestroyTextPickerColumnTestNgObject()
{
    frameNode_ = nullptr;
    textPickerPattern_ = nullptr;
    textPickerAccessibilityProperty_ = nullptr;
    textPickerRowAccessibilityProperty_ = nullptr;
    stackNode_ = nullptr;
    blendNode_ = nullptr;
    columnNode_ = nullptr;
    textPickerColumnPattern_ = nullptr;
    stackNodeNext_ = nullptr;
    blendNodeNext_ = nullptr;
    columnNodeNext_ = nullptr;
    textPickerColumnPatternNext_ = nullptr;
    textPickerAccessibilityPropertyNext_ = nullptr;
}

void TextPickerColumnTestNg::InitTextPickerColumnTestNg()
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
    blendNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode_, nullptr);
    columnNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode_, nullptr);
    textPickerAccessibilityProperty_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityProperty_, nullptr);
    textPickerColumnPattern_ = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->MountToParent(blendNode_);
    blendNode_->MountToParent(stackNode_);
    stackNode_->MountToParent(frameNode_);

    stackNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNodeNext_, nullptr);
    blendNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNodeNext_, nullptr);
    columnNodeNext_ =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNodeNext_, nullptr);
    textPickerAccessibilityPropertyNext_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityPropertyNext_, nullptr);
    textPickerColumnPatternNext_ = columnNodeNext_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPatternNext_, nullptr);
    columnNodeNext_->MountToParent(blendNodeNext_);
    blendNodeNext_->MountToParent(stackNodeNext_);
    stackNodeNext_->MountToParent(frameNode_);
}

void TextPickerColumnTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerColumnTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerColumnTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerColumnTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"2", content);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollUp001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"2", content);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollDown001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move down).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollDown001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"4", content);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions002
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(kind:ICON).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollUp002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollDown002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "" }, { "/demo/demo2.jpg", "" },
        { "/demo/demo3.jpg", "" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"test2", content);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions004
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is invalid).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions004, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions005, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions006, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions007, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions008, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"", content);
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions009
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is ICON, showCount > optionCount).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions009, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions010, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions011, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 4;

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions012, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 4;

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetColumnKind(ICON);
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
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions013
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(column kind is MIXTURE, showCount != column item count).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions013, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 4;

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, MIXTURE);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions014, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    std::vector<NG::RangeContent> range = { { "/demo/demo1.jpg", "test1" }, { "/demo/demo2.jpg", "test2" },
        { "/demo/demo3.jpg", "test3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions015, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
}

void InnerHandleScrollUp003Init()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp003
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:MIXTURE, move up).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollUp003, TestSize.Level1)
{
    InnerHandleScrollUp003Init();
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"test3", content);
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollUp004
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, move up(jump then up)).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollUp004, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScrollDown003
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:MIXTURE, move down).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScrollDown003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value_or(u"");
    EXPECT_EQ(u"test1", content);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
}

/**
 * @tc.name: TextPickerColumnPatternInnerHandleScroll001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll(kind:TEXT, OptionCount is 0).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScroll001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScroll002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 4;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScroll003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, ICON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScroll004, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInnerHandleScroll005, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    EXPECT_EQ(u"1", textLayoutProperty->GetContent().value());
}

/**
 * @tc.name: TextPickerColumnPatternFlushCurrentOptions016
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions(Clear Option).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternFlushCurrentOptions016, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(SELECTED_INDEX_1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
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
    std::u16string content = textLayoutProperty->GetContent().value();
    EXPECT_EQ(u"", content);
    count = columnPattern->GetOptionCount();
    EXPECT_EQ(ZERO, count);
}

/**
 * @tc.name: TextPickerColumnPatternTest001
 * @tc.desc: test TextPickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    auto textPickerLayoutAlgorithm = AceType::MakeRefPtr<TextPickerLayoutAlgorithm>();
    textPickerLayoutAlgorithm->halfDisplayCounts_ = 2;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textPickerLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    /**
     * @tc.step: step2. call columnpattern's OnDirtyLayoutWrapperSwap method.
     */
    auto ret = pickerColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pickerColumnPattern->GetHalfDisplayCounts(), 2);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TextPickerColumnPatternTest002
 * @tc.desc: test TextPickerColumnPattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    /**
     * @tc.cases: case1. up KeyEvent.
     */
    KeyEvent keyEventOne(KeyCode::KEY_A, KeyAction::UP);
    auto ret = pickerColumnPattern->OnKeyEvent(keyEventOne);
    EXPECT_FALSE(ret);
    /**
     * @tc.cases: case2. cover branch KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN.
     */
    KeyEvent keyEventFour(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventFour);
    EXPECT_TRUE(ret);

    std::vector<RangeContent> options { { "icon", "text" } };
    pickerColumnPattern->SetOptions(options);
    pickerColumnPattern->columnkind_ = 0x00;
    /**
     * @tc.cases: case3. cover branch KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN.
     */
    KeyEvent keyEventFIve(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventFIve);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case4. cover branch KeyCode::KEY_DPAD_UP, KeyAction::DOWN.
     */
    KeyEvent keyEventTwo(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventTwo);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case5. cover branch KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN.
     */
    KeyEvent keyEventThr(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventThr);
    EXPECT_TRUE(ret);
    /**
     * @tc.cases: case6. cover branch KeyCode::KEY_1, KeyAction::DOWN.
     */
    KeyEvent keyEventSix(KeyCode::KEY_1, KeyAction::DOWN);
    ret = pickerColumnPattern->OnKeyEvent(keyEventSix);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TextPickerColumnPatternTest003
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(true);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    /**
     * cover actionUpdate_ callback
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    /**
     * cover actionEnd_ callback
     */
    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->yOffset_, 0.0);
    EXPECT_EQ(columnPattern->yLast_, 0.0);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->pressed_ = true;
    columnPattern->yOffset_ = OFFSET_Y;
    columnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_EQ(columnPattern->yOffset_, 0.0);
    EXPECT_EQ(columnPattern->yLast_, 0.0);
    EXPECT_FALSE(columnPattern->pressed_);
}

/**
 * @tc.name: TextPickerColumnPatternTest005
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(true);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    /**
     * cover actionStart_ callback
     */
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    EXPECT_EQ(columnPattern->GetToss()->yStart_, OFFSET_Y);
    EXPECT_TRUE(columnPattern->pressed_);
    /**
     * cover actionUpdate_ callback
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->pressed_ = true;
    columnPattern->yOffset_ = OFFSET_Y;
    columnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    /**
     * cover actionCancel_ callback
     */
    columnPattern->animationCreated_ = false;
    panEvent->actionCancel_();
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);
}

/**
 * @tc.name: TextPickerColumnPatternTest004
 * @tc.desc: Test GetSelectedObject
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);
    /**
     * @tc.step: step2. call method GetSelectedObject.
     */
    columnPattern->GetSelectedObject(false, 0);
    columnPattern->GetSelectedObject(true, 1);
}

/**
 * @tc.name: TextPickerColumnPatternTest007
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistance when dir == UP.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest007, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::UP;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    EXPECT_EQ(textPickerColumnPattern->GetShiftDistance(COLUMN_INDEX_0, dir), -2.0f);
}

/**
 * @tc.name: TextPickerColumnPatternTest008
 * @tc.desc: Test TextPickerColumnPattern CalcAlgorithmOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest008, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 5;
    textPickerColumnPattern->algorithmOffset_.clear();
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 10.0f;
    prop.nextDistance = 10.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->CalcAlgorithmOffset(ScrollDirection::UP, DISTANCE);
    EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.size() - BUFFER_NODE_NUMBER, 5);
}

/**
 * @tc.name: TextPickerColumnPatternTest009
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape when dir == DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest009, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::DOWN;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->GetShiftDistanceForLandscape(COLUMN_INDEX_2, dir);
    double distance = textPickerColumnPattern->optionProperties_[COLUMN_INDEX_2].height;
    EXPECT_EQ(textPickerColumnPattern_->GetShiftDistanceForLandscape(COLUMN_INDEX_2, dir), distance);
}

/**
 * @tc.name: TextPickerColumnPatternTest010
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape when dir == UP.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest010, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::UP;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->GetShiftDistanceForLandscape(COLUMN_INDEX_0, dir);
    double distance = 0.0f - textPickerColumnPattern->optionProperties_[COLUMN_INDEX_0].height;
    EXPECT_EQ(textPickerColumnPattern_->GetShiftDistanceForLandscape(COLUMN_INDEX_0, dir), distance);
}

/**
 * @tc.name: TextPickerColumnPatternTest011
 * @tc.desc: Test TextPickerColumnPattern ScrollOption.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest011, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 4;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->ScrollOption(20.0f);
    EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.size() - BUFFER_NODE_NUMBER, 5);
}

/**
 * @tc.name: TextPickerColumnPatternTest012
 * @tc.desc: Test TextPickerColumnPattern ResetAlgorithmOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest012, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    textPickerColumnPattern->algorithmOffset_.clear();
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    uint32_t counts = theme->GetShowOptionCount();
    textPickerColumnPattern->ResetAlgorithmOffset();
    for (uint32_t i = 0; i < counts; i++) {
        EXPECT_EQ(textPickerColumnPattern->algorithmOffset_.emplace_back(i), i);
    }
}

/**
 * @tc.name: TextPickerColumnPatternTest013
 * @tc.desc: Test TextPickerColumnPattern ScrollOption and HandleEnterSelectedArea.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternTest013, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 4;
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern->SetOptions(range);
    textPickerColumnPattern->SetCurrentIndex(SELECTED_INDEX_2);
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->optionProperties_.emplace_back(prop);
    textPickerColumnPattern->ScrollOption(10.0f);
    EXPECT_EQ(textPickerColumnPattern->GetEnterIndex(), 1);
}

/**
 * @tc.name: TextPickerColumnPatternInitTextFontFamily001
 * @tc.desc: Test InitTextFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInitTextFontFamily001, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    auto textPickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerLayoutProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == false && ALL FontFamily_ == false.
     */
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == false && ALL FontFamily_ == true.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(true);
    textPickerPattern->HasUserDefinedNormalFontFamily(true);
    textPickerPattern->HasUserDefinedSelectedFontFamily(true);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
}

/**
 * @tc.name: TextPickerColumnPatternInitTextFontFamily002
 * @tc.desc: Test InitTextFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternInitTextFontFamily002, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_->appCustomFont_ = "appCustomFont";
    auto textPickerPattern = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerLayoutProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == true && ALL FontFamily_ == true.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(true);
    textPickerPattern->HasUserDefinedNormalFontFamily(true);
    textPickerPattern->HasUserDefinedSelectedFontFamily(true);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), DEFAULT_VALUE);
    /**
     * @tc.cases: case. cover hasAppCustomFont_ == true && ALL FontFamily_ == false.
     */
    textPickerPattern->HasUserDefinedDisappearFontFamily(false);
    textPickerPattern->HasUserDefinedNormalFontFamily(false);
    textPickerPattern->HasUserDefinedSelectedFontFamily(false);
    textPickerColumnPattern_->InitTextFontFamily();
    EXPECT_EQ(textPickerLayoutProperty->GetDisappearFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
    EXPECT_EQ(textPickerLayoutProperty->GetSelectedFontFamilyValue(DEFAULT_VALUE), CUSTOM_VALUE);
}

/**
 * @tc.name: TextPickerColumnPatternSetCanLoop001
 * @tc.desc: Test SetCanLoop.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestNg, TextPickerColumnPatternSetCanLoop001, TestSize.Level1)
{
    InitTextPickerColumnTestNg();
    /**
     * @tc.cases: case. cover isLoop_ == isLoop.
     */
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_TRUE(textPickerColumnPattern_->isLoop_);

    textPickerColumnPattern_->SetCanLoop(false);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);
    /**
     * @tc.cases: case. cover isLoop_ != isLoop.
     */
    textPickerColumnPattern_->isLoop_ = false;
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);

    textPickerColumnPattern_->isLoop_ = false;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->SetCanLoop(true);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);

    textPickerColumnPattern_->isLoop_ = true;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->SetCanLoop(false);
    EXPECT_EQ(textPickerColumnPattern_->overscroller_.loopTossOffset_, 0.0);
}
} // namespace OHOS::Ace::NG
