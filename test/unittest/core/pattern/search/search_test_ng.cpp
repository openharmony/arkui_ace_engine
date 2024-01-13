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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/animation/curves.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/edge.h"
#include "core/components/search/search_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
constexpr float COLUMN_HEIGHT = 200.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO = 0.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
const std::string EMPTY_VALUE;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
const std::string SEARCH_SVG = "resource:///ohos_search.svg";
} // namespace

class SearchTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateColumn();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

void SearchTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    auto searchTheme = AceType::MakeRefPtr<SearchTheme>();
    searchTheme->iconHeight_ = 24.0_px;
    searchTheme->height_ = 60.0_px;
    searchTheme->searchButtonTextColor_ = Color::RED;
    searchTheme->placeholderColor_ = Color::RED;
    textFieldTheme->bgColor_ = Color::RED;
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == SearchTheme::TypeId()) {
            return searchTheme;
        }
        if (type == IconTheme::TypeId()) {
            return iconTheme;
        }
        return textFieldTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
}

void SearchTestNg::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> SearchTestNg::CreateColumn()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(columnLayoutPattern, nullptr);
    auto rowLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    return { columnFrameNode, layoutWrapper };
}

PaddingProperty SearchTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

/**
 * @tc.name: Measure001
 * @tc.desc: Measure and layout
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Measure001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    auto searchLayoutAlgorithm =
        AccessibilityManager::DynamicCast<SearchLayoutAlgorithm>(searchPattern->CreateLayoutAlgorithm());
    ASSERT_NE(searchLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(searchLayoutAlgorithm));

    // textField Wrapper
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    RefPtr<GeometryNode> textFieldNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textFieldNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textFieldFrameNode, textFieldNodeGeometryNode, textFieldFrameNode->GetLayoutProperty());
    ASSERT_NE(textFieldNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textFieldNodeLayoutWrapper);

    // image Wrapper
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> imageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        imageFrameNode, imageNodeGeometryNode, imageFrameNode->GetLayoutProperty());
    ASSERT_NE(imageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(imageNodeLayoutWrapper);

    // cancelImage Wrapper
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> cancelImageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> cancelImageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        cancelImageFrameNode, cancelImageNodeGeometryNode, cancelImageFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelImageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelImageNodeLayoutWrapper);

    // cancelButton Wrapper
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> cancelButtonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> cancelButtonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        cancelButtonFrameNode, cancelButtonNodeGeometryNode, cancelButtonFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelButtonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelButtonNodeLayoutWrapper);

    // button Wrapper
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> buttonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> buttonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        buttonFrameNode, buttonNodeGeometryNode, buttonFrameNode->GetLayoutProperty());
    ASSERT_NE(buttonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(buttonNodeLayoutWrapper);

    LayoutConstraintF LayoutConstraintVaildSize;
    double textfieldHeight = 50;
    textFieldNodeGeometryNode->SetFrameSize(SizeF(100, textfieldHeight));
    searchModelInstance.SetSearchIconSize(Dimension(16, DimensionUnit::VP));
    double cancelButtonSize = 200;
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(100, cancelButtonSize));
    double searchButtonHeight = 300;
    buttonNodeGeometryNode->SetFrameSize(SizeF(100, searchButtonHeight));
    LayoutConstraintVaildSize.selfIdealSize.SetWidth(10000);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), textfieldHeight);

    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), cancelButtonSize);

    searchModelInstance.SetSearchButton("SEARCH");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchButtonHeight);

    searchModelInstance.SetSearchButton("SEARCH");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchButtonHeight);

    searchModelInstance.SetSearchButton("");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_LT(geometryNode->GetFrameSize().Height(), searchButtonHeight);
    EXPECT_GE(geometryNode->GetFrameSize().Height(), cancelButtonSize);
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    layoutWrapper->GetLayoutProperty()->UpdatePadding(
        PaddingProperty({ CalcLength(0.0f), CalcLength(0.0f), CalcLength(0.0f), CalcLength(20.0f) }));
    searchLayoutAlgorithm->searchIconSizeMeasure_ = SizeF(24.0f, 24.0f);
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    double searchHeight = 100;
    LayoutConstraintVaildSize.selfIdealSize.SetHeight(searchHeight);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchHeight);

    geometryNode->SetFrameSize(SizeF(10, 10));
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(40, 40));
    buttonNodeGeometryNode->SetFrameSize(SizeF(40, 40));
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(cancelButtonNodeGeometryNode->GetFrameSize().Height(), 40);
    EXPECT_EQ(buttonNodeGeometryNode->GetFrameSize().Height(), 40);

    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(100, 100));
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(cancelButtonNodeGeometryNode->GetFrameSize().Height(), 100);
}

/**
 * @tc.name: Measure002
 * @tc.desc: Measure child is null
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Measure002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::SEARCH_ETS_TAG, nodeId, AceType::MakeRefPtr<SearchPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    auto searchLayoutAlgorithm = searchPattern->CreateLayoutAlgorithm();
    ASSERT_NE(searchLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 0);
}

/**
 * @tc.name: SearchPatternMethodTest001
 * @tc.desc: OnClickCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto imageGesture = imageFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(imageGesture, nullptr);
    imageGesture->ActClick();

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonGesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(buttonGesture, nullptr);
    buttonGesture->ActClick();

    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelButtonGesture = cancelButtonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(cancelButtonGesture, nullptr);
    cancelButtonGesture->ActClick();

    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    searchPattern->searchController_->CaretPosition(10);
}

/**
 * @tc.name: SearchPatternMethodTest002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();

    /**
     * @tc.cases: case1.
     */
    KeyEvent keyEventOne(KeyCode::KEY_ENTER, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    focusHub->ProcessOnKeyEventInternal(keyEventOne);

    /**
     * @tc.cases: case2.
     */
    KeyEvent keyEventTwo(KeyCode::KEY_ENTER, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    focusHub->ProcessOnKeyEventInternal(keyEventTwo);

    /**
     * @tc.cases: case3.
     */
    KeyEvent keyEventThree(KeyCode::KEY_ENTER, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    focusHub->ProcessOnKeyEventInternal(keyEventThree);

    /**
     * @tc.cases: case4.
     */
    KeyEvent keyEventFour(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    focusHub->ProcessOnKeyEventInternal(keyEventFour);

    /**
     * @tc.cases: case5.
     */
    KeyEvent keyEventFive(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    focusHub->ProcessOnKeyEventInternal(keyEventFive);

    /**
     * @tc.cases: case6.
     */
    KeyEvent keyEventSix(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    focusHub->ProcessOnKeyEventInternal(keyEventSix);

    /**
     * @tc.cases: case7.
     */
    KeyEvent keyEventSeven(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    focusHub->ProcessOnKeyEventInternal(keyEventSeven);
}

/**
 * @tc.name: SearchPatternMethodTest003
 * @tc.desc: GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest003, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();
    RoundRect paintRect;

    /**
     * @tc.cases: case1.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    focusHub->getInnerFocusRectFunc_(paintRect);

    /**
     * @tc.cases: case2.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    focusHub->getInnerFocusRectFunc_(paintRect);

    /**
     * @tc.cases: case3.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    focusHub->getInnerFocusRectFunc_(paintRect);
}

/**
 * @tc.name: SearchPatternMethodTest004
 * @tc.desc: OnClickTextField
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest004, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.cases: case1.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto gesture = textFieldFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->ActClick();

    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: SearchPatternMethodTest005
 * @tc.desc: click cancel button when no focus at cancel button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest005, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("Text", 0);

    /**
     * @tc.step: step2. click cancel button.
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto gesture = textFieldFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->ActClick();

    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: SearchPatternMethodTest006
 * @tc.desc: click cancel button when focus at cancel button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchPatternMethodTest006, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("Text", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(
        KeyCode::KEY_TAB, KeyAction::DOWN, { KeyCode::KEY_TAB }, 0, timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: move focus to cancel button by pressing TAB
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. click cancel button.
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto gesture = textFieldFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->ActClick();

    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern001
 * @tc.desc: isHover_ is false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    MouseInfo info;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto renderContext = buttonFrameNode->GetRenderContext();
    auto mouseStyle = MouseFormat::TEXT_CURSOR;
    pattern->isCancelButtonHover_ = true;
    pattern->UpdateChangeEvent("");
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(pattern->buttonSize_.Height(), 0);
    EXPECT_EQ(pattern->buttonSize_.Width(), 0);
    pattern->OnModifyDone();
    pattern->OnButtonTouchDown(0);
    pattern->OnButtonTouchUp(0);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
    pattern->OnButtonTouchDown(3);
    pattern->OnButtonTouchUp(3);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
    pattern->SetMouseStyle(mouseStyle);
    pattern->HandleButtonMouseEvent(true, 3);
    ASSERT_TRUE(pattern->isCancelButtonHover_);
    pattern->HandleButtonMouseEvent(true, 0);
    ASSERT_TRUE(pattern->isSearchButtonHover_);
    pattern->HandleButtonMouseEvent(false, 3);
    ASSERT_FALSE(pattern->isCancelButtonHover_);
    pattern->HandleButtonMouseEvent(false, 0);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
}

/**
 * @tc.name: Pattern002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // textField Wrapper
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    RefPtr<GeometryNode> textFieldNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textFieldNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textFieldFrameNode, textFieldNodeGeometryNode, textFieldFrameNode->GetLayoutProperty());
    ASSERT_NE(textFieldNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textFieldNodeLayoutWrapper);

    // image Wrapper
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> imageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        imageFrameNode, imageNodeGeometryNode, imageFrameNode->GetLayoutProperty());
    ASSERT_NE(imageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(imageNodeLayoutWrapper);

    // cancelImage Wrapper
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> cancelImageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> cancelImageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        cancelImageFrameNode, cancelImageNodeGeometryNode, cancelImageFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelImageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelImageNodeLayoutWrapper);

    // cancelButton Wrapper
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> cancelButtonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> cancelButtonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        cancelButtonFrameNode, cancelButtonNodeGeometryNode, cancelButtonFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelButtonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelButtonNodeLayoutWrapper);

    // button Wrapper
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> buttonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> buttonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        buttonFrameNode, buttonNodeGeometryNode, buttonFrameNode->GetLayoutProperty());
    ASSERT_NE(buttonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(buttonNodeLayoutWrapper);

    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 5);

    searchModelInstance.SetSearchButton("search");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 5);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: UpdateChangeEvent and ToJsonValue while cancel button style is different
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateChangeEvent("search");
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INPUT);
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INPUT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    pattern->UpdateChangeEvent("");
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: InitButtonTouchEvent TouchType = DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern007, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: Pattern008
 * @tc.desc: InitButtonTouchEvent TouchType = UP
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern008, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));

    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: PatternOnColorConfigurationUpdate009
 * @tc.desc: Test pttern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PatternOnColorConfigurationUpdate009, TestSize.Level1)
{
    /**
     * @tc.step: step2. create frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), true);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);

    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);

    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.step: step3. call OnColorConfigurationUpdate.
     * @tc.expected: cover branch cancelButtonNode_、buttonNode_ and textField_ not null and call
     * OnColorConfigurationUpdate.
     */
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->cancelButtonNode_);
}

/**
 * @tc.name: PatternOnColorConfigurationUpdate010
 * @tc.desc: Test pttern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PatternOnColorConfigurationUpdate010, TestSize.Level1)
{
    /**
     * @tc.step: step2. create frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), true);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);

    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);

    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.step: step3. call OnColorConfigurationUpdate.
     * @tc.expected: cover branch cancelButtonNode_、buttonNode_ and textField_ all null and call
     * OnColorConfigurationUpdate.
     */
    pattern->SetButtonNode(nullptr);
    pattern->SetTextFieldNode(nullptr);
    pattern->SetCancelButtonNode(nullptr);
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(pattern->cancelButtonNode_, nullptr);
}

/**
 * @tc.name: PatternOnColorConfigurationUpdate012
 * @tc.desc: Test pttern HandleTextContentLines
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PatternOnColorConfigurationUpdate012, TestSize.Level1)
{
    /**
     * @tc.step: step2. create frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);

    /**
     * @tc.step: create textFieldPattern and searchPattern.
     */
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->UpdateEditingValue("", 0);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.step: step3. call HandleTextContentLines.
     * @tc.expected: cover branch IsOperation is false and call HandleTextContentLines
     */
    int32_t result = pattern->HandleTextContentLines();
    EXPECT_EQ(result, 0);

    /**
     * @tc.step: step4. call HandleTextContentLines.
     * @tc.expected: cover branch IsOperation is true and GetLineHeight value is 0.
     */
    textFieldPattern->UpdateEditingValue("aaa", 0);
    result = pattern->HandleTextContentLines();
    EXPECT_EQ(result, 0);
    pattern->HandleCaretPosition(3); // 3 is caret index
    pattern->HandleGetCaretPosition();
    auto index = pattern->HandleGetCaretIndex();
    ASSERT_EQ(index, 3); // 3 is caret index
}

/**
 * @tc.name: SetCaretWidth001
 * @tc.desc: Set caretwidth and CursorColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCaretWidth001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textPaintProperty, nullptr);
    searchModelInstance.SetCaretWidth(14.0_vp);
    searchModelInstance.SetCaretColor(Color::RED);
    EXPECT_EQ(textPaintProperty->GetCursorWidth()->Value(), 14);
    EXPECT_EQ(textPaintProperty->GetCursorColor(), Color::RED);
}

/**
 * @tc.name: SetSearchIconSize001
 * @tc.desc: Set search icon size
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchIconSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();

    searchModelInstance.SetSearchIconSize(14.0_vp);
    EXPECT_EQ(searchLayoutProperty->GetSearchIconUDSize(), 14.0_vp);
}

/**
 * @tc.name: SetSearchIconColor001
 * @tc.desc: Set search icon color while search icon is svg
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchIconColor001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    searchModelInstance.SetSearchIconColor(Color::RED);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);
}

/**
 * @tc.name: SetSearchIconColor002
 * @tc.desc: Set search icon color while search icon is not svg
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchIconColor002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("/common/icon.png");
    searchModelInstance.SetSearchIconColor(Color::RED);
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetSearchSrcPath001
 * @tc.desc: Set search icon src path and src is empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchSrcPath001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");
}

/**
 * @tc.name: SetSearchSrcPath002
 * @tc.desc: Set search icon src path and src is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchSrcPath002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetRightIconSrcPath001
 * @tc.desc: Set search icon src path and src is empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetRightIconSrcPath001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath("");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");
}

/**
 * @tc.name: SetRightIconSrcPath002
 * @tc.desc: Set search icon src path and src is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetRightIconSrcPath002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetCancelButtonStyle001
 * @tc.desc: Set cancel button style
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCancelButtonStyle001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INPUT);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INPUT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: SetCancelIconSize001
 * @tc.desc: Set cancel icon size/color/path
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCancelIconSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;

    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();

    searchModelInstance.SetCancelIconSize(14.0_vp);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonUDSize(), 14.0_vp);

    searchModelInstance.SetCancelIconColor(Color::RED);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);
    searchModelInstance.SetRightIconSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
    searchModelInstance.SetCancelIconColor(Color::RED);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);
}

/**
 * @tc.name: SetSearchButtonFontSize001
 * @tc.desc: Set search button font size and color
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchButtonFontSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontSize(14.0_vp);
    EXPECT_EQ(buttonLayoutProperty->GetFontSize(), 14.0_vp);
    searchModelInstance.SetSearchButtonFontColor(Color::RED);
    EXPECT_EQ(buttonLayoutProperty->GetFontColor(), Color::RED);
}

/**
 * @tc.name: SetTextColor001
 * @tc.desc: Set text color
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetTextColor001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    searchModelInstance.SetTextColor(Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetTextColor(), Color::RED);
}

/**
 * @tc.name: Create001
 * @tc.desc: Create
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Create001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;

    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, EMPTY_VALUE);
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    ASSERT_NE(frameNode, nullptr);
    searchModelInstance.CreateTextField(frameNode, PLACEHOLDER, EMPTY_VALUE, true);
    searchModelInstance.CreateImage(frameNode, SEARCH_SVG, true);
    searchModelInstance.CreateCancelImage(frameNode, true);
    searchModelInstance.CreateButton(frameNode, true);
    searchModelInstance.CreateCancelButton(frameNode, true);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFrameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    EXPECT_NE(buttonFrameNode, nullptr);
}

/**
 * @tc.name: SetPlaceholderColor001
 * @tc.desc: Set Placeholder Color
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetPlaceholderColor001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    searchModelInstance.SetPlaceholderColor(Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), Color::RED);
}

/**
 * @tc.name: SetPlaceholderFont001
 * @tc.desc: Set Placeholder Font
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetPlaceholderFont001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    Font font;
    searchModelInstance.SetPlaceholderFont(font);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);

    std::vector<std::string> fontFamilies { "Georgia", "Serif" };
    Font otherFont { FontWeight::W200, Dimension(12), OHOS::Ace::FontStyle::ITALIC, fontFamilies };
    searchModelInstance.SetPlaceholderFont(otherFont);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight(), FontWeight::W200);
}

/**
 * @tc.name: SetTextFont001
 * @tc.desc: Set Text Font
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetTextFont001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    Font font;
    searchModelInstance.SetTextFont(font);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);

    std::vector<std::string> fontFamilies { "Georgia", "Serif" };
    Font otherFont { FontWeight::W200, Dimension(12), OHOS::Ace::FontStyle::ITALIC, fontFamilies };
    searchModelInstance.SetTextFont(otherFont);
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);
}

/**
 * @tc.name: SetTextAlign001
 * @tc.desc: Set Text Align
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetTextAlign001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    searchModelInstance.SetTextAlign(OHOS::Ace::TextAlign::CENTER);
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), OHOS::Ace::TextAlign::CENTER);
    searchModelInstance.SetTextAlign(OHOS::Ace::TextAlign::CENTER);
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), OHOS::Ace::TextAlign::CENTER);
}

/**
 * @tc.name: SetCopyOption001
 * @tc.desc: Set Copy Option
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCopyOption001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    searchModelInstance.SetCopyOption(OHOS::Ace::CopyOptions::Local);
    EXPECT_EQ(textFieldLayoutProperty->GetCopyOptions(), OHOS::Ace::CopyOptions::Local);
}

/**
 * @tc.name: SetMenuOptionItems001
 * @tc.desc: Set Menu Option Items
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetMenuOptionItems001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::vector<MenuOptionsParam> menuOptionsParam;
    searchModelInstance.SetMenuOptionItems(std::move(menuOptionsParam));
}

/**
 * @tc.name: SetOnSubmit001
 * @tc.desc: Set On Submit
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetOnSubmit001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    searchModelInstance.SetOnSubmit([&](const std::string& title) {
        if (title == "SetOnSubmit") {
            std::vector<std::string> fontFamilies { "Georgia", "Serif" };
            Font otherFont { FontWeight::W200, Dimension(12), OHOS::Ace::FontStyle::ITALIC, fontFamilies };
            searchModelInstance.SetTextFont(otherFont);
            EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);
        }
    });
    eventHub->UpdateSubmitEvent("SetOnSubmit");
}

/**
 * @tc.name: SetOn001
 * @tc.desc: Set On
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetOn001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * SetOnCopy
     */
    searchModelInstance.SetOnCopy([](const std::string& title) {});
    eventHub->FireOnCopy("");
    /**
     * SetOnCut
     */
    searchModelInstance.SetOnCut([](const std::string& title) {});
    eventHub->FireOnCut("");
    /**
     * SetOnPaste
     */
    searchModelInstance.SetOnPaste([](const std::string& title) {});
    eventHub->FireOnPaste("");
    /**
     * SetOnPasteWithEvent
     */
    searchModelInstance.SetOnPasteWithEvent([](const std::string& title, NG::TextCommonEvent& event) {});
    TextCommonEvent event;
    eventHub->FireOnPasteWithEvent("", event);
}

/**
 * @tc.name: RequestKeyboardOnFocus001
 * @tc.desc: Request Keyboard On Focus
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, RequestKeyboardOnFocus001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    searchModelInstance.RequestKeyboardOnFocus(true);
    EXPECT_EQ(pattern->needToRequestKeyboardOnFocus_, true);
}

/**
 * @tc.name: AddChildToGroup001
 * @tc.desc: Add Child To Group
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, AddChildToGroup001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);

    auto searchNode = AceType::MakeRefPtr<SearchNode>(
        "Search", ViewStackProcessor::GetInstance()->ClaimNodeId(), AceType::MakeRefPtr<SearchPattern>());
    auto tempFrameNode = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    searchNode->AddChildToGroup(tempFrameNode, 1);
    searchNode->AddChildToGroup(tempFrameNode, 1);
}

/**
 * @tc.name: PaintMethodTest001
 * @tc.desc: GetContentDrawFunction, PaintSearch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PaintMethodTest001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), true);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);

    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: PaintMethodTest002
 * @tc.desc: GetContentDrawFunction, PaintSearch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PaintMethodTest002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), false);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: PaintMethodTest003
 * @tc.desc: GetContentDrawFunction, PaintSearch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PaintMethodTest003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->UpdatePaddingWithBorder(PaddingPropertyF({ 0.0f, 0.0f, 10.0f, 0.0f }));
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), true);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);

    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: PaintMethodTest004
 * @tc.desc: GetContentDrawFunction, PaintSearch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PaintMethodTest004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->UpdatePaddingWithBorder(PaddingPropertyF({ 0.0f, 0.0f, 0.0f, 20.0f }));
    geometryNode->SetFrameSize(SizeF(200.0f, 60.0f));
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas rsCanvas;
    auto searchPaintMethod = AceType::MakeRefPtr<SearchPaintMethod>(SizeF(80, 20), std::string("search"), true);
    auto canvasDrawFunction = searchPaintMethod->GetContentDrawFunction(paintWrapper);
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(2);
    EXPECT_CALL(rsCanvas, Restore()).Times(2);
    canvasDrawFunction(rsCanvas);

    paintWrapper->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF({ 0.0f, 0.0f, 20.0f, 0.0f }));
    auto canvasDrawFunction2 = searchPaintMethod->GetContentDrawFunction(paintWrapper);
    canvasDrawFunction2(rsCanvas);
}

/**
 * @tc.name: SearchChangeEventHub001
 * @tc.desc: SearchEventHub
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchChangeEventHub001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ChangeAndSubmitEvent changeEvent = [](const std::string str) {};
    searchModelInstance.SetOnChangeEvent(changeEvent);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    eventHub->UpdateChangeEvent("");
    ASSERT_EQ(eventHub->onValueChangeEvent_, nullptr);
    eventHub->onValueChangeEvent_ = nullptr;
    eventHub->UpdateChangeEvent("");
    EXPECT_EQ(eventHub->onValueChangeEvent_, nullptr);
}

/**
 * @tc.name: Pattern009
 * @tc.desc: test InitButtonAndImageClickEvent, buttonClickListener_ already exist
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern009, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.step: step2. Reset pattern->imageClickListener_.
     * @tc.expected: pattern->imageClickListener_ is nullptr.
     */
    pattern->imageClickListener_.Reset();
    EXPECT_EQ(pattern->imageClickListener_, nullptr);
    pattern->InitButtonAndImageClickEvent();
    EXPECT_EQ(pattern->GetMaxLength(), 1000000); // Not set maxLength
    searchModelInstance.SetMaxLength(19);
    EXPECT_EQ(pattern->GetMaxLength(), 19);
    searchModelInstance.SetMaxLength(0);
    EXPECT_EQ(pattern->GetMaxLength(), 0); // Set maxLength = 0
    searchModelInstance.ResetMaxLength();
    EXPECT_EQ(pattern->GetMaxLength(), 1000000);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_ENTER, keyEvent.action = KeyAction::UP;
    pattern->OnKeyEvent(keyEvent);
    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT, keyEvent.action = KeyAction::DOWN;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);
}

