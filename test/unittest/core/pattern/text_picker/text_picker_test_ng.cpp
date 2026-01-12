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

#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<TextPickerModel> TextPickerModel::textPickerInstance_ = nullptr;
std::unique_ptr<TextPickerDialogModel> TextPickerDialogModel::textPickerDialogInstance_ = nullptr;

TextPickerModel* TextPickerModel::GetInstance()
{
    if (!textPickerInstance_) {
        if (!textPickerInstance_) {
            textPickerInstance_.reset(new NG::TextPickerModelNG());
        }
    }
    return textPickerInstance_.get();
}

TextPickerDialogModel* TextPickerDialogModel::GetInstance()
{
    if (!textPickerDialogInstance_) {
        if (!textPickerDialogInstance_) {
            textPickerDialogInstance_.reset(new NG::TextPickerDialogModelNG());
        }
    }
    return textPickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr size_t THREE = 3;
constexpr uint32_t SELECTED_INDEX_1 = 1;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
const Dimension ICON_TEXT_SPACE = 8.0_vp;
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

class TextPickerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerTestNg();
    void DestroyTextPickerTestNgObject();

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

void TextPickerTestNg::DestroyTextPickerTestNgObject()
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

void TextPickerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerTestNg::TearDown()
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
 * @tc.name: TextPickerModelNGSetSelecteds001
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
 * @tc.name: TextPickerModelNGSetSelecteds002
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    /**
     * @tc.cases: case. cover branch isHasSelectAttr_ == false.
     */

    TextPickerModel::GetInstance()->SetHasSelectAttr(false);

    /**
     * @tc.cases: case. cover isCascade_ == true
     */
    TextPickerModel::GetInstance()->SetIsCascade(true);

    /**
     * @tc.cases: case. cover branch ProcessCascadeOptions values_ size more than 0.
     */
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    TextPickerModelNG::GetInstance()->SetColumns(options);

    std::vector<uint32_t> selecteds = { 0, 1, 2 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(2, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetSelecteds003
 * @tc.desc: Test TextPickerModelNG SetSelecteds.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetSelecteds003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->MultiInit(theme);

    /**
     * @tc.cases: case. cover branch isHasSelectAttr_ == true.
     */
    TextPickerModel::GetInstance()->SetHasSelectAttr(true);

    /**
     * @tc.cases: case. cover isCascade_ == true
     */
    TextPickerModel::GetInstance()->SetIsCascade(true);

    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::vector<uint32_t> selecteds = { 1, 3, 5 };
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step. Get pickerProperty and compare the result.
     * @tc.expected: the result of SetSelecteds is correct.
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    ASSERT_TRUE(pickerProperty->HasSelecteds());
    EXPECT_EQ(3, pickerProperty->GetSelecteds().value().at(1));
    EXPECT_EQ(5, pickerProperty->GetSelecteds().value().at(2));
}

/**
 * @tc.name: TextPickerModelNGSetValues001
 * @tc.desc: Test TextPickerModelNG SetValues.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetValues001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    std::vector<std::string> values = { "0", "1", "2" };
    TextPickerModelNG::GetInstance()->SetValues(values);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    options2.rangeResult = { "21", "22", "23" };
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    options3.rangeResult = { "31", "32", "33" };
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Multi Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    options2Child.rangeResult = { "21", "22" };
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
HWTEST_F(TextPickerTestNg, TextPickerModelNGSetColumns003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(false);
    std::vector<NG::TextCascadePickerOptions> options;
    NG::TextCascadePickerOptions options1;
    NG::TextCascadePickerOptions options1Child;
    options1Child.rangeResult = { "11", "12" };
    options1.rangeResult = { "1" };
    options1.children.emplace_back(options1Child);
    options.emplace_back(options1);
    NG::TextCascadePickerOptions options2;
    NG::TextCascadePickerOptions options2Child;
    NG::TextCascadePickerOptions options2Child2Child;
    options2Child2Child.rangeResult = { "221", "222" };
    options2Child.rangeResult = { "21" };
    options2Child.children.emplace_back(options2Child2Child);
    options2.rangeResult = { "2" };
    options2.children.emplace_back(options2Child);
    options.emplace_back(options2);
    NG::TextCascadePickerOptions options3;
    NG::TextCascadePickerOptions options3Child;
    options3Child.rangeResult = { "31", "32" };
    options3.rangeResult = { "3" };
    options3.children.emplace_back(options3Child);
    options.emplace_back(options3);
    /**
     * @tc.step: step2. Set Cascade Columns and compare the result.
     * @tc.expected: the result of SetColumns is correct.
     */
    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_EQ(THREE, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerAlgorithmTest
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);

    /**
     * @tc.cases: case. cover branch isDefaultPickerItemHeight_ is true.
     */
    textPickerLayoutAlgorithm.isDefaultPickerItemHeight_ = true;
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
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
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest003
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
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
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest004, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto subNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    textPickerLayoutAlgorithm.Layout(&layoutWrapper);
    auto childGeometryNode = subLayoutWrapper->GetGeometryNode();
    childGeometryNode->SetMarginFrameOffset(CHILD_OFFSET);
    EXPECT_EQ(childGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 10.0f));
}

