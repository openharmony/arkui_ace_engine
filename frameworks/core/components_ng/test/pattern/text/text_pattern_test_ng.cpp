/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextAlign TEXT_ALIGN_VALUE = Ace::TextAlign::CENTER;
const Ace::TextOverflow TEXT_OVERFLOW_VALUE = Ace::TextOverflow::CLIP;
const uint32_t MAX_LINES_VALUE = 10;
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Dimension BASELINE_OFFSET_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension ADAPT_MIN_FONT_SIZE_VALUE = Dimension(50, DimensionUnit::PX);
const Dimension ADAPT_MAX_FONT_SIZE_VALUE = Dimension(200, DimensionUnit::PX);
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;

using OnClickCallback = std::function<void(const BaseEventInfo* info)>;
using DragDropBaseCallback = std::function<DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
void onclickFunc(const BaseEventInfo* info) {};
void onRemoteMessage() {};
const CopyOptions copyOption = CopyOptions::None;
DragDropBaseInfo OnDragStartFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)
{
    DragDropBaseInfo temp;
    return temp;
};
void OnDragDropFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
} // namespace

struct TestProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyleValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Ace::TextAlign> textAlignValue = std::nullopt;
    std::optional<Ace::TextOverflow> textOverflowValue = std::nullopt;
    std::optional<uint32_t> maxLinesValue = std::nullopt;
    std::optional<Dimension> lineHeightValue = std::nullopt;
    std::optional<Ace::TextDecoration> textDecorationValue = std::nullopt;
    std::optional<Color> textDecorationColorValue = std::nullopt;
    std::optional<Dimension> baselineOffsetValue = std::nullopt;
    std::optional<Ace::TextCase> textCaseValue = std::nullopt;
    std::optional<Dimension> adaptMinFontSize = std::nullopt;
    std::optional<Dimension> adaptMaxFontSize = std::nullopt;
    std::optional<Dimension> letterSpacing = std::nullopt;
};

class TextPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateTextParagraph(const std::string& createValue, const TestProperty& testProperty);
};

void TextPatternTestNg::SetUpTestCase() {}
void TextPatternTestNg::TearDownTestCase() {}
void TextPatternTestNg::SetUp() {}
void TextPatternTestNg::TearDown() {}