/**
 * @tc.name: Pattern011
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern011, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_1;
    pattern->OnKeyEvent(keyEvent);

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT, keyEvent.action = KeyAction::DOWN;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern013
 * @tc.desc: test InitFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern013, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    /**
     * @tc.step: step2. call onFocusInternal_().
     */
    focusHub->onFocusInternal_();
    /**
     * @tc.step: step3. call onBlurInternal_().
     * @tc.expected: selectionMode_ = SelectionMode::NONE.
     */
    focusHub->onBlurInternal_();
    EXPECT_EQ(textFieldPattern->selectionMode_, SelectionMode::NONE);
    GestureEvent gestureEvent;
    pattern->clickListener_->GetGestureEventFunc()(gestureEvent);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test Oncolorconfigurationupdate
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern014, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnColorConfigurationUpdate();
    ASSERT_NE(pattern->cancelButtonNode_, nullptr);
    auto textFieldLayoutProperty = pattern->textField_->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), Color::RED);
    auto cancelButtonTextNode = AceType::DynamicCast<FrameNode>(pattern->cancelButtonNode_->GetChildren().front());
    ASSERT_NE(cancelButtonTextNode, nullptr);
    auto cancelButtonTextLayout = cancelButtonTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(cancelButtonTextLayout, nullptr);
    EXPECT_EQ(cancelButtonTextLayout->GetTextColor(), Color::RED);
}

