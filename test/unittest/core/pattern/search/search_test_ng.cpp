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
#include "search_base.h"
#include "ui/base/geometry/dimension.h"
#include "ui/properties/color.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"

namespace OHOS::Ace::NG {

namespace {
const Color STROKE_COLOR_VALUE_0 = Color::FromRGB(255, 100, 100);
const Color STORKE_COLOR_VALUE_1 = Color::FromRGB(255, 255, 100);
} // namespace

class SearchTestNg : public SearchBases {
public:
};

/**
 * @tc.name: Measure001
 * @tc.desc: Measure and layout
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, Measure001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());

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
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    pattern->UpdateChangeEvent(u"");
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
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INPUT);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INPUT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    pattern->UpdateChangeEvent(u"");
    pattern->ToJsonValue(json, filter);
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
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.step: step3. call OnColorConfigurationUpdate.
     * @tc.expected: cover branch cancelButtonNode_、buttonNode_ and textField_ not null and call
     * OnColorConfigurationUpdate.
     */
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->cancelButtonNode_.Upgrade());
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
    EXPECT_EQ(pattern->cancelButtonNode_.Upgrade(), nullptr);
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
    auto textFieldPattern = textFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->InitDragEvent();
    NG::DragPreviewOption option { false };
    searchModelInstance.SetDragPreviewOptions(option);
    searchModelInstance.SetCaretWidth(14.0_vp);
    searchModelInstance.SetCaretColor(Color::RED);
    EXPECT_EQ(textPaintProperty->GetCursorWidth()->Value(), 14);
    EXPECT_EQ(textPaintProperty->GetCursorColor(), Color::RED);
    searchModelInstance.SetBackBorderRadius();
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
    std::string bundleName = "";
    std::string moduleName = "";
    searchModelInstance.SetSearchSrcPath("/common/icon.png", bundleName, moduleName);
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
    std::string bundleName = "";
    std::string moduleName = "";
    searchModelInstance.SetSearchSrcPath("", bundleName, moduleName);
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
    std::string bundleName = "";
    std::string moduleName = "";
    searchModelInstance.SetSearchSrcPath("/common/icon.png", bundleName, moduleName);
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetSearchImageIcon001
 * @tc.desc: Set search image icon
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchImageIcon001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    NG::IconOptions iconOptions = NG::IconOptions(Color::RED, 14.0_vp, "/common/icon.png", "", "");
    searchModelInstance.SetSearchImageIcon(iconOptions);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
    EXPECT_EQ(searchLayoutProperty->GetSearchIconUDSize(), 14.0_vp);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);
}

