/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include <cstdint>
#include <cstring>
#include <iostream>
#include "securec.h"

#include "gtest/gtest.h"
#define private public
#define protected public
#include "event_converter.h"
#include "gesture_impl.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_styled_string_descriptor.h"
#include "node_extened.h"
#include "node_model.h"
#include "span_style_native_impl.h"
#include "text_native_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/node/event_converter.h"

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class NativeStyledStringTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: CreateTextStyle001
 * @tc.desc: Test the fontSize.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set fontSize
     */
    auto errorCode = OH_ArkUI_TextStyle_SetFontSize(textStyle, 32.0f);
    EXPECT_EQ(textStyle->fontSize, 32.0f);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get fontSize
     */
    float fontSize = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontSize(textStyle, &fontSize);
    EXPECT_EQ(fontSize, 32.0f);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    textStyle->fontSize = 10.0f;
    errorCode = OH_ArkUI_TextStyle_GetFontSize(textStyle, &fontSize);
    EXPECT_EQ(fontSize, 10.0f);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle002
 * @tc.desc: Test the fontColor.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set fontColor
     */
    auto errorCode = OH_ArkUI_TextStyle_SetFontColor(textStyle, 0xFFFF0000);
    EXPECT_EQ(textStyle->fontColor, 0xFFFF0000);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step2. test get fontColor
     */
    uint32_t fontColor = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontColor(textStyle, &fontColor);
    EXPECT_EQ(fontColor, 0xFFFF0000);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    textStyle->fontColor = 0xFFFF0001;
    errorCode = OH_ArkUI_TextStyle_GetFontColor(textStyle, &fontColor);
    EXPECT_EQ(fontColor, 0xFFFF0001);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle003
 * @tc.desc: Test the fontfaimly.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set fontfaimly
     */
    auto errorCode = OH_ArkUI_TextStyle_SetFontFamily(textStyle, "sans");
    EXPECT_EQ(textStyle->fontFamily, "sans");
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step2. test get fontfaimly
     */
    char *buffer = new char[6];
    int32_t writeLength = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontFamily(textStyle, buffer, 6, &writeLength);
    EXPECT_EQ(writeLength, 4);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    textStyle->fontFamily = "sans1";
    errorCode = OH_ArkUI_TextStyle_GetFontFamily(textStyle, buffer, 6, &writeLength);
    EXPECT_EQ(writeLength, 5);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle004
 * @tc.desc: Test the font weight.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set font weight
     */
    uint32_t fontWeight = 700;
    auto errorCode = OH_ArkUI_TextStyle_SetFontWeight(textStyle, fontWeight);
    EXPECT_EQ(textStyle->fontWeight, fontWeight);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get font weight
     */
    uint32_t getFontWeight = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontWeight(textStyle, &getFontWeight);
    EXPECT_EQ(getFontWeight, fontWeight);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle005
 * @tc.desc: Test the font style.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set font style
     */
    ArkUI_FontStyle fontStyle = ArkUI_FontStyle::ARKUI_FONT_STYLE_ITALIC;
    auto errorCode = OH_ArkUI_TextStyle_SetFontStyle(textStyle, fontStyle);
    EXPECT_EQ(textStyle->fontStyle, fontStyle);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get font style
     */
    ArkUI_FontStyle getFontStyle = ArkUI_FontStyle::ARKUI_FONT_STYLE_NORMAL;
    errorCode = OH_ArkUI_TextStyle_GetFontStyle(textStyle, &getFontStyle);
    EXPECT_EQ(getFontStyle, fontStyle);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle006
 * @tc.desc: Test the stroke width.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set stroke width
     */
    float strokeWidth = 2.5f;
    auto errorCode = OH_ArkUI_TextStyle_SetStrokeWidth(textStyle, strokeWidth);
    EXPECT_EQ(textStyle->strokeWidth, strokeWidth);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get stroke width
     */
    float getStrokeWidth = 0.0f;
    errorCode = OH_ArkUI_TextStyle_GetStrokeWidth(textStyle, &getStrokeWidth);
    EXPECT_EQ(getStrokeWidth, strokeWidth);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle007
 * @tc.desc: Test the stroke color.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set stroke color
     */
    uint32_t strokeColor = 0xFF0000FF;
    auto errorCode = OH_ArkUI_TextStyle_SetStrokeColor(textStyle, strokeColor);
    EXPECT_EQ(textStyle->strokeColor, strokeColor);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get stroke color
     */
    uint32_t getStrokeColor = 0x00000000;
    errorCode = OH_ArkUI_TextStyle_GetStrokeColor(textStyle, &getStrokeColor);
    EXPECT_EQ(getStrokeColor, strokeColor);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateTextStyle008
 * @tc.desc: Test the superscript style.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text style
     */
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();

    /**
     * @tc.steps: step2. test set superscript
     */
    OH_ArkUI_SuperscriptStyle superscript = OH_ArkUI_SuperscriptStyle::OH_ARKUI_SUPERSCRIPTSTYLE_SUPERSCRIPT;
    auto errorCode = OH_ArkUI_TextStyle_SetSuperscript(textStyle, superscript);
    EXPECT_EQ(textStyle->superscript, superscript);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get superscript
     */
    OH_ArkUI_SuperscriptStyle getSuperscript = OH_ArkUI_SuperscriptStyle::OH_ARKUI_SUPERSCRIPTSTYLE_NORMAL;
    errorCode = OH_ArkUI_TextStyle_GetSuperscript(textStyle, &getSuperscript);
    EXPECT_EQ(getSuperscript, superscript);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_TextStyle_Destroy(textStyle);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo001
 * @tc.desc: Test the X coordinate.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set X
     */
    float x = 10.5f;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetX(drawInfo, x);
    EXPECT_EQ(drawInfo->x, x);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get X
     */
    float getX = 0.0f;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetX(drawInfo, &getX);
    EXPECT_EQ(getX, x);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo002
 * @tc.desc: Test the Top coordinate.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set Top
     */
    float top = 20.5f;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetTop(drawInfo, top);
    EXPECT_EQ(drawInfo->top, top);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get Top
     */
    float getTop = 0.0f;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetTop(drawInfo, &getTop);
    EXPECT_EQ(getTop, top);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo003
 * @tc.desc: Test the Bottom coordinate.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set Bottom
     */
    float bottom = 30.5f;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetBottom(drawInfo, bottom);
    EXPECT_EQ(drawInfo->bottom, bottom);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get Bottom
     */
    float getBottom = 0.0f;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetBottom(drawInfo, &getBottom);
    EXPECT_EQ(getBottom, bottom);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo004
 * @tc.desc: Test the Baseline coordinate.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set Baseline
     */
    float baseline = 40.5f;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetBaseline(drawInfo, baseline);
    EXPECT_EQ(drawInfo->baseline, baseline);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get Baseline
     */
    float getBaseline = 0.0f;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetBaseline(drawInfo, &getBaseline);
    EXPECT_EQ(getBaseline, baseline);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo005
 * @tc.desc: Test the Text Direction.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set Text Direction
     */
    ArkUI_TextDirection direction = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_RTL;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetTextDirection(drawInfo, direction);
    EXPECT_EQ(drawInfo->direction, direction);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get Text Direction
     */
    ArkUI_TextDirection getDirection = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_LTR;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetTextDirection(drawInfo, &getDirection);
    EXPECT_EQ(getDirection, direction);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo006
 * @tc.desc: Test the Start position.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set Start
     */
    uint32_t start = 100;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetStart(drawInfo, start);
    EXPECT_EQ(drawInfo->start, start);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get Start
     */
    uint32_t getStart = 0;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetStart(drawInfo, &getStart);
    EXPECT_EQ(getStart, start);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo007
 * @tc.desc: Test the End position.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set End
     */
    uint32_t end = 200;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetEnd(drawInfo, end);
    EXPECT_EQ(drawInfo->end, end);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get End
     */
    uint32_t getEnd = 0;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetEnd(drawInfo, &getEnd);
    EXPECT_EQ(getEnd, end);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}