/**
 * @tc.name: Pattern015
 * @tc.desc: test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern015, TestSize.Level1)
{
    /**
     * @tc.step: step1. Get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test whether search need soft keyboard.
     */
    EXPECT_TRUE(pattern->NeedSoftKeyboard());
}

/**
 * @tc.name: MaxLength001
 * @tc.desc: test search maxLength
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, MaxLength001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();

    /**
     * @tc.step: step2. test  default maxLength.
     */
    EXPECT_EQ(pattern->GetMaxLength(), 1000000);

    /**
     * @tc.step: step3.  set maxLength 5.
     */
    searchModelInstance.SetMaxLength(5);
    TextEditingValue value;
    TextSelection selection;
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    textFieldPattern->UpdateEditingValue(std::make_shared<TextEditingValue>(value));

    /**
     * @tc.step: step2. test maxLength
     */
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->GetTextValue().compare("12345"), 0);
    EXPECT_EQ(pattern->GetMaxLength(), 5);

    /**
     * @tc.step: step4. set maxLength 0.
     */
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    textFieldPattern->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    searchModelInstance.SetMaxLength(0);
    frameNode->MarkModifyDone();
    EXPECT_EQ(pattern->GetMaxLength(), 0);

    /**
     * @tc.step: step5. Reset maxLength.
     */
    searchModelInstance.ResetMaxLength();
    frameNode->MarkModifyDone();
    EXPECT_EQ(pattern->GetMaxLength(), 1000000);

    /**
     * @tc.step: step6. Set maxLength -1.
     */
    value.text = "1234567890";
    selection.baseOffset = value.text.length();
    value.selection = selection;
    textFieldPattern->UpdateEditingValue(std::make_shared<TextEditingValue>(value));
    searchModelInstance.SetMaxLength(-1);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->GetTextValue().compare("1234567890"), 0);
    EXPECT_EQ(pattern->GetMaxLength(), -1);

    /**
     * @tc.step: step7. Set maxLength 1000012.
     */
    searchModelInstance.SetMaxLength(1000012);
    frameNode->MarkModifyDone();
    EXPECT_EQ(pattern->GetMaxLength(), 1000012);
}

