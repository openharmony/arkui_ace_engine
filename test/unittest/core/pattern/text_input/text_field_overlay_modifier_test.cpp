/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "text_input_base.h"

#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float MIN_RECT_X = 0.0f;
constexpr float MIN_RECT_Y = 0.0f;
constexpr float DEFAULT_RECT_X = 10.0f;
constexpr float DEFAULT_RECT_Y = 10.0f;
constexpr float MIN_RECT_WIDTH = 0.0f;
constexpr float MIN_RECT_HEIGHT = 0.0f;
constexpr float PREVIEW_TEXT_RECT_X = 200.0f;
constexpr float PREVIEW_TEXT_RECT_Y = 30.0f;
constexpr float PREVIEW_TEXT_RECT_W = 300.0f;
constexpr float PREVIEW_TEXT_RECT_H = 60.0f;
constexpr float PREVIEW_DRAW_LEFT = 10.0f;
constexpr float PREVIEW_DRAW_TOP = 20.0f;
constexpr float PREVIEW_DRAW_WIDTH = 100.0f;
constexpr float PREVIEW_DRAW_HEIGHT = 30.0f;
constexpr float PREVIEW_CONTENT_OFFSET_X = 50.0f;
constexpr float PREVIEW_CONTENT_OFFSET_Y = 40.0f;
constexpr float PREVIEW_CONTENT_WIDTH = 200.0f;
constexpr float PREVIEW_CONTENT_HEIGHT = 100.0f;
constexpr int32_t PREVIEW_TEXT_START_INDEX = 0;
constexpr int32_t PREVIEW_TEXT_END_INDEX = 5;
constexpr size_t RECTS_FOR_RANGE_OUT_ARG_INDEX = 2;
} // namespace

class TextFieldOverlayModifierTest : public TextInputBases {
public:
};

/**
 * @tc.name: TextFieldOverlayModifierTest001
 * @tc.desc: Test textfield to create TextFieldOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create scrollEdgeEffect
     * tc.expected: step2. Check if scrollEdgeEffect is created.
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step3. create textFieldOverlayModifier
     * tc.expected: step3. Check if textFieldOverlayModifier is created.
     */
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);
    EXPECT_NE(textFieldOverlayModifier, nullptr);
}

/**
 * @tc.name: TextFieldOverlayModifierTest002
 * @tc.desc: Test textfield to draw caret.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create scrollEdgeEffect
     * tc.expected: step2. Check if scrollEdgeEffect is created.
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step3. create textFieldOverlayModifier
     * tc.expected: step3. Check if textFieldOverlayModifier is created.
     */
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);
    EXPECT_NE(textFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step4. set cursorOffset
     * tc.expected: step4. Check if textFieldOverlayModifier is created.
     */
    OffsetF caretOffset(DEFAULT_RECT_X, DEFAULT_RECT_Y);
    pattern_->SetMovingCaretOffset(caretOffset);
    textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);
    EXPECT_NE(textFieldOverlayModifier, nullptr);
    
    /**
     * @tc.steps: step5. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step6. Do onDraw(context)
     */
    textFieldOverlayModifier->onDraw(context);

    /**
     * @tc.steps: step7. get cursorOffset
     * tc.expected: step7. Check if cursorOffset is changed.
     */
    auto caretOffsetX = pattern_->GetCaretOffset().GetX();
    auto caretOffsetY = pattern_->GetCaretOffset().GetY();
    EXPECT_EQ(caretOffsetX, DEFAULT_RECT_X);
    EXPECT_EQ(caretOffsetY, DEFAULT_RECT_Y);
}

