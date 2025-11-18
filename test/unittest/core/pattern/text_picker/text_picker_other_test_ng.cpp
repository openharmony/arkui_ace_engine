/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
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
const InspectorFilter filter;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_10 = 10.0;
constexpr double FONT_SIZE_20 = 20.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
constexpr double TOSS_DELTA = 20.0;
constexpr double DISTANCE = 20.0;
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
constexpr double OVER_SCROLL_OFFSET1 = 40.0;
constexpr double OVER_SCROLL_OFFSET2 = 60.0;
constexpr double OVER_SCROLL_DELTA = 10.0;
constexpr uint32_t OVER_SCROLL_ITEMS = 20;
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
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

class TextPickerOtherTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerOtherTestNg();
    void DestroyTextPickerOtherTestNgObject();

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

void TextPickerOtherTestNg::DestroyTextPickerOtherTestNgObject()
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

void TextPickerOtherTestNg::InitTextPickerOtherTestNg()
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

void TextPickerOtherTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerOtherTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerOtherTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerOtherTestNg::TearDown()
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
 * @tc.name: GetOptionsMultiStr001
 * @tc.desc: Test TextPickerPattern GetOptionsMultiStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, GetOptionsMultiStr001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode =ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsMultiStr().
     * @tc.expected: the result of GetOptionsMultiStr is empty.
     */
    std::string result = pickerPattern->GetOptionsMultiStr();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: GetOptionsMultiStr002
 * @tc.desc: Test TextPickerPattern GetOptionsMultiStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, GetOptionsMultiStr002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsMultiStr().
     * @tc.expected: the result of GetOptionsMultiStr is [["11"]].
     */
    std::vector<TextCascadePickerOptions> options;
    TextCascadePickerOptions options1;
    options1.rangeResult = { "11", "12", "13" };
    options.emplace_back(options1);
    TextPickerModelNG::GetInstance()->SetColumns(options);
    std::string result = pickerPattern->GetOptionsMultiStr();
    std::string expectResult = "[[\"11\",\"12\",\"13\"]]";
    EXPECT_EQ(result, expectResult);
}

/**
 * @tc.name: GetOptionsCascadeStr001
 * @tc.desc: Test GetOptionsCascadeStr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, GetOptionsCascadeStr001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
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

    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.step: step2. call GetOptionsCascadeStr().
     * @tc.expected: the result of GetOptionsCascadeStr is "[{"text":"11"},{"text":"21"},{"text":"31"}]".
     */
    std::string result = pickerPattern->GetOptionsCascadeStr(options);
    std::string expectResult = "[{\"text\":\"11\"},{\"text\":\"21\"},{\"text\":\"31\"}]";
    EXPECT_EQ(result, expectResult);
}

/**
 * @tc.name: ChangeTextStyle001
 * @tc.desc: Test TextPickerLayoutAlgorithm::ChangeTextStyle().
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, ChangeTextStyle001, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->ClearStack();
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    TextPickerModelNG::GetInstance()->Create(pickerTheme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultPickerItemHeight(Dimension(10));
    SizeF size(100.0f, 100.0f);
    pickerProperty->UpdateMarginSelfIdealSize(size);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    auto columnSubNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    ASSERT_NE(columnSubNode, nullptr);

    /**
     * @tc.steps: creat a layoutwrapper and SetLayoutAlgorithm for it.
     */
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(columnNode, columnNode->GetGeometryNode(), pickerProperty);

    auto node = layoutWrapper.GetHostNode();
    ASSERT_NE(node, nullptr);
    auto layoutProperty_ = node->GetLayoutProperty()->Clone();
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: set layoutWrapper->layoutProperty_ is not null.
     */
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnSubNode, columnSubNode->GetGeometryNode(), layoutProperty_);
    EXPECT_NE(subLayoutWrapper, nullptr);

    auto layoutAlgorithmWrapper = subLayoutWrapper->GetLayoutAlgorithm();
    layoutWrapper.AppendChild(subLayoutWrapper);
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);

    /**
     * @tc.steps: set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto pattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    subLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    uint32_t index = 1;
    uint32_t showOptionCount = 2;
    TextPickerLayoutAlgorithm textPickerLayoutAlgorithm;
    textPickerLayoutAlgorithm.ChangeTextStyle(index, showOptionCount, size, subLayoutWrapper, &layoutWrapper);
    auto frameSize = subLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_TEXT_FRAME_SIZE);

    /**
     * @tc.case: cover branch index not equals selectedIndex .
     */
    uint32_t showOptionCount1 = 1;
    textPickerLayoutAlgorithm.ChangeTextStyle(index, showOptionCount1, size, subLayoutWrapper, &layoutWrapper);
    EXPECT_EQ(100.0f, subLayoutWrapper->GetGeometryNode()->GetFrameSize().Width());
}

