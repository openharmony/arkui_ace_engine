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
    textPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
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
 * @tc.name: OnModifyDone001
 * @tc.desc: Test TextPattern OnModifyDone when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
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
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
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
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
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
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);

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
} // namespace OHOS::Ace::NG