/**
 * @tc.name: TextFieldOverlayModifierTest003
 * @tc.desc: Test function GetFrameRectClip().
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create scrollEdgeEffect
     * tc.expected: step2. Check if scrollEdgeEffect is created.
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step3. create textFieldOverlayModifier
     * tc.expected: step3. Check if textFieldOverlayModifier is created.
     */
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);
    EXPECT_NE(textFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step4. call GetFrameRectClip() by textFieldOverlayModifier
     * tc.expected: step4. Check frameRect.
     */
    RSRect clipRect;
    std::vector<RSPoint> clipRadius;
    textFieldOverlayModifier->GetFrameRectClip(clipRect, clipRadius);
    EXPECT_NE(textFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step5. get frameRect value
     * tc.expected: step5. Check frameRect value.
     */
    auto frameRectX = clipRect.GetLeft();
    EXPECT_EQ(frameRectX, MIN_RECT_X);
    auto frameRectY = clipRect.GetTop();
    EXPECT_EQ(frameRectY, MIN_RECT_Y);
    auto frameRectWidth = clipRect.GetWidth();
    EXPECT_NE(frameRectWidth, MIN_RECT_WIDTH);
    auto frameRectHeight = clipRect.GetHeight();
    EXPECT_NE(frameRectHeight, MIN_RECT_HEIGHT);
}

/**
 * @tc.name: TextFieldOverlayModifierTest004
 * @tc.desc: Test show underline.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create scrollEdgeEffect
     * tc.expected: step2. Check if scrollEdgeEffect is created.
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step3. create textFieldOverlayModifier
     * tc.expected: step3. Check if textFieldOverlayModifier is created.
     */
    auto textFieldOverlayModifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern_, scrollEdgeEffect);
    EXPECT_NE(textFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step4. Get layoutProperty
     */
    auto host = pattern_->GetHost();
    EXPECT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step5. Create rsCanvas
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.steps: step6. call PaintUnderline()
     * tc.expected: step6. Check if underline is showed.
     */
    textFieldOverlayModifier->PaintUnderline(rsCanvas);
    auto ret = layoutProperty->GetShowUnderline();
    EXPECT_NE(ret, false);

    /**
     * @tc.steps: step7. Change show underline
     */
    layoutProperty->UpdateShowUnderline(true);

    /**
     * @tc.steps: step8. call PaintUnderline()
     * tc.expected: step8. Check if underline is showed.
     */
    textFieldOverlayModifier->PaintUnderline(rsCanvas);
    ret = layoutProperty->GetShowUnderline();
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step7. Change show counter
     */
    layoutProperty->UpdateShowCounter(true);

    /**
     * @tc.steps: step8. call PaintUnderline()
     * tc.expected: step8. Check if underline is showed.
     */
    textFieldOverlayModifier->PaintUnderline(rsCanvas);
    ret = layoutProperty->GetShowUnderline();
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step9.
     * Change show counter
     */

    layoutProperty->UpdateShowCounter(false);
}

static void SetupPreviewTextPattern(const RefPtr<TextFieldPattern>& pattern)
{
    pattern->hasPreviewText_ = true;
    pattern->previewTextStart_ = PREVIEW_TEXT_START_INDEX;
    pattern->previewTextEnd_ = PREVIEW_TEXT_END_INDEX;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->paragraph_ = paragraph;
    pattern->SetTextRect(
        RectF(PREVIEW_TEXT_RECT_X, PREVIEW_TEXT_RECT_Y, PREVIEW_TEXT_RECT_W, PREVIEW_TEXT_RECT_H));
    std::vector<RectF> rects {
        RectF(PREVIEW_DRAW_LEFT, PREVIEW_DRAW_TOP, PREVIEW_DRAW_WIDTH, PREVIEW_DRAW_HEIGHT)
    };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(SetArgReferee<RECTS_FOR_RANGE_OUT_ARG_INDEX>(rects));
}