/**
 * @tc.name: CopyOption001
 * @tc.desc: test search CopyOption
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, CopyOption001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and textFieldPattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();

    /**
     * @tc.step: step2. Set CopyOption
     */
    searchModelInstance.SetCopyOption(CopyOptions::Distributed);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->AllowCopy(), true);
    EXPECT_EQ(textFieldPattern->GetCopyOptionString(), "CopyOptions.Distributed");

    /**
     * @tc.step: step3. Set CopyOption
     */
    searchModelInstance.SetCopyOption(CopyOptions::Local);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->AllowCopy(), true);
    EXPECT_EQ(textFieldPattern->GetCopyOptionString(), "CopyOptions.Local");

    /**
     * @tc.step: step4. Set CopyOption
     */
    searchModelInstance.SetCopyOption(CopyOptions::InApp);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->AllowCopy(), true);
    EXPECT_EQ(textFieldPattern->GetCopyOptionString(), "CopyOptions.InApp");

    /**
     * @tc.step: step5. Set CopyOption
     */
    searchModelInstance.SetCopyOption(CopyOptions::None);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->AllowCopy(), false);
    EXPECT_EQ(textFieldPattern->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: testType001
 * @tc.desc: test search type
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testType001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and LayoutProperty.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::BEGIN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::BEGIN);

    /**
     * @tc.step: step3. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::UNSPECIFIED);

    /**
     * @tc.step: step4. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::TEXT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::TEXT);

    /**
     * @tc.step: step5. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::MULTILINE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::MULTILINE);

    /**
     * @tc.step: step6. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::NUMBER);

    /**
     * @tc.step: step7. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::PHONE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::PHONE);

    /**
     * @tc.step: step8. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::DATETIME);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::DATETIME);

    /**
     * @tc.step: step9. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::EMAIL_ADDRESS);

    /**
     * @tc.step: step10. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::URL);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::URL);

    /**
     * @tc.step: step11. Set type
     */
    textFieldLayoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType(), TextInputType::VISIBLE_PASSWORD);
}

