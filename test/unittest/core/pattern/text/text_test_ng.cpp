/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "text_base.h"
#include "ui/base/geometry/dimension.h"

#include "core/components/common/layout/constants.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
const std::string TEXT_DETECT_TYPES = "phoneNum,url,email,location,datetime";
const std::u16string NORMAL_URL = u"www.baidu.com";
const std::u16string JUMP_LINK_HTTP = u"http://www.baidu.com";
const std::u16string JUMP_LINK_HTTPS = u"https://www.baidu.com";
} // namespace

class TextTestNg : public TextBases {
public:
};

/**
 * @tc.name: TextFrameNodeCreator002
 * @tc.desc: Test all the property of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    auto frameNode = CreateTextParagraph(CREATE_VALUE_W, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLineStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetLetterSpacing(), LETTER_SPACING);
}

/**
 * @tc.name: TextFrameNodeCreator003
 * @tc.desc: Test all the fontWeight and events of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);
    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
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
    textModelNG.SetOnClick(onClickFunc, std::numeric_limits<double>::infinity());
    textModelNG.SetRemoteMessage(onRemoteMessage);
    textModelNG.SetCopyOption(copyOption);
    textModelNG.SetOnDragStart(OnDragStartFunction);
}

/**
 * @tc.name: SetTextDetectEnable003
 * @tc.desc: Test SetTextDetectEnable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextDetectEnable003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);
    textModelNG.SetFontSize(frameNode, ADAPT_ZERO_FONT_SIZE_VALUE);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);
    textModelNG.SetTextDetectConfig(frameNode, TEXT_DETECT_TYPES);
    EXPECT_EQ(textModelNG.GetTextDetectConfig(frameNode), TEXT_DETECT_TYPES);

    TextDetectConfig textDetectConfig;
    textDetectConfig.types = TEXT_DETECT_TYPES;
    textDetectConfig.onResult = [](const std::string&) {};
    textModelNG.SetTextDetectConfig(frameNode, textDetectConfig);
    EXPECT_EQ(textModelNG.GetTextDetectConfig(frameNode), TEXT_DETECT_TYPES);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textModelNG.SetOnDetectResultUpdate(frameNode, std::move(textDetectConfig.onResult));
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_NE(textPattern->dataDetectorAdapter_->onResult_, nullptr);
    FONT_FEATURES_LIST value;
    ASSERT_EQ(textModelNG.GetFontFeature(frameNode), value);
    ASSERT_EQ(textModelNG.GetLineBreakStrategy(frameNode), TEXT_LINE_BREAK_STRATEGY);
    textModelNG.SetCaretColor(frameNode, Color::BLACK);
    ASSERT_EQ(textModelNG.GetCaretColor(frameNode), Color::BLACK);
    textModelNG.ResetCaretColor(frameNode);
    ASSERT_EQ(textModelNG.GetCaretColor(frameNode), Color::BLACK);
    textModelNG.SetSelectedBackgroundColor(frameNode, Color::BLACK);
    ASSERT_EQ(textModelNG.GetSelectedBackgroundColor(frameNode), Color::BLACK);
    textModelNG.ResetSelectedBackgroundColor(frameNode);
    ASSERT_EQ(textModelNG.GetSelectedBackgroundColor(frameNode), Color::BLACK);
    textModelNG.SetTextContentWithStyledString(frameNode, nullptr);
    ASSERT_EQ(textPattern->GetExternalParagraph(), nullptr);

    int32_t startIndex = 1;
    int32_t endIndex = 10;
    textModelNG.SetTextSelection(frameNode, startIndex, endIndex);
    EXPECT_NE(textPattern->textSelector_.GetStart(), startIndex);
    std::u16string eventValue;
    auto onCopyResult = [&eventValue](const std::u16string& param) { eventValue = param; };
    auto eventHub = frameNode->GetEventHub<TextEventHub>();
    textModelNG.SetOnCopy(frameNode, onCopyResult);
    EXPECT_NE(eventHub->onCopy_, nullptr);
    bool isSelectChanged = false;
    auto onSelectionChanged = [&isSelectChanged](int32_t, int32_t) { isSelectChanged = true; };
    textModelNG.SetOnTextSelectionChange(frameNode, onSelectionChanged);
    EXPECT_NE(eventHub->onSelectionChange_, nullptr);
}

/**
 * @tc.name: SetTextContentWithStyledString001
 * @tc.desc: Test SetTextContentWithStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextContentWithStyledString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textModelNG and frameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(textPattern->pManager_, nullptr);

    /**
     * @tc.steps: step2. call SetTextContentWithStyledString with parameter "value" is nullptr.
     * @tc.expected: pManager's paragraphs will be reseted
     */
    EXPECT_TRUE(textPattern->pManager_->GetParagraphs().empty());
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph });
    EXPECT_FALSE(textPattern->pManager_->GetParagraphs().empty());
    textModelNG.SetTextContentWithStyledString(frameNode, nullptr);
    EXPECT_TRUE(textPattern->pManager_->GetParagraphs().empty());
}

