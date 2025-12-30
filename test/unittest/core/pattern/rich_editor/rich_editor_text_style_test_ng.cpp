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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::u16string URL_ADDRESS_1 = u"https://www.abc.com";
    const std::u16string URL_ADDRESS_2 = u"";
    const Color STROKE_COLOR_VALUE = Color::FromRGB(255, 100, 100);
    const Dimension STROKE_WIDTH_VALUE = Dimension(20.1, DimensionUnit::PX);
    const struct UpdateSpanStyle TYPING_STYLE = {
    .updateTextColor = Color::RED,
    .updateFontSize = CalcDimension(50.0),
    .updateStrokeWidth = CalcDimension(5.0),
    .updateStrokeColor = Color::GREEN,
};
}

class RichEditorTextStyleTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorTextStyleTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorTextStyleTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorTextStyleTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTextStyleTestNg, AddTextSpan001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get RichEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. set text style
     */
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetStrokeColor(STROKE_COLOR_VALUE);
    style.SetStrokeWidth(STROKE_WIDTH_VALUE);

    /**
     * @tc.steps: step2. test add span
     */
    TextSpanOptions options;
    options.offset = 1;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index1 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index2, 1);

    /**
     * @tc.steps: step2. check stroke style
     */
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_EQ(newSpan->GetStrokeColor(), STROKE_COLOR_VALUE);
    EXPECT_EQ(newSpan->GetStrokeWidth(), STROKE_WIDTH_VALUE);

    ClearSpan();
}

/**
 * @tc.name: AddTextSpan002
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTextStyleTestNg, AddTextSpan002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get RichEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. strokeColor does not follow fontColor
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.urlAddress = URL_ADDRESS_1;
    options.useThemeFontColor = true;
    options.style = TEXT_STYLE_1;
    auto index = richEditorPattern->AddTextSpan(options);
    EXPECT_EQ(index, 0);

    /**
     * @tc.steps: step3. strokeColor follow fontColor
     */
    options.strokeColorFollowFontColor = true;
    index = richEditorPattern->AddTextSpan(options);
    EXPECT_EQ(index, 1);

    /**
     * @tc.steps: step4. empty url address
     */
    options.urlAddress = URL_ADDRESS_2;
    index = richEditorPattern->AddTextSpan(options);
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: UpdateSpanStyle001
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTextStyleTestNg, UpdateSpanStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get RichEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. add span
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 2);

    /**
     * @tc.steps: step3. set textStyle
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetStrokeColor(STROKE_COLOR_VALUE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateStrokeColor = STROKE_COLOR_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;

    /**
     * @tc.steps: step3. update span
     */
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    auto newSpan = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan, nullptr);
    EXPECT_EQ(newSpan->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan->GetStrokeColor(), STROKE_COLOR_VALUE);

    /**
     * @tc.steps: step4. update stroke width
     */
    textStyle.SetStrokeWidth(STROKE_WIDTH_VALUE);
    updateSpanStyle.updateStrokeWidth = STROKE_WIDTH_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_EQ(newSpan->GetStrokeWidth(), STROKE_WIDTH_VALUE);

    textStyle.SetStrokeWidth(STROKE_WIDTH_VALUE);
    updateSpanStyle.updateTextColor = std::nullopt;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(0, 6, textStyle, imageStyle);
    EXPECT_EQ(newSpan->GetTextColor(), TEXT_COLOR_VALUE);

    ClearSpan();
}

/**
 * @tc.name: TypingStyle001
 * @tc.desc: test set and get TypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTextStyleTestNg, TypingStyle001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get RichEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. set typing style
     */
    richEditorController->SetTypingStyle(TYPING_STYLE, std::nullopt);

    /**
     * @tc.steps: step3. get typing style
     */
    auto typingStyleResult = richEditorController->GetTypingStyle();

    /**
     * @tc.steps: step4. check typing style result
     */
    EXPECT_TRUE(typingStyleResult.has_value());
    auto strokeWidth = typingStyleResult->updateStrokeWidth;
    EXPECT_TRUE(strokeWidth.has_value());
    EXPECT_EQ(strokeWidth.value(), CalcDimension(5.0));
    auto strokeColor = typingStyleResult->updateStrokeColor;
    EXPECT_TRUE(strokeColor.has_value());
    EXPECT_EQ(strokeColor.value(), Color::GREEN);

    richEditorPattern->SetTypingStyle(std::nullopt, std::nullopt);
}

/**
 * @tc.name: CreateTextSpanNode001
 * @tc.desc: test CreateTextSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTextStyleTestNg, CreateTextSpanNode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get RichEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto typingStyle = richEditorPattern->typingStyle_;
    auto typingTextStyle = richEditorPattern->typingTextStyle_;

    RefPtr<SpanNode> spanNode;
    TextInsertValueInfo info;
    std::u16string insertValue;
    UpdateSpanStyle updateSpanStyle;
    TextStyle textStyle;

    /**
     * @tc.steps: step2. test CreateTextSpanNode
     */
    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->typingTextStyle_ = textStyle;
    updateSpanStyle.useThemeFontColor = false;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    updateSpanStyle.updateTextColor = Color::RED,
    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_FALSE(richEditorPattern->typingStyle_->updateStrokeColor.has_value());

    updateSpanStyle.strokeColorFollowFontColor = true;
    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_TRUE(richEditorPattern->typingStyle_->updateStrokeColor.has_value());

    updateSpanStyle.updateTextColor = std::nullopt;
    updateSpanStyle.updateStrokeColor = std::nullopt;
    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue);
    EXPECT_FALSE(richEditorPattern->typingStyle_->updateStrokeColor.has_value());

    /**
     * @tc.steps: step2. reset typingStyle and typingTextStyle
     */
    richEditorPattern->typingStyle_ = typingStyle;
    richEditorPattern->typingTextStyle_ = typingTextStyle;
}
}