/**
 * @tc.name: testSelectionMenuHidden001
 * @tc.desc: test search selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testSelectionMenuHidden001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and textFieldLayoutProperty.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2. Set selectionMenuHidden
     */
    textFieldLayoutProperty->UpdateSelectionMenuHidden(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden(), false);

    /**
     * @tc.step: step3. Set selectionMenuHidden
     */
    textFieldLayoutProperty->UpdateSelectionMenuHidden(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden(), true);
}


/**
 * @tc.name: testEnableKeyboardOnFocus001
 * @tc.desc: test search EnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testEnableKeyboardOnFocus001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and textFieldPattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();

    /**
     * @tc.step: step2. Set enableKeyboardOnFocus
     */
    textFieldPattern->SetNeedToRequestKeyboardOnFocus(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->needToRequestKeyboardOnFocus_, true);

    /**
     * @tc.step: step3. Set enableKeyboardOnFocus
     */
    textFieldPattern->SetNeedToRequestKeyboardOnFocus(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldPattern->needToRequestKeyboardOnFocus_, false);
}

/**
 * @tc.name: testCaretStyle001
 * @tc.desc: test search caretStyle
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testCaretStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set caretStyle
     */
    searchModelInstance.SetCaretWidth(Dimension(2.5, DimensionUnit::VP));
    searchModelInstance.SetCaretColor(Color::BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetCursorWidth().value().Value(), 2.5);
    EXPECT_EQ(paintProperty->GetCursorColor(), Color::BLUE);
}