static RefPtr<TextFieldOverlayModifier> CreatePreviewModifier(const RefPtr<TextFieldPattern>& pattern)
{
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto modifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollEdgeEffect);
    modifier->SetPreviewTextStyle(PreviewTextStyle::UNDERLINE);
    modifier->SetShowPreviewTextDecoration(true);
    modifier->SetPreviewTextRects(true);
    modifier->SetPreviewTextDecorationColor(Color::RED);
    OffsetF contentOffset(PREVIEW_CONTENT_OFFSET_X, PREVIEW_CONTENT_OFFSET_Y);
    SizeF contentSize(PREVIEW_CONTENT_WIDTH, PREVIEW_CONTENT_HEIGHT);
    modifier->SetContentOffset(contentOffset);
    modifier->SetContentSize(contentSize);
    return modifier;
}

static Testing::TestingRoundRect CaptureDrawnRoundRect(Testing::MockCanvas& rsCanvas)
{
    EXPECT_CALL(rsCanvas, Save()).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, ClipRect(_, _, _)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    Testing::TestingRoundRect capturedRoundRect;
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).WillOnce(SaveArg<0>(&capturedRoundRect));
    return capturedRoundRect;
}

/**
 * @tc.name: TextFieldOverlayModifierTest005
 * @tc.desc: Test PaintPreviewTextDecoration when isNotAllowScrollX is true
 *           (TextArea + horizontal scroll disabled). offsetX uses contentOffset.GetX().
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest005, TestSize.Level1)
{
    CreateTextField();
    GetFocus();
    layoutProperty_->UpdateMaxLines(2);
    EXPECT_TRUE(pattern_->IsTextArea());

    SetupPreviewTextPattern(pattern_);
    auto textFieldOverlayModifier = CreatePreviewModifier(pattern_);

    EXPECT_FALSE(pattern_->IsHorizontalScrollEnabled());
    EXPECT_TRUE(pattern_->IsTextArea() && !pattern_->IsHorizontalScrollEnabled());

    Testing::MockCanvas rsCanvas;
    auto capturedRoundRect = CaptureDrawnRoundRect(rsCanvas);
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier->PaintPreviewTextDecoration(context);

    auto capturedRect = capturedRoundRect.GetRect();
    EXPECT_FLOAT_EQ(capturedRect.GetLeft(), PREVIEW_DRAW_LEFT + PREVIEW_CONTENT_OFFSET_X);
    EXPECT_FLOAT_EQ(capturedRect.GetRight(), PREVIEW_DRAW_LEFT + PREVIEW_DRAW_WIDTH + PREVIEW_CONTENT_OFFSET_X);
}

/**
 * @tc.name: TextFieldOverlayModifierTest006
 * @tc.desc: Test PaintPreviewTextDecoration when isNotAllowScrollX is false
 *           (TextArea + horizontal scroll enabled). offsetX uses textRect.GetX().
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldOverlayModifierTest, TextFieldOverlayModifierTest006, TestSize.Level1)
{
    CreateTextField();
    GetFocus();
    layoutProperty_->UpdateMaxLines(2);
    pattern_->SetHorizontalScrolling(true);
    EXPECT_TRUE(pattern_->IsTextArea());
    EXPECT_TRUE(pattern_->IsHorizontalScrollEnabled());

    SetupPreviewTextPattern(pattern_);
    auto textFieldOverlayModifier = CreatePreviewModifier(pattern_);

    EXPECT_FALSE(pattern_->IsTextArea() && !pattern_->IsHorizontalScrollEnabled());

    Testing::MockCanvas rsCanvas;
    auto capturedRoundRect = CaptureDrawnRoundRect(rsCanvas);
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldOverlayModifier->PaintPreviewTextDecoration(context);

    auto capturedRect = capturedRoundRect.GetRect();
    EXPECT_FLOAT_EQ(capturedRect.GetLeft(), PREVIEW_DRAW_LEFT + PREVIEW_TEXT_RECT_X);
    EXPECT_FLOAT_EQ(capturedRect.GetRight(), PREVIEW_DRAW_LEFT + PREVIEW_DRAW_WIDTH + PREVIEW_TEXT_RECT_X);
}
} // namespace OHOS::Ace::NG