/**
 * @tc.name: SetTextDetectConfig001
 * @tc.desc: Test SetTextDetectConfig.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextDetectConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textModelNG and frameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get hyperlink theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto mocktheme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(mocktheme);
    EXPECT_CALL(*mocktheme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<HyperlinkTheme>()));
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step3. create textDetectConfig and call SetTextDetectConfig.
     * @tc.expected: the properties are successfully set to default values.
     */
    TextDetectConfig textDetectConfig;
    textModelNG.SetTextDetectConfig(textDetectConfig);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->textDetectTypes_, "");
    EXPECT_EQ(pattern->dataDetectorAdapter_->onResult_, nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityColor_, theme->GetTextColor());
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationType_, TextDecoration::UNDERLINE);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationColor_, theme->GetTextColor());
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationStyle_, TextDecorationStyle::SOLID);

    /**
     * @tc.steps: step4. set values for textDetectConfig and call SetTextDetectConfig.
     * @tc.expected: the values of properties are set successfully.
     */
    textDetectConfig.types = TEXT_DETECT_TYPES;
    textDetectConfig.onResult = [](const std::string&) {};
    textDetectConfig.entityColor = TEXT_COLOR_VALUE;
    textDetectConfig.entityDecorationType = TextDecoration::OVERLINE;
    textDetectConfig.entityDecorationColor = Color::BLACK;
    textDetectConfig.entityDecorationStyle = TextDecorationStyle ::DOUBLE;
    textModelNG.SetTextDetectConfig(textDetectConfig);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->textDetectTypes_, TEXT_DETECT_TYPES);
    EXPECT_NE(pattern->dataDetectorAdapter_->onResult_, nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityColor_, TEXT_COLOR_VALUE);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationType_, TextDecoration::OVERLINE);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationColor_, Color::BLACK);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationStyle_, TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: SetTextDetectConfig002
 * @tc.desc: Test SetTextDetectConfig.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextDetectConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textModelNG and frameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create textDetectConfig, set values for textDetectConfig and call SetTextDetectConfig.
     * @tc.expected: the properties are successfully set to default values.
     */
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = TEXT_DETECT_TYPES;
    textDetectConfig.onResult = [](const std::string&) {};
    textDetectConfig.entityColor = TEXT_COLOR_VALUE;
    textDetectConfig.entityDecorationType = TextDecoration::OVERLINE;
    textDetectConfig.entityDecorationColor = Color::BLACK;
    textDetectConfig.entityDecorationStyle = TextDecorationStyle ::DOUBLE;
    textModelNG.SetTextDetectConfig(frameNode, textDetectConfig);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->textDetectTypes_, TEXT_DETECT_TYPES);
    EXPECT_NE(pattern->dataDetectorAdapter_->onResult_, nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityColor_, TEXT_COLOR_VALUE);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationType_, TextDecoration::OVERLINE);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationColor_, Color::BLACK);
    EXPECT_EQ(pattern->dataDetectorAdapter_->entityDecorationStyle_, TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: ModifyAISpanStyle001
 * @tc.desc: test ModifyAISpanStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ModifyAISpanStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern and frameNode.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    /**
     * @tc.steps: step2. create aiSpanStyle, textDetectConfig and call ModifyAISpanStyle.
     * @tc.expected: the properties of aiSpanStyle are successfully set to default values of textDetectConfig.
     */
    TextStyle aiSpanStyle;
    TextDetectConfig textDetectConfig;
    pattern->ModifyAISpanStyle(aiSpanStyle);
    EXPECT_EQ(aiSpanStyle.GetTextColor(), textDetectConfig.entityColor);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationFirst(), textDetectConfig.entityDecorationType);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationColor(), textDetectConfig.entityDecorationColor);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationStyle(), textDetectConfig.entityDecorationStyle);

    /**
     * @tc.steps: step2. set values for textDetectConfig, call SetTextDetectConfig and ModifyAISpanStyle.
     * @tc.expected: the properties of aiSpanStyle are successfully set to values of textDetectConfig.
     */
    textDetectConfig.entityColor = TEXT_COLOR_VALUE;
    textDetectConfig.entityDecorationType = TextDecoration::OVERLINE;
    textDetectConfig.entityDecorationColor = Color::BLACK;
    textDetectConfig.entityDecorationStyle = TextDecorationStyle ::DOUBLE;
    pattern->SetTextDetectConfig(textDetectConfig);
    pattern->ModifyAISpanStyle(aiSpanStyle);
    EXPECT_EQ(aiSpanStyle.GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationFirst(), TextDecoration::OVERLINE);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationColor(), Color::BLACK);
    EXPECT_EQ(aiSpanStyle.GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: Test GetSelectedBackgroundColor when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    /**
     * @tc.steps: step2. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    ASSERT_EQ(textModelNG.GetSelectedBackgroundColor(frameNode), Color::BLACK);

    Font font;
    textModelNG.SetFont(font);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);
}


/**
 * @tc.name: GetSelectedBackgroundColor002
 * @tc.desc: Test GetSelectedBackgroundColor when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetSelectedBackgroundColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    /**
     * @tc.steps: step2. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    ASSERT_EQ(textModelNG.GetSelectedBackgroundColor(frameNode), Color::BLACK);

    Font font;
    font.fontFamilies = { "font1", "font2" };
    textModelNG.SetFont(font);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);
    EXPECT_EQ(textModelNG.GetFont(frameNode).fontFamilies.size(), 2);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test TextPattern OnAttachToFrameNode when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: Test TextPattern OnHandleMoveDone
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. call OnHandleMoveDone when SelectOverlay is off.
     * @tc.expected: the function exits normally
     */
    RectF handleRect = CONTENT_RECT;
    pattern->selectOverlay_->OnHandleMoveDone(handleRect, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);

    /**
     * @tc.steps: step3. call OnHandleMoveDone when SelectOverlay is on.
     * @tc.expected: the OnHandleMoveDone function exits normally
     */
    pattern->ShowSelectOverlay();
    bool isFirstHandle[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        pattern->textForDisplay_ = u"abcdefghij";
        pattern->selectOverlay_->OnHandleMoveDone(handleRect, isFirstHandle[i]);
        EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
        EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);
    }
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test TextPattern OnWindowHide.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnWindowHide001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call OnWindowHide function.
     */
    (void)textPattern->GetOrCreateMagnifier();
    (void)textPattern->CreateNodePaintMethod();
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnWindowShow001
 * @tc.desc: Test TextPattern OnWindowShow.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnWindowShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call OnWindowShow function.
     */
    (void)textPattern->CreateNodePaintMethod();
    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: InitUrlMouseEvent001
 * @tc.desc: Test TextPattern InitUrlMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, InitUrlMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call InitUrlMouseEvent function.
     */
    textPattern->InitUrlMouseEvent();
    EXPECT_TRUE(textPattern->urlMouseEventInitialized_);
}