/**
 * @tc.name: CreateLeadingMarginSpanDrawInfo008
 * @tc.desc: Test the First flag.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateLeadingMarginSpanDrawInfo008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create draw info
     */
    OH_ArkUI_LeadingMarginSpanDrawInfo *drawInfo = OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

    /**
     * @tc.steps: step2. test set First
     */
    bool first = true;
    auto errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_SetFirst(drawInfo, first);
    EXPECT_EQ(drawInfo->first, first);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get First
     */
    bool getFirst = false;
    errorCode = OH_ArkUI_LeadingMarginSpanDrawInfo_GetFirst(drawInfo, &getFirst);
    EXPECT_EQ(getFirst, first);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(drawInfo);
}


/**
 * @tc.name: CreateParagraphStyle001
 * @tc.desc: Test the text alignment.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set text alignment
     */
    ArkUI_TextAlignment align = ArkUI_TextAlignment::ARKUI_TEXT_ALIGNMENT_CENTER;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetTextAlign(paragraphStyle, align);
    EXPECT_EQ(paragraphStyle->textAlign, align);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get text alignment
     */
    ArkUI_TextAlignment getAlign = ArkUI_TextAlignment::ARKUI_TEXT_ALIGNMENT_START;
    errorCode = OH_ArkUI_ParagraphStyle_GetTextAlign(paragraphStyle, &getAlign);
    EXPECT_EQ(getAlign, align);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle002
 * @tc.desc: Test the text indent.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set text indent
     */
    float textIndent = 20.5f;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetTextIndent(paragraphStyle, textIndent);
    EXPECT_EQ(paragraphStyle->textIndent, textIndent);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get text indent
     */
    float getTextIndent = 0.0f;
    errorCode = OH_ArkUI_ParagraphStyle_GetTextIndent(paragraphStyle, &getTextIndent);
    EXPECT_EQ(getTextIndent, textIndent);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle003
 * @tc.desc: Test the maximum lines.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set max lines
     */
    int32_t maxLines = 5;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetMaxLines(paragraphStyle, maxLines);
    EXPECT_EQ(paragraphStyle->maxLines.value_or(0), maxLines);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get max lines
     */
    int32_t getMaxLines = 0;
    errorCode = OH_ArkUI_ParagraphStyle_GetMaxLines(paragraphStyle, &getMaxLines);
    EXPECT_EQ(getMaxLines, maxLines);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle004
 * @tc.desc: Test the text overflow.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set text overflow
     */
    ArkUI_TextOverflow overflow = ArkUI_TextOverflow::ARKUI_TEXT_OVERFLOW_ELLIPSIS;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetOverflow(paragraphStyle, overflow);
    EXPECT_EQ(paragraphStyle->overflow, overflow);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get text overflow
     */
    ArkUI_TextOverflow getOverflow = ArkUI_TextOverflow::ARKUI_TEXT_OVERFLOW_CLIP;
    errorCode = OH_ArkUI_ParagraphStyle_GetOverflow(paragraphStyle, &getOverflow);
    EXPECT_EQ(getOverflow, overflow);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle005
 * @tc.desc: Test the word break.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set word break
     */
    ArkUI_WordBreak wordBreak = ArkUI_WordBreak::ARKUI_WORD_BREAK_BREAK_WORD;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetWordBreak(paragraphStyle, wordBreak);
    EXPECT_EQ(paragraphStyle->wordBreak, wordBreak);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get word break
     */
    ArkUI_WordBreak getWordBreak = ArkUI_WordBreak::ARKUI_WORD_BREAK_NORMAL;
    errorCode = OH_ArkUI_ParagraphStyle_GetWordBreak(paragraphStyle, &getWordBreak);
    EXPECT_EQ(getWordBreak, wordBreak);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle006
 * @tc.desc: Test the leading margin width.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set leading margin width
     */
    uint32_t width = 100;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetLeadingMarginWidth(paragraphStyle, width);
    EXPECT_EQ(paragraphStyle->leadingMarginWidth, width);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get leading margin width
     */
    uint32_t getWidth = 0;
    errorCode = OH_ArkUI_ParagraphStyle_GetLeadingMarginWidth(paragraphStyle, &getWidth);
    EXPECT_EQ(getWidth, width);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateTextController001
 * @tc.desc: Test text controller create.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextController001, TestSize.Level1)
{
    OH_ArkUI_TextController *controller = nullptr;
    controller = OH_ArkUI_TextController_Create();
    EXPECT_NE(controller, nullptr);
    EXPECT_EQ(controller->node, nullptr);
}