/**
 * @tc.name: FlushAnimationTextProperties001
 * @tc.desc: Test TextPickerColumnPattern FlushAnimationTextProperties
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, FlushAnimationTextProperties001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    /**
     * @tc.step: step2. create textpicker cloumn pattern and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 0.
     */
    columnPattern->FlushAnimationTextProperties(false);
    EXPECT_EQ(0, columnPattern->animationProperties_.size());

    /**
     * @tc.step: step3. construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is 1 and fontSize meet expectation.
     */
    std::vector<TextProperties> animationProperties;
    TextProperties properties1;
    properties1.upFontSize = Dimension(FONT_SIZE_5);
    properties1.fontSize = Dimension(FONT_SIZE_20);
    properties1.downFontSize = Dimension(FONT_SIZE_5);
    properties1.upColor = Color::RED;
    properties1.currentColor = Color::RED;
    properties1.downColor = Color::RED;
    animationProperties.emplace_back(properties1);
    columnPattern->animationProperties_ = animationProperties;

    columnPattern->FlushAnimationTextProperties(false);
    Dimension result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    columnPattern->FlushAnimationTextProperties(true);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_5), result);

    /**
     * @tc.step: step4. add construct columnPattern animationProperties_ and call FlushAnimationTextProperties.
     * @tc.expected: cover branch animationProperties_ size is more than 1 and fontSize meet expectation.
     */
    TextProperties properties2;
    properties2.upFontSize = Dimension(FONT_SIZE_10);
    properties2.fontSize = Dimension(FONT_SIZE_20);
    properties2.downFontSize = Dimension(FONT_SIZE_10);
    properties2.upColor = Color::RED;
    properties2.currentColor = Color::RED;
    properties2.downColor = Color::RED;
    animationProperties.emplace_back(properties2);
    columnPattern->animationProperties_ = animationProperties;

    columnPattern->FlushAnimationTextProperties(false);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_10), result);
    columnPattern->FlushAnimationTextProperties(true);
    result = columnPattern->animationProperties_[0].fontSize;
    EXPECT_EQ(Dimension(FONT_SIZE_20), result);
}