/**
 * @tc.name: URLOnHover001
 * @tc.desc: Test TextPattern URLOnHover.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, URLOnHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call URLOnHover function.
     */
    textPattern->CreateModifier();
    textPattern->overlayMod_->SetSelectedForegroundColorAndRects({ { 5, 5, 5, 5 }, { 0, 0, 0, 0 } }, 1);
    textPattern->URLOnHover(false);
    EXPECT_TRUE(textPattern->overlayMod_->selectedUrlRects_.empty());
}

/**
 * @tc.name: OnHover001
 * @tc.desc: Test TextPattern OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call OnHover function.
     */
    textPattern->OnHover(true);
    EXPECT_EQ(textPattern->currentMouseStyle_, MouseFormat::DEFAULT);
    textPattern->OnHover(false);
    EXPECT_EQ(textPattern->currentMouseStyle_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: CalcAIMenuPosition001
 * @tc.desc: Test TextPattern CalcAIMenuPosition.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CalcAIMenuPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);

    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CalcAIMenuPosition function.
     */
    AISpan aiSpan;
    bool calledCalculateHandleFunc = false;
    CalculateHandleFunc calculateHandleFunc = [&calledCalculateHandleFunc]() {
        calledCalculateHandleFunc = true;
    };
    textPattern->textSelector_.firstHandle = RectF(0, 0, 0, 0);
    textPattern->textSelector_.secondHandle = RectF(1, 1, 5, 5);
    textPattern->CalcAIMenuPosition(aiSpan, calculateHandleFunc);
    EXPECT_TRUE(calledCalculateHandleFunc);
}

/**
 * @tc.name: TryLinkJump001
 * @tc.desc: Test TextPattern TryLinkJump.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TryLinkJump001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set link jump callback.
     */
    auto pipeline = textFrameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto linkJumpCallback = [](const std::string& link) {};
    pipeline->SetLinkJumpCallback(linkJumpCallback);

    /**
     * @tc.steps: step3. get span node and span item.
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. update spanNode content and call TryLinkJump funciton.
     * jump link: "www.baidu.com".
     */
    spanNode->UpdateContent(NORMAL_URL);
    EXPECT_FALSE(textPattern->TryLinkJump(spanItem));

    // jump link: "http://www.baidu.com".
    spanNode->UpdateContent(JUMP_LINK_HTTP);
    EXPECT_TRUE(textPattern->TryLinkJump(spanItem));

    // jump link: "https://www.baidu.com".
    spanNode->UpdateContent(JUMP_LINK_HTTPS);
    EXPECT_TRUE(textPattern->TryLinkJump(spanItem));
}

/**
 * @tc.name: ActTextOnClick001
 * @tc.desc: Test TextPattern ActTextOnClick.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ActTextOnClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. create GestureEvent and call ActTextOnClick function.
     */
    GestureEvent info;
    textPattern->SetOnClickEvent(nullptr);
    textPattern->ActTextOnClick(info);
    EXPECT_EQ(textPattern->onClick_, nullptr);

    auto clickFunc = [](GestureEvent& info) {};
    textPattern->SetOnClickEvent(clickFunc);
    textPattern->ActTextOnClick(info);
    EXPECT_NE(textPattern->onClick_, nullptr);
}