/**
 * @tc.name: TextPickerAlgorithmTest005
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest005, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest006
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest006, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.cases: case. cover branch isShowInDialog_ is true .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    pickerPattern->SetIsShowInDialog(true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerAlgorithmTest007
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerAlgorithmTest007, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.cases: case. cover branch isShowInDialog_ is true .
     */
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    pickerPattern->SetIsShowInDialog(true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.cases: case. cover branch defaultPickerItemHeightValue LessOrEqual 0 .
     */
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(-10.0f));
    SizeF value(400.0f, 300.0f);
    pickerProperty->UpdateMarginSelfIdealSize(value);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: TextPickerDialogViewOnKeyEvent
 * @tc.desc: Test TextPickerDialogView OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewOnKeyEvent, TestSize.Level0)
{
    KeyEvent event;

    /**
     * @tc.cases: case. cover KeyAction is not DOWN.
     */
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_TAB;
    bool result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);

    /**
     * @tc.cases: case. cover KeyCode is KEY_ESCAPE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_ESCAPE;
    result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);

    /**
     * @tc.cases: case. cover KeyCode is not KEY_ESCAPE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_FORWARD_DEL;
    result = TextPickerDialogView::OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextPickerModelTest001
 * @tc.desc: Test SetDefaultPickerItemHeight, SetCanLoop, SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest001, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method SetDefaultPickerItemHeight.
     */
    Dimension dimension(20.0);
    TextPickerModelNG::GetInstance()->SetDefaultPickerItemHeight(dimension);
    EXPECT_EQ(textPickerLayoutProperty->GetDefaultPickerItemHeight(), dimension);
    /**
     * test method SetCanLoop.
     */
    TextPickerModelNG::GetInstance()->SetCanLoop(true);
    EXPECT_TRUE(textPickerLayoutProperty->GetCanLoop());
    /**
     * test method SetBackgroundColor.
     */
    Color color;
    TextPickerModelNG::GetInstance()->SetBackgroundColor(color);
    EXPECT_EQ(textPickerPattern->backgroundColor_, color);
}

/**
 * @tc.name: TextPickerModelTest002
 * @tc.desc: Test GetSingleRange, GetMultiOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest002, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker framenode.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method GetSingleRange.
     */
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    std::vector<NG::RangeContent> rangeValue;
    auto ret = TextPickerModelNG::GetInstance()->GetSingleRange(rangeValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(rangeValue.size(), 3);

    EXPECT_TRUE(TextPickerModelNG::GetInstance()->IsSingle());
    /**
     * test method GetMultiOptions.
     */
    std::vector<TextCascadePickerOptions> options;
    TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::vector<NG::TextCascadePickerOptions> multiOptions;
    ret = TextPickerModelNG::GetInstance()->GetMultiOptions(multiOptions);
    EXPECT_TRUE(ret);
    EXPECT_EQ(multiOptions.size(), 1);
}


/**
 * @tc.name: TextPickerModelTest003
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest003, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * test method SetDefaultPickerItemHeight.
     */
    ItemDivider divider;
    divider.color = Color::TRANSPARENT;
    divider.strokeWidth = 10.0_vp;
    divider.startMargin = 10.0_vp;
    divider.endMargin = 10.0_vp;
    TextPickerModelNG::GetInstance()->SetDivider(divider);
    EXPECT_EQ(textPickerLayoutProperty->GetDivider(), divider);
}