/**
 * @tc.name: testFontColor001
 * @tc.desc: test search fontColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testFontColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2. Set fontColor
     */
    searchModelInstance.SetTextColor(Color::BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetTextColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set fontColor
     */
    searchModelInstance.SetTextColor(Color::RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetTextColor(), Color::RED);
}

/**
 * @tc.name: testTextAlign001
 * @tc.desc: test search textAlign
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testTextAlign001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and textFieldLayoutProperty.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.step: step2. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::LEFT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::LEFT);

    /**
     * @tc.step: step3. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::RIGHT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::RIGHT);

    /**
     * @tc.step: step4. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::CENTER);

    /**
     * @tc.step: step5. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::JUSTIFY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::JUSTIFY);

    /**
     * @tc.step: step6. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::START);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::START);

    /**
     * @tc.step: step7. Set textAlign
     */
    textFieldLayoutProperty->UpdateTextAlign(TextAlign::END);
    frameNode->MarkModifyDone();
    EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), TextAlign::END);
}

/**
 * @tc.name: testCancelButton001
 * @tc.desc: test search cancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testCancelButton001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buttonHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    auto cancelButtonRenderContext = buttonHost->GetRenderContext();
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();

    /**
     * @tc.step: step2. Set cancelButton
     */
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
    EXPECT_EQ(cancelButtonRenderContext->GetOpacity(), 1.0);

    /**
     * @tc.step: step3. Set cancelButton
     */
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(cancelButtonRenderContext->GetOpacity(), 0.0);
}

/**
 * @tc.name: Pattern016
 * @tc.desc: test OnKeyEvent for arrow key presses and with text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern016, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("Text", 0);
    textFieldPattern->HandleOnSelectAll(true);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step4. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step5. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern017
 * @tc.desc: test OnKeyEvent for arrow key presses and without text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern017, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("", 0);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(0, 0);
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern018
 * @tc.desc: test OnKeyEvent for Tab/Shift+Tab key presses and with text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern018, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("Text", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step4. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step5. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern019
 * @tc.desc: test OnKeyEvent for Tab/Shift+Tab key presses and without text
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern019, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = true;
    pattern->cancelButtonSize_ = SizeF(0, 0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */

    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern020
 * @tc.desc: test OnKeyEvent for pressing Enter when the focus is at cancel button
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern020, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue("Text", 0);
    TimeStamp timeStamp;
    KeyEvent keyEvent(
        KeyCode::KEY_TAB, KeyAction::DOWN, { KeyCode::KEY_TAB }, 0, timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.step: step2. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::CANCEL_BUTTON.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->cancelButtonSize_ = SizeF(100.0, 50.0);
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.step: step3. call OnKeyEvent().
     * @tc.expected: focusChoice_ = FocusChoice::SEARCH.
     */
    keyEvent.code = KeyCode::KEY_ENTER, keyEvent.action = KeyAction::DOWN;
    pattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern021
 * @tc.desc: Test DragEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern021, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldEventHub = textFieldFrameNode->GetEventHub<EventHub>();
    pattern->ResetDragOption();

    /**
     * @tc.cases: case1.
     */
    eventHub->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->onDragStart_, nullptr);

    /**
     * @tc.cases: case2.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_ENTER, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragEnter_, nullptr);

    /**
     * @tc.cases: case3.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_LEAVE, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragLeave_, nullptr);

    /**
     * @tc.cases: case4.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_MOVE, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragMove_, nullptr);

    /**
     * @tc.cases: case5.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_DROP, [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDrop_, nullptr);

    /**
     * @tc.cases: case6.
     */
    eventHub->SetCustomerOnDragFunc(
        DragFuncType::DRAG_END, [](const RefPtr<OHOS::Ace::DragEvent>&){});
    pattern->InitTextFieldDragEvent();
    ASSERT_NE(textFieldEventHub->customerOnDragEnd_, nullptr);
}