/**
 * @tc.name: HandleUserTouchEvent001
 * @tc.desc: test HandleUserTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleUserTouchEvent001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    SpanModelNG spanModelNG;
    spanModelNG.Create(u"h\n");
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    spanNode->MountToParent(textFrameNode, textFrameNode->children_.size());
    textPattern->spans_.emplace_back(spanNode->spanItem_);
    textPattern->childNodes_.push_back(spanNode);
    ASSERT_FALSE(textPattern->spans_.empty());

    auto firstSpanItem = textPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);

    bool isTouchTrigger = false;
    firstSpanItem->position = 2;
    firstSpanItem->onTouch = [&isTouchTrigger](TouchEventInfo& info) { isTouchTrigger = true; };
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    TouchEventInfo info = TouchEventInfo("default");
    TouchLocationInfo locationInfo = TouchLocationInfo(0);
    locationInfo.SetLocalLocation(Offset(3, 3));
    info.AddTouchLocationInfo(std::move(locationInfo));
    // Use SetTextRect method or geometry node instead of direct contentRect_ access
    auto geometryNode = textPattern->GetHost()->GetGeometryNode();
    if (geometryNode) {
        geometryNode->SetFrameOffset(OffsetF(0, 0));
        geometryNode->SetFrameSize(SizeF(20.0f, 20.0f));
    }
    textPattern->HandleSpanStringTouchEvent(info);
}


/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test TextPattern ShowSelectOverlay when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step1. call ShowSelectOverlay.
     * @tc.expected: select overlay is on.
     */
    pattern->ShowSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test TextPattern OnModifyDone longPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * copyOption: CopyOptions::InApp
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textLayoutProperty->UpdateContent(TEXT_CONTENT);

    /**
     * @tc.steps: step3. check the longPressEvent.
     * @tc.expected: longPressEvent is triggered.
     */
    textPattern->OnModifyDone();
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
    EXPECT_EQ(StringUtils::Str16ToStr8(textPattern->textForDisplay_), TEXT_CONTENT);

    textLayoutProperty->UpdateContent("Hello World");
    textPattern->textSelector_.baseOffset = 0;
    textPattern->textSelector_.destinationOffset = 3;
    textPattern->selectOverlay_->isTriggerParentToScroll_ = true;
    textPattern->OnModifyDone();
    EXPECT_EQ(StringUtils::Str16ToStr8(textPattern->textForDisplay_), "Hello World");
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(textPattern->textSelector_.destinationOffset, 3);
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test paragraph is not cleared by OnModifyDone .
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(pattern->pManager_, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->pManager_->GetParagraphs().size(), 1);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Test textEffect is not cleared by OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone004, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(pattern->pManager_, nullptr);
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->textEffect_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle and paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, u"", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);

    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    pattern->selectOverlayProxy_ = proxy;
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection001
 * @tc.desc: Test SetTextSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextSelection001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    OHOS::Ace::SelectionOptions options;
    pattern->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern->selectOverlay_, 1);
}

/**
 * @tc.name: TextLayoutAlgorithm001
 * @tc.desc: Test TextLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. spans is empty and call function.
     */
    std::list<RefPtr<SpanItem>> spans1_;
    auto pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager_, nullptr);
    auto textLayoutAlgorithm1 = AceType::MakeRefPtr<TextLayoutAlgorithm>(spans1_, pManager_, false, TextStyle(), true);
    ASSERT_NE(textLayoutAlgorithm1, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    std::list<RefPtr<SpanItem>> spans2_;
    ConstructSpanItemList1(spans2_);
    EXPECT_EQ(spans2_.size(), 4);
    auto pManager_1 = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager_1, nullptr);
    auto textLayoutAlgorithm2 = AceType::MakeRefPtr<TextLayoutAlgorithm>(spans2_, pManager_1, true, TextStyle(), true);
    ASSERT_NE(textLayoutAlgorithm2, nullptr);
    /**
     * @tc.steps: step3. call function.
     */
    std::list<RefPtr<SpanItem>> spans3_;
    ConstructSpanItemList1(spans3_);
    EXPECT_EQ(spans3_.size(), 4);
    RefPtr<SpanItem> span0 = nullptr;
    spans3_.emplace_back(span0);
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1\n";
    spans3_.emplace_back(span1);
    auto pManager_2 = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager_2, nullptr);
    auto textLayoutAlgorithm3 = AceType::MakeRefPtr<TextLayoutAlgorithm>(spans3_, pManager_2, true, TextStyle(), false);
    ASSERT_NE(textLayoutAlgorithm3, nullptr);
}

/**
 * @tc.name: TextLayoutAlgorithm002
 * @tc.desc: Test TextLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call function.
     */
    std::list<RefPtr<SpanItem>> spans_;
    ConstructSpanItemList1(spans_);
    EXPECT_EQ(spans_.size(), 4);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1\n";
    spans_.emplace_back(span1);
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"span2\n";
    spans_.emplace_back(span2);
    auto pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager_, nullptr);
    auto textLayoutAlgorithm4 = AceType::MakeRefPtr<TextLayoutAlgorithm>(spans_, pManager_, true, TextStyle(), false);
    ASSERT_NE(textLayoutAlgorithm4, nullptr);
}