/**
 * @tc.name: TextPickerModelTest004
 * @tc.desc: Test SetTextPickerDialogShow
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest004, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker dialog model.
     */
    TextPickerDialogModelNG textPickerDialogModel;
    RefPtr<AceType> pickerText = AceType::MakeRefPtr<AceType>();
    TextPickerSettingData settingData;
    std::function<void()> onCancel = []() {};
    std::function<void(const std::string&)> onAccept = [](const std::string&) {};
    std::function<void(const std::string&)> onChange = [](const std::string&) {};
    std::function<void(const std::string&)> onScrollStop = [](const std::string&) {};
    std::function<void(const std::string&)> onEnterSelectedArea = [](const std::string&) {};
    TextPickerDialog textPickerDialog;
    textPickerDialog.alignment = DialogAlignment::CENTER;
    TextPickerDialogEvent textPickerDialogEvent;
    std::vector<ButtonInfo> buttonInfos;

    /**
     * test method SetTextPickerDialogShow.
     */
    textPickerDialogModel.SetTextPickerDialogShow(pickerText, settingData, std::move(onCancel),
        std::move(onAccept), std::move(onChange), std::move(onScrollStop), std::move(onEnterSelectedArea),
        textPickerDialog, textPickerDialogEvent, buttonInfos);
    EXPECT_EQ(textPickerDialog.alignment, DialogAlignment::CENTER);
}

/**
 * @tc.name: TextPickerModelTest005
 * @tc.desc: Test SetNormalTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest005, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker model.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    PickerTextStyle pickerTextStyle;
    TextPickerModelNG::SetNormalTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetSelectedTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetDisappearTextStyle(node, theme, pickerTextStyle);

    /**
     * @tc.steps: step2. execute SetNormalTextStyle
     * @tc.expected: prop is set as expected
     */
    Dimension fontSize(10.0f);
    pickerTextStyle.fontSize = fontSize;
    TextPickerModelNG::SetNormalTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetSelectedTextStyle(node, theme, pickerTextStyle);
    TextPickerModelNG::SetDisappearTextStyle(node, theme, pickerTextStyle);

    auto textPickerLayoutProperty = node->GetLayoutProperty<TextPickerLayoutProperty>();
    EXPECT_EQ(textPickerLayoutProperty->GetFontSizeValue(Dimension(0)).Value(), 10.0f);
}

/**
 * @tc.name: TextPickerModelTest006
 * @tc.desc: Test SetColumns
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest006, TestSize.Level0)
{
    /**
     * @tc.step: step1. create textpicker model.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerModelNG::SetColumns(node, options);
    TextPickerModelNG::getTextPickerRange(node);

    /**
     * @tc.steps: step2. execute SetColumns
     * @tc.expected: prop is set as expected
     */
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
    TextPickerModelNG::isSingleRange_ = !TextPickerModelNG::isSingleRange_;
    NG::TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::SetColumns(node, options);
    TextPickerModelNG::getTextPickerRange(node);
    EXPECT_EQ(TextPickerModelNG::GetInstance()->IsCascade(), true);
    EXPECT_EQ(TextPickerModelNG::isSingleRange_, false);
}


/**
 * @tc.name: TextPickerModelTest007
 * @tc.desc: Test TextPickerModelTest.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerModelTest007, TestSize.Level0)
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
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
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
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->left, CalcLength(ICON_TEXT_SPACE));
}

/**
 * @tc.name: TextPickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test TextPickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontScaleValue001, TestSize.Level0)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: TextPickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test TextPickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontScaleValue002, TestSize.Level0)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TextPickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest001, TestSize.Level0)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest002, TestSize.Level0)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest003, TestSize.Level0)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: TextPickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test TextPickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewConvertFontSizeLimitTest004, TestSize.Level0)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TextPickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest001, TestSize.Level0)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest002, TestSize.Level0)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest003, TestSize.Level0)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TextPickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test TextPickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerTestNg, TextPickerDialogViewGetUserSettingLimitTest004, TestSize.Level0)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = TextPickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

/**
* @tc.name: TextPickerToJsonDefaultPickerItemHeight001
* @tc.desc: Test TextPicker ToJsonValue.
* @tc.type: FUNC
*/
HWTEST_F(TextPickerTestNg, TextPickerToJsonDefaultPickerItemHeight001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    /**
    * @tc.step: step1. Set Selecteds Values and Set Values.
    * @tc.expected: default PickerItemHeight is 0.00px
    */
    std::vector<uint32_t> selecteds;
    selecteds.emplace_back(1);
    selecteds.emplace_back(2);
    TextPickerModelNG::GetInstance()->SetSelecteds(selecteds);
    std::vector<std::string> values;
    values.emplace_back("1");
    values.emplace_back("2");
    TextPickerModelNG::GetInstance()->SetValues(values);
    TextPickerModelNG::GetInstance()->SetDefaultPickerItemHeight(Dimension(10.0f, DimensionUnit::VP));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
    * @tc.steps: step2. call ToJsonValue.
    * @tc.expected: as follows
    */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    GTEST_LOG_(INFO) << json->ToString();
    /**
    * @tc.steps: check the key value.
    * @tc.expected: it should be -.
    */
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "10.00vp");
}
} // namespace OHOS::Ace::NG