/**
 * @tc.name: SetSearchIconSymbolGlyphModofier001
 * @tc.desc: Set search icon symbolGlyphModifier is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchIconSymbolGlyphModofier001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    SearchModelNG searchModelInstance;
    searchModelInstance.SetSearchSymbolIcon(onApply);
    auto search = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(search, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    ASSERT_NE(searchTheme, nullptr);

    auto searchLayoutProperty = search->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    ASSERT_NE(searchLayoutProperty->GetSearchIconSymbol(), nullptr);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(search->GetChildAtIndex(IMAGE_INDEX));
    EXPECT_TRUE(iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    auto symbolLayoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolLayoutProperty, nullptr);

    const std::unique_ptr<FontStyle>& symbolStyle = symbolLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    EXPECT_EQ(symbolStyle->GetFontSize(), Dimension(16, DimensionUnit::FP));
    std::vector<Color> color = { searchTheme->GetSymbolIconColor() };
    EXPECT_EQ(symbolStyle->GetSymbolColorList(), color);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
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

    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
 * @tc.name: SetCancelImageIcon001
 * @tc.desc: Set cancel image icon
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCancelImageIcon001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    NG::IconOptions iconOptions = NG::IconOptions(Color::RED, 14.0_vp, "/common/icon.png", "", "");
    searchModelInstance.SetCancelImageIcon(iconOptions);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
    EXPECT_EQ(searchLayoutProperty->GetCancelButtonUDSize(), 14.0_vp);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor(), Color::RED);
}

/**
 * @tc.name: SetCancelIconSymbolGlyphModofier001
 * @tc.desc: Set cancel icon symbolGlyphModifier is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetCancelIconSymbolGlyphModofier001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelSymbolIcon(onApply);
    auto search = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(search, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    ASSERT_NE(searchTheme, nullptr);

    auto searchLayoutProperty = search->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    ASSERT_NE(searchLayoutProperty->GetCancelIconSymbol(), nullptr);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(search->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    EXPECT_TRUE(iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    auto symbolLayoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolLayoutProperty, nullptr);

    const std::unique_ptr<FontStyle>& symbolStyle = symbolLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    EXPECT_EQ(symbolStyle->GetFontSize(), Dimension(16, DimensionUnit::FP));
    std::vector<Color> color = { searchTheme->GetSymbolIconColor() };
    EXPECT_EQ(symbolStyle->GetSymbolColorList(), color);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
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
 * @tc.name: SetSearchButtonAutodisable001
 * @tc.desc: Set search button autodisable
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchButtonAutodisable001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonAutoDisable(true);
    EXPECT_EQ(buttonLayoutProperty->GetAutoDisableValue(), true);
}

/**
 * @tc.name: SetSearchButtonAutodisable002
 * @tc.desc: Set search button autodisable
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchButtonAutodisable002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    searchModelInstance.SetSearchButtonAutoDisable(true);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);

    auto textStr = "";
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->UpdateEditingValue(textStr, 0);
    auto buttonEventHub = buttonFrameNode->GetOrCreateEventHub<ButtonEventHub>();
    ASSERT_NE(buttonEventHub, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateDisable(textFieldPattern->GetTextUtf16Value());
    EXPECT_EQ(buttonEventHub->IsEnabled(), false);
}

/**
 * @tc.name: SetSearchButtonAutodisable003
 * @tc.desc: Set search button autodisable
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchButtonAutodisable003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonAutoDisable(false);
    EXPECT_EQ(buttonLayoutProperty->GetAutoDisableValue(), false);
}

/**
 * @tc.name: SetSearchButtonAutodisable004
 * @tc.desc: Set search button autodisable
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchButtonAutodisable004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonEventHub = buttonFrameNode->GetOrCreateEventHub<ButtonEventHub>();
    ASSERT_NE(buttonEventHub, nullptr);

    auto textStr = "a";
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->UpdateEditingValue(textStr, 0);
    searchModelInstance.SetSearchButtonAutoDisable(true);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateDisable(textFieldPattern->GetTextUtf16Value());
    EXPECT_EQ(buttonEventHub->IsEnabled(), true);
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
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    SearchModelNG searchModelInstance;

    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = frameNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);

    ASSERT_NE(frameNode, nullptr);
    searchModelInstance.CreateTextField(frameNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true);
    pattern->CreateSearchIcon(SEARCH_SVG);
    pattern->CreateCancelIcon();
    searchModelInstance.CreateButton(frameNode, true);
    searchModelInstance.CreateCancelButton(frameNode, true);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFrameNode, nullptr);
    auto searchIconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(searchIconFrameNode, nullptr);
    EXPECT_EQ(searchIconFrameNode->GetTag(), V2::SYMBOL_ETS_TAG);
    auto cancelIconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelIconFrameNode, nullptr);
    EXPECT_EQ(cancelIconFrameNode->GetTag(), V2::SYMBOL_ETS_TAG);
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    EXPECT_NE(buttonFrameNode, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
* @tc.name: Create002
* @tc.desc: check search api available
* @tc.type: FUNC
*/
HWTEST_F(SearchTestNg, Create002, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto searchNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = searchNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(pattern);
    ASSERT_NE(searchNode, nullptr);
    searchModelInstance.CreateTextField(searchNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true);
    searchModelInstance.SetMaxFontScale(2.0);
    searchModelInstance.CreateTextField(searchNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true);
    searchModelInstance.CreateDivider(searchNode, true);
    pattern->CreateSearchIcon(SEARCH_SVG);
    pattern->CreateCancelIcon();
    searchModelInstance.CreateButton(searchNode, true);
    searchModelInstance.CreateCancelButton(searchNode, true);
    SearchModelNG::CreateFrameNode(-1);
    searchModelInstance.SetEnableHapticFeedback(true);
    searchModelInstance.SetKeyboardAppearance(OHOS::Ace::KeyboardAppearance::NONE_IMMERSIVE);
    searchModelInstance.SetSearchButton("");
    searchModelInstance.SetCancelDefaultIcon();
    searchModelInstance.SetBackBorderRadius();
    OHOS::Ace::NG::SearchModelNG::SetInputFilter(frameNode, NUM_FILTER, nullptr);
    OHOS::Ace::NG::SearchModelNG::SetTextIndent(frameNode, Dimension());
    OHOS::Ace::NG::SearchModelNG::SetTextValue(frameNode, "1");
    OHOS::Ace::NG::SearchModelNG::SetCaretPosition(frameNode, 0);
    OHOS::Ace::NG::SearchModelNG::SetSearchButtonAutoDisable(frameNode, true);
    NG::IconOptions iconOptions = NG::IconOptions(Color::RED, 14.0_vp, "/common/icon.png", "", "");
    OHOS::Ace::NG::SearchModelNG::SetCancelImageIcon(frameNode, iconOptions);
    OHOS::Ace::NG::SearchModelNG::SetMinFontScale(frameNode, 0.5f);
    OHOS::Ace::NG::SearchModelNG::SetMaxFontScale(frameNode, 2.0f);
    OHOS::Ace::NG::SearchModelNG::SetHalfLeading(frameNode, false);
    OHOS::Ace::NG::SearchModelNG::SetSelectedBackgroundColor(frameNode, Color());
    OHOS::Ace::NG::SearchModelNG::ResetMaxLength(frameNode);
    OHOS::Ace::NG::SearchModelNG::SetMaxLength(frameNode, 100);
    OHOS::Ace::NG::SearchModelNG::SetShowCounter(frameNode, false);
    OHOS::Ace::NG::SearchModelNG::SetCounterType(frameNode, 0);
    OHOS::Ace::NG::SearchModelNG::SetShowCounterBorder(frameNode, false);
    OHOS::Ace::NG::SearchModelNG::SetEnableHapticFeedback(frameNode, true);
    OHOS::Ace::NG::SearchModelNG::SetStopBackPress(frameNode, true);
    OHOS::Ace::NG::SearchModelNG::SetKeyboardAppearance(frameNode, OHOS::Ace::KeyboardAppearance::NONE_IMMERSIVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
* @tc.name: Create003
* @tc.desc: check search api available
* @tc.type: FUNC
*/
HWTEST_F(SearchTestNg, Create003, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto searchNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    searchModelInstance.CreateTextField(searchNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true);
    std::function<void(bool)> onEditChangefunc;
    std::function<void(const ChangeValueInfo&)> onChange;
    std::function<void(const std::u16string&)> onCut;
    std::function<void(const std::u16string&)> onPaste;
    std::function<bool(const ChangeValueInfo&)> onWillChange;
    std::function<bool(const InsertValueInfo&)> onWillInsert;
    std::function<bool(const InsertValueInfo&)> onDidInsert;
    std::function<bool(const DeleteValueInfo&)> onWillDelete;
    std::function<bool(const DeleteValueInfo&)> onDidDelete;
    std::function<void(const std::u16string&)> onChangeEvent;
    NG::OnCreateMenuCallback onCreate;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepare;
    searchModelInstance.SetOnEditChanged(std::move(onEditChangefunc));
    searchModelInstance.SetOnChange(std::move(onChange));
    searchModelInstance.SetOnCut(std::move(onCut));
    searchModelInstance.SetOnPaste(std::move(onPaste));
    searchModelInstance.SetOnWillChangeEvent(std::move(onWillChange));
    searchModelInstance.SetOnWillInsertValueEvent(std::move(onWillInsert));
    searchModelInstance.SetOnDidInsertValueEvent(std::move(onDidInsert));
    searchModelInstance.SetOnWillDeleteEvent(std::move(onWillDelete));
    searchModelInstance.SetOnDidDeleteEvent(std::move(onDidDelete));
    searchModelInstance.SetOnChangeEvent(std::move(onChangeEvent));
    searchModelInstance.SetSelectionMenuOptions(std::move(onCreate), std::move(onMenuItemClick), std::move(onPrepare));
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto eventHub = searchTextField->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ChangeValueInfo changeValueInfo;
    changeValueInfo.value = u"123";
    changeValueInfo.previewText.offset = -1;
    changeValueInfo.previewText.value = u"456";
    InsertValueInfo insertValueInfo;
    DeleteValueInfo deleteValueInfo;
    eventHub->FireOnChange(changeValueInfo);
    eventHub->FireOnCut(u"123");
    eventHub->FireOnPaste(u"123");
    eventHub->FireOnWillChangeEvent(changeValueInfo);
    eventHub->FireOnWillInsertValueEvent(insertValueInfo);
    eventHub->FireOnDidInsertValueEvent(insertValueInfo);
    eventHub->FireOnWillDeleteEvent(deleteValueInfo);
    eventHub->FireOnDidDeleteValueEvent(deleteValueInfo);
}

/**
* @tc.name: Create004
* @tc.desc: check search modifier api available
* @tc.type: FUNC
*/
HWTEST_F(SearchTestNg, Create004, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto searchNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(searchNode, nullptr);
    searchModelInstance.CreateTextField(searchNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true);
    std::function<void(bool)> onEditChangefunc;
    std::function<void(const ChangeValueInfo&)> onChange;
    std::function<void(const std::u16string&)> onCut;
    std::function<void(const std::u16string&)> onPaste;
    std::function<bool(const ChangeValueInfo&)> onWillChange;
    std::function<bool(const InsertValueInfo&)> onWillInsert;
    std::function<bool(const InsertValueInfo&)> onDidInsert;
    std::function<bool(const DeleteValueInfo&)> onWillDelete;
    std::function<bool(const DeleteValueInfo&)> onDidDelete;
    std::function<void(const std::u16string&)> onChangeEvent;
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    OHOS::Ace::NG::SearchModelNG::SetOnEditChange(frameNode, std::move(onEditChangefunc));
    std::function<void(float, float)> onContentScroll;
    OHOS::Ace::NG::SearchModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
    OHOS::Ace::NG::SearchModelNG::SetShowCounter(frameNode, false);
    OHOS::Ace::NG::SearchModelNG::SetCounterType(frameNode, 0);
    OHOS::Ace::NG::SearchModelNG::SetShowCounterBorder(frameNode, false);
    OHOS::Ace::NG::SearchModelNG::SetOnWillChangeEvent(frameNode, std::move(onWillChange));
    OHOS::Ace::NG::SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
    OHOS::Ace::NG::SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
    OHOS::Ace::NG::SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
    OHOS::Ace::NG::SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
    OHOS::Ace::NG::SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    OHOS::Ace::NG::SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClickCallback));
    std::function<void(const std::u16string&, NG::TextCommonEvent&)> onPasteEvent;
    searchModelInstance.SetOnPasteWithEvent(std::move(onPasteEvent));
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto eventHub = searchTextField->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextCommonEvent event;
    eventHub->FireOnPasteWithEvent(u"", event);
}