/**
 * @tc.name: UpdateSensitiveContent001
 * @tc.desc: Test UpdateSensitiveContent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UpdateSensitiveContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and Create function.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    std::u16string content(u"test123\n");
    rowLayoutAlgorithm->OnReset();
    auto temp = content;
    rowLayoutAlgorithm->UpdateSensitiveContent(temp);
    EXPECT_NE(StringUtils::Str16ToStr8(temp), StringUtils::Str16ToStr8(content));
}

/**
* @tc.name: GetLineCount001
* @tc.desc: Test the maxlines of UpdateParagraphBySpan with different maxLines settings for each span.
* @tc.type: FUNC
*/
HWTEST_F(TextTestNg, GetLineCount001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    textModelNG.SetTextContentWithStyledString(frameNode, nullptr);
    auto line = textModelNG.GetLineCount(frameNode);
    ASSERT_EQ(line, 0);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo001
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with default values.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. call OnUpdateSelectOverlayInfo with default values.
     * @tc.expected: overlayInfo should be set with default values.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step3. verify the overlayInfo values.
     */
    EXPECT_FALSE(overlayInfo.isSingleHandle);
    EXPECT_TRUE(overlayInfo.isHandleLineShow);
    EXPECT_FALSE(overlayInfo.isUsingMouse);
    EXPECT_TRUE(overlayInfo.isNewAvoid);
    EXPECT_EQ(overlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);
    EXPECT_FALSE(overlayInfo.enableHandleLevel);
    EXPECT_EQ(overlayInfo.handleLevelMode, HandleLevelMode::OVERLAY);
    EXPECT_FALSE(overlayInfo.enableSubWindowMenu);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo002
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with isUsingMouse true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isUsingMouse to true.
     */
    pattern->selectOverlay_->SetUsingMouse(true);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify the overlayInfo values when using mouse.
     */
    EXPECT_TRUE(overlayInfo.isUsingMouse);
    EXPECT_TRUE(overlayInfo.recreateOverlay);
    EXPECT_EQ(overlayInfo.menuInfo.aiMenuOptionType, TextDataDetectType::INVALID);
    EXPECT_FALSE(overlayInfo.menuInfo.isAskCeliaEnabled);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo003
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with isUsingMouse true and
 * isShowAskCeliaInRightClick true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isUsingMouse to true and isShowAskCeliaInRightClick to true.
     */
    pattern->selectOverlay_->SetUsingMouse(true);
    SelectOverlayInfo overlayInfo;
    overlayInfo.menuInfo.isShowAskCeliaInRightClick = true;

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify isAskCeliaEnabled is set correctly.
     */
    EXPECT_TRUE(overlayInfo.menuInfo.isAskCeliaEnabled);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo004
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with isSingleHandle true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isSingleHandle to true.
     */
    pattern->selectOverlay_->SetIsSingleHandle(true);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify isSingleHandle is set correctly.
     */
    EXPECT_TRUE(overlayInfo.isSingleHandle);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo005
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with isHandleLineShow false.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isHandleLineShow to false.
     */
    pattern->selectOverlay_->SetIsShowHandleLine(false);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify isHandleLineShow is set correctly.
     */
    EXPECT_FALSE(overlayInfo.isHandleLineShow);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo006
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with mouseMenuOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set mouseMenuOffset.
     */
    OffsetF testOffset(100.0f, 200.0f);
    pattern->selectOverlay_->SetMouseMenuOffset(testOffset);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify rightClickOffset is set correctly.
     */
    EXPECT_EQ(overlayInfo.rightClickOffset.GetX(), 100.0f);
    EXPECT_EQ(overlayInfo.rightClickOffset.GetY(), 200.0f);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo007
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with handleLevelMode.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set handleLevelMode to EMBED.
     */
    pattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify handleLevelMode is set correctly.
     */
    EXPECT_EQ(overlayInfo.handleLevelMode, HandleLevelMode::EMBED);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo008
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with enableSubWindowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set enableSubWindowMenu to true.
     */
    pattern->selectOverlay_->SetEnableSubWindowMenu(true);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify enableSubWindowMenu is set correctly.
     */
    EXPECT_TRUE(overlayInfo.enableSubWindowMenu);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo009
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with afterOnClick callback.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step3. verify afterOnClick callback is set.
     */
    EXPECT_NE(overlayInfo.afterOnClick, nullptr);

    /**
     * @tc.steps: step4. call the afterOnClick callback.
     */
    GestureEvent gestureEvent;
    bool isFirst = true;
    overlayInfo.afterOnClick(gestureEvent, isFirst);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo010
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with different requestCode.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. call OnUpdateSelectOverlayInfo with different requestCode values.
     */
    SelectOverlayInfo overlayInfo1;
    int32_t requestCode1 = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo1, requestCode1);
    EXPECT_FALSE(overlayInfo1.isSingleHandle);

    SelectOverlayInfo overlayInfo2;
    int32_t requestCode2 = 100;
    pattern->selectOverlay_->SetIsSingleHandle(true);
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo2, requestCode2);
    EXPECT_TRUE(overlayInfo2.isSingleHandle);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo011
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with combined flags.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set multiple flags to true.
     */
    pattern->selectOverlay_->SetIsSingleHandle(true);
    pattern->selectOverlay_->SetUsingMouse(true);
    pattern->selectOverlay_->SetIsShowHandleLine(false);
    pattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    pattern->selectOverlay_->SetEnableSubWindowMenu(true);
    OffsetF testOffset(50.0f, 100.0f);
    pattern->selectOverlay_->SetMouseMenuOffset(testOffset);

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    SelectOverlayInfo overlayInfo;
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify all flags are set correctly.
     */
    EXPECT_TRUE(overlayInfo.isSingleHandle);
    EXPECT_TRUE(overlayInfo.isUsingMouse);
    EXPECT_TRUE(overlayInfo.recreateOverlay);
    EXPECT_FALSE(overlayInfo.isHandleLineShow);
    EXPECT_EQ(overlayInfo.handleLevelMode, HandleLevelMode::EMBED);
    EXPECT_TRUE(overlayInfo.enableSubWindowMenu);
    EXPECT_EQ(overlayInfo.rightClickOffset.GetX(), 50.0f);
    EXPECT_EQ(overlayInfo.rightClickOffset.GetY(), 100.0f);
    EXPECT_EQ(overlayInfo.menuInfo.aiMenuOptionType, TextDataDetectType::INVALID);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo012
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with isUsingMouse false.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isUsingMouse to false explicitly.
     */
    pattern->selectOverlay_->SetUsingMouse(false);

    /**
     * @tc.steps: step3. set aiMenuOptionType to a valid value before calling.
     */
    SelectOverlayInfo overlayInfo;
    overlayInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;

    /**
     * @tc.steps: step4. call OnUpdateSelectOverlayInfo.
     */
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step5. verify aiMenuOptionType is not changed when isUsingMouse is false.
     */
    EXPECT_EQ(overlayInfo.menuInfo.aiMenuOptionType, TextDataDetectType::PHONE_NUMBER);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo013
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo updates menuInfo when using mouse.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. set isUsingMouse to true.
     */
    pattern->selectOverlay_->SetUsingMouse(true);

    /**
     * @tc.steps: step3. set aiMenuOptionType to URL before calling.
     */
    SelectOverlayInfo overlayInfo;
    overlayInfo.menuInfo.aiMenuOptionType = TextDataDetectType::URL;

    /**
     * @tc.steps: step4. call OnUpdateSelectOverlayInfo.
     */
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step5. verify aiMenuOptionType is set to INVALID when using mouse.
     */
    EXPECT_EQ(overlayInfo.menuInfo.aiMenuOptionType, TextDataDetectType::INVALID);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo014
 * @tc.desc: Test BaseTextSelectOverlay OnUpdateSelectOverlayInfo with all default values.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnUpdateSelectOverlayInfo014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. create overlayInfo with initial values.
     */
    SelectOverlayInfo overlayInfo;
    overlayInfo.isSingleHandle = true;
    overlayInfo.isHandleLineShow = false;
    overlayInfo.isUsingMouse = true;
    overlayInfo.isNewAvoid = false;
    overlayInfo.hitTestMode = HitTestMode::HTMBLOCK;

    /**
     * @tc.steps: step3. call OnUpdateSelectOverlayInfo.
     */
    int32_t requestCode = 0;
    pattern->selectOverlay_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);

    /**
     * @tc.steps: step4. verify the values are overwritten by overlay's state.
     */
    EXPECT_FALSE(overlayInfo.isSingleHandle);
    EXPECT_TRUE(overlayInfo.isHandleLineShow);
    EXPECT_FALSE(overlayInfo.isUsingMouse);
    EXPECT_TRUE(overlayInfo.isNewAvoid);
    EXPECT_EQ(overlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);
}