/**
 * @tc.name: Pattern022
 * @tc.desc: Test key events with different focus
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern022, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    TimeStamp timeStamp;

    /**
     * @tc.cases: case1.
     */
    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_TAB;
    keyEventOne.action = KeyAction::UP;
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->OnKeyEvent(keyEventOne);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case2.
     */
    KeyEvent keyEventTwo(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = false;
    pattern->OnKeyEvent(keyEventTwo);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case3.
     */
    KeyEvent keyEventThree(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    pattern->cancelButtonSize_ = SizeF(100.0f, 0.0f);
    textFieldPattern->UpdateEditingValue("", 0);
    pattern->OnKeyEvent(keyEventThree);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case4.
     */
    KeyEvent keyEventFour(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN, {KeyCode::KEY_DPAD_RIGHT}, 0, timeStamp,
        0, 0, SourceType::KEYBOARD, {});
    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->OnKeyEvent(keyEventFour);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case5.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0f, 50.0f);
    pattern->OnKeyEvent(keyEventFour);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case6.
     */
    KeyEvent keyEventFive;
    keyEventFive.code = KeyCode::KEY_DPAD_LEFT;
    keyEventFive.action = KeyAction::DOWN;
    pattern->cancelButtonSize_ = SizeF(100.0f, 50.0f);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->OnKeyEvent(keyEventFive);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern023
 * @tc.desc: Test key events with column layout
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern023, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.step: step2. create column layout.
     */
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;
    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    columnFrameNode->AddChild(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto parentHub = focusHub->GetParentFocusHub();
    ASSERT_NE(parentHub, nullptr);

    /**
     * @tc.cases: case1.
     */
    TimeStamp timeStamp;
    KeyEvent keyEventShiftTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::CANCEL_BUTTON);

    /**
     * @tc.cases: case2.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventShiftTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case3.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::CANCEL_BUTTON;
    pattern->cancelButtonSize_ = SizeF(100.0f, 0.0f);
    KeyEvent keyEventTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    pattern->OnKeyEvent(keyEventTab);
}

/**
 * @tc.name: Pattern024
 * @tc.desc: Test key events in different scenarios
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern024, TestSize.Level1)
{
    /**
     * @tc.step: step1. get frameNode and pattern.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.step: step2. create key events.
     */
    TimeStamp timeStamp;
    KeyEvent keyEventTab(KeyCode::KEY_TAB, KeyAction::DOWN, {KeyCode::KEY_TAB}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventDpadRight(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN, {KeyCode::KEY_DPAD_RIGHT}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});
    KeyEvent keyEventNumsEight(KeyCode::KEY_8, KeyAction::DOWN, {KeyCode::KEY_8}, 0,
        timeStamp, 0, 0, SourceType::KEYBOARD, {});

    /**
     * @tc.cases: case1.
     */
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->OnKeyEvent(keyEventTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case2.
     */
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    columnFrameNode->AddChild(frameNode);
    pattern->focusChoice_ = SearchPattern::FocusChoice::SEARCH_BUTTON;
    pattern->isSearchButtonEnabled_ = true;
    pattern->OnKeyEvent(keyEventDpadRight);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH_BUTTON);

    /**
     * @tc.cases: case3.
     */
    pattern->OnKeyEvent(keyEventTab);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);

    /**
     * @tc.cases: case4.
     */
    pattern->OnKeyEvent(keyEventNumsEight);
    EXPECT_EQ(pattern->focusChoice_, SearchPattern::FocusChoice::SEARCH);
}