/**
* @tc.name: Create005
* @tc.desc: check search modifier api available
* @tc.type: FUNC
*/
HWTEST_F(SearchTestNg, Create005, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(99);
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    searchModelInstance.CreateSearchNode(nodeId, u"", u"", "");
    searchModelInstance.CreateSearchNode(nodeId, u"", u"", "");
    auto searchNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(searchNode, nullptr);
    searchModelInstance.SetMaxFontScale(2.0);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetHasPreviewTextOption(true);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    ASSERT_NE(searchTheme, nullptr);
    searchModelInstance.CreateTextField(searchNode, PLACEHOLDER_U16, EMPTY_VALUE_U16, true, searchTheme);
    searchModelInstance.SetSearchButton("");
    OHOS::Ace::NG::SearchModelNG::SetId(frameNode, "12345");
    OHOS::Ace::NG::SearchModelNG::SetEnablePreviewText(frameNode, true);
    OHOS::Ace::NG::SearchModelNG::GetSearchController(frameNode);
    OHOS::Ace::NG::SearchModelNG::SetType(frameNode, TextInputType::NUMBER);
    OHOS::Ace::NG::SearchModelNG::SetTextDecorationStyle(frameNode, Ace::TextDecorationStyle::DASHED);
    OHOS::Ace::NG::SearchModelNG::SetTextDecorationColor(frameNode, Color::BLUE);
    OHOS::Ace::NG::SearchModelNG::SetTextDecoration(frameNode, Ace::TextDecoration::UNDERLINE);
    Font font;
    OHOS::Ace::NG::SearchModelNG::SetTextFont(frameNode, font);
    OHOS::Ace::NG::SearchModelNG::SetCopyOption(frameNode, CopyOptions::Local);
    OHOS::Ace::NG::SearchModelNG::SetTextColor(frameNode, Color::BLUE);
    OHOS::Ace::NG::SearchModelNG::SetSearchButtonFontColor(frameNode, Color::BLUE);
    OHOS::Ace::NG::SearchModelNG::SetSearchButtonFontSize(frameNode, Dimension());
    OHOS::Ace::NG::SearchModelNG::SetSearchButton(frameNode, "SEARCH");
    OHOS::Ace::NG::SearchModelNG::SetSearchIconColor(frameNode, Color::BLUE);
    OHOS::Ace::NG::SearchModelNG::SetSearchSrcPath(frameNode, "");
    OHOS::Ace::NG::SearchModelNG::SetSearchIconSize(frameNode, Dimension());
    OHOS::Ace::NG::SearchModelNG::SetPlaceholder(frameNode, "");
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
* @tc.name: Create006
* @tc.desc: check search modifier api available
* @tc.type: FUNC
*/
HWTEST_F(SearchTestNg, Create006, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, EMPTY_VALUE);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    searchModelInstance.CreateSearchNode(nodeId, u"", u"", "");
    auto searchNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(searchNode, nullptr);
    std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)> onSubmit;
    std::function<void(const ChangeValueInfo&)> onChange;
    std::function<void(const std::u16string&)> onCopy;
    std::function<void(const std::u16string&)> onCut;
    std::function<void(const std::u16string&, NG::TextCommonEvent&)> onPasteEvent;
    std::function<void(int32_t, int32_t)> OnTextSelectionChange;
    OHOS::Ace::NG::SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
    OHOS::Ace::NG::SearchModelNG::SetOnChange(frameNode, std::move(onChange));
    OHOS::Ace::NG::SearchModelNG::SetOnCopy(frameNode, std::move(onCopy));
    OHOS::Ace::NG::SearchModelNG::SetOnCut(frameNode, std::move(onCut));
    OHOS::Ace::NG::SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onPasteEvent));
    OHOS::Ace::NG::SearchModelNG::SetType(frameNode, TextInputType::NUMBER);
    OHOS::Ace::NG::SearchModelNG::SetType(frameNode, TextInputType::TEXT);
    OHOS::Ace::NG::SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(OnTextSelectionChange));
    OHOS::Ace::NG::SearchModelNG::SetAutoCapitalizationMode(frameNode, AutoCapitalizationMode::SENTENCES);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto eventHub = searchTextField->GetOrCreateEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextCommonEvent event;
    eventHub->FireOnPasteWithEvent(u"", event);
    eventHub->FireOnCut(u"");
    ChangeValueInfo changeValueInfo;
    eventHub->FireOnChange(changeValueInfo);
    onPasteEvent = [](const std::u16string& u1, NG::TextCommonEvent& te) {
        return;
    };
    onCut = [](const std::u16string& u1) { return; };
    onChange = [](const ChangeValueInfo& u1) { return; };
    OHOS::Ace::NG::SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onPasteEvent));
    eventHub->FireOnPasteWithEvent(u"", event);
    eventHub->FireOnCut(u"");
    eventHub->FireOnChange(changeValueInfo);
    std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
    Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::RED };
    OHOS::Ace::NG::SearchModelNG::SetTextFont(frameNode, testFont1);
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
    searchModelInstance.SetTextAlign(OHOS::Ace::TextAlign::START);
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
    auto eventHub = frameNode->GetOrCreateEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    searchModelInstance.SetOnSubmit([&searchModelInstance, &textFieldLayoutProperty](
        const std::u16string& title, NG::TextFieldCommonEvent& commonEvent) {
        if (title == u"SetOnSubmit") {
            std::vector<std::string> fontFamilies { "Georgia", "Serif" };
            Font otherFont { FontWeight::W200, Dimension(12), OHOS::Ace::FontStyle::ITALIC, fontFamilies };
            searchModelInstance.SetTextFont(otherFont);
            EXPECT_EQ(textFieldLayoutProperty->GetFontWeight(), FontWeight::W200);
            commonEvent.SetKeepEditable(true);
            EXPECT_TRUE(commonEvent.keepEditable_);
        }
    });
    TextFieldCommonEvent event;
    eventHub->FireOnSubmit(u"SetOnSubmit", event);
    EXPECT_EQ(event.GetText(), u"SetOnSubmit");
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
    auto eventHub = frameNode->GetOrCreateEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * SetOnCopy
     */
    searchModelInstance.SetOnCopy([](const std::u16string& title) {});
    eventHub->FireOnCopy(u"");
    /**
     * SetOnCut
     */
    searchModelInstance.SetOnCut([](const std::u16string& title) {});
    eventHub->FireOnCut(u"");
    /**
     * SetOnPaste
     */
    searchModelInstance.SetOnPaste([](const std::u16string& title) {});
    eventHub->FireOnPaste(u"");
    /**
     * SetOnPasteWithEvent
     */
    searchModelInstance.SetOnPasteWithEvent([](const std::u16string& title, NG::TextCommonEvent& event) {});
    TextCommonEvent event;
    eventHub->FireOnPasteWithEvent(u"", event);
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
 * @tc.name: SearchChangeEventHub001
 * @tc.desc: SearchEventHub
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchChangeEventHub001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    ChangeAndSubmitEvent changeEvent = [](const std::u16string str) {};
    searchModelInstance.SetOnChangeEvent(changeEvent);
    auto eventHub = frameNode->GetOrCreateEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    eventHub->UpdateChangeEvent(u"");
    ASSERT_EQ(eventHub->onValueChangeEvent_, nullptr);
    eventHub->onValueChangeEvent_ = nullptr;
    eventHub->UpdateChangeEvent(u"");
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    focusHub->onFocusInternal_(focusHub->focusReason_);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnColorConfigurationUpdate();
    auto cancelButtonNode = pattern->cancelButtonNode_.Upgrade();
    ASSERT_NE(cancelButtonNode, nullptr);
    auto textField = pattern->textField_.Upgrade();
    ASSERT_NE(textField, nullptr);
    auto textFieldLayoutProperty =
        textField->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), Color::RED);
    auto cancelButtonTextNode = AceType::DynamicCast<FrameNode>(
        cancelButtonNode->GetChildren().front());
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
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
 * @tc.name: testSelectedBackgroundColor001
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testInputFilter001
 * @tc.desc: Test Search input filter
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testInputFilter001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();

    /**
     * @tc.steps: step2. assign filter as number filter
     */
    layoutProperty->UpdateInputFilter(NUMBER_FILTER);
    auto numStr = u"1";

    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    textFieldPattern->InsertValue(numStr);
    EXPECT_EQ(textFieldPattern->GetInputFilter(), NUMBER_FILTER);
}