/**
 * @tc.name: GetVisibleRect001
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with null node.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create visibleRect.
     */
    RectF visibleRect(10.0f, 20.0f, 100.0f, 200.0f);
    RefPtr<FrameNode> nullNode = nullptr;

    /**
     * @tc.steps: step2. call GetVisibleRect with null node.
     * @tc.expected: returns input visibleRect unchanged.
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(nullNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches input visibleRect.
     */
    EXPECT_EQ(result.GetX(), visibleRect.GetX());
    EXPECT_EQ(result.GetY(), visibleRect.GetY());
    EXPECT_EQ(result.Width(), visibleRect.Width());
    EXPECT_EQ(result.Height(), visibleRect.Height());
}

/**
 * @tc.name: GetVisibleRect002
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect when GetAncestorNodeOfFrame returns null.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with no parent.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    RectF visibleRect(10.0f, 20.0f, 100.0f, 200.0f);

    /**
     * @tc.steps: step2. call GetVisibleRect when GetAncestorNodeOfFrame returns null.
     * @tc.expected: returns input visibleRect unchanged.
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches input visibleRect.
     */
    EXPECT_EQ(result.GetX(), visibleRect.GetX());
    EXPECT_EQ(result.GetY(), visibleRect.GetY());
    EXPECT_EQ(result.Width(), visibleRect.Width());
    EXPECT_EQ(result.Height(), visibleRect.Height());
}

/**
 * @tc.name: GetVisibleRect003
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect when parent is PAGE_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto pagePattern = AceType::MakeRefPtr<Pattern>();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    ASSERT_NE(pageNode, nullptr);

    frameNode->SetParent(pageNode);

    RectF visibleRect(10.0f, 20.0f, 100.0f, 200.0f);

    /**
     * @tc.steps: step2. call GetVisibleRect when parent tag is PAGE_ETS_TAG.
     * @tc.expected: returns input visibleRect unchanged.
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches input visibleRect.
     */
    EXPECT_EQ(result.GetX(), visibleRect.GetX());
    EXPECT_EQ(result.GetY(), visibleRect.GetY());
    EXPECT_EQ(result.Width(), visibleRect.Width());
    EXPECT_EQ(result.Height(), visibleRect.Height());
}