/**
 * @tc.name: CreateParagraphStyle007
 * @tc.desc: Test the leading margin height.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set leading margin height
     */
    uint32_t height = 200;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetLeadingMarginHeight(paragraphStyle, height);
    EXPECT_EQ(paragraphStyle->leadingMarginHeight, height);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get leading margin height
     */
    uint32_t getHeight = 0;
    errorCode = OH_ArkUI_ParagraphStyle_GetLeadingMarginHeight(paragraphStyle, &getHeight);
    EXPECT_EQ(getHeight, height);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle008
 * @tc.desc: Test the paragraph spacing.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set paragraph spacing
     */
    uint32_t paragraphSpacing = 30;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetParagraphSpacing(paragraphStyle, paragraphSpacing);
    EXPECT_EQ(paragraphStyle->paragraphSpacing, paragraphSpacing);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get paragraph spacing
     */
    uint32_t getParagraphSpacing = 0;
    errorCode = OH_ArkUI_ParagraphStyle_GetParagraphSpacing(paragraphStyle, &getParagraphSpacing);
    EXPECT_EQ(getParagraphSpacing, paragraphSpacing);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle009
 * @tc.desc: Test the text vertical alignment.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set text vertical alignment
     */
    ArkUI_TextVerticalAlignment verticalAlignment = ArkUI_TextVerticalAlignment::ARKUI_TEXT_VERTICAL_ALIGNMENT_TOP;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetTextVerticalAlign(paragraphStyle, verticalAlignment);
    EXPECT_EQ(paragraphStyle->textVerticalAlignment, verticalAlignment);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get text vertical alignment
     */
    ArkUI_TextVerticalAlignment getVerticalAlignment =
        ArkUI_TextVerticalAlignment::ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE;
    errorCode = OH_ArkUI_ParagraphStyle_GetTextVerticalAlign(paragraphStyle, &getVerticalAlignment);
    EXPECT_EQ(getVerticalAlignment, verticalAlignment);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: CreateParagraphStyle010
 * @tc.desc: Test the text direction.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateParagraphStyle010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paragraph style
     */
    OH_ArkUI_ParagraphStyle *paragraphStyle = OH_ArkUI_ParagraphStyle_Create();

    /**
     * @tc.steps: step2. test set text direction
     */
    ArkUI_TextDirection textDirection = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_RTL;
    auto errorCode = OH_ArkUI_ParagraphStyle_SetTextDirection(paragraphStyle, textDirection);
    EXPECT_EQ(paragraphStyle->textDirection, textDirection);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. test get text direction
     */
    ArkUI_TextDirection getTextDirection = ArkUI_TextDirection::ARKUI_TEXT_DIRECTION_LTR;
    errorCode = OH_ArkUI_ParagraphStyle_GetTextDirection(paragraphStyle, &getTextDirection);
    EXPECT_EQ(getTextDirection, textDirection);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);

    delete paragraphStyle;
    paragraphStyle = nullptr;
}

/**
 * @tc.name: TextControllerSetStyledString001
 * @tc.desc: Test the function of text controller about SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, TextControllerSetStyledString001, TestSize.Level1)
{
    OH_ArkUI_TextController *controller = nullptr;
    controller = OH_ArkUI_TextController_Create();
    auto styledString = OH_ArkUI_StyledString_Descriptor_Create();
    auto code = OH_ArkUI_TextController_SetStyledString(controller, styledString);
    EXPECT_EQ(code, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DestroyTextController001
 * @tc.desc: Test text controller destroy.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, DestroyTextController001, TestSize.Level1)
{
    OH_ArkUI_TextController *controller = nullptr;
    controller = OH_ArkUI_TextController_Create();
    EXPECT_NE(controller, nullptr);
    OH_ArkUI_TextController_Destroy(controller);
}
} // namespace OHOS::Ace