/**
 * @tc.name: testInputFilter002
 * @tc.desc: Test Search input filter
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, testInputFilter002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    /**
     * @tc.steps: step2. assign filter as number filter
     */
    searchModelInstance.SetInputFilter(NUM_FILTER, nullptr);
    auto textFieldController = textFieldPattern->contentController_;
    textFieldController->InsertValue(0, DEFAULT_FILTER_TEXT_U16);
    /**
     * @tc.expected: Check if the text filter patterns for the input box are compliant
     */
    EXPECT_EQ(textFieldPattern->GetTextValue().compare(FILTER_NUM_TEXT), 0);
}

/**
 * @tc.name: SetTextAlign002
 * @tc.desc: Set Text Align
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetTextAlign002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    TextAlign textAligns[] = {TextAlign::CENTER, TextAlign::JUSTIFY, TextAlign::START, TextAlign::END};
    TextDirection textDirectoins[] = {TextDirection::LTR, TextDirection::RTL, TextDirection::AUTO};
    for (auto textAlign : textAligns) {
        for (auto textDirection : textDirectoins) {
            textFieldLayoutProperty->UpdateTextAlign(textAlign);
            textFieldLayoutProperty->UpdateLayoutDirection(textDirection);
            frameNode->MarkModifyDone();
            EXPECT_EQ(textFieldLayoutProperty->GetTextAlign(), textAlign);
        }
    }
}

/**
 * @tc.name: SetSearchEnterKeyType001
 * @tc.desc: SetSearchEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchEnterKeyType001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetSearchEnterKeyType(TextInputAction::UNSPECIFIED);
    EXPECT_EQ(textFieldPattern->GetTextInputAction(), TextInputAction::SEARCH);
}

/**
 * @tc.name: SetSearchEnterKeyType002
 * @tc.desc: SetSearchEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchEnterKeyType002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetTextIndent(DEFAULT_INDENT_SIZE);
    searchModelInstance.SetSearchEnterKeyType(TextInputAction::GO);
    EXPECT_EQ(textFieldPattern->GetTextInputAction(), TextInputAction::GO);
}

/**
 * @tc.name: SetSearchCapitalizationMode001
 * @tc.desc: SetSearchCapitalizationMode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchCapitalizationMode001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetSearchCapitalizationMode(AutoCapitalizationMode::SENTENCES);
    EXPECT_EQ(AutoCapitalizationMode::SENTENCES, textFieldPattern->GetAutoCapitalizationMode());
}

/**
 * @tc.name: SetSearchCapitalizationMode002
 * @tc.desc: SetSearchCapitalizationMode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchCapitalizationMode002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetTextIndent(DEFAULT_INDENT_SIZE);
    searchModelInstance.SetSearchCapitalizationMode(AutoCapitalizationMode::WORDS);
    EXPECT_EQ(AutoCapitalizationMode::WORDS, textFieldPattern->GetAutoCapitalizationMode());
}

/**
 * @tc.name: SetEnablePreviewText
 * @tc.desc: Test SetEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetEnablePreviewText, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetEnablePreviewText(true);
    EXPECT_TRUE(textFieldPattern->GetSupportPreviewText());
}

/**
 * @tc.name: SetSearchIcon001
 * @tc.desc: Test SetIcon works fine for a second or more use
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetSearchIcon001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    searchModelInstance.SetIcon(frameNode, "");
    auto searchIconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(searchIconFrameNode, nullptr);
    auto imageLayoutProperty = searchIconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto searchIconPath1 = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
    EXPECT_NE(searchIconPath1.c_str(), "");
    searchModelInstance.SetIcon(frameNode, "sys.media.wifi_router_fill");
    auto searchIconPath2 = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
    EXPECT_NE(searchIconPath1.c_str(), searchIconPath2.c_str());
}

/**
 * @tc.name: StrokeTest001
 * @tc.desc: test search storkeWidth and strokeColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, StrokeTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();

    /**
     * @tc.step: step2.  set strokeWidth 2.0 px.
     */
    searchModelInstance.SetStrokeWidth(Dimension(2.0));
    searchModelInstance.SetStrokeColor(STORKE_COLOR_VALUE_1);

    /**
     * @tc.step: step3. test strokeWidth
     */
    EXPECT_EQ(layoutProperty->GetStrokeWidth(), Dimension(2.0));
    EXPECT_EQ(layoutProperty->GetStrokeColor(), STORKE_COLOR_VALUE_1);

    searchModelInstance.ResetStrokeColor();
    EXPECT_EQ(layoutProperty->GetStrokeColor().has_value(), false);
}