/**
 * @tc.name: Pattern025
 * @tc.desc: InitButtonTouchEvent ColorMode = DARK
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern025, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));

    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(events.size(), 0);
    SystemProperties::SetColorMode(ColorMode::DARK);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: Pattern026
 * @tc.desc: Test SearchController init
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Pattern026, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue("", 0);

    pattern->InitSearchController();
    pattern->searchController_->getTextContentRect_();
    RectF textRect = textFieldPattern->GetTextRect();
    EXPECT_EQ(textRect, RectF(0, 0, 0, 0));

    pattern->searchController_->getTextContentLinesNum_();
    auto textFieldController = textFieldPattern->GetTextFieldController();
    int32_t contentLines = textFieldController->GetTextContentLinesNum();
    EXPECT_EQ(contentLines, 0);

    pattern->searchController_->getCaretIndex_();
    int32_t caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 0);

    pattern->searchController_->getCaretPosition_();
    auto caretPosition = textFieldController->GetCaretPosition();
    EXPECT_EQ(caretPosition, OffsetF(0, 0));

    textFieldPattern->UpdateEditingValue("Text", 0);
    pattern->searchController_->stopEditing_();
    caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 0);
}

/**
 * @tc.name: UpdateChangeEvent001
 * @tc.desc: test search UpdateChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, UpdateChangeEvent001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    eventHub->onValueChangeEvent_ = [](const std::string str) {};
    eventHub->changeEvent_ = [](const std::string str) {};
    eventHub->UpdateChangeEvent("");
}

/**
 * @tc.name: PackInnerRecognizer001
 * @tc.desc: test search PackInnerRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, PackInnerRecognizerr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SearchGestureEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto searchgestureEventHub = AceType::MakeRefPtr<SearchGestureEventHub>(eventHub);
    EXPECT_TRUE(searchgestureEventHub);

    Offset offset;
    std::list<RefPtr<NGGestureRecognizer>> innerRecognizers;
    int32_t touchId = 0;
    RefPtr<TargetComponent> targetComponent;
    searchgestureEventHub->innerParallelRecognizer_ = nullptr;
    searchgestureEventHub->CheckClickActuator();
    auto clickEventActuator = searchgestureEventHub->GetUserClickEventActuator();
    GestureEventFunc callback = [](GestureEvent& info) {};
    clickEventActuator->SetUserCallback(std::move(callback));
    searchgestureEventHub->PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
    searchgestureEventHub->PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
}

/**
 * @tc.name: SetHeight001
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetProperty001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto eventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    //test SetHeight
    searchModelInstance.SetHeight(Dimension(2.5, DimensionUnit::VP));

    //test SetOnChange
    searchModelInstance.SetOnChange([](const std::string str) {});
    EXPECT_NE(eventHub->GetOnChange(), nullptr);

    //test SetOnTextSelectionChange
    searchModelInstance.SetOnTextSelectionChange([](int32_t a, int32_t b) {});
    EXPECT_NE(eventHub->onSelectionChange_, nullptr);

    //test SetOnScroll
    searchModelInstance.SetOnScroll([](float a, float b) {});
    EXPECT_NE(eventHub->onScrollChangeEvent_, nullptr);

    //test SetSelectionMenuHidden
    searchModelInstance.SetSelectionMenuHidden(true);
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden().value(), true);

    //test SetOnCut
    searchModelInstance.SetOnCut([](const std::string str) {});
    EXPECT_NE(eventHub->onCut_, nullptr);

    //test SetCustomKeyboard
    searchModelInstance.SetCustomKeyboard([]() {});
    EXPECT_NE(pattern->customKeyboardBuilder_, nullptr);

    //test SetType
    searchModelInstance.SetType(TextInputType::BEGIN);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::BEGIN);
    searchModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(textFieldLayoutProperty->GetTextInputType().value(), TextInputType::TEXT);
}

/**
 * @tc.name: SetHeight002
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetProperty002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    //test RequestKeyboardOnFocus
    searchModelInstance.RequestKeyboardOnFocus(frameNode, true);
    EXPECT_EQ(pattern->needToRequestKeyboardOnFocus_, true);

    //test SetPlaceholderFont
    Font font;
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    searchModelInstance.SetPlaceholderFont(frameNode, font);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight(), FontWeight::W200);

    //test SetSearchIconSize
    auto searchLayoutProperty = fNode->GetLayoutProperty<SearchLayoutProperty>();
    searchModelInstance.SetSearchIconSize(frameNode, Dimension(2.5, DimensionUnit::VP));
    EXPECT_EQ(searchLayoutProperty->GetSearchIconUDSize(), 2.5_vp);

    //test SetSearchSrcPath
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath(frameNode, EMPTY_VALUE);
    searchModelInstance.SetSearchSrcPath(frameNode, "/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");

    //test SetSearchIconColor
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    ImageSourceInfo imageSourceInfo("", Dimension(-1), Dimension(-1), InternalResource::ResourceId::CORRECT_SVG);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    searchModelInstance.SetSearchIconColor(frameNode, Color::RED);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);

    //test SetSearchButton
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(searchButtonRenderContext);
    searchModelInstance.SetSearchButton(frameNode, EMPTY_VALUE);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 0.0);
    searchModelInstance.SetSearchButton(frameNode, PLACEHOLDER);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 1.0);

    //test SetSearchButtonFontSize
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontSize(frameNode, 14.0_vp);
    EXPECT_EQ(buttonLayoutProperty->GetFontSize(), 14.0_vp);

    //test SetTextColor
    searchModelInstance.SetTextColor(frameNode, Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetTextColor(), Color::RED);
}

/**
 * @tc.name: SetHeight003
 * @tc.desc: test search
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetProperty003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto fNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    FrameNode* frameNode = &(*fNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(fNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    //test SetSearchButtonFontColor
    auto buttonFNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(BUTTON_INDEX));
    auto bnLayoutProperty = buttonFNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontColor(frameNode, Color::RED);
    EXPECT_EQ(bnLayoutProperty->GetFontColor(), Color::RED);

    //test SetCopyOption
    searchModelInstance.SetCopyOption(frameNode, CopyOptions::Distributed);
    EXPECT_EQ(textFieldLayoutProperty->GetCopyOptions(), OHOS::Ace::CopyOptions::Distributed);

    //test SetTextFont
    Font font;
    font.fontSize = Dimension(2);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W200;
    std::vector<std::string> families = { "cursive" };
    font.fontFamilies = families;
    searchModelInstance.SetTextFont(frameNode, font);
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);

    //test SetPlaceholderColor
    searchModelInstance.SetPlaceholderColor(frameNode, Color::RED);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), Color::RED);

    //test SetSelectionMenuHidden
    searchModelInstance.SetSelectionMenuHidden(frameNode, true);
    EXPECT_EQ(textFieldLayoutProperty->GetSelectionMenuHidden(), true);

    //test SetCaretWidth
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    searchModelInstance.SetCaretWidth(frameNode, Dimension(2.5, DimensionUnit::VP));
    EXPECT_EQ(paintProperty->GetCursorWidth().value().Value(), 2.5);

    //test SetCaretColor
    searchModelInstance.SetCaretColor(frameNode, Color::BLUE);
    searchModelInstance.SetTextAlign(frameNode, TextAlign::CENTER);

    //test SetCancelButtonStyle
    searchModelInstance.SetCancelButtonStyle(frameNode, CancelButtonStyle::CONSTANT);
    fNode->MarkModifyDone();
    auto searchLayoutProperty = fNode->GetLayoutProperty<SearchLayoutProperty>();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);
    searchModelInstance.SetCancelButtonStyle(frameNode, CancelButtonStyle::INVISIBLE);
    fNode->MarkModifyDone();
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);

    //test SetCancelIconSize
    searchModelInstance.SetCancelIconSize(frameNode, 14.0_vp);
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonUDSize(), 14.0_vp);

    //test SetCancelIconColor
    auto imageFNode = AceType::DynamicCast<FrameNode>(fNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageRProperty = imageFNode->GetPaintProperty<ImageRenderProperty>();
    searchModelInstance.SetCancelIconColor(frameNode, Color::RED);
    EXPECT_EQ(imageRProperty->GetSvgFillColor(), Color::RED);

    //test SetRightIconSrcPath
    auto cancelImageLayoutProperty = imageFNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath(frameNode, PLACEHOLDER);
    searchModelInstance.SetRightIconSrcPath(frameNode, "");
    ASSERT_STREQ(cancelImageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");
}
} // namespace OHOS::Ace::NG