RefPtr<FrameNode> TextPatternTestNg::CreateTextParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    TextModelNG textModel;
    textModel.Create(createValue);
    if (testProperty.fontSizeValue.has_value()) {
        textModel.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        textModel.SetTextColor(testProperty.textColorValue.value());
    }
    if (testProperty.italicFontStyleValue.has_value()) {
        textModel.SetItalicFontStyle(testProperty.italicFontStyleValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        textModel.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        textModel.SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.textAlignValue.has_value()) {
        textModel.SetTextAlign(testProperty.textAlignValue.value());
    }
    if (testProperty.textOverflowValue.has_value()) {
        textModel.SetTextOverflow(testProperty.textOverflowValue.value());
    }
    if (testProperty.maxLinesValue.has_value()) {
        textModel.SetMaxLines(testProperty.maxLinesValue.value());
    }
    if (testProperty.lineHeightValue.has_value()) {
        textModel.SetLineHeight(testProperty.lineHeightValue.value());
    }
    if (testProperty.textDecorationValue.has_value()) {
        textModel.SetTextDecoration(testProperty.textDecorationValue.value());
    }
    if (testProperty.textDecorationColorValue.has_value()) {
        textModel.SetTextDecorationColor(testProperty.textDecorationColorValue.value());
    }
    if (testProperty.baselineOffsetValue.has_value()) {
        textModel.SetBaselineOffset(testProperty.baselineOffsetValue.value());
    }
    if (testProperty.textCaseValue.has_value()) {
        textModel.SetTextCase(testProperty.textCaseValue.value());
    }
    if (testProperty.adaptMinFontSize.has_value()) {
        textModel.SetAdaptMinFontSize(testProperty.adaptMinFontSize.value());
    }
    if (testProperty.adaptMaxFontSize.has_value()) {
        textModel.SetAdaptMaxFontSize(testProperty.adaptMaxFontSize.value());
    }
    if (testProperty.letterSpacing.has_value()) {
        textModel.SetLetterSpacing(testProperty.letterSpacing.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: TextFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    testProperty.textAlignValue = std::make_optional(TEXT_ALIGN_VALUE);
    testProperty.textOverflowValue = std::make_optional(TEXT_OVERFLOW_VALUE);
    testProperty.maxLinesValue = std::make_optional(MAX_LINES_VALUE);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.adaptMinFontSize = std::make_optional(ADAPT_MIN_FONT_SIZE_VALUE);
    testProperty.adaptMaxFontSize = std::make_optional(ADAPT_MAX_FONT_SIZE_VALUE);

    RefPtr<FrameNode> frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    EXPECT_EQ(fontStyle == nullptr, false);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    EXPECT_EQ(textLineStyle == nullptr, false);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textStyle.GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetFontFamilies(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textStyle.GetTextAlign(), TEXT_ALIGN_VALUE);
    EXPECT_EQ(textStyle.GetTextOverflow(), TEXT_OVERFLOW_VALUE);
    EXPECT_EQ(textStyle.GetMaxLines(), MAX_LINES_VALUE);
    EXPECT_EQ(textStyle.GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetBaselineOffset(), BASELINE_OFFSET_VALUE);
    EXPECT_EQ(textStyle.GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize(), ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize(), ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptTextSize(),
        testProperty.adaptMinFontSize.has_value() || testProperty.adaptMaxFontSize.has_value());
}

/**
 * @tc.name: TextFrameNodeCreator002
 * @tc.desc: Test all the property of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    auto frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    EXPECT_EQ(fontStyle == nullptr, false);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    EXPECT_EQ(textLineStyle == nullptr, false);
    auto textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetLetterSpacing(), LETTER_SPACING);
}

/**
 * @tc.name: TextFrameNodeCreator003
 * @tc.desc: Test all the fontweight and events of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);

    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textStyle.SetFontWeight(FontWeight::W100);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W100);
    textModelNG.SetFontWeight(FontWeight::REGULAR);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::NORMAL);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::MEDIUM);
    textStyle.SetFontWeight(FontWeight::W500);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W500);
    textModelNG.SetFontWeight(FontWeight::BOLD);
    textStyle.SetFontWeight(FontWeight::W700);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W700);
    textModelNG.SetFontWeight(FontWeight::BOLDER);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);
    textModelNG.SetFontWeight(FontWeight::W900);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);

    textModelNG.SetOnClick(onclickFunc);
    textModelNG.SetRemoteMessage(onRemoteMessage);
    textModelNG.SetCopyOption(copyOption);
    textModelNG.SetOnDragStart(OnDragStartFunction);
    textModelNG.SetOnDragEnter(OnDragDropFunction);
    textModelNG.SetOnDragMove(OnDragDropFunction);
    textModelNG.SetOnDragLeave(OnDragDropFunction);
    textModelNG.SetOnDrop(OnDragDropFunction);
}

/**
 * @tc.name: TextFrameNodeCreator004
 * @tc.desc: Test TextAccessibilityProperty.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator004, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    EXPECT_FALSE(textAccessibilityProperty == nullptr);
    textAccessibilityProperty->SetHost(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_EQ(textAccessibilityProperty->GetText(), CREATE_VALUE);
}

/**
 * @tc.name: TextFrameNodeCreator005
 * @tc.desc: Test TextAccessibilityProperty.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator005, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    EXPECT_FALSE(textAccessibilityProperty == nullptr);
    textAccessibilityProperty->SetHost(nullptr);
    EXPECT_EQ(textAccessibilityProperty->GetText(), "");
}

/**
 * @tc.name: TextFrameNodeCreator006
 * @tc.desc: Test TextAccessibilityProperty.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator006, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    EXPECT_FALSE(textAccessibilityProperty == nullptr);
    textAccessibilityProperty->SetHost(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    frameNode->layoutProperty_ = nullptr;
    EXPECT_EQ(textAccessibilityProperty->GetText(), "");
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test TextPattern OnAttachToFrameNode when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test TextPattern OnDetachFromFrameNode when FrameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->selectOverlayProxy_ = nullptr;
    pattern->OnDetachFromFrameNode(nullptr);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDetachFromFrameNode002
 * @tc.desc: Test TextPattern OnDetachFromFrameNode when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDetachFromFrameNode002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: step2. return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    pattern->selectOverlayProxy_ = proxy;
    pattern->OnDetachFromFrameNode(nullptr);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: Test TextPattern OnHandleMoveDone when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: step2. return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    pattern->selectOverlayProxy_ = proxy;
    RectF handleRect;
    pattern->OnHandleMoveDone(handleRect, true);
    pattern->OnHandleMoveDone(handleRect, false);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test TextPattern ShowSelectOverlay when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: step2. return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    pattern->selectOverlayProxy_ = proxy;
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    pipeline->selectOverlayManager_ = selectOverlayManager;
    RectF firstHandle;
    RectF secondHandle;
    pattern->ShowSelectOverlay(firstHandle, secondHandle);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: ShowSelectOverlay002
 * @tc.desc: Test TextPattern ShowSelectOverlay when SelectOverlayProxy is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ShowSelectOverlay002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->selectOverlayProxy_ = nullptr;
    RectF firstHandle;
    RectF secondHandle;
    pattern->ShowSelectOverlay(firstHandle, secondHandle);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test TextPattern HandleOnSelectAll when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleOnSelectAll001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test TextPattern OnModifyDone when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test TextPattern OnModifyDone longPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * copyOption: CopyOptions::InApp
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);

    /**
     * @tc.steps: step3. check the longPressEvent.
     */
    textPattern->OnModifyDone();
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle and paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint);
    EXPECT_EQ(ret, true);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint);
    EXPECT_EQ(ret, true);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper002
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);

    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper003
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, BeforeCreateLayoutWrapper003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint);
    EXPECT_EQ(ret, true);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, AceType::MakeRefPtr<GeometryNode>(), nullptr);
    EXPECT_FALSE(layoutWrapper == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, true);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper004
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, BeforeCreateLayoutWrapper004, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    EXPECT_FALSE(frameNode == nullptr);

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto frameNodeChild = FrameNode::CreateFrameNode("Test", 1, patternChild);
    EXPECT_FALSE(frameNodeChild == nullptr);

    frameNode->AddChild(frameNodeChild);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Test TextPattern DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, DumpInfo001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->selectOverlayProxy_ = nullptr;
    pattern->DumpInfo();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test TextPattern OnHandleMove when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnHandleMove001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: step2. return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo);
    pattern->selectOverlayProxy_ = proxy;
    RectF handleRect;
    pattern->OnHandleMove(handleRect, true);
    pattern->OnHandleMove(handleRect, false);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}
} // namespace OHOS::Ace::NG