/**
 * @tc.name: UpdateFontFeatureWithStroke001
 * @tc.desc: test UpdateFontFeature
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, UpdateFontFeatureWithStroke001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    SearchModelNG searchModelInstance;
    searchModelInstance.SetStrokeWidth(Dimension(2.0));
    searchModelInstance.SetStrokeColor(STORKE_COLOR_VALUE_1);

    layoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 1"));
    SearchModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_0);

    EXPECT_EQ(layoutProperty->GetStrokeWidth(), Dimension(2.0));
    EXPECT_EQ(layoutProperty->GetStrokeColor(), STORKE_COLOR_VALUE_1);
}

/**
 * @tc.name: SearchEnableAutoSpacing
 * @tc.desc: Test the enable or disable the EnableAutoSpacing attribute.
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SearchEnableAutoSpacing, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    searchModelInstance.SetEnableAutoSpacing(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.expected: Get EnableAutoSpacing Value
     */
    EXPECT_EQ(textFieldLayoutProperty->GetEnableAutoSpacing(), true);
    EXPECT_EQ(SearchModelNG::GetEnableAutoSpacing(frameNode), true);
    /**
     * @tc.expected: Set EnableAutoSpacing False
     */
    SearchModelNG::SetEnableAutoSpacing(frameNode, false);
    /**
     * @tc.expected: Get EnableAutoSpacing Value
     */
    EXPECT_EQ(textFieldLayoutProperty->GetEnableAutoSpacing(), false);
    EXPECT_EQ(SearchModelNG::GetEnableAutoSpacing(frameNode), false);
}