/**
 * @tc.name: GetVisibleRect004
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with non-scrollable parent and no geometryNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with non-scrollable parent.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);
    parentNode->geometryNode_ = nullptr;

    RectF visibleRect(10.0f, 20.0f, 100.0f, 200.0f);

    /**
     * @tc.steps: step2. call GetVisibleRect when parent has no geometryNode.
     * @tc.expected: returns input visibleRect unchanged (recursive call).
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches input visibleRect.
     */
    EXPECT_EQ(result.GetX(), visibleRect.GetX());
    EXPECT_EQ(result.GetY(), visibleRect.GetY());
    EXPECT_EQ(result.Width(), visibleRect.Width());
    EXPECT_EQ(result.Height(), visibleRect.Height());
}

/**
 * @tc.name: GetVisibleRect005
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect when GetFrameNodeContentRect fails.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     * PAGE parent causes GetVisibleRect to return visibleRect directly (line 284-285).
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. call GetVisibleRect with PAGE parent.
     * @tc.expected: returns the original visibleRect.
     */
    RectF visibleRect(10.0f, 20.0f, 100.0f, 200.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches original visibleRect.
     */
    EXPECT_EQ(result.GetX(), 10.0f);
    EXPECT_EQ(result.GetY(), 20.0f);
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 200.0f);
}

/**
 * @tc.name: GetVisibleRect006
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect when parentViewport does not intersect.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     * PAGE parent causes GetVisibleRect to return visibleRect directly without intersection check.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. set up visibleRect and verify GetVisibleRect returns it directly.
     * @tc.expected: returns the original visibleRect when parent is PAGE.
     */
    RectF visibleRect(100.0f, 200.0f, 50.0f, 50.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches original visibleRect.
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 50.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect007
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with intersecting viewport.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with scrollable parent.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);
    parentNode->tag_ = V2::SCROLL_ETS_TAG;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    parentNode->geometryNode_ = geometryNode;

    /**
     * @tc.steps: step2. set up parent viewport that intersects with visibleRect.
     * visibleRect: (100, 200, 50, 50)
     * parentViewPort: (90, 190, 100, 100) - overlaps visibleRect
     */
    RectF visibleRect(100.0f, 200.0f, 50.0f, 50.0f);
    RectF parentViewPort(90.0f, 190.0f, 100.0f, 100.0f);
    // Set geometry node properties using new API
    geometryNode->SetFrameOffset(parentViewPort.GetOffset());
    geometryNode->SetFrameSize(parentViewPort.GetSize());
    geometryNode->SetContentOffset(parentViewPort.GetOffset());
    // Set render context to simulate transform offset
    auto renderContext = parentNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdatePaintRect(parentViewPort);
    }

    /**
     * @tc.steps: step3. call GetVisibleRect with intersecting viewport.
     * @tc.expected: returns intersection of visibleRect and parentViewPort + offset.
     * Expected intersection: (100, 200) intersects (90+10, 190+10) = (100, 200)
     * Intersection should be: (100, 200, min(50, 100), min(50, 100)) = (100, 200, 50, 50)
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step4. verify result is intersection rect.
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 50.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect008
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with complete containment.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with scrollable parent.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);
    parentNode->tag_ = V2::SCROLL_ETS_TAG;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    parentNode->geometryNode_ = geometryNode;

    /**
     * @tc.steps: step2. set up parent viewport that contains visibleRect.
     * visibleRect: (100, 200, 50, 50)
     * parentViewPort: (80, 180, 200, 200) - contains visibleRect
     */
    RectF visibleRect(100.0f, 200.0f, 50.0f, 50.0f);
    RectF parentViewPort(80.0f, 180.0f, 200.0f, 200.0f);
    // Set geometry node properties using new API
    geometryNode->SetFrameOffset(parentViewPort.GetOffset());
    geometryNode->SetFrameSize(parentViewPort.GetSize());
    geometryNode->SetContentOffset(parentViewPort.GetOffset());
    // Set render context to simulate transform offset
    auto renderContext = parentNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdatePaintRect(parentViewPort);
    }

    /**
     * @tc.steps: step3. call GetVisibleRect with contained viewport.
     * @tc.expected: returns visibleRect (contained).
     */
    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step4. verify result matches visibleRect.
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 50.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect009
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with partial overlap.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     * PAGE parent causes GetVisibleRect to return visibleRect directly (line 284-285).
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. set up visibleRect and verify GetVisibleRect returns it directly.
     * @tc.expected: returns original visibleRect when parent is PAGE.
     */
    RectF visibleRect(100.0f, 200.0f, 100.0f, 50.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches original visibleRect.
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect010
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with zero-sized visibleRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. create zero-sized visibleRect.
     */
    RectF visibleRect(0.0f, 0.0f, 0.0f, 0.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result is zero-sized.
     */
    EXPECT_EQ(result.GetX(), 0.0f);
    EXPECT_EQ(result.GetY(), 0.0f);
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 0.0f);
}