/**
 * @tc.name: TextPickerOverscroller001
 * @tc.desc: Test TextPickerColumnPattern OverScroller, move down.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerOverscroller001, TestSize.Level1)
{
    InitTextPickerOtherTestNg();
    ASSERT_NE(frameNode_, nullptr);
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(false);

    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->GetGeometryNode()->SetFrameSize(COLUMN_SIZE);
    textPickerColumnPattern_->SetCurrentIndex(0);
    std::vector<NG::RangeContent> range = { { "", "" } };
    textPickerColumnPattern_->SetOptions(range);

    // init overscroller
    TextPickerOverscroller overscroller;
    overscroller.SetColumn(textPickerColumnPattern_);
    EXPECT_EQ(overscroller.GetOverScroll(), 0);

    // overScroll to OVER_SCROLL_OFFSET1
    overscroller.ApplyCurrentOffset(0.0, OVER_SCROLL_OFFSET1, TOSS_DELTA);
    EXPECT_TRUE(overscroller.IsOverScroll());
    EXPECT_GT(overscroller.GetOverScroll(), DISTANCE);
    EXPECT_FALSE(overscroller.IsBackOverScroll());
    EXPECT_EQ(overscroller.GetBackScroll(), 0);

    // overScroll to max
    overscroller.SetOverScroll(OVER_SCROLL_OFFSET2);
    auto yLast = OVER_SCROLL_OFFSET1;
    auto offsetY = OVER_SCROLL_OFFSET1 + OVER_SCROLL_DELTA;
    for (auto i = 0; i < OVER_SCROLL_ITEMS; i++) {
        overscroller.ApplyCurrentOffset(yLast, offsetY, TOSS_DELTA);
        yLast = offsetY;
        offsetY = yLast + OVER_SCROLL_DELTA;
    }

    EXPECT_TRUE(overscroller.InMaxOverScroll());
    EXPECT_TRUE(overscroller.ShouldStartRebound());

    // reset overscroller
    overscroller.Reset();
    EXPECT_EQ(overscroller.GetOverScroll(), 0);
    EXPECT_FALSE(overscroller.IsOverScroll());
}
/**
 * @tc.name: TextPickerModelNGSetGradientHeight002
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerModelNGSetGradientHeight002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TextPickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TextPickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}
/**
 * @tc.name: TextPickerModelNGSetColumns004
 * @tc.desc: Test SetCascadeColumns.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerModelNGSetColumns004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    TextPickerModelNG::GetInstance()->MultiInit(theme);
    TextPickerModelNG::GetInstance()->SetIsCascade(true);
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

    TextPickerModelNG::GetInstance()->SetColumns(options);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.step: step2. call GetCascadeOptionCount.
     * @tc.expected: the result of GetCascadeOptionCount is 1.
     */
    EXPECT_EQ(1, pickerPattern->GetCascadeOptionCount());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight001
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerModelNGSetGradientHeight001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerPaintTest005
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerPaintTest005, TestSize.Level1)
{
#ifdef ARKUI_WEARABLE
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    auto renderContext = frameNode->GetRenderContext();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = textPickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
#endif
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue002
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();

    /**
     * @tc.step: step2. call ToJsonValue.
     * @tc.expected: the default result.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), "0.00px");
    EXPECT_EQ(json->GetString("gradientHeight"), "0.00px");
    EXPECT_EQ(json->GetString("canLoop"), "true");
    EXPECT_EQ(json->GetString("selected"), "0");
    EXPECT_EQ(json->GetString("value"), "");

    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FF000000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "14.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Normal");

    auto textStyle = json->GetObject("textStyle");
    ASSERT_NE(textStyle, nullptr);
    ASSERT_EQ(textStyle->GetString("color"), "#FF000000");
    auto normalFont = textStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "14.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Normal");

    auto selectTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectTextStyle, nullptr);
    EXPECT_EQ(selectTextStyle->GetString("color"), "#FF000000");
    auto selectFont = textStyle->GetObject("font");
    ASSERT_NE(selectFont, nullptr);
    EXPECT_EQ(selectFont->GetString("size"), "14.00px");
    EXPECT_EQ(selectFont->GetString("weight"), "FontWeight.Normal");

    auto defaulTextStyle = json->GetObject("defaultTextStyle");
    ASSERT_NE(defaulTextStyle, nullptr);
    EXPECT_EQ(defaulTextStyle->GetString("color"), "#FF000000");
    EXPECT_EQ(defaulTextStyle->GetString("minFontSize"), "0.00px");
    EXPECT_EQ(defaulTextStyle->GetString("maxFontSize"), "0.00px");
    EXPECT_EQ(defaulTextStyle->GetString("overflow"), "TextOverflow.Clip");
    auto defaulFont = textStyle->GetObject("font");
    ASSERT_NE(defaulFont, nullptr);
    EXPECT_EQ(defaulFont->GetString("size"), "14.00px");
    EXPECT_EQ(defaulFont->GetString("weight"), "FontWeight.Normal");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue003
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);
    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);

    /**
     * @tc.step: step2. call ToJsonValue.
     * @tc.expected: the canLoop result is true.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("canLoop"), "true");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue004
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);
    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    std::vector<uint32_t> selecteds;
    int selectedCount = 5;
    for (int i = 1; i < selectedCount; i++) {
        selecteds.emplace_back(i);
    }
    selecteds.emplace_back(66);
    pickerProperty->UpdateSelecteds(selecteds);

    auto selectedRes = pickerProperty->CloneSelecteds().value_or(std::vector<uint32_t>());
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(selectedRes[i], selecteds[i]);
    }

    std::vector<std::string> values;
    values.emplace_back("hellow");
    values.emplace_back("good");
    values.emplace_back("better");
    values.emplace_back("best");
    values.emplace_back("most");
    pickerProperty->UpdateValues(values);

    auto values2 = pickerProperty->CloneValues().value_or(std::vector<std::string>());
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(values2[i], values[i]);
    }

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto jsonArraySelected = json->GetValue("selecteds");
    ASSERT_NE(jsonArraySelected, nullptr);
    EXPECT_EQ(jsonArraySelected->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArraySelected->GetString(std::to_string(i).c_str()), std::to_string(selecteds[i]));
    }

    auto jsonArrayValues = json->GetValue("values");
    EXPECT_EQ(jsonArrayValues->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArrayValues->GetString(std::to_string(i).c_str()), values[i]);
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue005
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set selectedIndex.
     */
    bool isCanLoop = true;
    TextPickerModelNG::GetInstance()->SetCanLoop(isCanLoop);
    EXPECT_EQ(TextPickerModelNG::GetCanLoop(frameNode), isCanLoop);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    std::vector<uint32_t> selectIndex;
    selectIndex.push_back(1);
    selectIndex.push_back(2);
    pickerProperty->UpdateSelectedIndex(selectIndex);

    std::vector<uint32_t> selecteds;
    int selectedCount = 5;
    for (int i = 0; i < selectedCount; i++) {
        selecteds.emplace_back(i);
    }

    pickerProperty->UpdateSelecteds(selecteds);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     * The result is the same as selects
     */
    auto jsonArraySelectIndex = json->GetValue("selectedIndex");
    ASSERT_NE(jsonArraySelectIndex, nullptr);
    EXPECT_EQ(jsonArraySelectIndex->GetArraySize(), selectedCount);
    for (int i = 0; i < selectedCount; i++) {
        EXPECT_EQ(jsonArraySelectIndex->GetString(std::to_string(i).c_str()), std::to_string(selecteds[i]));
    }
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue006
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set.
     */
    Dimension defaultPickerItemHeight = Dimension(6);
    Dimension gradientHeight = Dimension(7);
    std::string value = "testValue";
    uint32_t selected = 0;
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateSelected(selected);
    pickerProperty->UpdateDefaultPickerItemHeight(defaultPickerItemHeight);
    pickerProperty->UpdateGradientHeight(gradientHeight);
    pickerProperty->UpdateValue(value);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("defaultPickerItemHeight"), defaultPickerItemHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("gradientHeight"), gradientHeight.ToString().c_str());
    EXPECT_EQ(json->GetString("selected"), std::to_string(selected));
    EXPECT_EQ(json->GetString("value"), value.c_str());
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue007
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set selectedTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto selectedTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectedTextStyle, nullptr);
    EXPECT_EQ(selectedTextStyle->GetString("color"), "#FFFF0000");
    auto selectedFont = selectedTextStyle->GetObject("font");
    ASSERT_NE(selectedFont, nullptr);
    EXPECT_EQ(selectedFont->GetString("size"), "10.00px");
    EXPECT_EQ(selectedFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue008
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set disappearTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue009
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue009, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set normalTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TextPickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto normalTextStyle = json->GetObject("textStyle");
    ASSERT_NE(normalTextStyle, nullptr);
    EXPECT_EQ(normalTextStyle->GetString("color"), "#FFFF0000");
    auto normalFont = normalTextStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "10.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: TextPickerLayoutPropertyToJsonValue0010
 * @tc.desc: Test TextPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerOtherTestNg, TextPickerLayoutPropertyToJsonValue010, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. Construct property values and set defaultTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    Dimension minFontSize = Dimension(10);
    Dimension maxFontSize = Dimension(10);
    auto pickerProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->UpdateDefaultFontSize(data.fontSize.value());
    pickerProperty->UpdateDefaultColor(data.textColor.value());
    pickerProperty->UpdateDefaultWeight(data.fontWeight.value());
    pickerProperty->UpdateDefaultMinFontSize(minFontSize);
    pickerProperty->UpdateDefaultMaxFontSize(maxFontSize);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.step: step3 call ToJsonValue and Judging expected results.
     */
    auto disappearTextStyle = json->GetObject("defaultTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    EXPECT_EQ(disappearTextStyle->GetString("minFontSize"), "10.00px");
    EXPECT_EQ(disappearTextStyle->GetString("maxFontSize"), "10.00px");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");
}
} // namespace OHOS::Ace::NG