/**
 * @tc.name: InitMargin
 * @tc.desc: Test the margin setup method.
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, InitMargin, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node with default text and placeholder
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto searchPattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(searchPattern, nullptr);

    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    searchPattern->InitMargin(searchLayoutProperty);
    const auto& marginProperty = searchLayoutProperty->GetMarginProperty();
    ASSERT_NE(marginProperty, nullptr);
    EXPECT_TRUE(marginProperty->top);
    EXPECT_TRUE(marginProperty->bottom);

    searchLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    searchPattern->InitMargin(searchLayoutProperty);
    EXPECT_FALSE(marginProperty->top);
    EXPECT_FALSE(marginProperty->bottom);

    MarginProperty margin;
    margin.top = CalcLength(10.0f);
    margin.bottom = CalcLength(10.0f);
    searchLayoutProperty->UpdateUserMargin(margin);
    searchLayoutProperty->UpdateMargin(margin);
    searchPattern->InitMargin(searchLayoutProperty);

    EXPECT_TRUE(marginProperty->top);
    EXPECT_TRUE(marginProperty->bottom);
}

/**
 * @tc.name: SearchFieldPattern::ProcessSelection
 * @tc.desc: Test the ProcessSelection method.
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, ProcessSelection, TestSize.Level1)
{
    /**
     * @tc.steps: Create Search node with default text and placeholder
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldPattern = textFieldFrameNode->GetPattern<SearchTextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto paintProperty = textFieldPattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateCursorColor(Color::RED);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayHolder_ = textFieldPattern->selectOverlay_;
    textFieldPattern->selectOverlay_->OnBind(manager);

    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(manager->shareOverlayInfo_, nullptr);
    auto handleNode = SelectOverlayNode::CreateSelectOverlayNode(manager->shareOverlayInfo_);
    ASSERT_NE(handleNode, nullptr);
    auto root = AceType::MakeRefPtr<FrameNode>("TEMP", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(root, nullptr);
    handleNode->MountToParent(root);
    manager->selectOverlayNode_ = AceType::WeakClaim(AceType::RawPtr(handleNode));

    textFieldPattern->ProcessSelection();
    EXPECT_EQ(manager->shareOverlayInfo_->handlerColor, Color::RED);
}

/**
 * @tc.name: SetAutoCapitalizationMode001
 * @tc.desc: test SetAutoCapitalizationMode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestNg, SetAutoCapitalizationMode001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(frameNode->GetChildren().empty());
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    searchModelInstance.SetAutoCapitalizationMode(frameNode, AutoCapitalizationMode::NONE);
    EXPECT_EQ(AutoCapitalizationMode::NONE, pattern->GetAutoCapitalizationMode());
}
} // namespace OHOS::Ace::NG