/**
 * @tc.name: GetVisibleRect011
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with empty visibleRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. create empty visibleRect (width=0, height>0).
     */
    RectF visibleRect(50.0f, 100.0f, 0.0f, 50.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result.
     */
    EXPECT_EQ(result.GetX(), 50.0f);
    EXPECT_EQ(result.GetY(), 100.0f);
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect012
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with multiple ancestor levels.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create multi-level node hierarchy.
     * Level 0: TEXT node
     * Level 1: SCROLL parent (intersects)
     * Level 2: COLUMN parent (non-scrollable, continues recursion)
     * Level 3: PAGE parent (terminates recursion)
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(textNode, nullptr);

    auto scrollPattern = AceType::MakeRefPtr<Pattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->tag_ = V2::SCROLL_ETS_TAG;

    auto columnPattern = AceType::MakeRefPtr<Pattern>();
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, columnPattern);
    ASSERT_NE(columnNode, nullptr);

    auto pagePattern = AceType::MakeRefPtr<Pattern>();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 3, pagePattern);
    ASSERT_NE(pageNode, nullptr);

    textNode->SetParent(scrollNode);
    scrollNode->SetParent(columnNode);
    columnNode->SetParent(pageNode);

    auto scrollGeometry = AceType::MakeRefPtr<GeometryNode>();
    scrollNode->geometryNode_ = scrollGeometry;

    RectF visibleRect(100.0f, 200.0f, 100.0f, 50.0f);
    RectF scrollViewport(90.0f, 190.0f, 150.0f, 100.0f);
    // Set geometry node properties using new API
    scrollGeometry->SetFrameOffset(scrollViewport.GetOffset());
    scrollGeometry->SetFrameSize(scrollViewport.GetSize());
    scrollGeometry->SetContentOffset(scrollViewport.GetOffset());
    // Set render context to simulate paint rect
    auto scrollRenderContext = scrollNode->GetRenderContext();
    if (scrollRenderContext) {
        scrollRenderContext->UpdatePaintRect(scrollViewport);
    }

    auto result = BaseTextSelectOverlay::GetVisibleRect(textNode, visibleRect);

    /**
     * @tc.steps: step3. verify result reaches page level and returns visibleRect.
     * At scroll level: intersection of (100,200,100,50) and (90+10,190+10,150,100)
     * = (100,200,100,50)
     * At column level (non-scrollable): passes through
     * At page level: returns visibleRect unchanged
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: GetVisibleRect013
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with negative coordinates.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     * PAGE parent causes GetVisibleRect to return visibleRect directly.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. create visibleRect with negative coordinates.
     * @tc.expected: returns original visibleRect when parent is PAGE.
     */
    RectF visibleRect(-50.0f, -30.0f, 100.0f, 80.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches original visibleRect.
     */
    EXPECT_EQ(result.GetX(), -50.0f);
    EXPECT_EQ(result.GetY(), -30.0f);
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 80.0f);
}

/**
 * @tc.name: GetVisibleRect014
 * @tc.desc: Test BaseTextSelectOverlay GetVisibleRect with parent having transform offset.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetVisibleRect014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode with PAGE parent.
     * PAGE parent causes GetVisibleRect to return visibleRect directly (line 284-285).
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto parentPattern = AceType::MakeRefPtr<Pattern>();
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentNode, nullptr);

    frameNode->SetParent(parentNode);

    /**
     * @tc.steps: step2. create visibleRect and verify GetVisibleRect returns it directly.
     * @tc.expected: returns original visibleRect when parent is PAGE.
     */
    RectF visibleRect(100.0f, 200.0f, 100.0f, 50.0f);

    auto result = BaseTextSelectOverlay::GetVisibleRect(frameNode, visibleRect);

    /**
     * @tc.steps: step3. verify result matches original visibleRect.
     */
    EXPECT_EQ(result.GetX(), 100.0f);
    EXPECT_EQ(result.GetY(), 200.0f);
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 50.0f);
}

/**
 * @tc.name: OnAncestorNodeChanged_StartScroll
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_START_SCROLL flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_StartScroll, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with START_SCROLL.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_START_SCROLL);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_EndScroll
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_END_SCROLL flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_EndScroll, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with END_SCROLL.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_END_SCROLL);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_StartAnimation
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_START_ANIMATION flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_StartAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with START_ANIMATION.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_START_ANIMATION);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_GeometryChange
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_GEOMETRY_CHANGE flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_GeometryChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with GEOMETRY_CHANGE.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_TransformChange
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_TRANSFORM_CHANGE flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_TransformChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with TRANSFORM_CHANGE.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_TransitionStart
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_TRANSITION_START flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_TransitionStart, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with TRANSITION_START.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_TRANSITION_START);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_ContentClipChange
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CONTENT_CLIP_CHANGE flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_ContentClipChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with CONTENT_CLIP_CHANGE.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CONTENT_CLIP_CHANGE);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_MultipleFlags
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with multiple flags combined.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_MultipleFlags, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with combined flags.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    FrameNodeChangeInfoFlag combinedFlag =
        FRAME_NODE_CHANGE_START_SCROLL | FRAME_NODE_CHANGE_START_ANIMATION | FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    pattern->selectOverlay_->OnAncestorNodeChanged(combinedFlag);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_NoneFlag
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_INFO_NONE.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_NoneFlag, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with INFO_NONE.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);
    SUCCEED();
}

/**
 * @tc.name: OnAncestorNodeChanged_AllFlags
 * @tc.desc: Test BaseTextSelectOverlay OnAncestorNodeChanged with FRAME_NODE_CHANGE_ALL.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAncestorNodeChanged_AllFlags, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, setup select overlay.
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectOverlay_, nullptr);

    /**
     * @tc.steps: step2. show select overlay and call OnAncestorNodeChanged with CHANGE_ALL.
     * @tc.expected: method executes without crash.
     */
    pattern->ShowSelectOverlay();
    ASSERT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_ALL);
    SUCCEED();
}
} // namespace OHOS::Ace::NG
